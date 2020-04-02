/*===========================================================================
 *
 * File:	ObAmmoview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obammoview.h"
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

  IMPLEMENT_DYNCREATE(CObAmmoView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAmmoView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObAmmoView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObAmmoView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObAmmoView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObAmmoView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_DAMAGE,	   IDC_DAMAGE,		8,	IDS_TT_DAMAGE)
	ADD_OBRECUIFIELDS( OB_FIELD_SPEED,	   IDC_SPEED,		8,	IDS_TT_SPEED)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTMENT,   IDC_ENCHANTMENT,	128,	IDS_TT_ENCHANTMENT)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTPOINTS, IDC_ENCHANTCHARGE,	8,	IDS_TT_ENCHANTPOINTS)
	ADD_OBRECUIFIELDS( OB_FIELD_IGNORERESIST,  IDC_IGNORERESIST,	0,	IDS_TT_IGNORERESIST)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_INVENTORYICON,	256,	IDS_TT_ICON)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoView Constructor
 *
 *=========================================================================*/
CObAmmoView::CObAmmoView() : CObRecordDialog(CObAmmoView::IDD) {
  //{{AFX_DATA_INIT(CObAmmoView)
  //}}AFX_DATA_INIT

  m_ScriptType  = 0;
  m_EnchantType = OB_ENCHTYPE_WEAPON;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObAmmoView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoView Destructor
 *
 *=========================================================================*/
CObAmmoView::~CObAmmoView() {

}
/*===========================================================================
 *		End of Class CObAmmoView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObAmmoView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObAmmoView)
	DDX_Control(pDX, IDC_INVENTORYICON, m_Icon);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_IGNORERESIST, m_IgnoreResist);
	DDX_Control(pDX, IDC_SPEED, m_Speed);
	DDX_Control(pDX, IDC_DAMAGE, m_Damage);
	DDX_Control(pDX, IDC_ENCHANTCHARGE, m_EnchantCharge);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_ENCHANTMENT, m_Enchantment);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObAmmoView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAmmoView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObAmmoView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObAmmoView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObAmmoView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObAmmoView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObAmmoView::OnInitialUpdate()
 *=========================================================================*/
