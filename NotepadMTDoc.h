// NotepadMTDoc.h : interface of the CNotepadMTDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEPADMTDOC_H__F186A660_BE60_408A_A096_8548593374BE__INCLUDED_)
#define AFX_NOTEPADMTDOC_H__F186A660_BE60_408A_A096_8548593374BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNotepadMTDoc : public CDocument, public CUndo
{
protected: // create from serialization only
	CNotepadMTDoc();
	DECLARE_DYNCREATE(CNotepadMTDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadMTDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNotepadMTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNotepadMTDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPADMTDOC_H__F186A660_BE60_408A_A096_8548593374BE__INCLUDED_)
