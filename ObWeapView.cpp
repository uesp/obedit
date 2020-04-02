/*===========================================================================
 *
 * File:	ObWeapView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 11, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obweapview.h"
#include "dialogs/obeditdlghandler.h"


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

  IMPLEMENT_DYNCREATE(CObWeapView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWeapView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObWeapView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObWeapView)
	ON_CBN_SELCHANGE(IDC_TYPE_LIST, OnSelchangeTypeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObWeapView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObWeapView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_TYPE,	   IDC_TYPE_LIST,	0,	IDS_TT_WEAPTYPE)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_HEALTH,	   IDC_HEALTH,		16,	IDS_TT_HEALTH)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTMENT,   IDC_ENCHANTMENT,	128,	IDS_TT_ENCHANTMENT)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTPOINTS, IDC_ENCHANTCHARGE,	8,	IDS_TT_ENCHANTPOINTS)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_IGNORERESIST,  IDC_IGNORESRESIST,	0,	IDS_TT_IGNORERESIST)
	ADD_OBRECUIFIELDS( OB_FIELD_DAMAGE,        IDC_DAMAGE,	        8,	IDS_TT_DAMAGE)
	ADD_OBRECUIFIELDS( OB_FIELD_SPEED,         IDC_SPEED,	        8,	IDS_TT_SPEED)
	ADD_OBRECUIFIELDS( OB_FIELD_REACH,         IDC_REACH,	        8,	IDS_TT_REACH)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,	        256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_INVENTORYICON,	256,	IDS_TT_ICON)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapView Constructor
 *
 *=========================================================================*/
CObWeapView::CObWeapView() : CObRecordDialog(CObWeapView::IDD) {
  //{{AFX_DATA_INIT(CObWeapView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = OB_ENCHTYPE_WEAPON;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObWeapView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapView Destructor
 *
 *=========================================================================*/
CObWeapView::~CObWeapView() {

}
/*===========================================================================
 *		End of Class CObWeapView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObWeapView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObWeapView)
	DDX_Control(pDX, IDC_INVENTORYICON, m_Icon);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_REACH, m_Reach);
	DDX_Control(pDX, IDC_SPEED, m_Speed);
	DDX_Control(pDX, IDC_DAMAGE, m_Damage);
	DDX_Control(pDX, IDC_ENCHANTCHARGE, m_EnchantPoints);
	DDX_Control(pDX, IDC_HEALTH, m_Health);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_TYPE_LIST, m_TypeList);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_ENCHANTMENT, m_Enchantment);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_IGNORESRESIST, m_IgnoreResist);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObWeapView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWeapView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObWeapView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObWeapView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObWeapView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObWeapView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  ::ObFillComboList(m_TypeList, s_ObWeaponTypes, 0);

  SetControlData();
  OnSelchangeTypeList();
}
/*===========================================================================
 *		End of Class Event CObWeapView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapView Event - void OnSelchangeTypeList ();
 *
 *=========================================================================*/
void CObWeapView::OnSelchangeTypeList() {
  int ListIndex;
  int WeaponType;

  ListIndex = m_TypeList.GetCurSel();
  if (ListIndex  < 0) return;

  WeaponType = m_TypeList.GetItemData(ListIndex);

  if (WeaponType == OB_WEAPTYPE_STAFF) {
    m_EnchantType = OB_ENCHTYPE_STAFF;
  }
  else {
    m_EnchantType = OB_ENCHTYPE_WEAPON;
  }
	
}
/*===========================================================================
 *		End of Class Event CObWeapView::OnSelchangeTypeList()
 *=========================================================================*/
