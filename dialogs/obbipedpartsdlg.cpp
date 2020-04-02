/*===========================================================================
 *
 * File:	Obbipedpartsdlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 25, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obbipedpartsdlg.h"


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
 * Begin CObBipedPartsDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObBipedPartsDlg, CDialog)
	//{{AFX_MSG_MAP(CObBipedPartsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObBipedPartsDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsDlg Constructor
 *
 *=========================================================================*/
CObBipedPartsDlg::CObBipedPartsDlg(CWnd* pParent) : CDialog(CObBipedPartsDlg::IDD, pParent) {
  m_BipedParts = 0;

  //{{AFX_DATA_INIT(CObBipedPartsDlg)
  //}}AFX_DATA_INIT
}
/*===========================================================================
 *		End of Class CObBipedPartsDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObBipedPartsDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObBipedPartsDlg)
  DDX_Control(pDX, IDC_BIPEDPART_1,  m_BipedButtons[0]);
  DDX_Control(pDX, IDC_BIPEDPART_2,  m_BipedButtons[1]);
  DDX_Control(pDX, IDC_BIPEDPART_3,  m_BipedButtons[2]);
  DDX_Control(pDX, IDC_BIPEDPART_4,  m_BipedButtons[3]);
  DDX_Control(pDX, IDC_BIPEDPART_5,  m_BipedButtons[4]);
  DDX_Control(pDX, IDC_BIPEDPART_6,  m_BipedButtons[5]);
  DDX_Control(pDX, IDC_BIPEDPART_7,  m_BipedButtons[6]);
  DDX_Control(pDX, IDC_BIPEDPART_8,  m_BipedButtons[7]);
  DDX_Control(pDX, IDC_BIPEDPART_9,  m_BipedButtons[8]);
  DDX_Control(pDX, IDC_BIPEDPART_10, m_BipedButtons[9]);
  DDX_Control(pDX, IDC_BIPEDPART_11, m_BipedButtons[10]);
  DDX_Control(pDX, IDC_BIPEDPART_12, m_BipedButtons[11]);
  DDX_Control(pDX, IDC_BIPEDPART_13, m_BipedButtons[12]);
  DDX_Control(pDX, IDC_BIPEDPART_14, m_BipedButtons[13]);
  DDX_Control(pDX, IDC_BIPEDPART_15, m_BipedButtons[14]);
  DDX_Control(pDX, IDC_BIPEDPART_16, m_BipedButtons[15]);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObBipedPartsDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObBipedPartsDlg::GetControlData (void) {
  dword Index;
  dword Mask = 1;

  m_BipedParts = 0;

  for (Index = 0; Index < 16; ++Index) {
    m_BipedParts |= m_BipedButtons[Index].GetCheck() ? Mask : 0;
    Mask <<= 1;
  }

}
/*===========================================================================
 *		End of Class Method CObBipedPartsDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObBipedPartsDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  SetControlData();
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObBipedPartsDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CObBipedPartsDlg::OnOK (void) {
  GetControlData();

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObBipedPartsDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObBipedPartsDlg::SetControlData (void) {
  dword Index;
  dword Mask = 1;

  for (Index = 0; Index < 16; ++Index) {
    m_BipedButtons[Index].SetCheck((m_BipedParts & Mask) != 0);
    Mask <<= 1;
  }
  
}
/*===========================================================================
 *		End of Class Method CObBipedPartsDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObEditBipedParts (BipedParts);
 *
 *=========================================================================*/
bool ObEditBipedParts (dword& BipedParts) {
  CObBipedPartsDlg Dlg;
  int              Result;

  Dlg.SetBipedParts(BipedParts);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  BipedParts = Dlg.GetBipedParts();
  return (true);
}
/*===========================================================================
 *		End of Function ObEditBipedParts()
 *=========================================================================*/




