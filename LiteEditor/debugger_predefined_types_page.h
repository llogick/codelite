//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : debugger_predefined_types_page.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef __debugger_predefined_types_page__
#define __debugger_predefined_types_page__

/**
@file
Subclass of PreDefinedTypesPageBase, which is generated by wxFormBuilder.
*/

#include "Debugger/debuggersettings.h"
#include "debuggersettingsbasedlg.h"

/** Implementing PreDefinedTypesPageBase */
class PreDefinedTypesPage : public PreDefinedTypesPageBase
{
protected:
	long                    m_selectedItem;
	DebuggerPreDefinedTypes m_data;
	
protected:
	// Handlers for PreDefinedTypesPageBase events.
	void OnItemActivated( wxListEvent& event );
	void OnItemDeselected( wxListEvent& event );
	void OnItemSelected( wxListEvent& event );
	void OnNewShortcut( wxCommandEvent& event );
	void OnEditShortcut( wxCommandEvent& event );
	void OnDeleteShortcut( wxCommandEvent& event );
	
	void DoEditItem();
	void DoDeleteItem();
	
public:
	/** Constructor */
	PreDefinedTypesPage( wxWindow* parent, const DebuggerPreDefinedTypes& preDefTypes );
	DebuggerPreDefinedTypes GetPreDefinedTypes();
};

#endif // __debugger_predefined_types_page__
