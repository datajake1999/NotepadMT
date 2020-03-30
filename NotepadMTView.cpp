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
