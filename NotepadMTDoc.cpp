// NotepadMTDoc.cpp : implementation of the CNotepadMTDoc class
//

#include "stdafx.h"
#include "NotepadMT.h"

#include "NotepadMTDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTDoc

IMPLEMENT_DYNCREATE(CNotepadMTDoc, CDocument)

BEGIN_MESSAGE_MAP(CNotepadMTDoc, CDocument)
	//{{AFX_MSG_MAP(CNotepadMTDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTDoc construction/destruction

CNotepadMTDoc::CNotepadMTDoc()
{
	// TODO: add one-time construction code here

}

CNotepadMTDoc::~CNotepadMTDoc()
{
}

BOOL CNotepadMTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	CheckPoint();
	return TRUE;
}

BOOL CNotepadMTDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	CheckPoint();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNotepadMTDoc serialization

void CNotepadMTDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

void CNotepadMTDoc::DeleteContents()
{
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTDoc diagnostics

#ifdef _DEBUG
void CNotepadMTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNotepadMTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNotepadMTDoc commands
