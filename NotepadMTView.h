// NotepadMTView.h : interface of the CNotepadMTView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEPADMTVIEW_H__501F0A05_3119_4AF3_BF15_671A73A77F39__INCLUDED_)
#define AFX_NOTEPADMTVIEW_H__501F0A05_3119_4AF3_BF15_671A73A77F39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTTS.H"
#include "TTSID.H"

class CNotepadMTView : public CEditView
{
protected: // create from serialization only
	CNotepadMTView();
	DECLARE_DYNCREATE(CNotepadMTView)

// Attributes
public:
	CNotepadMTDoc* GetDocument();
	CTTS TTS;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadMTView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnClearDocument();
	virtual void OnUpdateClearDocument(CCmdUI* pCmdUI);
	virtual BOOL OnEditChange();
	virtual void OnEditUndo();
	virtual void OnUpdateEditUndo(CCmdUI* pCmdUI);
	virtual void OnEditRedo();
	virtual void OnUpdateEditRedo(CCmdUI* pCmdUI);
	virtual void OnFormatFont();
	virtual void OnSpeakDocument();
	virtual void OnSpeakSelected();
	virtual void OnPauseResume();
	virtual void OnStopSpeech();
	virtual void OnCreateWAV();
	virtual void OnPlayWAV();
	virtual void OnResetSpeech();
	virtual void OnSpeakFaster();
	virtual void OnSpeakSlower();
	virtual void OnSpeakLouder();
	virtual void OnSpeakQuieter();
	virtual void OnXMLProcessing();
	virtual void OnUpdateXMLProcessing(CCmdUI* pCmdUI);
	virtual void OnRewind();
	virtual void OnFastForward();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNotepadMTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNotepadMTView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NotepadMTView.cpp
inline CNotepadMTDoc* CNotepadMTView::GetDocument()
   { return (CNotepadMTDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPADMTVIEW_H__501F0A05_3119_4AF3_BF15_671A73A77F39__INCLUDED_)
