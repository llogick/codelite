//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: gui.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef _CODELITE_WXCRAFTER_GUI_BASE_CLASSES_H
#define _CODELITE_WXCRAFTER_GUI_BASE_CLASSES_H

// clang-format off
#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/frame.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/toolbar.h>
#include "clToolBar.h"
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include "output_nbook.h"
#include <wx/imaglist.h>
#include <wx/pen.h>
#include <wx/aui/auibar.h>
#include <map>
#include <wx/scrolwin.h>
#include "designer_panel.h"
#include <wx/stc/stc.h>
#include <wx/propgrid/manager.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIP
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif

// clang-format on

class MainFrameBase : public wxFrame
{
public:
    enum {
        ID_CUSTOM_CONTROL_DELETE = 1001,
        ID_CUSTOM_CONTROL_EDIT = 1002,
        ID_BATCH_GENERATE_CODE = 1003,
        ID_CUSTOM_CONTROL_NEW = 1004,
        ID_GENERATE_CODE = 1005,
    };

protected:
    clToolBar* m_mainToolbar;
    wxPanel* m_MainPanel;
    wxSplitterWindow* m_splitterMain;
    wxPanel* m_splitterPageTreeView;
    wxPanel* m_splitterPageDesigner;
    wxStatusBar* m_statusBar;
    wxMenuBar* m_menuBar;
    wxMenu* m_menuFile;
    wxMenuItem* m_menuItemOpen;
    wxMenuItem* m_menuItemSave;
    wxMenuItem* m_menuItemSep1;
    wxMenuItem* m_menuItemGenerate;
    wxMenuItem* m_menuItemBatchGenerate;
    wxMenuItem* m_menuItemSep2;
    wxMenuItem* m_menuItemHide;
    wxMenu* m_menuView;
    wxMenuItem* m_menuItemPreview;
    wxMenu* m_menuEdit;
    wxMenuItem* m_menuItem74;
    wxMenuItem* m_menuItem88;
    wxMenuItem* m_menuItemCopy;
    wxMenuItem* m_menuItemPaste;
    wxMenuItem* m_menuItemCut;
    wxMenuItem* m_menuItem76;
    wxMenuItem* m_menuItemUndo;
    wxMenuItem* m_menuItemRedo;
    wxMenuItem* m_menuItemLabelCurrentState;
    wxMenuItem* m_menuItem100;
    wxMenuItem* m_menuItemRename;
    wxMenuItem* m_menuItemSeparator_1;
    wxMenuItem* m_menuItemPreferences;
    wxMenu* m_menuSearch;
    wxMenuItem* m_menuItemFind;
    wxMenu* m_menuBuild;
    wxMenuItem* m_menuItemBuild;
    wxMenu* m_menuImport;
    wxMenuItem* m_menuItemFB;
    wxMenuItem* m_menuItemSmith;
    wxMenuItem* m_menuItemXRC;
    wxMenu* m_menuCustomControl;
    wxMenuItem* m_menuItemNewCustomControl;
    wxMenuItem* m_menuItemEditCustomControl;
    wxMenuItem* m_menuItemDeleteCustonControl;
    wxMenu* m_menuHelp;
    wxMenuItem* m_menuItemAbout;

protected:
    virtual void OnCloseFrame(wxCloseEvent& event) { event.Skip(); }
    virtual void OnFileOpen(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSave(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSaveUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnGenerateCode(wxCommandEvent& event) { event.Skip(); }
    virtual void OnGenerateCodeUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnBatchGenerateCode(wxCommandEvent& event) { event.Skip(); }
    virtual void OnBatchGenerateCodeUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnHide(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPreview(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPreviewUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnDeleteItem(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteItemUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnCopy(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSelectionUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnPaste(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPasteUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnCut(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUndo(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUndoUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnRedo(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRedoUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnRename(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSettings(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOpenFindDialog(wxCommandEvent& event) { event.Skip(); }
    virtual void OnBuild(wxCommandEvent& event) { event.Skip(); }
    virtual void OnBuildUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnImportFB(wxCommandEvent& event) { event.Skip(); }
    virtual void OnImportSmith(wxCommandEvent& event) { event.Skip(); }
    virtual void OnImportXRC(wxCommandEvent& event) { event.Skip(); }
    virtual void OnNewCustomControl(wxCommandEvent& event) { event.Skip(); }
    virtual void OnEditCustomControl(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteCustomControl(wxCommandEvent& event) { event.Skip(); }
    virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }

public:
    clToolBar* GetMainToolbar() { return m_mainToolbar; }
    wxPanel* GetSplitterPageTreeView() { return m_splitterPageTreeView; }
    wxPanel* GetSplitterPageDesigner() { return m_splitterPageDesigner; }
    wxSplitterWindow* GetSplitterMain() { return m_splitterMain; }
    wxPanel* GetMainPanel() { return m_MainPanel; }
    wxStatusBar* GetStatusBar() { return m_statusBar; }
    wxMenuBar* GetMenuBar() { return m_menuBar; }
    MainFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("wxCrafter"),
                  const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                  long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
    virtual ~MainFrameBase();
};

class GUICraftMainPanelBase : public wxPanel
{
protected:
    wxPanel* m_panelRightSidebar;
    wxSplitterWindow* m_mainSplitter;
    wxPanel* m_panelDesigner;
    OutputNBook* m_mainBook;
    wxPanel* m_designerNBPage;
    wxPanel* m_panelToolBox;
    wxAuiToolBar* m_toolbar;
    DesignerPanel* m_dp;
    wxPanel* m_cppNBPage;
    wxNotebook* m_notebookCpp;
    wxPanel* m_cppPage;
    wxStyledTextCtrl* m_textCtrlCppSource;
    wxPanel* m_headerPage;
    wxStyledTextCtrl* m_textCtrlHeaderSource;
    wxPanel* m_xrcNBPage;
    wxStyledTextCtrl* m_textCtrlXrc;
    wxPanel* m_panel10;
    wxNotebook* m_notebook2;
    wxPanel* m_pageProps;
    wxPanel* m_panelProperties;
    wxPanel* m_panelStyles;
    wxPropertyGridManager* m_pgMgrStyles;
    wxPanel* m_panelSizerFlags;
    wxPropertyGridManager* m_pgMgrSizerFlags;
    wxPanel* m_panelAuiPaneInfo;
    wxPropertyGridManager* m_pgMgrAuiProperties;

protected:
    virtual void OnPageChanged(wxBookCtrlEvent& event) { event.Skip(); }
    virtual void OnCppBookPageChanged(wxBookCtrlEvent& event) { event.Skip(); }
    virtual void OnStylesChanged(wxPropertyGridEvent& event) { event.Skip(); }
    virtual void OnSizerFlagsChanged(wxPropertyGridEvent& event) { event.Skip(); }
    virtual void OnSizerFlagsUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnAuiPaneInfoChanged(wxPropertyGridEvent& event) { event.Skip(); }

public:
    wxPanel* GetPanelToolBox() { return m_panelToolBox; }
    wxAuiToolBar* GetToolbar() { return m_toolbar; }
    DesignerPanel* GetDp() { return m_dp; }
    wxPanel* GetDesignerNBPage() { return m_designerNBPage; }
    wxStyledTextCtrl* GetTextCtrlCppSource() { return m_textCtrlCppSource; }
    wxPanel* GetCppPage() { return m_cppPage; }
    wxStyledTextCtrl* GetTextCtrlHeaderSource() { return m_textCtrlHeaderSource; }
    wxPanel* GetHeaderPage() { return m_headerPage; }
    wxNotebook* GetNotebookCpp() { return m_notebookCpp; }
    wxPanel* GetCppNBPage() { return m_cppNBPage; }
    wxStyledTextCtrl* GetTextCtrlXrc() { return m_textCtrlXrc; }
    wxPanel* GetXrcNBPage() { return m_xrcNBPage; }
    OutputNBook* GetMainBook() { return m_mainBook; }
    wxPanel* GetPanelDesigner() { return m_panelDesigner; }
    wxPanel* GetPanelProperties() { return m_panelProperties; }
    wxPanel* GetPageProps() { return m_pageProps; }
    wxPropertyGridManager* GetPgMgrStyles() { return m_pgMgrStyles; }
    wxPanel* GetPanelStyles() { return m_panelStyles; }
    wxPropertyGridManager* GetPgMgrSizerFlags() { return m_pgMgrSizerFlags; }
    wxPanel* GetPanelSizerFlags() { return m_panelSizerFlags; }
    wxPropertyGridManager* GetPgMgrAuiProperties() { return m_pgMgrAuiProperties; }
    wxPanel* GetPanelAuiPaneInfo() { return m_panelAuiPaneInfo; }
    wxNotebook* GetNotebook2() { return m_notebook2; }
    wxPanel* GetPanel10() { return m_panel10; }
    wxSplitterWindow* GetMainSplitter() { return m_mainSplitter; }
    wxPanel* GetPanelRightSidebar() { return m_panelRightSidebar; }
    GUICraftMainPanelBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                          const wxSize& size = wxSize(-1, -1), long style = wxTAB_TRAVERSAL);
    virtual ~GUICraftMainPanelBase();
};

class PropertiesSheetBase : public wxPanel
{
protected:
    wxScrolledWindow* m_mainPanel;

protected:
public:
    wxScrolledWindow* GetMainPanel() { return m_mainPanel; }
    PropertiesSheetBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxSize(-1, -1), long style = wxTAB_TRAVERSAL);
    virtual ~PropertiesSheetBase();
};

class EnterStringsDlgBase : public wxDialog
{
protected:
    wxStaticText* m_staticTextMessage;
    wxStyledTextCtrl* m_stc;
    wxStdDialogButtonSizer* m_stdBtnSizer234;
    wxButton* m_button236;
    wxButton* m_button238;

protected:
public:
    wxStaticText* GetStaticTextMessage() { return m_staticTextMessage; }
    wxStyledTextCtrl* GetStc() { return m_stc; }
    EnterStringsDlgBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Enter Text"),
                        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                        long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    virtual ~EnterStringsDlgBase();
};

class ColorPaletteDlgBase : public wxDialog
{
protected:
    wxPanel* m_panel11;
    wxButton* m_button6;
    wxButton* m_button7;

protected:
public:
    wxPanel* GetPanel11() { return m_panel11; }
    wxButton* GetButton6() { return m_button6; }
    wxButton* GetButton7() { return m_button7; }
    ColorPaletteDlgBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Color"),
                        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                        long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~ColorPaletteDlgBase();
};

class ColourPickerDlgbase : public wxDialog
{
protected:
    wxChoice* m_choiceStandardColors;
    wxButton* m_button5;
    wxPanel* m_panelColorPreview;
    wxButton* m_button8;
    wxButton* m_button11;

protected:
    virtual void OnStandardColorSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSelectColor(wxCommandEvent& event) { event.Skip(); }
    virtual void OnErasePreviewColor(wxEraseEvent& event) { event.Skip(); }
    virtual void OnPaintPreviewColor(wxPaintEvent& event) { event.Skip(); }

public:
    wxChoice* GetChoiceStandardColors() { return m_choiceStandardColors; }
    wxButton* GetButton5() { return m_button5; }
    wxPanel* GetPanelColorPreview() { return m_panelColorPreview; }
    wxButton* GetButton8() { return m_button8; }
    wxButton* GetButton11() { return m_button11; }
    ColourPickerDlgbase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Colour..."),
                        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                        long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~ColourPickerDlgbase();
};

class wxcSettingsDlgBase : public wxDialog
{
protected:
    wxCheckBox* m_checkBoxUseTRay;
    wxCheckBox* m_checkBoxFormatInheritedFiles;
    wxStaticText* m_staticText215;
    wxCheckBox* m_checkBoxKeepAllUsersetNames;
    wxCheckBox* m_checkBoxKeepAllPossibleNames;
    wxCheckBox* m_checkBoxCopyEventhandlerToo;
    wxStdDialogButtonSizer* m_stdBtnSizer264;
    wxButton* m_button266;
    wxButton* m_button268;

protected:
    virtual void OnMinimizeToTrayUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnOk(wxCommandEvent& event) { event.Skip(); }

public:
    wxCheckBox* GetCheckBoxUseTRay() { return m_checkBoxUseTRay; }
    wxCheckBox* GetCheckBoxFormatInheritedFiles() { return m_checkBoxFormatInheritedFiles; }
    wxStaticText* GetStaticText215() { return m_staticText215; }
    wxCheckBox* GetCheckBoxKeepAllUsersetNames() { return m_checkBoxKeepAllUsersetNames; }
    wxCheckBox* GetCheckBoxKeepAllPossibleNames() { return m_checkBoxKeepAllPossibleNames; }
    wxCheckBox* GetCheckBoxCopyEventhandlerToo() { return m_checkBoxCopyEventhandlerToo; }
    wxcSettingsDlgBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("wxCrafter Settings"),
                       const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                       long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    virtual ~wxcSettingsDlgBase();
};

class CaptionBarBase : public wxPanel
{
protected:
protected:
    virtual void OnPaint(wxPaintEvent& event) { event.Skip(); }
    virtual void OnEraseBG(wxEraseEvent& event) { event.Skip(); }
    virtual void OnLeftDown(wxMouseEvent& event) { event.Skip(); }

public:
    CaptionBarBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxSize(150, 24), long style = wxTAB_TRAVERSAL);
    virtual ~CaptionBarBase();
};

class wxcImages : public wxImageList
{
protected:
    // Maintain a map of all bitmaps representd by their name
    std::map<wxString, wxBitmap> m_bitmaps;
    // The requested image resolution (can be one of @2x, @1.5x, @1.25x or an empty string (the default)
    wxString m_resolution;
    int m_imagesWidth;
    int m_imagesHeight;

protected:
public:
    wxcImages();
    const wxBitmap& Bitmap(const wxString& name) const
    {
        if(!m_bitmaps.count(name + m_resolution))
            return wxNullBitmap;
        return m_bitmaps.find(name + m_resolution)->second;
    }

    void SetBitmapResolution(const wxString& res = wxEmptyString) { m_resolution = res; }

    virtual ~wxcImages();
};

#endif
