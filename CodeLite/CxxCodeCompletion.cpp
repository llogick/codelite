#include "CxxCodeCompletion.hpp"

#include "CompletionHelper.hpp"
#include "CxxExpression.hpp"
#include "CxxScannerTokens.h"
#include "CxxVariableScanner.h"
#include "ctags_manager.h"
#include "file_logger.h"
#include "fileextmanager.h"
#include "fileutils.h"
#include "function.h"
#include "language.h"

#include <algorithm>
#include <deque>

namespace
{
TagEntryPtr create_global_scope_tag()
{
    TagEntryPtr global_scope(new TagEntry());
    global_scope->SetName("<global>");
    global_scope->SetPath("<global>");
    return global_scope;
}

wxArrayString to_wx_array_string(const vector<wxString>& v)
{
    wxArrayString a;
    a.reserve(v.size());
    for(const wxString& s : v) {
        a.Add(s);
    }
    return a;
}

} // namespace

#define RECURSE_GUARD_RETURN_NULLPTR() \
    m_recurse_protector++;             \
    if(m_recurse_protector > 150) {    \
        return nullptr;                \
    }

#define RECURSE_GUARD_RETURN()      \
    m_recurse_protector++;          \
    if(m_recurse_protector > 150) { \
        return;                     \
    }

CxxCodeCompletion::CxxCodeCompletion(ITagsStoragePtr lookup)
{
    m_lookup.reset(new LookupTable(lookup));
    m_template_manager.reset(new TemplateManager(this));
}

CxxCodeCompletion::CxxCodeCompletion(ITagsStoragePtr lookup, const unordered_map<wxString, TagEntryPtr>& unit_tests_db)
{
    m_lookup.reset(new LookupTable(lookup, unit_tests_db));
    m_template_manager.reset(new TemplateManager(this));
}

CxxCodeCompletion::~CxxCodeCompletion() {}

void CxxCodeCompletion::determine_current_scope()
{
    if(m_current_function_tag || m_filename.empty() || m_line_number == wxNOT_FOUND) {
        return;
    }

    if(!m_lookup) {
        return;
    }

    m_current_function_tag = m_lookup->GetScope(m_filename, m_line_number);
    if(m_current_function_tag && m_current_function_tag->IsMethod()) {
        vector<TagEntryPtr> tmp_tags;
        m_lookup->GetTagsByPath(m_current_function_tag->GetScope(), tmp_tags, 1);
        if(tmp_tags.size() == 1) {
            m_current_container_tag = move(tmp_tags[0]);
        }
    }
}

TagEntryPtr CxxCodeCompletion::code_complete(const wxString& expression, const vector<wxString>& visible_scopes,
                                             CxxRemainder* remainder)
{
    // build expression from the expression
    m_recurse_protector = 0;
    m_template_manager.reset(new TemplateManager(this));

    vector<wxString> scopes = { visible_scopes.begin(), visible_scopes.end() };
    vector<CxxExpression> expr_arr = CxxExpression::from_expression(expression, remainder);
    auto where =
        find_if(visible_scopes.begin(), visible_scopes.end(), [](const wxString& scope) { return scope.empty(); });

    if(where == visible_scopes.end()) {
        // add the global scope
        scopes.push_back(wxEmptyString);
    }

    // Check the current scope
    if(m_current_container_tag) {
        prepend_scope(scopes, m_current_container_tag->GetPath());
    }

    clDEBUG() << "code_complete() called with scopes:" << scopes << endl;

    // handle global scope
    if(expr_arr.empty()) {
        // user types Ctrl+SPACE
        return nullptr;
    } else if(expr_arr.size() == 1 && expr_arr[0].type_name().empty() && expr_arr[0].operand_string() == "::") {
        // return a dummy entry representing the global scope
        return create_global_scope_tag();
    } else if(expr_arr.size() >= 2 && expr_arr[0].type_name().empty() && expr_arr[0].operand_string() == "::") {
        // explicity requesting for the global namespace
        // clear the `scopes` and use only the global namespace (empty string)
        scopes.clear();
        scopes.push_back(wxEmptyString);
        // in addition, we can remove the first expression from the array
        expr_arr.erase(expr_arr.begin());
    }
    m_first_time = true;
    return resolve_compound_expression(expr_arr, scopes, {});
}

TagEntryPtr CxxCodeCompletion::resolve_compound_expression(vector<CxxExpression>& expression,
                                                           const vector<wxString>& visible_scopes,
                                                           const CxxExpression& orig_expression)
{
    RECURSE_GUARD_RETURN_NULLPTR();

    // resolve each expression
    if(expression.empty()) {
        return nullptr;
    }

    // copy the subscript operator to the last expression
    if(!expression.empty() && orig_expression.check_subscript_operator()) {
        expression.back().set_subscript_params(orig_expression.subscript_params());
    }

    TagEntryPtr resolved;
    for(CxxExpression& curexpr : expression) {
        resolved = resolve_expression(curexpr, resolved, visible_scopes);
        CHECK_PTR_RET_NULL(resolved);
        // once we resolved something we make it with this flag
        // this way we avoid checking for locals/global scope etc
        // since we already have some context
        m_first_time = false;
    }
    return resolved;
}

size_t CxxCodeCompletion::parse_locals(const wxString& text, unordered_map<wxString, __local>* locals) const
{
    shrink_scope(text, locals, nullptr);
    return locals->size();
}

wxString CxxCodeCompletion::shrink_scope(const wxString& text, unordered_map<wxString, __local>* locals,
                                         unordered_map<wxString, TagEntryPtr>* functions) const
{
    CxxVariableScanner scanner(text, eCxxStandard::kCxx11, get_tokens_map(), false);
    const wxString& trimmed_text = scanner.GetOptimizeBuffer();

    CxxVariable::Vec_t variables = scanner.GetVariables(false);
    locals->reserve(variables.size());

    // we also include the anonymous entries for this scope
    wxArrayString kinds;
    kinds.Add("class");
    kinds.Add("struct");
    kinds.Add("namespace");
    kinds.Add("member");
    kinds.Add("function");
    kinds.Add("variable");
    kinds.Add("enum");
    kinds.Add("macro");
    vector<TagEntryPtr> anonymous_tags;
    get_anonymous_tags(wxEmptyString, kinds, anonymous_tags);

    // create a local variable from the anonymous tags
    for(auto tag : anonymous_tags) {
        if(tag->GetKind() == "variable") {
            CxxVariableScanner scanner(normalize_pattern(tag), eCxxStandard::kCxx11, m_macros_table_map, false);
            auto _variables = scanner.GetVariables(false);
            variables.insert(variables.end(), _variables.begin(), _variables.end());
        } else if(tag->IsMethod() && functions) {
            functions->insert({ tag->GetName(), tag });
        }
    }

    for(auto var : variables) {
        __local local;
        wxString assignement_expr_raw = var->GetDefaultValue();
        // strip it from any keywords etc and only keep interesting parts

        local.set_assignment_raw(assignement_expr_raw);
        local.set_assignment(assignement_expr_raw);
        local.set_type_name(var->GetTypeAsString());
        local.set_is_auto(var->IsAuto());
        local.set_name(var->GetName());
        local.set_pattern(var->ToString(CxxVariable::kToString_Name | CxxVariable::kToString_DefaultValue));
        locals->insert({ var->GetName(), local });
    }
    return trimmed_text;
}

TagEntryPtr CxxCodeCompletion::lookup_operator_arrow(TagEntryPtr parent, const vector<wxString>& visible_scopes)
{
    return lookup_child_symbol(parent, "operator->", visible_scopes, { "function", "prototype" });
}

TagEntryPtr CxxCodeCompletion::lookup_subscript_operator(TagEntryPtr parent, const vector<wxString>& visible_scopes)
{
    CHECK_PTR_RET_NULL(m_lookup);
    vector<TagEntryPtr> scopes = get_scopes(parent, visible_scopes);
    for(auto scope : scopes) {
        vector<TagEntryPtr> tags;
        m_lookup->GetSubscriptOperator(scope->GetPath(), tags);
        if(!tags.empty()) {
            return tags[0];
        }
    }
    return nullptr;
}

TagEntryPtr CxxCodeCompletion::lookup_child_symbol(TagEntryPtr parent, const wxString& child_symbol,
                                                   const vector<wxString>& visible_scopes,
                                                   const vector<wxString>& kinds)
{
    CHECK_PTR_RET_NULL(m_lookup);
    auto resolved = lookup_symbol_by_kind(child_symbol, visible_scopes, kinds);
    if(resolved) {
        return resolved;
    }

    // try with the parent
    CHECK_PTR_RET_NULL(parent);

    // to avoid spaces and other stuff that depends on the user typing
    // we tokenize the symbol name
    vector<wxString> requested_symbol_tokens;
    {
        CxxLexerToken tok;
        CxxTokenizer tokenizer;
        tokenizer.Reset(child_symbol);
        while(tokenizer.NextToken(tok)) {
            requested_symbol_tokens.push_back(tok.GetWXString());
        }
    }

    auto compare_tokens_func = [&requested_symbol_tokens](const wxString& symbol_name) -> bool {
        CxxLexerToken tok;
        CxxTokenizer tokenizer;
        tokenizer.Reset(symbol_name);
        for(const wxString& token : requested_symbol_tokens) {
            if(!tokenizer.NextToken(tok)) {
                return false;
            }

            if(tok.GetWXString() != token)
                return false;
        }

        // if we can read more tokens from the tokenizer, it means that
        // the comparison is not complete, it "contains" the requested name
        if(tokenizer.NextToken(tok)) {
            return false;
        }
        return true;
    };

    deque<TagEntryPtr> q;
    q.push_front(parent);
    wxStringSet_t visited;
    while(!q.empty()) {
        auto t = q.front();
        q.pop_front();

        // avoid visiting the same tag twice
        if(!visited.insert(t->GetPath()).second)
            continue;

        vector<TagEntryPtr> tags;
        m_lookup->GetTagsByScope(t->GetPath(), tags);
        for(TagEntryPtr child : tags) {
            if(compare_tokens_func(child->GetName())) {
                return child;
            }
        }

        // if we got here, no match
        wxArrayString inherits = t->GetInheritsAsArrayNoTemplates();
        for(const wxString& inherit : inherits) {
            auto match = lookup_symbol_by_kind(inherit, visible_scopes, { "class", "struct" });
            if(match) {
                q.push_back(match);
            }
        }
    }
    return nullptr;
}

TagEntryPtr CxxCodeCompletion::lookup_symbol_by_kind(const wxString& name, const vector<wxString>& visible_scopes,
                                                     const vector<wxString>& kinds)
{
    vector<TagEntryPtr> tags;
    vector<wxString> scopes_to_check = visible_scopes;
    if(scopes_to_check.empty()) {
        scopes_to_check.push_back(wxEmptyString);
    }

    for(const wxString& scope : scopes_to_check) {
        wxString path;
        if(!scope.empty()) {
            path << scope << "::";
        }
        path << name;
        m_lookup->GetTagsByPathAndKind(path, tags, kinds);
        if(tags.size() == 1) {
            // we got a match
            return tags[0];
        }
    }
    return tags.empty() ? nullptr : tags[0];
}

void CxxCodeCompletion::update_template_table(TagEntryPtr resolved, CxxExpression& curexpr,
                                              const vector<wxString>& visible_scopes, wxStringSet_t& visited)
{
    CHECK_PTR_RET(resolved);
    if(!visited.insert(resolved->GetPath()).second) {
        // already visited this node
        return;
    }

    // simple template instantiaion line
    if(curexpr.is_template()) {
        curexpr.parse_template_placeholders(resolved->GetTemplateDefinition());
        wxStringMap_t M = curexpr.get_template_placeholders_map();
        m_template_manager->add_placeholders(M, visible_scopes);
    }

    // Check if one of the parents is a template class
    vector<wxString> inhertiance_expressions = CxxExpression::split_subclass_expression(normalize_pattern(resolved));
    for(const wxString& inherit : inhertiance_expressions) {
        vector<CxxExpression> more_expressions = CxxExpression::from_expression(inherit + ".", nullptr);
        if(more_expressions.empty())
            continue;

        auto match = lookup_symbol_by_kind(more_expressions[0].type_name(), visible_scopes, { "class", "struct" });
        if(match) {
            update_template_table(match, more_expressions[0], visible_scopes, visited);
        }
    }
}

TagEntryPtr CxxCodeCompletion::lookup_symbol(CxxExpression& curexpr, const vector<wxString>& visible_scopes,
                                             TagEntryPtr parent)
{
    wxString name_to_find = curexpr.type_name();
    auto resolved_name = m_template_manager->resolve(name_to_find, visible_scopes);
    if(resolved_name != name_to_find) {
        name_to_find = resolved_name;
        auto expressions = CxxExpression::from_expression(name_to_find + curexpr.operand_string(), nullptr);
        return resolve_compound_expression(expressions, visible_scopes, curexpr);
    }

    // try classes first
    auto resolved = lookup_child_symbol(parent, name_to_find, visible_scopes,
                                        { "typedef", "class", "struct", "namespace", "enum", "union" });
    if(!resolved) {
        // try methods
        // `lookup_child_symbol` takes inheritance into consideration
        resolved = lookup_child_symbol(parent, name_to_find, visible_scopes,
                                       { "function", "prototype", "member", "enumerator" });
    }

    if(resolved) {
        // update the template table
        wxStringSet_t visited;
        update_template_table(resolved, curexpr, visible_scopes, visited);

        // Check for operator-> overloading
        if(curexpr.check_subscript_operator()) {
            // we check for subscript before ->
            TagEntryPtr subscript_tag = lookup_subscript_operator(resolved, visible_scopes);
            if(subscript_tag) {
                resolved = subscript_tag;
                curexpr.pop_subscript_operator();
            }
        }

        if(curexpr.operand_string() == "->") {
            // search for operator-> overloading
            TagEntryPtr arrow_tag = lookup_operator_arrow(resolved, visible_scopes);
            if(arrow_tag) {
                resolved = arrow_tag;
                // change the operand from -> to .
                // to avoid extra resolving in case we are resolving expression like this:
                // ```
                //  shared_ptr<shared_ptr<wxString>> p;
                //  p->
                // ```
                // without changing the operand, we will get completions for `wxString`
                curexpr.set_operand('.');
            }
        }
    }
    return resolved;
}

vector<wxString> CxxCodeCompletion::update_visible_scope(const vector<wxString>& curscopes, TagEntryPtr tag)
{
    vector<wxString> scopes;
    scopes.insert(scopes.end(), curscopes.begin(), curscopes.end());

    if(tag && (tag->IsClass() || tag->IsStruct() || tag->IsNamespace() || tag->GetKind() == "union")) {
        prepend_scope(scopes, tag->GetPath());
    } else if(tag && (tag->IsMethod() || tag->IsMember())) {
        prepend_scope(scopes, tag->GetScope());
    }
    return scopes;
}

TagEntryPtr CxxCodeCompletion::resolve_expression(CxxExpression& curexp, TagEntryPtr parent,
                                                  const vector<wxString>& visible_scopes)
{
    // test locals first, if its empty, its the first time we are entering here
    if(m_first_time && !parent) {
        if(curexp.is_this()) {
            // this can only work with ->
            if(curexp.operand_string() != "->") {
                return nullptr;
            }

            // replace "this" with the current scope name
            determine_current_scope();
            wxString current_scope_name = m_current_container_tag ? m_current_container_tag->GetPath() : wxString();
            wxString exprstr = current_scope_name + curexp.operand_string();
            vector<CxxExpression> expr_arr = CxxExpression::from_expression(exprstr, nullptr);
            return resolve_compound_expression(expr_arr, visible_scopes, curexp);

        } else if(curexp.operand_string() == "." || curexp.operand_string() == "->") {
            if(m_locals.count(curexp.type_name())) {
                // local or anonymous member
                wxString exprstr = m_locals.find(curexp.type_name())->second.type_name() + curexp.operand_string();
                vector<CxxExpression> expr_arr = CxxExpression::from_expression(exprstr, nullptr);
                return resolve_compound_expression(expr_arr, visible_scopes, curexp);

            } else if(m_local_functions.count(curexp.type_name())) {
                // anonymous / static function
                return on_method(curexp, m_local_functions.find(curexp.type_name())->second, visible_scopes);

            } else {
                determine_current_scope();

                // try to load the symbol this order:
                // current-scope::name (if we are in a scope)
                // other-scopes::name
                // global-scope::name
                vector<wxString> paths_to_try;
                vector<TagEntryPtr> parent_tags;
                wxStringSet_t visited;
                if(m_current_container_tag) {
                    // get list of scopes to try (including parents)
                    parent_tags = get_scopes(m_current_container_tag, visible_scopes);
                    paths_to_try.reserve(parent_tags.size());
                    for(auto parent : parent_tags) {
                        wxString fullpath = parent->GetPath() + "::" + curexp.type_name();
                        if(visited.insert(fullpath).second) {
                            paths_to_try.push_back(fullpath);
                        }
                    }
                }

                // add the other scopes
                for(auto scope : visible_scopes) {
                    // build the path
                    wxString path_to_try;
                    if(!scope.empty()) {
                        path_to_try << scope << "::";
                    }
                    path_to_try << curexp.type_name();
                    if(visited.insert(path_to_try).second) {
                        paths_to_try.push_back(path_to_try);
                    }
                }

                for(const auto& path_to_try : paths_to_try) {
                    // note that we pass here empty visible_scopes since we already prepended it earlier
                    auto scope_tag = lookup_symbol_by_kind(
                        path_to_try, {}, { "class", "struct", "union", "prototype", "function", "member" });
                    if(scope_tag) {
                        // we are inside a scope, use the scope as the parent
                        // and call resolve_expression() again
                        return resolve_expression(curexp, scope_tag, visible_scopes);
                    }
                }
            }
        }
    }

    // update the visible scopes
    vector<wxString> scopes = update_visible_scope(visible_scopes, parent);

    auto resolved = lookup_symbol(curexp, scopes, parent);
    CHECK_PTR_RET_NULL(resolved);

    if(resolved->IsContainer()) {
        // nothing more to be done here
        return resolved;
    }

    // continue only if one of 3: member, method or typedef
    if(!resolved->IsMethod() && !resolved->IsMember() && !resolved->IsTypedef()) {
        return nullptr;
    }

    // after we resolved the expression, update the scope
    scopes = update_visible_scope(scopes, resolved);

    if(resolved->IsMethod()) {
        return on_method(curexp, resolved, scopes);

    } else if(resolved->IsTypedef()) {
        return on_typedef(curexp, resolved, scopes);

    } else if(resolved->IsMember()) {
        return on_member(curexp, resolved, scopes);
    }

    return nullptr;
}

TagEntryPtr CxxCodeCompletion::on_typedef(CxxExpression& curexp, TagEntryPtr tag,
                                          const vector<wxString>& visible_scopes)
{
    // substitude the type with the typeref
    wxString new_expr;
    if(!resolve_user_type(tag->GetPath(), visible_scopes, &new_expr)) {
        new_expr = typedef_from_tag(tag);
    }
    new_expr += curexp.operand_string();
    vector<CxxExpression> expr_arr = CxxExpression::from_expression(new_expr, nullptr);
    return resolve_compound_expression(expr_arr, visible_scopes, curexp);
}

TagEntryPtr CxxCodeCompletion::on_member(CxxExpression& curexp, TagEntryPtr tag, const vector<wxString>& visible_scopes)
{
    // replace the member variable by its type
    unordered_map<wxString, __local> locals_variables;
    if((parse_locals(normalize_pattern(tag), &locals_variables) == 0) ||
       (locals_variables.count(tag->GetName()) == 0)) {
        return nullptr;
    }

    wxString new_expr = locals_variables[tag->GetName()].type_name() + curexp.operand_string();
    vector<CxxExpression> expr_arr = CxxExpression::from_expression(new_expr, nullptr);
    return resolve_compound_expression(expr_arr, visible_scopes, curexp);
}

TagEntryPtr CxxCodeCompletion::on_method(CxxExpression& curexp, TagEntryPtr tag, const vector<wxString>& visible_scopes)
{
    // parse the return value
    wxString new_expr = get_return_value(tag) + curexp.operand_string();
    vector<CxxExpression> expr_arr = CxxExpression::from_expression(new_expr, nullptr);
    return resolve_compound_expression(expr_arr, visible_scopes, curexp);
}

const wxStringMap_t& CxxCodeCompletion::get_tokens_map() const { return m_macros_table_map; }

wxString CxxCodeCompletion::get_return_value(TagEntryPtr tag) const
{
    return tag->GetTypename();
    // wxString pattern = normalize_pattern(tag);
    // wxString return_value = do_get_return_value(pattern, tag->GetName());
    // if(return_value.empty()) {
    //
    //     return_value = do_get_return_value(pattern, tag->GetName());
    // }
    // return return_value;
}

namespace
{
void remove_template_instantiation(vector<pair<int, wxString>>& tokens)
{
    bool is_template_inst = !tokens.empty() && tokens.back().first == '>';
    if(!is_template_inst)
        return;

    // remove the open angle bracket
    tokens.pop_back();

    int depth = 1;
    bool cont = true;
    while(cont && !tokens.empty()) {
        int type = tokens.back().first;
        switch(type) {
        case '<':
            depth--;
            if(depth == 0) {
                cont = false;
            }
            tokens.pop_back();
            break;
        case '>':
            depth++;
            tokens.pop_back();
            break;
        default:
            tokens.pop_back();
            break;
        }
    }
}
} // namespace
wxString CxxCodeCompletion::do_get_return_value(const wxString& pattern, const wxString& name) const
{
    // parse the function and extract the return type
    CxxTokenizer tokenizer;
    CxxLexerToken token;
    tokenizer.Reset(pattern);

    // strip template definition if any
    wxString definition;
    read_template_definition(tokenizer, &definition);

    // when to stop?
    // when we find our function name
    int depth = 0;
    bool cont = true;
    vector<pair<int, wxString>> tokens;
    const wxString& function_name = name;
    wxString peeked_token;
    while(cont && tokenizer.NextToken(token)) {
        wxString token_str = token.GetWXString();
        switch(token.GetType()) {
        case T_OPERATOR:
            // operator method, we can stop now
            cont = false;
            break;
        case T_IDENTIFIER:
            if(depth == 0) {
                if(token_str == function_name && tokenizer.PeekToken(peeked_token) == '(') {
                    // found "foo("
                    cont = false;
                    break;
                } else {
                    tokens.push_back({ token.GetType(), token_str });
                }
            } else {
                tokens.push_back({ token.GetType(), token_str });
            }
            break;
        case '<':
        case '[':
        case '{':
        case '(':
            depth++;
            tokens.push_back({ token.GetType(), token_str });
            break;
        case '>':
        case ']':
        case '}':
        case ')':
            depth--;
            tokens.push_back({ token.GetType(), token_str });
            break;
        default:
            tokens.push_back({ token.GetType(), token_str });
            break;
        }
    }

    if(tokens.empty())
        return "";

    // remove the scope tokens
    // assume the signature looks like this:
    //
    //  ```
    //  vector<string> foo::bar::baz::koo::kookoo::
    //  ```
    //
    // check if the last token is T_DOUBLE_COLONS ->
    // remove it and the next one after it
    // another case:
    //  ```
    //  template<typename T> T* CLASS<T>::FUNC
    //  ```
    while(!tokens.empty()) {
        if(tokens.back().first == T_DOUBLE_COLONS) {
            tokens.pop_back();
            // handle template instantiation e.g. `template<typename T> T* CLASS<T>::FUNC`
            remove_template_instantiation(tokens);
            if(!tokens.empty()) {
                tokens.pop_back();
            }
        } else {
            break;
        }
    }

    // conver the array into string
    wxString as_str;
    int last_type = 0;
    for(const auto& d : tokens) {
        CxxLexerToken t;
        t.SetType(d.first);
        if(t.is_keyword() || t.is_builtin_type()) {
            as_str << d.second << " ";
        } else if(d.first == T_IDENTIFIER && last_type == T_IDENTIFIER) {
            as_str << " " << d.second;
        } else {
            as_str << d.second;
        }

        last_type = d.first;
    }
    return as_str;
}

void CxxCodeCompletion::prepend_scope(vector<wxString>& scopes, const wxString& scope) const
{
    auto where = find_if(scopes.begin(), scopes.end(), [=](const wxString& s) { return s == scope; });

    if(where != scopes.end()) {
        scopes.erase(where);
    }

    scopes.insert(scopes.begin(), scope);
}

void CxxCodeCompletion::reset()
{
    m_locals.clear();
    m_optimized_scope.clear();
    m_template_manager->clear();
    m_recurse_protector = 0;
    m_current_function_tag.Reset(nullptr);
    m_current_container_tag.Reset(nullptr);
}

namespace
{
wxString read_n_lines_from_file(size_t from_line, size_t line_count, const wxString& filepath)
{
    wxString content;
    if(!FileUtils::ReadFileContent(filepath, content)) {
        return wxEmptyString;
    }
    wxArrayString lines = ::wxStringTokenize(content, "\n", wxTOKEN_RET_EMPTY_ALL);
    if(from_line >= lines.size()) {
        return wxEmptyString;
    }
    size_t first_line = from_line;
    size_t last_line = wxMin(from_line + line_count, lines.size() - 1);

    content.Clear();
    for(size_t i = first_line; i < last_line; ++i) {
        content << lines[i];
    }
    return content;
}
} // namespace

wxString CxxCodeCompletion::typedef_from_tag(TagEntryPtr tag) const
{
    wxString typedef_str;
    CxxTokenizer tkzr;
    CxxLexerToken tk;

    if(!tag->GetTypename().empty()) {
        typedef_str = tag->GetTypename();
        return typedef_str.Trim();
    }

    wxString pattern = normalize_pattern(tag);
    tkzr.Reset(pattern);

    vector<wxString> V;
    wxString last_identifier;
    // consume the first token which is one of T_USING | T_TYPEDEF
    tkzr.NextToken(tk);

    bool parse_succeeded = false;
    if(tk.GetType() == T_TEMPLATE) {
        // instead of reading the pattern, read 10 lines from the source code and use that instead
        // (ctags is not that good at collecting typedef properly)
        pattern = read_n_lines_from_file(tag->GetLine() - 1, 10, tag->GetFile());
        clDEBUG() << "read 10 lines from file:" << tag->GetLine() << endl;
        clDEBUG() << pattern << endl;
        // reset the tokenizer with the new buffer
        tkzr.Reset(pattern);
        tkzr.NextToken(tk);
    }

    if(tk.GetType() == T_USING) {
        // "using" syntax:
        // using element_type = _Tp;
        // read until the "=";

        // consume everything until we find the "="
        while(tkzr.NextToken(tk)) {
            if(tk.GetType() == '=')
                break;
        }

        // read until the ";"
        while(tkzr.NextToken(tk)) {
            if(tk.GetType() == ';') {
                parse_succeeded = true;
                break;
            }
            if(tk.is_keyword()) {
                // dont pick keywords
                continue;
            }
            if(tk.is_builtin_type()) {
                V.push_back((V.empty() ? "" : " ") + tk.GetWXString() + " ");
            } else {
                V.push_back(tk.GetWXString());
            }
        }

    } else if(tk.GetType() == T_TYPEDEF) {
        // standard "typedef" syntax:
        // typedef wxString MyString;
        while(tkzr.NextToken(tk)) {
            if(tk.is_keyword()) {
                continue;
            }
            if(tk.GetType() == ';') {
                // end of typedef
                if(!V.empty()) {
                    V.pop_back();
                }
                parse_succeeded = true;
                break;
            } else {
                if(tk.is_builtin_type()) {
                    V.push_back((V.empty() ? "" : " ") + tk.GetWXString() + " ");
                } else {
                    V.push_back(tk.GetWXString());
                }
            }
        }
    }

    if(!parse_succeeded) {
        return wxEmptyString;
    } else {
        for(const wxString& s : V) {
            typedef_str << s;
        }
    }
    return typedef_str.Trim();
}

vector<TagEntryPtr> CxxCodeCompletion::get_local_functions(const wxString& filter) const
{
    vector<TagEntryPtr> locals;
    locals.reserve(m_locals.size());
    for(const auto& vt : m_local_functions) {
        if(vt.second->GetName().StartsWith(filter)) {
            locals.push_back(vt.second);
        }
    }
    return locals;
}

vector<TagEntryPtr> CxxCodeCompletion::get_locals(const wxString& filter) const
{
    vector<TagEntryPtr> locals;
    locals.reserve(m_locals.size());

    wxString lowercase_filter = filter.Lower();
    for(const auto& vt : m_locals) {
        const auto& local = vt.second;
        TagEntryPtr tag(new TagEntry());
        tag->SetName(local.name());
        tag->SetKind("variable");
        tag->SetParent("<local>");
        tag->SetScope(local.type_name());
        tag->SetAccess("public");
        tag->SetPattern("/^ " + local.pattern() + " $/");

        if(!tag->GetName().Lower().StartsWith(lowercase_filter))
            continue;
        locals.push_back(tag);
    }
    return locals;
}

size_t CxxCodeCompletion::get_completions(TagEntryPtr parent, const wxString& operand_string, const wxString& filter,
                                          vector<TagEntryPtr>& candidates, const vector<wxString>& visible_scopes,
                                          size_t limit)
{
    if(!parent) {
        return 0;
    }

    vector<wxString> kinds = { "function", "prototype", "member", "enum",      "enumerator",
                               "class",    "struct",    "union",  "namespace", "typedef" };
    if(operand_string == "." || operand_string == "->") {
        kinds = { "prototype", "function", "member" };
    }
    // the global scope
    candidates = get_children_of_scope(parent, kinds, filter, visible_scopes);
    wxStringSet_t visited;

    vector<TagEntryPtr> unique_candidates;
    unique_candidates.reserve(candidates.size());
    CompletionHelper helper;
    for(TagEntryPtr tag : candidates) {
        // by default, the path is enough
        // however, for methods, we also include the method
        // signature
        wxString unique_path = tag->GetPath();
        if(tag->IsMethod()) {
            unique_path = helper.normalize_function(tag->GetName(), tag->GetSignature());
        }

        if(!visited.insert(unique_path).second) {
            // already seen this
            continue;
        }

        unique_candidates.emplace_back(tag);
    }

    // sort the matches
    auto sort_cb = [=](TagEntryPtr a, TagEntryPtr b) { return a->GetName().CmpNoCase(b->GetName()) < 0; };
    sort(unique_candidates.begin(), unique_candidates.end(), sort_cb);
    // truncate the list to match the limit
    if(unique_candidates.size() > limit) {
        unique_candidates.resize(limit);
    }
    candidates.swap(unique_candidates);

    // filter the results
    vector<TagEntryPtr> sorted_tags;
    sort_tags(candidates, sorted_tags, false, {});
    candidates.swap(sorted_tags);
    return candidates.size();
}

vector<TagEntryPtr> CxxCodeCompletion::get_scopes(TagEntryPtr parent, const vector<wxString>& visible_scopes)
{
    vector<TagEntryPtr> scopes;
    scopes.reserve(100);

    deque<TagEntryPtr> q;
    q.push_front(parent);
    wxStringSet_t visited;
    while(!q.empty()) {
        auto t = q.front();
        q.pop_front();

        // avoid visiting the same tag twice
        if(!visited.insert(t->GetPath()).second)
            continue;

        scopes.push_back(t);

        // if we got here, no match
        wxArrayString inherits = t->GetInheritsAsArrayNoTemplates();
        for(const wxString& inherit : inherits) {
            auto match = lookup_symbol_by_kind(inherit, visible_scopes, { "class", "struct" });
            if(match) {
                q.push_back(match);
            } else {
                // could not find a match, try the macros table
                if(m_macros_table_map.count(inherit)) {
                    match = lookup_symbol_by_kind(m_macros_table_map[inherit], visible_scopes, { "class", "struct" });
                    if(match) {
                        q.push_back(match);
                    }
                }
            }
        }
    }
    return scopes;
}

vector<TagEntryPtr> CxxCodeCompletion::get_children_of_scope(TagEntryPtr parent, const vector<wxString>& kinds,
                                                             const wxString& filter,
                                                             const vector<wxString>& visible_scopes)
{
    if(!m_lookup) {
        return {};
    }

    vector<TagEntryPtr> tags;
    wxArrayString wx_kinds;
    wx_kinds.reserve(kinds.size());
    for(const wxString& kind : kinds) {
        wx_kinds.Add(kind);
    }

    auto parents = get_scopes(parent, visible_scopes);
    for(auto tag : parents) {
        wxString scope = tag->GetPath();
        if(tag->IsMethod()) {
            scope = tag->GetScope();
        }
        vector<TagEntryPtr> parent_tags;
        m_lookup->GetTagsByScopeAndKind(scope, wx_kinds, filter, parent_tags, true);
        tags.reserve(tags.size() + parent_tags.size());
        tags.insert(tags.end(), parent_tags.begin(), parent_tags.end());
    }
    return tags;
}

void CxxCodeCompletion::set_text(const wxString& text, const wxString& filename, int current_line)
{
    m_locals.clear();
    m_local_functions.clear();
    m_filename = filename;
    m_line_number = current_line;
    m_current_container_tag = nullptr;
    m_current_function_tag = nullptr;

    m_optimized_scope.clear();
    m_optimized_scope = shrink_scope(text, &m_locals, &m_local_functions);
    determine_current_scope();
}

namespace
{

bool find_wild_match(const vector<pair<wxString, wxString>>& table, const wxString& find_what, wxString* match)
{
    for(const auto& p : table) {
        // we support wildcard matching
        if(::wxMatchWild(p.first, find_what)) {
            *match = p.second;
            return true;
        }
    }
    return false;
}

bool try_resovle_user_type_with_scopes(const vector<pair<wxString, wxString>>& table, const wxString& type,
                                       const vector<wxString>& visible_scopes, wxString* resolved)
{
    for(const wxString& scope : visible_scopes) {
        wxString user_type = scope;
        if(!user_type.empty()) {
            user_type << "::";
        }
        user_type << type;
        if(find_wild_match(table, type, resolved)) {
            return true;
        }
    }
    return false;
}
}; // namespace

bool CxxCodeCompletion::resolve_user_type(const wxString& type, const vector<wxString>& visible_scopes,
                                          wxString* resolved) const
{
    bool match_found = false;
    wxStringSet_t visited;
    *resolved = type;
    while(true) {
        if(!visited.insert(*resolved).second) {
            // already tried this type
            break;
        }

        if(!try_resovle_user_type_with_scopes(m_types_table, *resolved, visible_scopes, resolved)) {
            break;
        }
        match_found = true;
    }

    if(match_found) {
        return true;
    }
    return false;
}

void TemplateManager::clear() { m_table.clear(); }

void TemplateManager::add_placeholders(const wxStringMap_t& table, const vector<wxString>& visible_scopes)
{
    // try to resolve any of the template before we insert them
    // its important to do it now so we use the correct scope
    wxStringMap_t M;
    for(const auto& vt : table) {
        wxString name = vt.first;
        wxString value;

        auto resolved = m_completer->lookup_child_symbol(
            nullptr, vt.second, visible_scopes,
            { "class", "struct", "typedef", "union", "namespace", "enum", "enumerator" });
        if(resolved) {
            // use the path found in the db
            value = resolved->GetPath();
        } else {
            // lets try and avoid pushing values that are templates
            // consider
            // template <typename _Tp> class vector : protected _Vector_base<_Tp> {..}
            // Looking at the definitio of _Vector_base:
            // template <typename _Tp> class _Vector_base {...}
            // this will cause us to push {"_Tp", "_Tp"} (where _Tp is both the key and value)
            // if the resolve will fail, it will return vt.second unmodified
            value = this->resolve(vt.second, visible_scopes);
        }
        M.insert({ name, value });
    }
    m_table.insert(m_table.begin(), M);
}

#define STRIP_PLACEHOLDER(__ph)                        \
    stripped_placeholder.Replace("*", wxEmptyString);  \
    stripped_placeholder.Replace("->", wxEmptyString); \
    stripped_placeholder.Replace("&&", wxEmptyString);

namespace
{
bool try_resolve_placeholder(const wxStringMap_t& table, const wxString& name, wxString* resolved)
{
    // strip operands from `s`
    wxString stripped_placeholder = name;
    STRIP_PLACEHOLDER(stripped_placeholder);

    if(table.count(name)) {
        *resolved = table.find(name)->second;
        return true;
    }
    return false;
}
}; // namespace

wxString TemplateManager::resolve(const wxString& name, const vector<wxString>& visible_scopes) const
{
    wxStringSet_t visited;
    wxString resolved = name;
    for(const wxStringMap_t& table : m_table) {
        try_resolve_placeholder(table, resolved, &resolved);
    }
    return resolved;
}

void CxxCodeCompletion::set_macros_table(const vector<pair<wxString, wxString>>& t)
{
    m_macros_table = t;
    m_macros_table_map.reserve(m_macros_table.size());
    for(const auto& d : m_macros_table) {
        m_macros_table_map.insert(d);
    }
}

void CxxCodeCompletion::sort_tags(const vector<TagEntryPtr>& tags, vector<TagEntryPtr>& sorted_tags,
                                  bool include_ctor_dtor, const wxStringSet_t& visible_files)
{
    TagEntryPtrVector_t publicTags;
    TagEntryPtrVector_t protectedTags;
    TagEntryPtrVector_t privateTags;
    TagEntryPtrVector_t locals;
    TagEntryPtrVector_t members;

    bool skip_tor = !include_ctor_dtor;

    // first: remove duplicates
    unordered_set<int> visited_by_id;
    unordered_set<wxString> visited_by_name;

    for(size_t i = 0; i < tags.size(); ++i) {
        TagEntryPtr tag = tags[i];

        // only include matches from the provided list of files
        if(!visible_files.empty() && visible_files.count(tag->GetFile()) == 0)
            continue;

        if(skip_tor && (tag->IsConstructor() || tag->IsDestructor()))
            continue;

        bool is_local = tag->IsLocalVariable() || tag->GetScope() == "<local>" || tag->GetParent() == "<local>";
        // we filter local tags by name
        if(is_local && !visited_by_name.insert(tag->GetName()).second) {
            continue;
        }

        // other tags (loaded from the db) are filtered by their ID
        if(!is_local && !visited_by_id.insert(tag->GetId()).second) {
            continue;
        }

        // filter by type/access
        wxString access = tag->GetAccess();
        wxString kind = tag->GetKind();

        if(kind == "variable") {
            locals.push_back(tag);

        } else if(kind == "member") {
            members.push_back(tag);

        } else if(access == "private") {
            privateTags.push_back(tag);

        } else if(access == "protected") {
            protectedTags.push_back(tag);

        } else if(access == "public") {
            if(tag->GetName().StartsWith("_") || tag->GetName().Contains("operator")) {
                // methods starting with _ usually are meant to be private
                // and also, put the "operator" methdos at the bottom
                privateTags.push_back(tag);
            } else {
                publicTags.push_back(tag);
            }
        } else {
            // assume private
            privateTags.push_back(tag);
        }
    }

    auto sort_func = [=](TagEntryPtr a, TagEntryPtr b) { return a->GetName().CmpNoCase(b->GetName()) < 0; };

    sort(privateTags.begin(), privateTags.end(), sort_func);
    sort(publicTags.begin(), publicTags.end(), sort_func);
    sort(protectedTags.begin(), protectedTags.end(), sort_func);
    sort(members.begin(), members.end(), sort_func);
    sort(locals.begin(), locals.end(), sort_func);

    sorted_tags.clear();
    sorted_tags.insert(sorted_tags.end(), locals.begin(), locals.end());
    sorted_tags.insert(sorted_tags.end(), publicTags.begin(), publicTags.end());
    sorted_tags.insert(sorted_tags.end(), protectedTags.begin(), protectedTags.end());
    sorted_tags.insert(sorted_tags.end(), privateTags.begin(), privateTags.end());
    sorted_tags.insert(sorted_tags.end(), members.begin(), members.end());
}

size_t CxxCodeCompletion::get_file_completions(const wxString& user_typed, vector<TagEntryPtr>& files,
                                               const wxString& suffix)
{
    if(!m_lookup) {
        return 0;
    }
    wxArrayString files_arr;
    m_lookup->GetFilesForCC(user_typed, files_arr);

    files.reserve(files_arr.size());
    for(const wxString& file : files_arr) {
        // exclude source file
        if(FileExtManager::GetType(file) == FileExtManager::TypeSourceC ||
           FileExtManager::GetType(file) == FileExtManager::TypeSourceCpp) {
            continue;
        }
        TagEntryPtr tag(new TagEntry());

        wxString display_name = file + suffix;
        tag->SetKind("file");
        tag->SetName(display_name); // display name
        display_name = display_name.AfterLast('/');
        tag->SetPattern(display_name); // insert text
        tag->SetLine(-1);
        files.push_back(tag);
    }
    return files.size();
}

size_t CxxCodeCompletion::get_children_of_current_scope(const vector<wxString>& kinds, const wxString& filter,
                                                        const vector<wxString>& visible_scopes,
                                                        vector<TagEntryPtr>* current_scope_children,
                                                        vector<TagEntryPtr>* other_scopes_children,
                                                        vector<TagEntryPtr>* global_scope_children)
{
    determine_current_scope();
    if(m_current_container_tag) {
        *current_scope_children = get_children_of_scope(m_current_container_tag, kinds, filter, visible_scopes);
    }

    // collect "other scopes"
    wxArrayString wx_kinds = to_wx_array_string(kinds);
    wxArrayString wx_scope = to_wx_array_string(visible_scopes);
    m_lookup->GetTagsByScopeAndName(wx_scope, filter, true, *other_scopes_children);

    // global scope children
    *global_scope_children = get_children_of_scope(create_global_scope_tag(), kinds, filter, visible_scopes);
    return current_scope_children->size() + other_scopes_children->size() + global_scope_children->size();
}

size_t CxxCodeCompletion::get_word_completions(const CxxRemainder& remainder, vector<TagEntryPtr>& candidates,
                                               const vector<wxString>& visible_scopes,
                                               const wxStringSet_t& visible_files)

{
    vector<TagEntryPtr> locals;
    vector<TagEntryPtr> local_functions;
    vector<TagEntryPtr> keywords;
    vector<TagEntryPtr> scope_members;
    vector<TagEntryPtr> other_scopes_members;
    vector<TagEntryPtr> global_scopes_members;

    vector<TagEntryPtr> sorted_locals;
    vector<TagEntryPtr> sorted_local_functions;
    vector<TagEntryPtr> sorted_scope_members;
    vector<TagEntryPtr> sorted_other_scopes_members;
    vector<TagEntryPtr> sorted_global_scopes_members;

    locals = get_locals(remainder.filter);
    local_functions = get_local_functions(remainder.filter);

    vector<wxString> kinds;
    // based on the lasts operand, build the list of items to fetch
    determine_current_scope();
    bool add_keywords = false;
    if(remainder.operand_string.empty()) {
        kinds = { "function", "prototype", "class",      "struct", "namespace", "union",
                  "typedef",  "enum",      "enumerator", "macro",  "cenum" };
        if(m_current_container_tag) {
            // if we are inside a scope, add member types
            kinds.push_back("member");
        }
        add_keywords = true;
    } else if(remainder.operand_string == "::") {
        kinds = { "member",    "function", "prototype", "class", "struct",
                  "namespace", "union",    "typedef",   "enum",  "enumerator" };
    } else {
        // contextual completions
        kinds = { "member", "function", "prototype" };
    }

    // collect member variabels if we are within a scope
    get_children_of_current_scope(kinds, remainder.filter, visible_scopes, &scope_members, &other_scopes_members,
                                  &global_scopes_members);

    // sort the matches:
    sort_tags(locals, sorted_locals, true, {}); // locals are accepted, so dont pass list of files
    sort_tags(local_functions, sorted_local_functions, true,
              {}); // locals fucntions are accepted, so dont pass list of files
    sort_tags(scope_members, sorted_scope_members, true, {}); // members are all accepted
    sort_tags(other_scopes_members, sorted_other_scopes_members, true, visible_files);
    sort_tags(global_scopes_members, sorted_global_scopes_members, true, visible_files);

    if(add_keywords) {
        get_keywords_tags(remainder.filter, keywords);
    }
    candidates.reserve(sorted_local_functions.size() + sorted_locals.size() + sorted_scope_members.size() +
                       sorted_other_scopes_members.size() + sorted_global_scopes_members.size() + keywords.size());

    // place the keywords first
    candidates.insert(candidates.end(), keywords.begin(), keywords.end());
    candidates.insert(candidates.end(), sorted_locals.begin(), sorted_locals.end());
    candidates.insert(candidates.end(), sorted_local_functions.begin(), sorted_local_functions.end());
    candidates.insert(candidates.end(), sorted_scope_members.begin(), sorted_scope_members.end());
    candidates.insert(candidates.end(), sorted_other_scopes_members.begin(), sorted_other_scopes_members.end());
    candidates.insert(candidates.end(), sorted_global_scopes_members.begin(), sorted_global_scopes_members.end());
    return candidates.size();
}

TagEntryPtr CxxCodeCompletion::find_definition(const wxString& filepath, int line, const wxString& expression,
                                               const wxString& text, const vector<wxString>& visible_scopes)
{
    // ----------------------------------
    // word completion
    // ----------------------------------
    clDEBUG() << "find_definition is called for expression:" << expression << endl;
    vector<TagEntryPtr> candidates;
    if(word_complete(filepath, line, expression, text, visible_scopes, true, candidates) == 0) {
        return nullptr;
    }

    // filter tags with no line numbers
    vector<TagEntryPtr> good_tags;
    TagEntryPtr first;
    for(auto tag : candidates) {
        if(tag->GetLine() != wxNOT_FOUND && !tag->GetFile().empty()) {
            first = tag;
            break;
        }
    }

    if(!first) {
        return nullptr;
    }

    if(first->IsMethod()) {
        // we prefer the definition, unless we are already on it, and in that case, return the declaration
        // locate both declaration + implementation
        wxString path = first->GetPath();
        vector<TagEntryPtr> impl_vec;
        vector<TagEntryPtr> decl_vec;
        clDEBUG() << "Searching for path:" << path << endl;
        m_lookup->GetTagsByPathAndKind(path, impl_vec, { "function" }, 1);
        m_lookup->GetTagsByPathAndKind(path, decl_vec, { "prototype" }, 1);

        clDEBUG() << "impl:" << impl_vec.size() << "decl:" << decl_vec.size() << endl;
        if(impl_vec.empty() || decl_vec.empty()) {
            return first;
        }

        TagEntryPtr impl = impl_vec[0];
        TagEntryPtr decl = decl_vec[0];

        if(impl->GetLine() == line && impl->GetFile() == filepath) {
            // already on the impl line, return the decl
            return decl;
        }

        if(decl->GetLine() == line && decl->GetFile() == filepath) {
            // already on the decl line, return the decl
            return impl;
        }

        return impl;
    } else {
        // no need to manipulate this tag
        return first;
    }
}

size_t CxxCodeCompletion::word_complete(const wxString& filepath, int line, const wxString& expression,
                                        const wxString& text, const vector<wxString>& visible_scopes, bool exact_match,
                                        vector<TagEntryPtr>& candidates, const wxStringSet_t& visible_files)
{
    // ----------------------------------
    // word completion
    // ----------------------------------
    clDEBUG() << "word_complete expression:" << expression << endl;
    set_text(text, filepath, line);

    CxxRemainder remainder;
    TagEntryPtr resolved = code_complete(expression, visible_scopes, &remainder);

    wxString filter = remainder.filter;
    if(!resolved) {
        // check if this is a contextual text (A::B or a->b or a.b etc)
        // we only allow global completion of there is not expression list
        // and the remainder has something in it (r.type_name() is not empty)
        CxxRemainder r;
        auto expressions = CxxExpression::from_expression(expression, &r);
        if(expressions.size() == 0 && !r.filter.empty()) {
            clDEBUG() << "code_complete failed to resolve:" << expression << endl;
            clDEBUG() << "filter:" << r.filter << endl;
            get_word_completions(remainder, candidates, visible_scopes, visible_files);
        }
    } else if(resolved) {
        // it was resolved into something...
        clDEBUG() << "code_complete resolved:" << resolved->GetPath() << endl;
        clDEBUG() << "filter:" << remainder.filter << endl;
        get_completions(resolved, remainder.operand_string, remainder.filter, candidates, visible_scopes);
    }
    clDEBUG() << "Number of completion entries:" << candidates.size() << endl;

    // take the first one with the exact match
    if(!exact_match) {
        return candidates.size();
    }

    vector<TagEntryPtr> matches;
    matches.reserve(candidates.size());
    for(TagEntryPtr t : candidates) {
        if(t->GetName() == filter) {
            matches.push_back(t);
        }
    }
    candidates.swap(matches);
    return candidates.size();
}

wxString CxxCodeCompletion::normalize_pattern(TagEntryPtr tag) const
{
    CxxTokenizer tokenizer;
    CxxLexerToken tk;

    tokenizer.Reset(tag->GetPatternClean());
    wxString pattern;
    while(tokenizer.NextToken(tk)) {
        wxString str = tk.GetWXString();
        switch(tk.GetType()) {
        case T_IDENTIFIER:
            if(m_macros_table_map.count(str) && m_macros_table_map.find(str)->second.empty()) {
                // skip this token
            } else {
                pattern << str << " ";
            }
            break;
        default:
            if(tk.is_keyword() || tk.is_builtin_type()) {
                pattern << str << " ";
            } else {
                pattern << str;
            }
            break;
        }
    }
    return pattern;
}

size_t CxxCodeCompletion::get_anonymous_tags(const wxString& name, const wxArrayString& kinds,
                                             vector<TagEntryPtr>& tags) const
{
    if(!m_lookup) {
        return 0;
    }
    m_lookup->GetAnonymouseTags(m_filename, name, kinds, tags);
    return tags.size();
}

size_t CxxCodeCompletion::get_keywords_tags(const wxString& name, vector<TagEntryPtr>& tags)
{
    CompletionHelper helper;
    vector<wxString> keywords;
    helper.get_cxx_keywords(keywords);
    tags.reserve(keywords.size());

    for(const auto& keyword : keywords) {
        if(keyword.StartsWith(name)) {
            TagEntryPtr tag(new TagEntry());
            tag->SetName(keyword);
            tag->SetPath(keyword);
            tag->SetKind("keyword");
            tag->SetFile("<built-in>");
            tags.push_back(tag);
        }
    }
    return tags.size();
}

///====--------------------------------------------------------------------------------
///====--------------------------------------------------------------------------------
///
/// LookupTable
///
///====--------------------------------------------------------------------------------
///====--------------------------------------------------------------------------------

TagEntryPtr LookupTable::GetScope(const wxString& filename, int line_number)
{
    CHECK_PTR_RET_NULL(pdb);
    return pdb->GetScope(filename, line_number);
}

void LookupTable::GetTagsByPath(const wxString& path, vector<TagEntryPtr>& tags, int limit)
{
    if(pdb) {
        pdb->GetTagsByPath(path, tags, limit);
    }

    if(!tests_db.empty()) {
        if(tests_db.count(path)) {
            tags.push_back(tests_db[path]);
        }
    }
}

void LookupTable::GetSubscriptOperator(const wxString& scope, vector<TagEntryPtr>& tags)
{
    if(pdb) {
        pdb->GetSubscriptOperator(scope, tags);
    }
}

void LookupTable::GetTagsByPathAndKind(const wxString& path, vector<TagEntryPtr>& tags, const vector<wxString>& kinds,
                                       int limit)
{
    if(pdb) {
        pdb->GetTagsByPathAndKind(path, tags, kinds, limit);
    }

    // add the tests tags
    if(!tests_db.empty() && tests_db.count(path)) {
        auto tag = tests_db[path];
        for(const wxString& kind : kinds) {
            if(tag->GetKind() == kind) {
                tags.push_back(tag);
                break;
            }
        }
    }
}

void LookupTable::GetTagsByScopeAndKind(const wxString& scope, const wxArrayString& kinds, const wxString& filter,
                                        vector<TagEntryPtr>& tags, bool applyLimit)
{
    if(pdb) {
        pdb->GetTagsByScopeAndKind(scope, kinds, filter, tags, applyLimit);
    }

    if(!tests_db.empty()) {
        wxStringSet_t kinds_map = { kinds.begin(), kinds.end() };
        for(const auto& vt : tests_db) {
            if(vt.second->GetScope() == scope && kinds_map.count(vt.second->GetKind()) &&
               vt.second->GetName().StartsWith(filter)) {
                tags.push_back(vt.second);
            }
        }
    }
}

void LookupTable::GetFilesForCC(const wxString& userTyped, wxArrayString& matches)
{
    CHECK_PTR_RET(pdb);
    pdb->GetFilesForCC(userTyped, matches);
}

void LookupTable::GetTagsByScopeAndName(const wxString& scope, const wxString& name, bool partialNameAllowed,
                                        vector<TagEntryPtr>& tags)
{
    if(pdb) {
        pdb->GetTagsByScopeAndName(scope, name, partialNameAllowed, tags);
    }

    if(!tests_db.empty()) {
        auto compare_func = [=](const wxString& tag_name) {
            if(partialNameAllowed) {
                return tag_name.StartsWith(name);
            } else {
                return tag_name == name;
            }
        };

        for(const auto& vt : tests_db) {
            if(vt.second->GetScope() == scope && compare_func(vt.second->GetName())) {
                tags.push_back(vt.second);
            }
        }
    }
}

void LookupTable::GetTagsByScopeAndName(const wxArrayString& scopes, const wxString& name, bool partialNameAllowed,
                                        vector<TagEntryPtr>& tags)
{
    if(pdb) {
        pdb->GetTagsByScopeAndName(scopes, name, partialNameAllowed, tags);
    }

    if(!tests_db.empty()) {
        auto compare_func = [=](const wxString& tag_name) {
            if(partialNameAllowed) {
                return tag_name.StartsWith(name);
            } else {
                return tag_name == name;
            }
        };

        // use set instead of array
        wxStringSet_t scope_set = { scopes.begin(), scopes.end() };
        for(const auto& vt : tests_db) {
            if(scope_set.count(vt.second->GetScope()) && compare_func(vt.second->GetName())) {
                tags.push_back(vt.second);
            }
        }
    }
}

size_t LookupTable::GetAnonymouseTags(const wxString& filepath, const wxString& name, const wxArrayString& kinds,
                                      vector<TagEntryPtr>& tags)
{
    if(pdb) {
        pdb->GetAnonymouseTags(filepath, name, kinds, tags);
    }
    if(!tests_db.empty()) {
        // use set instead of array
        wxStringSet_t kinds_set = { kinds.begin(), kinds.end() };
        for(const auto& vt : tests_db) {
            if(vt.second->GetScope().StartsWith("__anon") && vt.second->GetFile() == filepath &&
               vt.second->GetName() == name && kinds_set.count(vt.second->GetKind())) {
                tags.push_back(vt.second);
            }
        }
    }
    return tags.size();
}

void LookupTable::GetTagsByScope(const wxString& scope, vector<TagEntryPtr>& tags)
{
    if(pdb) {
        pdb->GetTagsByScope(scope, tags);
    }

    if(!tests_db.empty()) {
        for(const auto& vt : tests_db) {
            if(vt.second->GetScope() == scope) {
                tags.push_back(vt.second);
            }
        }
    }
}

#define CHECK_EXPECTED(Token, ExpectedType)              \
    if(Token.IsEOF() || Token.GetType() != ExpectedType) \
        return false;

bool CxxCodeCompletion::read_template_definition(CxxTokenizer& tokenizer, wxString* definition) const
{
    CxxLexerToken token;
    tokenizer.NextToken(token);
    if(token.GetType() != T_TEMPLATE || token.IsEOF()) {
        tokenizer.UngetToken();
        return false;
    }

    definition->clear();

    // we are now expecting an open brace
    tokenizer.NextToken(token);
    CHECK_EXPECTED(token, '<');

    int depth = 1;
    while(tokenizer.NextToken(token)) {
        if(token.is_keyword() || token.is_builtin_type()) {
            definition->Append(" ");
            definition->Append(token.GetWXString());
            continue;
        }
        switch(token.GetType()) {
        case '<':
            depth++;
            definition->Append(token.GetWXString());
            break;
        case '>':
            depth--;
            if(depth == 0) {
                return true;
            } else {
                definition->Append(token.GetWXString());
            }
            break;
        default:
            definition->Append(token.GetWXString());
            break;
        }
    }
    return false;
}
#undef CHECK_EXPECTED

size_t CxxCodeCompletion::get_class_constructors(TagEntryPtr tag, vector<TagEntryPtr>& tags)
{
    if(!tag->IsClass() && !tag->IsStruct()) {
        tags.clear();
        return tags.size();
    }
    m_lookup->GetTagsByPathAndKind(tag->GetPath() + "::" + tag->GetName(), tags, { "prototype", "function" }, 250);

    vector<TagEntryPtr> sorted_tags;
    // filter duplicate
    sort_tags(tags, sorted_tags, true, {});
    tags.swap(sorted_tags);
    return tags.size();
}
