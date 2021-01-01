// NotepadMTView.cpp : implementation of the CNotepadMTView class
//

#include "stdafx.h"
#include "NotepadMT.h"

#include "NotepadMTDoc.h"
#include "NotepadMTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTView

IMPLEMENT_DYNCREATE(CNotepadMTView, CEditView)

BEGIN_MESSAGE_MAP(CNotepadMTView, CEditView)
	//{{AFX_MSG_MAP(CNotepadMTView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnClearDocument)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateClearDocument)
	ON_CONTROL_REFLECT(EN_CHANGE, OnEditChange)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_FORMAT_FONT, OnFormatFont)
	ON_COMMAND(ID_TTS_SPEAKDOC, OnSpeakDocument)
	ON_COMMAND(ID_TTS_SPEAKSEL, OnSpeakSelected)
	ON_COMMAND(ID_TTS_PAUSE, OnPauseResume)
	ON_COMMAND(ID_TTS_STOP, OnStopSpeech)
	ON_COMMAND(ID_TTS_CREATEWAV, OnCreateWAV)
	ON_COMMAND(ID_TTS_PLAYWAV, OnPlayWAV)
	ON_COMMAND(ID_TTS_RESET, OnResetSpeech)
	ON_COMMAND(ID_TTS_RATEUP, OnSpeakFaster)
	ON_COMMAND(ID_TTS_RATEDOWN, OnSpeakSlower)
	ON_COMMAND(ID_TTS_VOLUMEUP, OnSpeakLouder)
	ON_COMMAND(ID_TTS_VOLUMEDOWN, OnSpeakQuieter)
	ON_COMMAND(ID_TTS_XMLPROC, OnXMLProcessing)
	ON_UPDATE_COMMAND_UI(ID_TTS_XMLPROC, OnUpdateXMLProcessing)
	ON_COMMAND(ID_TTS_REWIND, OnRewind)
	ON_COMMAND(ID_TTS_FASTFORWARD, OnFastForward)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTView construction/destruction

CNotepadMTView::CNotepadMTView()
{
	// TODO: add construction code here

}

CNotepadMTView::~CNotepadMTView()
{
}

BOOL CNotepadMTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTView drawing

void CNotepadMTView::OnDraw(CDC* pDC)
{
	CNotepadMTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTView printing

BOOL CNotepadMTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CNotepadMTView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CNotepadMTView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CNotepadMTView::OnClearDocument()
{
	// Select all contents and delete
	CEditView::OnEditSelectAll();
	CEditView::OnEditClear();
}

void CNotepadMTView::OnUpdateClearDocument(CCmdUI* pCmdUI)
{
	// If the document is empty, the Clear Document menu item will be unavailable
	if (CEditView::GetBufferLength() != 0)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

BOOL CNotepadMTView::OnEditChange()
{
	CNotepadMTDoc* pDoc = GetDocument();
	pDoc->CheckPoint();
	return CEditView::OnEditChange();
}

void CNotepadMTView::OnEditUndo()
{
	CNotepadMTDoc* pDoc = GetDocument();
	pDoc->Undo();
}

void CNotepadMTView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	CNotepadMTDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanUndo());
}

void CNotepadMTView::OnEditRedo()
{
	CNotepadMTDoc* pDoc = GetDocument();
	pDoc->Redo();
}

void CNotepadMTView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	CNotepadMTDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanRedo());
}

void CNotepadMTView::OnFormatFont()
{
	CFont *font = GetFont();
	CFont *fontNew = new CFont;
	LOGFONT lf;
	if (font != NULL)
	{
		font->GetLogFont(&lf);
	}
	CFontDialog FontDialog(&lf);
	if (FontDialog.DoModal() == IDOK)
	{
		if (fontNew->CreateFontIndirect(&lf))
		{
			SetFont(fontNew);
		}
	}
}

void CNotepadMTView::OnSpeakDocument()
{
	CString text;
	GetWindowText(text);
	int strsize = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
	unsigned short *text2speak = new unsigned short[strsize];
	MultiByteToWideChar(CP_UTF8, 0, text, -1, text2speak, strsize);
	TTS.speak(text2speak);
}

void CNotepadMTView::OnSpeakSelected()
{
	CString text;
	GetSelectedText(text);
	int strsize = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
	unsigned short *text2speak = new unsigned short[strsize];
	MultiByteToWideChar(CP_UTF8, 0, text, -1, text2speak, strsize);
	TTS.speak(text2speak);
}

void CNotepadMTView::OnPauseResume()
{
	TTS.pauseResume();
}

void CNotepadMTView::OnStopSpeech()
{
	TTS.stop();
}

void CNotepadMTView::OnCreateWAV()
{
	CNotepadMTDoc* pDoc = GetDocument();
	TCHAR szFilters[] = _T("WAV Files (*.WAV)|*.WAV|All Files (*.*)|*.*||");
	CFileDialog fileDialog(FALSE, _T("WAV"), pDoc->GetTitle(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters);
	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		int strsize = MultiByteToWideChar(CP_UTF8, 0, pathName, -1, NULL, 0);
		unsigned short *filePath = new unsigned short[strsize];
		MultiByteToWideChar(CP_UTF8, 0, pathName, -1, filePath, strsize);
		CString text;
		GetWindowText(text);
		strsize = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
		unsigned short *text2speak = new unsigned short[strsize];
		MultiByteToWideChar(CP_UTF8, 0, text, -1, text2speak, strsize);
		TTS.speakToWAV(text2speak, filePath);
	}
}

void CNotepadMTView::OnPlayWAV()
{
	TCHAR szFilters[] = _T("WAV Files (*.WAV)|*.WAV|All Files (*.*)|*.*||");
	CFileDialog fileDialog(TRUE, _T("WAV"), _T("*.WAV"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		int strsize = MultiByteToWideChar(CP_UTF8, 0, pathName, -1, NULL, 0);
		unsigned short *filePath = new unsigned short[strsize];
		MultiByteToWideChar(CP_UTF8, 0, pathName, -1, filePath, strsize);
		TTS.playWAV(filePath);
	}
}

void CNotepadMTView::OnResetSpeech()
{
	TTS.reset();
}

void CNotepadMTView::OnSpeakFaster()
{
	TTS.rateUp();
}

void CNotepadMTView::OnSpeakSlower()
{
	TTS.rateDown();
}

void CNotepadMTView::OnSpeakLouder()
{
	TTS.volumeUp();
}

void CNotepadMTView::OnSpeakQuieter()
{
	TTS.volumeDown();
}

void CNotepadMTView::OnXMLProcessing()
{
	if (TTS.getXMLProcessing() == true)
	{
		TTS.setXMLProcessing(false);
		return;
	}
	TTS.setXMLProcessing(true);
}

void CNotepadMTView::OnUpdateXMLProcessing(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(TTS.getXMLProcessing());
}

void CNotepadMTView::OnRewind()
{
	TTS.rewind(1);
}

void CNotepadMTView::OnFastForward()
{
	TTS.fastForward(1);
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTView diagnostics

#ifdef _DEBUG
void CNotepadMTView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNotepadMTView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNotepadMTDoc* CNotepadMTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNotepadMTDoc)));
	return (CNotepadMTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTView message handlers
