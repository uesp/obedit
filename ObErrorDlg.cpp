/*===========================================================================
 *
 * File:	Oberrordlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 31, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObErrorDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObErrorDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObErrorDlg, CDialog)
  //{{AFX_MSG_MAP(CObErrorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObErrorDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorDlg Constructor
 *
 *=========================================================================*/
CObErrorDlg::CObErrorDlg(CWnd* pParent)	: CDialog(CObErrorDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CObErrorDlg)
  //}}AFX_DATA_INIT

  m_Flags       = 0;
  m_OutputCount = 0;
}
/*===========================================================================
 *		End of Class CObErrorDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorDlg Method - void AddErrorInfo (pError, ErrorIndex);
 *
 *=========================================================================*/
void CObErrorDlg::AddErrorInfo (CObError* pError, const int ErrorIndex) {
  CString Buffer;
  CString IndexBuffer;
  int     Length;

  if (ErrorIndex >= 0) IndexBuffer.Format(_T("%d) "), ErrorIndex);

	/* Check for no error information */
  if (pError == NULL) {
    Buffer.Format(_T("%sNo Error!\r\n"), ErrorIndex >= 0 ? IndexBuffer : _T(""));
  }
	/* Fill in error information */
  else {
    CSString ErrorString = pError->GetErrorString();

    Buffer.Format(_T("%s%s\r\n%s%s%s"), ErrorIndex >= 0 ? IndexBuffer : _T(""), pError->GetErrorMessage(), 
	ErrorString.IsEmpty() ? _T("") : _T("\t"),
	ErrorString.c_str(), ErrorString.IsEmpty() ? _T("") : _T("\r\n"));

    ++m_OutputCount;
  }

  Length = m_ErrorDetails.GetWindowTextLength();
  m_ErrorDetails.SetSel(Length, Length, TRUE);
  m_ErrorDetails.ReplaceSel(Buffer, FALSE);
}
/*===========================================================================
 *		End of Class Method CObErrorDlg::AddErrorInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorDlg Method - void AddLastError (void);
 *
 *=========================================================================*/
void CObErrorDlg::AddLastError (void) {
  CObError* pError;

  pError = ObErrorHandler->GetLastError();
  if (pError != NULL) pError->SetTag(1);
  AddErrorInfo(pError, -1);

}
/*===========================================================================
 *		End of Class Method CObErrorDlg::AddLastError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorDlg Method - void AddAllErrors (void);
 *
 *=========================================================================*/
void CObErrorDlg::AddAllErrors (void) {
  CObError* pError;
  dword     Index;

  for (Index = 0; Index < ObErrorHandler->GetNumErrors(); ++Index) {
    pError = ObErrorHandler->GetError(Index);
    pError->SetTag(1);
    AddErrorInfo(pError, Index + 1);
  }

}
/*===========================================================================
 *		End of Class Method CObErrorDlg::AddAllErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorDlg Method - void AddAllUntaggedErrors (void);
 *
 *=========================================================================*/
void CObErrorDlg::AddAllUntaggedErrors (void) {
  CObError* pError;
  dword     Index;
  dword     Count = 0;

  for (Index = 0; Index < ObErrorHandler->GetNumErrors(); ++Index) {
    pError = ObErrorHandler->GetError(Index);
    if (pError->GetTag() > 0) continue;
    pError->SetTag(1);
    ++Count;
    AddErrorInfo(pError, Count);
  }

}
/*===========================================================================
 *		End of Class Method CObErrorDlg::AddAllUntaggedErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObErrorDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObErrorDlg)
  DDX_Control(pDX, IDC_DETAILS, m_ErrorDetails);
  DDX_Control(pDX, IDC_MESSAGE, m_ErrorMessage);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObErrorDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObErrorDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  if (m_Title.IsEmpty()) m_Title = _T("ObEdit Error");
  SetWindowText(m_Title);
  m_ErrorMessage.SetWindowText(m_Message);

  if ((m_Flags & OBERRDLG_SHOWALLERRORS) != 0) {
    AddAllErrors();
  }
  else if ((m_Flags & OBERRDLG_SHOWUNTAGGEDERRORS) != 0) {
    AddAllUntaggedErrors();
  }
  else {
    AddLastError();
  }
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObErrorDlg::OnInitDialog()
 *=========================================================================*/
