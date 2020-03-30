// NotepadMT.h : main header file for the NOTEPADMT application
//

#if !defined(AFX_NOTEPADMT_H__2BA24494_4685_4BC4_999E_240BF9EF3BF8__INCLUDED_)
#define AFX_NOTEPADMT_H__2BA24494_4685_4BC4_999E_240BF9EF3BF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTApp:
// See NotepadMT.cpp for the implementation of this class
//

class CNotepadMTApp : public CWinApp
{
public:
	CNotepadMTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadMTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNotepadMTApp)
	afx_msg void OnAppAbout();
	afx_msg void OnPageDialog();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPADMT_H__2BA24494_4685_4BC4_999E_240BF9EF3BF8__INCLUDED_)
