//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: SyntaxHighlightBaseDlg.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "syntaxhighlightbasedlg.h"

// Declare the bitmap loading function
extern void wxCrafterqEa5vvInitBitmapResources();

static bool bBitmapLoaded = false;

SyntaxHighlightBaseDlg::SyntaxHighlightBaseDlg(wxWindow* parent, wxWindowID id, const wxString& title,
                                               const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterqEa5vvInitBitmapResources();
        bBitmapLoaded = true;
    }
    // Set icon(s) to the application/dialog
    wxIconBundle app_icons;
    {
        wxBitmap iconBmp = wxXmlResource::Get()->LoadBitmap(wxT("fonts-and-colours"));
        wxIcon icn;
        icn.CopyFromBitmap(iconBmp);
        app_icons.AddIcon(icn);
    }
    SetIcons(app_icons);

    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer1);

    m_panel171 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTAB_TRAVERSAL);

    bSizer1->Add(m_panel171, 1, wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer173 = new wxBoxSizer(wxVERTICAL);
    m_panel171->SetSizer(boxSizer173);

    m_toolbar = new wxToolBar(m_panel171, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panel171, wxSize(-1, -1)),
                              wxTB_HORZ_TEXT | wxTB_NOICONS | wxTB_FLAT);
    m_toolbar->SetToolBitmapSize(wxSize(16, 16));

    boxSizer173->Add(m_toolbar, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_notebook =
        new wxNotebook(m_panel171, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panel171, wxSize(-1, -1)), wxBK_DEFAULT);
    m_notebook->SetName(wxT("m_notebook"));

    boxSizer173->Add(m_notebook, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_panelGlobalColours =
        new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_panelGlobalColours->SetToolTip(_("Set global colours and fonts"));
    m_notebook->AddPage(m_panelGlobalColours, _("General"), true);

    wxBoxSizer* boxSizer82 = new wxBoxSizer(wxVERTICAL);
    m_panelGlobalColours->SetSizer(boxSizer82);

    wxStaticBoxSizer* staticBoxSizer179 =
        new wxStaticBoxSizer(new wxStaticBox(m_panelGlobalColours, wxID_ANY, _("Editor Colours")), wxVERTICAL);

    boxSizer82->Add(staticBoxSizer179, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxFlexGridSizer* flexGridSizer181 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer181->SetFlexibleDirection(wxBOTH);
    flexGridSizer181->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer181->AddGrowableCol(1);

    staticBoxSizer179->Add(flexGridSizer181, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_cbUseCustomBaseColour = new wxCheckBox(m_panelGlobalColours, wxID_ANY, _("Use custom base colour:"),
                                             wxDefaultPosition, wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), 0);
    m_cbUseCustomBaseColour->SetValue(true);

    flexGridSizer181->Add(m_cbUseCustomBaseColour, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_colourPickerBaseColour =
        new wxColourPickerCtrl(m_panelGlobalColours, wxID_ANY, *wxBLACK, wxDefaultPosition,
                               wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), wxCLRP_DEFAULT_STYLE);
    m_colourPickerBaseColour->SetToolTip(
        _("By default, CodeLite uses the current desktop theme to build the colour for the various\ncontrols. You can "
          "override this by choosing a different colour here"));

    flexGridSizer181->Add(m_colourPickerBaseColour, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxStaticBoxSizer* staticBoxSizer188 =
        new wxStaticBoxSizer(new wxStaticBox(m_panelGlobalColours, wxID_ANY, _("Text Selection")), wxVERTICAL);

    boxSizer82->Add(staticBoxSizer188, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxFlexGridSizer* fgSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    fgSizer3->SetFlexibleDirection(wxBOTH);
    fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    fgSizer3->AddGrowableCol(1);

    staticBoxSizer188->Add(fgSizer3, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText9 = new wxStaticText(m_panelGlobalColours, wxID_ANY, _("Selected Text Background Colour:"),
                                     wxDefaultPosition, wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), 0);

    fgSizer3->Add(m_staticText9, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_colourPickerSelTextBgColour =
        new wxColourPickerCtrl(m_panelGlobalColours, wxID_ANY, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT),
                               wxDefaultPosition, wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)),
                               wxCLRP_SHOW_LABEL | wxCLRP_USE_TEXTCTRL | wxCLRP_DEFAULT_STYLE);

    fgSizer3->Add(m_colourPickerSelTextBgColour, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText94 = new wxStaticText(m_panelGlobalColours, wxID_ANY, _("Use Custom Selection Foreground Colour:"),
                                      wxDefaultPosition, wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), 0);

    fgSizer3->Add(m_staticText94, 0, wxALL | wxALIGN_RIGHT, WXC_FROM_DIP(5));

    m_checkBoxCustomSelectionFgColour = new wxCheckBox(m_panelGlobalColours, wxID_ANY, wxT(""), wxDefaultPosition,
                                                       wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), 0);
    m_checkBoxCustomSelectionFgColour->SetValue(false);
    m_checkBoxCustomSelectionFgColour->SetToolTip(
        _("You can choose to override the default selection colouring by enabling this checkbox"));

    fgSizer3->Add(m_checkBoxCustomSelectionFgColour, 0, wxALL | wxEXPAND | wxALIGN_LEFT, WXC_FROM_DIP(5));

    m_staticText84 = new wxStaticText(m_panelGlobalColours, wxID_ANY, _("Selected Text Foreground Colour:"),
                                      wxDefaultPosition, wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), 0);

    fgSizer3->Add(m_staticText84, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_colourPickerSelTextFgColour =
        new wxColourPickerCtrl(m_panelGlobalColours, wxID_ANY, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT),
                               wxDefaultPosition, wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)),
                               wxCLRP_SHOW_LABEL | wxCLRP_USE_TEXTCTRL | wxCLRP_DEFAULT_STYLE);

    fgSizer3->Add(m_colourPickerSelTextFgColour, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxStaticBoxSizer* staticBoxSizer182 =
        new wxStaticBoxSizer(new wxStaticBox(m_panelGlobalColours, wxID_ANY, _("Syntax Highlight")), wxVERTICAL);

    boxSizer82->Add(staticBoxSizer182, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxFlexGridSizer* fgSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    fgSizer4->SetFlexibleDirection(wxBOTH);
    fgSizer4->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    fgSizer4->AddGrowableCol(1);

    staticBoxSizer182->Add(fgSizer4, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText159 = new wxStaticText(m_panelGlobalColours, wxID_ANY, _("Global font:"), wxDefaultPosition,
                                       wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), 0);

    fgSizer4->Add(m_staticText159, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_fontPickerGlobal = new wxFontPickerCtrl(m_panelGlobalColours, wxID_ANY, wxNullFont, wxDefaultPosition,
                                              wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), wxFNTP_DEFAULT_STYLE);
    m_fontPickerGlobal->SetToolTip(_("Set a global font for all the  supported languages"));

    fgSizer4->Add(m_fontPickerGlobal, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText155 = new wxStaticText(m_panelGlobalColours, wxID_ANY, _("Global theme:"), wxDefaultPosition,
                                       wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), 0);

    fgSizer4->Add(m_staticText155, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_choiceGlobalThemeArr;
    m_choiceGlobalTheme = new wxChoice(m_panelGlobalColours, wxID_ANY, wxDefaultPosition,
                                       wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, -1)), m_choiceGlobalThemeArr, 0);
    m_choiceGlobalTheme->SetToolTip(
        _("Set a global theme for all the supported languages.\nIf the theme is not available for a given language, "
          "CodeLite will use the next available theme from\nthe same family"));

    fgSizer4->Add(m_choiceGlobalTheme, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_stcPreview = new wxStyledTextCtrl(m_panelGlobalColours, wxID_ANY, wxDefaultPosition,
                                        wxDLG_UNIT(m_panelGlobalColours, wxSize(-1, 150)), 0);
    // Configure the fold margin
    m_stcPreview->SetMarginType(4, wxSTC_MARGIN_SYMBOL);
    m_stcPreview->SetMarginMask(4, wxSTC_MASK_FOLDERS);
    m_stcPreview->SetMarginSensitive(4, true);
    m_stcPreview->SetMarginWidth(4, 0);

    // Configure the tracker margin
    m_stcPreview->SetMarginWidth(1, 0);

    // Configure the symbol margin
    m_stcPreview->SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    m_stcPreview->SetMarginMask(2, ~(wxSTC_MASK_FOLDERS));
    m_stcPreview->SetMarginWidth(2, 0);
    m_stcPreview->SetMarginSensitive(2, true);

    // Configure the line numbers margin
    m_stcPreview->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stcPreview->SetMarginWidth(0, 0);

    // Configure the line symbol margin
    m_stcPreview->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stcPreview->SetMarginMask(3, 0);
    m_stcPreview->SetMarginWidth(3, 0);
    // Select the lexer
    m_stcPreview->SetLexer(wxSTC_LEX_NULL);
    // Set default font / styles
    m_stcPreview->StyleClearAll();
    m_stcPreview->SetWrapMode(0);
    m_stcPreview->SetIndentationGuides(0);
    m_stcPreview->SetKeyWords(0, wxT(""));
    m_stcPreview->SetKeyWords(1, wxT(""));
    m_stcPreview->SetKeyWords(2, wxT(""));
    m_stcPreview->SetKeyWords(3, wxT(""));
    m_stcPreview->SetKeyWords(4, wxT(""));

    boxSizer82->Add(m_stcPreview, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));
    m_stcPreview->SetMinSize(wxSize(-1, 150));

    m_panelSyntaxHighlight =
        new wxPanel(m_notebook, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_panelSyntaxHighlight->SetToolTip(_("Customize your colours and font per language"));
    m_notebook->AddPage(m_panelSyntaxHighlight, _("Customize"), false);

    wxBoxSizer* boxSizer21 = new wxBoxSizer(wxHORIZONTAL);
    m_panelSyntaxHighlight->SetSizer(boxSizer21);

    wxArrayString m_listBoxArr;
    m_listBox =
        new wxListBox(m_panelSyntaxHighlight, wxID_ANY, wxDefaultPosition,
                      wxDLG_UNIT(m_panelSyntaxHighlight, wxSize(-1, -1)), m_listBoxArr, wxLB_SORT | wxLB_SINGLE);

    boxSizer21->Add(m_listBox, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_panel25 = new wxPanel(m_panelSyntaxHighlight, wxID_ANY, wxDefaultPosition,
                            wxDLG_UNIT(m_panelSyntaxHighlight, wxSize(-1, -1)), wxTAB_TRAVERSAL);

    boxSizer21->Add(m_panel25, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
    m_panel25->SetSizer(bSizer3);

    m_notebook2 =
        new wxNotebook(m_panel25, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panel25, wxSize(-1, -1)), wxBK_DEFAULT);
    m_notebook2->SetName(wxT("m_notebook2"));

    bSizer3->Add(m_notebook2, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_panelGlobalSettings =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panelGlobalSettings, _("Global Settings"), true);

    wxBoxSizer* bSizer6 = new wxBoxSizer(wxVERTICAL);
    m_panelGlobalSettings->SetSizer(bSizer6);

    wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    fgSizer2->SetFlexibleDirection(wxBOTH);
    fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    fgSizer2->AddGrowableCol(1);

    bSizer6->Add(fgSizer2, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText70 = new wxStaticText(m_panelGlobalSettings, wxID_ANY, _("Available Themes:"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText70, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer95 = new wxBoxSizer(wxHORIZONTAL);

    fgSizer2->Add(boxSizer95, 0, wxEXPAND, WXC_FROM_DIP(5));

    wxArrayString m_choiceLexerThemesArr;
    m_choiceLexerThemes = new wxChoice(m_panelGlobalSettings, wxID_ANY, wxDefaultPosition,
                                       wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)), m_choiceLexerThemesArr, 0);

    boxSizer95->Add(m_choiceLexerThemes, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText6 = new wxStaticText(m_panelGlobalSettings, wxID_ANY, _("Global Font:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText6, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_globalFontPicker =
        new wxFontPickerCtrl(m_panelGlobalSettings, wxID_ANY, wxNullFont, wxDefaultPosition,
                             wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)), wxFNTP_USEFONT_FOR_LABEL);
    m_globalFontPicker->SetToolTip(_("Use this to select a font to be used by *all* styles of this lexer"));

    fgSizer2->Add(m_globalFontPicker, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText7 = new wxStaticText(m_panelGlobalSettings, wxID_ANY, _("Global background Colour:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText7, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_globalBgColourPicker = new wxColourPickerCtrl(m_panelGlobalSettings, wxID_ANY, *wxBLACK, wxDefaultPosition,
                                                    wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)),
                                                    wxCLRP_SHOW_LABEL | wxCLRP_USE_TEXTCTRL | wxCLRP_DEFAULT_STYLE);
    m_globalBgColourPicker->SetToolTip(
        _("Use this to select a background colour to be used by *all* styles of this lexer"));

    fgSizer2->Add(m_globalBgColourPicker, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText8 = new wxStaticText(m_panelGlobalSettings, wxID_ANY, _("File Extensions:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText8, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_fileSpec = new wxTextCtrl(m_panelGlobalSettings, wxID_ANY, wxT(""), wxDefaultPosition,
                                wxDLG_UNIT(m_panelGlobalSettings, wxSize(-1, -1)), 0);
    m_fileSpec->SetToolTip(_("Associate this lexer with files which have these extensions"));
#if wxVERSION_NUMBER >= 3000
    m_fileSpec->SetHint(wxT(""));
#endif

    fgSizer2->Add(m_fileSpec, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_panelCustomize =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panelCustomize, _("Styles"), false);

    wxBoxSizer* bSizer51 = new wxBoxSizer(wxVERTICAL);
    m_panelCustomize->SetSizer(bSizer51);

    wxBoxSizer* bSizer8 = new wxBoxSizer(wxHORIZONTAL);

    bSizer51->Add(bSizer8, 1, wxEXPAND, WXC_FROM_DIP(5));

    wxArrayString m_propertiesArr;
    m_properties =
        new wxListBox(m_panelCustomize, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)),
                      m_propertiesArr, wxLB_SORT | wxLB_SINGLE);

    bSizer8->Add(m_properties, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* bSizer9 = new wxBoxSizer(wxVERTICAL);

    bSizer8->Add(bSizer9, 1, wxEXPAND, WXC_FROM_DIP(5));

    wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    fgSizer1->SetFlexibleDirection(wxBOTH);
    fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    fgSizer1->AddGrowableCol(1);

    bSizer9->Add(fgSizer1, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText2 = new wxStaticText(m_panelCustomize, wxID_ANY, _("Style Font:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), 0);

    fgSizer1->Add(m_staticText2, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_fontPicker = new wxFontPickerCtrl(m_panelCustomize, wxID_ANY, wxNullFont, wxDefaultPosition,
                                        wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), wxFNTP_USEFONT_FOR_LABEL);
    m_fontPicker->SetToolTip(_("Select a font to be used with the selected style"));

    fgSizer1->Add(m_fontPicker, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText3 = new wxStaticText(m_panelCustomize, wxID_ANY, _("Foreground Colour:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), 0);

    fgSizer1->Add(m_staticText3, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_colourPicker = new wxColourPickerCtrl(m_panelCustomize, wxID_ANY, *wxBLACK, wxDefaultPosition,
                                            wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)),
                                            wxCLRP_SHOW_LABEL | wxCLRP_USE_TEXTCTRL | wxCLRP_DEFAULT_STYLE);
    m_colourPicker->SetToolTip(_("Select the foreground colour for the selected style"));

    fgSizer1->Add(m_colourPicker, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText4 = new wxStaticText(m_panelCustomize, wxID_ANY, _("Background Colour:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), 0);

    fgSizer1->Add(m_staticText4, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_bgColourPicker = new wxColourPickerCtrl(m_panelCustomize, wxID_ANY, *wxBLACK, wxDefaultPosition,
                                              wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)),
                                              wxCLRP_SHOW_LABEL | wxCLRP_USE_TEXTCTRL | wxCLRP_DEFAULT_STYLE);
    m_bgColourPicker->SetToolTip(_("Select the background colour for the selected style"));

    fgSizer1->Add(m_bgColourPicker, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    fgSizer1->Add(0, 0, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_eolFilled = new wxCheckBox(m_panelCustomize, wxID_ANY, _("Style is EOL Filled"), wxDefaultPosition,
                                 wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), 0);
    m_eolFilled->SetValue(false);
    m_eolFilled->SetToolTip(_("If a line ends with a character/word which has this style, the remaining of the line "
                              "will be coloured with this style background colour"));

    fgSizer1->Add(m_eolFilled, 0, wxALL, WXC_FROM_DIP(5));

    fgSizer1->Add(0, 0, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_styleWithinPreProcessor = new wxCheckBox(m_panelCustomize, wxID_ANY, _("Styling Within Pre-processor Line"),
                                               wxDefaultPosition, wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), 0);
    m_styleWithinPreProcessor->SetValue(false);

    fgSizer1->Add(m_styleWithinPreProcessor, 0, wxALL, WXC_FROM_DIP(5));

    m_staticline1 = new wxStaticLine(m_panelCustomize, wxID_ANY, wxDefaultPosition,
                                     wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), wxLI_HORIZONTAL);

    bSizer9->Add(m_staticline1, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText1 = new wxStaticText(m_panelCustomize, wxID_ANY, _("Edit Lexer Keyword Sets:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), 0);

    bSizer9->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);

    bSizer9->Add(bSizer5, 0, wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_button5 = new wxButton(m_panelCustomize, wxID_ANY, _("Set &0"), wxDefaultPosition,
                             wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), wxBU_EXACTFIT);

    bSizer5->Add(m_button5, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_button6 = new wxButton(m_panelCustomize, wxID_ANY, _("Set &1"), wxDefaultPosition,
                             wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), wxBU_EXACTFIT);

    bSizer5->Add(m_button6, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_button7 = new wxButton(m_panelCustomize, wxID_ANY, _("Set &2"), wxDefaultPosition,
                             wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), wxBU_EXACTFIT);

    bSizer5->Add(m_button7, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_button8 = new wxButton(m_panelCustomize, wxID_ANY, _("Set &3"), wxDefaultPosition,
                             wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), wxBU_EXACTFIT);

    bSizer5->Add(m_button8, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_button9 = new wxButton(m_panelCustomize, wxID_ANY, _("Set &4"), wxDefaultPosition,
                             wxDLG_UNIT(m_panelCustomize, wxSize(-1, -1)), wxBU_EXACTFIT);

    bSizer5->Add(m_button9, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer19 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer173->Add(boxSizer19, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_stdBtnSizer10 = new wxStdDialogButtonSizer();

    boxSizer19->Add(m_stdBtnSizer10, 0, wxALL, WXC_FROM_DIP(5));

    m_buttonOk =
        new wxButton(m_panel171, wxID_OK, wxT(""), wxDefaultPosition, wxDLG_UNIT(m_panel171, wxSize(-1, -1)), 0);
    m_buttonOk->SetDefault();
    m_stdBtnSizer10->AddButton(m_buttonOk);

    m_buttonCancel =
        new wxButton(m_panel171, wxID_CANCEL, wxT(""), wxDefaultPosition, wxDLG_UNIT(m_panel171, wxSize(-1, -1)), 0);
    m_stdBtnSizer10->AddButton(m_buttonCancel);

    m_buttonApply =
        new wxButton(m_panel171, wxID_APPLY, wxT(""), wxDefaultPosition, wxDLG_UNIT(m_panel171, wxSize(-1, -1)), 0);
    m_stdBtnSizer10->AddButton(m_buttonApply);
    m_stdBtnSizer10->Realize();

    SetName(wxT("SyntaxHighlightBaseDlg"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
    // Connect events
    m_cbUseCustomBaseColour->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED,
                                     wxCommandEventHandler(SyntaxHighlightBaseDlg::OnUseCustomBaseColour), NULL, this);
    m_cbUseCustomBaseColour->Connect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnUseCustomBaseColourUI), NULL, this);
    m_colourPickerBaseColour->Connect(wxEVT_UPDATE_UI,
                                      wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnUseCustomColourUI), NULL, this);
    m_colourPickerBaseColour->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                      wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnCustomBaseColourPIcked),
                                      NULL, this);
    m_colourPickerSelTextBgColour->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                           wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnSelTextChanged), NULL,
                                           this);
    m_checkBoxCustomSelectionFgColour->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED,
                                               wxCommandEventHandler(SyntaxHighlightBaseDlg::OnUseCustomFgTextColour),
                                               NULL, this);
    m_staticText84->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnTextSelFgUI), NULL, this);
    m_colourPickerSelTextFgColour->Connect(wxEVT_UPDATE_UI,
                                           wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnTextSelFgUI), NULL, this);
    m_colourPickerSelTextFgColour->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                           wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnSelTextFgChanged), NULL,
                                           this);
    m_fontPickerGlobal->Connect(wxEVT_COMMAND_FONTPICKER_CHANGED,
                                wxFontPickerEventHandler(SyntaxHighlightBaseDlg::OnGlobalFontSelected), NULL, this);
    m_choiceGlobalTheme->Connect(wxEVT_COMMAND_CHOICE_SELECTED,
                                 wxCommandEventHandler(SyntaxHighlightBaseDlg::OnGlobalThemeSelected), NULL, this);
    m_listBox->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnLexerSelected),
                       NULL, this);
    m_choiceLexerThemes->Connect(wxEVT_COMMAND_CHOICE_SELECTED,
                                 wxCommandEventHandler(SyntaxHighlightBaseDlg::OnThemeChanged), NULL, this);
    m_globalFontPicker->Connect(wxEVT_COMMAND_FONTPICKER_CHANGED,
                                wxFontPickerEventHandler(SyntaxHighlightBaseDlg::OnFontChanged), NULL, this);
    m_globalBgColourPicker->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                    wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnColourChanged), NULL, this);
    m_fileSpec->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnText), NULL, this);
    m_properties->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnItemSelected),
                          NULL, this);
    m_fontPicker->Connect(wxEVT_COMMAND_FONTPICKER_CHANGED,
                          wxFontPickerEventHandler(SyntaxHighlightBaseDlg::OnFontChanged), NULL, this);
    m_colourPicker->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                            wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnColourChanged), NULL, this);
    m_bgColourPicker->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                              wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnColourChanged), NULL, this);
    m_eolFilled->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEolFilled),
                         NULL, this);
    m_styleWithinPreProcessor->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED,
                                       wxCommandEventHandler(SyntaxHighlightBaseDlg::OnStyleWithinPreprocessor), NULL,
                                       this);
    m_styleWithinPreProcessor->Connect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnStyleWithingPreProcessorUI), NULL, this);
    m_button5->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                       wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton0), NULL, this);
    m_button6->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                       wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton1), NULL, this);
    m_button7->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                       wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton2), NULL, this);
    m_button8->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                       wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton3), NULL, this);
    m_button9->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                       wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton4), NULL, this);
    m_buttonOk->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnButtonOK), NULL,
                        this);
    m_buttonCancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnButtonCancel),
                            NULL, this);
    m_buttonApply->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnButtonApply),
                           NULL, this);
    m_buttonApply->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnButtonApplyUI), NULL,
                           this);
}

SyntaxHighlightBaseDlg::~SyntaxHighlightBaseDlg()
{
    m_cbUseCustomBaseColour->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED,
                                        wxCommandEventHandler(SyntaxHighlightBaseDlg::OnUseCustomBaseColour), NULL,
                                        this);
    m_cbUseCustomBaseColour->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnUseCustomBaseColourUI), NULL, this);
    m_colourPickerBaseColour->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnUseCustomColourUI), NULL, this);
    m_colourPickerBaseColour->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                         wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnCustomBaseColourPIcked),
                                         NULL, this);
    m_colourPickerSelTextBgColour->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                              wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnSelTextChanged),
                                              NULL, this);
    m_checkBoxCustomSelectionFgColour->Disconnect(
        wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnUseCustomFgTextColour), NULL,
        this);
    m_staticText84->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnTextSelFgUI), NULL,
                               this);
    m_colourPickerSelTextFgColour->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnTextSelFgUI), NULL, this);
    m_colourPickerSelTextFgColour->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                              wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnSelTextFgChanged),
                                              NULL, this);
    m_fontPickerGlobal->Disconnect(wxEVT_COMMAND_FONTPICKER_CHANGED,
                                   wxFontPickerEventHandler(SyntaxHighlightBaseDlg::OnGlobalFontSelected), NULL, this);
    m_choiceGlobalTheme->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED,
                                    wxCommandEventHandler(SyntaxHighlightBaseDlg::OnGlobalThemeSelected), NULL, this);
    m_listBox->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED,
                          wxCommandEventHandler(SyntaxHighlightBaseDlg::OnLexerSelected), NULL, this);
    m_choiceLexerThemes->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED,
                                    wxCommandEventHandler(SyntaxHighlightBaseDlg::OnThemeChanged), NULL, this);
    m_globalFontPicker->Disconnect(wxEVT_COMMAND_FONTPICKER_CHANGED,
                                   wxFontPickerEventHandler(SyntaxHighlightBaseDlg::OnFontChanged), NULL, this);
    m_globalBgColourPicker->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                       wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnColourChanged), NULL, this);
    m_fileSpec->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnText), NULL,
                           this);
    m_properties->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED,
                             wxCommandEventHandler(SyntaxHighlightBaseDlg::OnItemSelected), NULL, this);
    m_fontPicker->Disconnect(wxEVT_COMMAND_FONTPICKER_CHANGED,
                             wxFontPickerEventHandler(SyntaxHighlightBaseDlg::OnFontChanged), NULL, this);
    m_colourPicker->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                               wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnColourChanged), NULL, this);
    m_bgColourPicker->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                 wxColourPickerEventHandler(SyntaxHighlightBaseDlg::OnColourChanged), NULL, this);
    m_eolFilled->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEolFilled),
                            NULL, this);
    m_styleWithinPreProcessor->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED,
                                          wxCommandEventHandler(SyntaxHighlightBaseDlg::OnStyleWithinPreprocessor),
                                          NULL, this);
    m_styleWithinPreProcessor->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnStyleWithingPreProcessorUI), NULL, this);
    m_button5->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                          wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton0), NULL, this);
    m_button6->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                          wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton1), NULL, this);
    m_button7->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                          wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton2), NULL, this);
    m_button8->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                          wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton3), NULL, this);
    m_button9->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                          wxCommandEventHandler(SyntaxHighlightBaseDlg::OnEditKeyWordsButton4), NULL, this);
    m_buttonOk->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SyntaxHighlightBaseDlg::OnButtonOK),
                           NULL, this);
    m_buttonCancel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                               wxCommandEventHandler(SyntaxHighlightBaseDlg::OnButtonCancel), NULL, this);
    m_buttonApply->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                              wxCommandEventHandler(SyntaxHighlightBaseDlg::OnButtonApply), NULL, this);
    m_buttonApply->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SyntaxHighlightBaseDlg::OnButtonApplyUI), NULL,
                              this);
}

NewThemeDialogBase::NewThemeDialogBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
                                       const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterqEa5vvInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer115 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer115);

    wxFlexGridSizer* flexGridSizer125 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer125->SetFlexibleDirection(wxBOTH);
    flexGridSizer125->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer125->AddGrowableCol(1);

    boxSizer115->Add(flexGridSizer125, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText127 =
        new wxStaticText(this, wxID_ANY, _("Theme Name:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    flexGridSizer125->Add(m_staticText127, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_textCtrlName = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(300, -1)), 0);
    m_textCtrlName->SetToolTip(_("Set the theme name"));
    m_textCtrlName->SetFocus();
#if wxVERSION_NUMBER >= 3000
    m_textCtrlName->SetHint(wxT(""));
#endif

    flexGridSizer125->Add(m_textCtrlName, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText131 =
        new wxStaticText(this, wxID_ANY, _("Language:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    flexGridSizer125->Add(m_staticText131, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_choiceLanguageArr;
    m_choiceLanguage =
        new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), m_choiceLanguageArr, 0);
    m_choiceLanguage->SetToolTip(_("Make this theme for this language"));

    flexGridSizer125->Add(m_choiceLanguage, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText135 =
        new wxStaticText(this, wxID_ANY, _("Based on Theme:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    flexGridSizer125->Add(m_staticText135, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_choiceBaseThemeArr;
    m_choiceBaseTheme =
        new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), m_choiceBaseThemeArr, 0);
    m_choiceBaseTheme->SetToolTip(_("Set the base theme for this new theme"));

    flexGridSizer125->Add(m_choiceBaseTheme, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_stdBtnSizer117 = new wxStdDialogButtonSizer();

    boxSizer115->Add(m_stdBtnSizer117, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_buttonOK = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_buttonOK->SetDefault();
    m_stdBtnSizer117->AddButton(m_buttonOK);

    m_buttonCancel = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_stdBtnSizer117->AddButton(m_buttonCancel);
    m_stdBtnSizer117->Realize();

    SetName(wxT("NewThemeDialogBase"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
    // Connect events
    m_choiceLanguage->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(NewThemeDialogBase::OnLexerSelected),
                              NULL, this);
    m_buttonOK->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewThemeDialogBase::OnOkUI), NULL, this);
}

NewThemeDialogBase::~NewThemeDialogBase()
{
    m_choiceLanguage->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED,
                                 wxCommandEventHandler(NewThemeDialogBase::OnLexerSelected), NULL, this);
    m_buttonOK->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewThemeDialogBase::OnOkUI), NULL, this);
}
