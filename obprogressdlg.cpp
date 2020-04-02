/*===========================================================================
 *
 * File:	Obprogressdlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 29, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "common/oberrorhandler.h"
#include "resource.h"
#include "ObProgressDlg.h"
#include "common/oblogfile.h"


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
 * Begin CObProgressDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CObProgressDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObProgressDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditDefaultProgressCallback (pData);
 *
 * Default progress update callback.
 *
 *=========================================================================*/
int ObEditDefaultProgressCallback (CObCallback* pCallback) {
  CObProgressDlg* pProgressView;

  if (pCallback == NULL) return (OBCALLBACK_INVALIDINPUT);

  pProgressView = (CObProgressDlg *) pCallback->GetUserPtr();
  if (pProgressView == NULL) return (OBCALLBACK_INVALIDINPUT);
    

  if (pCallback->GetUpdateTitle()) {
    pProgressView->UpdateTitle(pCallback->GetTitle());  
    pCallback->SetUpdateTitle(false);
  }

  if (pCallback->GetUpdateLabel()) {
    pProgressView->UpdateLabel(pCallback->GetLabel());  
    pCallback->SetUpdateLabel(false);
  }

  pProgressView->Update(pCallback->GetPercentDone());

  if (pProgressView->GetIsCancelled()) {
    return (OBCALLBACK_USERABORT);
  }

  return (OBCALLBACK_OK);
}
/*===========================================================================
 *		End of Function ObEditDefaultProgressCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Constructor
 *
 *=========================================================================*/
CObProgressDlg::CObProgressDlg (const TCHAR* pTitle, const TCHAR* pLabel) : CDialog(CObProgressDlg::IDD, NULL) {
  //{{AFX_DATA_INIT(CObProgressDlg)
  //}}AFX_DATA_INIT

  m_Title        = pTitle;
  m_CancelMsg    = _T("Are you sure you wish to abort?");
  m_Label        = pLabel;

  m_AllowCancel  = true;
  m_PromptCancel = false;
  m_RunAsModal   = true;
  m_IsCancelled  = false;

  	/* Disable the application window if required */
  if (m_RunAsModal) AfxGetMainWnd()->EnableWindow(FALSE);
    
  Create(CObProgressDlg::IDD, NULL);
  ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class CObProgressDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObProgressDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObProgressDlg)
  DDX_Control(pDX, IDC_FILE_PERCENT, m_PercentLabel);
  DDX_Control(pDX, IDC_FILE_PROGRESS, m_ProgressCtrl);
  DDX_Control(pDX, IDC_FILE_LABEL, m_LabelText);
  DDX_Control(pDX, IDCANCEL, m_CancelButton);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObProgressDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Event - void OnCancel (void);
 *
 *=========================================================================*/
void CObProgressDlg::OnCancel (void) {
  int Result;

  if (!m_AllowCancel) return;

  if (m_PromptCancel) {
    Result = MessageBox(m_CancelMsg, _T("Cancel Operation"), MB_YESNO | MB_ICONEXCLAMATION);
    if (Result != IDYES) return;
  }

  AddObGeneralError("Action aborted by user!");
  m_IsCancelled = true;
  //CDialog::OnCancel();
}
/*===========================================================================
 *		End of Class Event CObProgressDlg::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Event - void OnDestroy (void);
 *
 *=========================================================================*/
void CObProgressDlg::OnDestroy (void) {

	/* Enable the application window if required */
  if (m_RunAsModal) AfxGetMainWnd()->EnableWindow(FALSE);

  CDialog::OnDestroy();
}
/*===========================================================================
 *		End of Class Event CObProgressDlg::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObProgressDlg::OnInitDialog() {

	/* Call the base class event */
  CDialog::OnInitDialog();

	/* Initialize the controls */
  m_ProgressCtrl.SetRange(0, 100);
  m_ProgressCtrl.SetPos(0);
  m_CancelButton.ShowWindow(m_AllowCancel ? SW_SHOW : SW_HIDE);

  UpdateControls();
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObProgressDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Method - BOOL Pump (void);
 *
 *=========================================================================*/
BOOL CObProgressDlg::Pump (void) {
  MSG msg;

  while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE)) {
    if (!AfxGetApp()->PumpMessage()) {
      ::PostQuitMessage(0);
      return FALSE;
    }
  }

	/* Simulate the framework's idle processing mechanism */
  LONG lIdle = 0;

  while (AfxGetApp()->OnIdle(lIdle++));

  return TRUE;
}
/*===========================================================================
 *		End of Class Method CObProgressDlg::Pump()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Method - void SetProgress (Progress);
 *
 *=========================================================================*/
void CObProgressDlg::SetProgress (const float Progress) {
  CString Buffer;

  m_ProgressCtrl.SetPos((int)Progress);

  Buffer.Format(_T("%d%%"), (int)Progress);
  m_PercentLabel.SetWindowText(Buffer);

  m_ProgressCtrl.UpdateWindow();
  m_PercentLabel.UpdateWindow();
}
/*===========================================================================
 *		End of Class Method CObProgressDlg::SetProgress()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Method - void UpdateControls (void);
 *
 *=========================================================================*/
void CObProgressDlg::UpdateControls (void) {
  SetWindowText(m_Title);
  m_LabelText.SetWindowText(m_Label);
}
/*===========================================================================
 *		End of Class Method CObProgressDlg::UpdateControls()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Method - void UpdateLabel (pString);
 *
 *=========================================================================*/
void CObProgressDlg::UpdateLabel (const TCHAR* pString) {
  m_LabelText.SetWindowText(pString);
  m_LabelText.RedrawWindow();
}
/*===========================================================================
 *		End of Class Method CObProgressDlg::UpdateLabel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Method - void UpdateTitle (pString);
 *
 *=========================================================================*/
void CObProgressDlg::UpdateTitle (const TCHAR* pString) {
  SetWindowText(pString);
  RedrawWindow();
}
/*===========================================================================
 *		End of Class Method CObProgressDlg::UpdateTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObProgressDlg Method - void Update (Percent);
 *
 * Main progress update callback. Updates the progress and pumps any
 * waiting messages.
 *
 *=========================================================================*/
void CObProgressDlg::Update (const float Percent) {
  SetProgress(Percent);

  Pump();
}
/*===========================================================================
 *		End of Class Method CObProgressDlg::Update()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CObProgressDlg* ShowObProgressDlg (pTitle, pLabel, ...);
 *
 * Creates and displays a new progress dialog. Ensure to destroy the
 * dialog using the DestroyObProgressDlg() function.
 *
 *=========================================================================*/
CObProgressDlg* ShowObProgressDlg (const TCHAR* pTitle, const TCHAR* pLabel, ...) {
  CObProgressDlg* pProgressDlg;
  CString	  Buffer;
  va_list	  Args;
  
  va_start(Args, pLabel);
  Buffer.FormatV(pLabel, Args);
  va_end(Args);

  pProgressDlg = new CObProgressDlg(pTitle, Buffer);

  return (pProgressDlg);
}
/*===========================================================================
 *		End of Function ShowObProgressDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void DestroyObProgressDlg (pProgressDlg);
 *
 * Closes and destroys a progress dialog created by ShowObProgressDlg().
 *
 *=========================================================================*/
void DestroyObProgressDlg (CObProgressDlg* pProgressDlg) {

  if (pProgressDlg != NULL) {
    pProgressDlg->EndDialog(IDOK);
    delete pProgressDlg;
  }

}
/*===========================================================================
 *		End of Function DestroyObProgressDlg()
 *=========================================================================*/
