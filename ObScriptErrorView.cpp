
#include "stdafx.h"
#include "obedit.h"
#include "ObScriptErrorView.h"
#include "ObScptView.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CObScriptErrorView, CFormView)


BEGIN_MESSAGE_MAP(CObScriptErrorView, CFormView)
	//{{AFX_MSG_MAP(CObScriptErrorView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_ERRORTEXT, OnDblclkErrortext)
	ON_NOTIFY(EN_MSGFILTER, IDC_ERRORTEXT, OnMsgfilterErrortext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CObScriptErrorView::CObScriptErrorView() : CFormView(CObScriptErrorView::IDD) {
  //{{AFX_DATA_INIT(CObScriptErrorView)
  //}}AFX_DATA_INIT

  m_pScriptView = NULL;
  m_HasDblClick = false;
}


CObScriptErrorView::~CObScriptErrorView() {

}


void CObScriptErrorView::DoDataExchange(CDataExchange* pDX) {
  CFormView::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObScriptErrorView)
  DDX_Control(pDX, IDC_ERRORTEXT, m_ErrorText);
  //}}AFX_DATA_MAP
}


#ifdef _DEBUG
void CObScriptErrorView::AssertValid() const {
	CFormView::AssertValid();
}

void CObScriptErrorView::Dump(CDumpContext& dc) const {
	CFormView::Dump(dc);
}
#endif


void CObScriptErrorView::OnSize(UINT nType, int cx, int cy) {
  CFormView::OnSize(nType, cx, cy);
	
  if (IsWindow(m_ErrorText.m_hWnd)) {
    m_ErrorText.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE);
  }
	
}


void CObScriptErrorView::OnInitialUpdate() {
  CFormView::OnInitialUpdate();

  SetScrollSizes(MM_TEXT, CSize(0,0));

  m_ErrorText.SetEventMask(ENM_MOUSEEVENTS);

  m_ErrorText.SetWindowText("Compiler errors and warnings list. Double-click an entry to jump to that point in the script.");
}


void CObScriptErrorView::ClearErrors (void) {
  m_ErrorText.SetWindowText("");
}


void CObScriptErrorView::AddErrors (CObScriptErrorArray& Errors) {
  dword Index;

  for (Index = 0; Index < Errors.GetSize(); ++Index) {
    AddError(Errors.GetAt(Index));
  }

}


void CObScriptErrorView::AddError (CObScriptError* pError) {
  CString Buffer;
  int     Length;
  int     LineNumber;

	/* Ignore invalid input */
  if (pError == NULL) return;

  Length     = m_ErrorText.GetWindowTextLength();
  LineNumber = m_ErrorText.LineFromChar(Length);
  pError->SetUserData(LineNumber);

  Buffer = pError->MakeErrorString();
  Buffer += "\r\n";
 
  m_ErrorText.SetSel(Length, Length);
  m_ErrorText.ReplaceSel(Buffer);
}


void CObScriptErrorView::AddMessage (const char* pString, ...) {
  CString Buffer;
  va_list Args;
  int     Length;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  Buffer += "\r\n";
  va_end(Args);

  Length = m_ErrorText.GetWindowTextLength();
  m_ErrorText.SetSel(Length, Length);
  m_ErrorText.ReplaceSel(Buffer);
}


CObScriptError* CObScriptErrorView::FindErrorFromLine (const int Line) {
  CObScriptError* pError;
  dword           Index;

  if (m_pScriptView == NULL) return (NULL);

  for (Index = 0; Index < m_pScriptView->GetCompiler().GetErrors().GetSize(); ++Index) {
    pError = m_pScriptView->GetCompiler().GetErrors().GetAt(Index);
    if (pError->GetUserData() == Line) return (pError);
  }

  return (NULL);
}


void CObScriptErrorView::OnDblclkErrortext(NMHDR* pNMHDR, LRESULT* pResult) {
  CObScriptError* pError;
  long            StartSel;
  long            EndSel;
  int             LineNumber;

  *pResult = 0;

  m_ErrorText.GetSel(StartSel, EndSel);
  if (StartSel < 0) return;
  if (m_pScriptView == NULL) return;

  LineNumber = m_ErrorText.LineFromChar(StartSel);
    
  pError = FindErrorFromLine(LineNumber);
  if (pError == NULL) return;

  m_pScriptView->SelectFromError(pError);
}


void CObScriptErrorView::OnMsgfilterErrortext(NMHDR* pNMHDR, LRESULT* pResult) {
  MSGFILTER *pMsgFilter = reinterpret_cast<MSGFILTER *>(pNMHDR);

  switch (pMsgFilter->msg) {
    case WM_LBUTTONDOWN:
	m_HasDblClick = false;
	break;
    case WM_LBUTTONUP:
	if (m_HasDblClick) {
	  m_HasDblClick = false;
	  OnDblclkErrortext(pNMHDR, pResult);
	}
	break;
    case WM_LBUTTONDBLCLK:
	m_HasDblClick = true;
	break;
  }

  *pResult = 0;
}
