/*===========================================================================
 *
 * File:	Obpromptdlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 26, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObPromptDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObPromptDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObPromptDlg, CDialog)
	//{{AFX_MSG_MAP(CObPromptDlg)
	ON_BN_CLICKED(ID_BUTTON1, OnButton1)
	ON_BN_CLICKED(ID_BUTTON2, OnButton2)
	ON_BN_CLICKED(ID_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObPromptDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPromptDlg Constructor
 *
 *=========================================================================*/
CObPromptDlg::CObPromptDlg(CWnd* pParent) : CDialog(CObPromptDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CObPromptDlg)
	//}}AFX_DATA_INIT
	m_SelectedButton = 0;
}
/*===========================================================================
 *		End of Class CObPromptDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPromptDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObPromptDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObPromptDlg)
	DDX_Control(pDX, IDC_LABEL, m_PromptLabel);
	DDX_Control(pDX, ID_BUTTON3, m_Button3);
	DDX_Control(pDX, ID_BUTTON2, m_Button2);
	DDX_Control(pDX, ID_BUTTON1, m_Button1);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObPromptDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPromptDlg Event - void OnButton1 ();
 *
 *=========================================================================*/
void CObPromptDlg::OnButton1() {
  m_SelectedButton = 1;
  EndDialog(IDOK);
}
/*===========================================================================
 *		End of Class Event CObPromptDlg::OnButton1()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPromptDlg Event - void OnButton2 ();
 *
 *=========================================================================*/
void CObPromptDlg::OnButton2() {
  m_SelectedButton = 2;
  EndDialog(IDOK);
}
/*===========================================================================
 *		End of Class Event CObPromptDlg::OnButton2()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPromptDlg Event - void OnButton3 ();
 *
 *=========================================================================*/
void CObPromptDlg::OnButton3() {
  m_SelectedButton = 3;
  EndDialog(IDOK);
}
/*===========================================================================
 *		End of Class Event CObPromptDlg::OnButton3()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPromptDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObPromptDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  SetWindowText(m_Title);
  m_PromptLabel.SetWindowText(m_Label);

  m_Button1.SetWindowText(m_Button1Text);
  m_Button2.SetWindowText(m_Button2Text);
  m_Button3.SetWindowText(m_Button3Text);

  m_Button1.ShowWindow(m_Button1Text.IsEmpty() ? SW_HIDE : SW_SHOW);
  m_Button2.ShowWindow(m_Button2Text.IsEmpty() ? SW_HIDE : SW_SHOW);
  m_Button3.ShowWindow(m_Button3Text.IsEmpty() ? SW_HIDE : SW_SHOW);
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObPromptDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPromptDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CObPromptDlg::OnOK (void) {
  m_SelectedButton = 1;
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObPromptDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ShowObOkDlg (pTitle, pLabel);
 *
 *=========================================================================*/
void ShowObOkDlg (const TCHAR* pTitle, const TCHAR* pLabel) {
  ShowObPromptDlg(pTitle, pLabel, "Ok");
}
/*===========================================================================
 *		End of Function ShowObOkDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ShowObYesNoDlg (pTitle, pLabel);
 *
 *=========================================================================*/
bool ShowObYesNoDlg (const TCHAR* pTitle, const TCHAR* pLabel) {
  return ShowObPromptDlg(pTitle, pLabel, "Yes", "No") == 1;
}
/*===========================================================================
 *		End of Function ShowObYesNoDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ShowObOkCancelDlg (pTitle, pLabel);
 *
 *=========================================================================*/
bool ShowObOkCancelDlg (const TCHAR* pTitle, const TCHAR* pLabel) {
  return ShowObPromptDlg(pTitle, pLabel, "Ok", "Cancel") == 1;
}
/*===========================================================================
 *		End of Function ShowObOkCancelDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ShowObPromptDlg (pTitle, pLabel, pButton1, pButton2, pButton3);
 *
 *=========================================================================*/
int ShowObPromptDlg (const TCHAR* pTitle, const TCHAR* pLabel, const TCHAR* pButton1, const TCHAR* pButton2, const TCHAR* pButton3) {
  CObPromptDlg	Dlg;
  int		Result;

  Dlg.SetTitle(pTitle);
  Dlg.SetLabel(pLabel);
  Dlg.SetButton1(pButton1);
  Dlg.SetButton2(pButton2);
  Dlg.SetButton3(pButton3);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (0);

  return Dlg.GetSelectedButton();
}
/*===========================================================================
 *		End of Function ShowObPromptDlg()
 *=========================================================================*/
