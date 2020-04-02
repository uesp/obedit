/*===========================================================================
 *
 * File:	Obbipedpartslistdlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 26, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "ObBipedPartsListDlg.h"
#include "dialogs/obeditdlghandler.h"


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
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObBipedPartsListDlg, CDialog)
	//{{AFX_MSG_MAP(CObBipedPartsListDlg)
	ON_LBN_DBLCLK(IDC_BIPED_LIST, OnDblclkBipedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsListDlg Constructor
 *
 *=========================================================================*/
CObBipedPartsListDlg::CObBipedPartsListDlg(CWnd* pParent) : CDialog(CObBipedPartsListDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CObBipedPartsListDlg)
  //}}AFX_DATA_INIT
  m_BipedParts = 0;
}
/*===========================================================================
 *		End of Class CObBipedPartsListDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsListDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObBipedPartsListDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObBipedPartsListDlg)
	DDX_Control(pDX, IDC_BIPED_LIST, m_BipedList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObBipedPartsListDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsListDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObBipedPartsListDlg::GetControlData (void) {
  int   Index;
  
  m_BipedParts = 0;

  for (Index = 0; Index < m_BipedList.GetCount(); ++Index) {
    if (m_BipedList.GetSel(Index)) m_BipedParts |= m_BipedList.GetItemData(Index);
  }

}
/*===========================================================================
 *		End of Class Method CObBipedPartsListDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsListDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObBipedPartsListDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  ObAddListBoxItem(m_BipedList, "Head",		OB_BIPEDFLAG_HEAD);
  ObAddListBoxItem(m_BipedList, "Hair",		OB_BIPEDFLAG_HAIR);
  ObAddListBoxItem(m_BipedList, "UpperBody",	OB_BIPEDFLAG_UPPERBODY);
  ObAddListBoxItem(m_BipedList, "LowerBody",	OB_BIPEDFLAG_LOWERBODY);
  ObAddListBoxItem(m_BipedList, "Hand",		OB_BIPEDFLAG_HAND);
  ObAddListBoxItem(m_BipedList, "Foot",		OB_BIPEDFLAG_FOOT);
  ObAddListBoxItem(m_BipedList, "RightRing",	OB_BIPEDFLAG_RIGHTRING);
  ObAddListBoxItem(m_BipedList, "LeftRing",	OB_BIPEDFLAG_LEFTRING);
  ObAddListBoxItem(m_BipedList, "Amulet",	OB_BIPEDFLAG_AMULET);
  ObAddListBoxItem(m_BipedList, "Head",		OB_BIPEDFLAG_WEAPON);
  ObAddListBoxItem(m_BipedList, "BackWeapon",	OB_BIPEDFLAG_BACKWEAPON);
  ObAddListBoxItem(m_BipedList, "SideWeapon",	OB_BIPEDFLAG_SIDEWEAPON);
  ObAddListBoxItem(m_BipedList, "Quiver",	OB_BIPEDFLAG_QUIVER);
  ObAddListBoxItem(m_BipedList, "Shield",	OB_BIPEDFLAG_SHIELD);
  ObAddListBoxItem(m_BipedList, "Torch",	OB_BIPEDFLAG_TORCH);
  ObAddListBoxItem(m_BipedList, "Tail",		OB_BIPEDFLAG_TAIL);

  SetControlData();
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObBipedPartsListDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsListDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CObBipedPartsListDlg::OnOK (void) {
  GetControlData();

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObBipedPartsListDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBipedPartsListDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObBipedPartsListDlg::SetControlData (void) {
  dword Index;
  int   ListIndex;
  dword Mask = 1;

  for (Index = 0; Index < 16; ++Index) {

    if ((m_BipedParts & Mask) != 0) {
      ListIndex = FindListBoxItemData(m_BipedList, Mask, false);
      if (ListIndex >= 0) m_BipedList.SetSel(ListIndex, TRUE);
    }

    Mask <<= 1;
  }
  
}
/*===========================================================================
 *		End of Class Method CObBipedPartsListDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObEditBipedPartsList (BipedParts);
 *
 *=========================================================================*/
bool ObEditBipedPartsList (dword& BipedParts) {
  CObBipedPartsListDlg Dlg;
  int                  Result;

  Dlg.SetBipedParts(BipedParts);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  BipedParts = Dlg.GetBipedParts();
  return (true);
}
/*===========================================================================
 *		End of Function ObEditBipedPartsList()
 *=========================================================================*/






void CObBipedPartsListDlg::OnDblclkBipedList() 
{
	// TODO: Add your control notification handler code here
	
}
