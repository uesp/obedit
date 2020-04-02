/*===========================================================================
 *
 * File:	Obarmorview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 25, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "..\obedit.h"
#include "obarmorview.h"
#include "obeditdlghandler.h"


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

  IMPLEMENT_DYNCREATE(CObArmorView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObArmorView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObArmorView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObArmorView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObArmorView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObArmorView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_TYPE,	   IDC_TYPE_LIST,	0,	IDS_TT_ARMORTYPE)
	ADD_OBRECUIFIELDS( OB_FIELD_REALARMOR,	   IDC_ARMOR,		16,	IDS_TT_ARMOR)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_HEALTH,	   IDC_HEALTH,		16,	IDS_TT_HEALTH)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTMENT,   IDC_ENCHANTMENT,	128,	IDS_TT_ENCHANTMENT)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_PLAYABLE,      IDC_PLAYABLE,	0,	IDS_TT_PLAYABLE)
	ADD_OBRECUIFIELDS( OB_FIELD_HIDERINGS,     IDC_HIDERINGS,	0,	IDS_TT_HIDERINGS)
	ADD_OBRECUIFIELDS( OB_FIELD_HIDEAMULET,    IDC_HIDEAMULET,	0,	IDS_TT_HIDEAMULET)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL2,        IDC_MALEWORLD,	0,	IDS_TT_MALEWORLDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MALEBIPED,	256,	IDS_TT_MALEBIPEDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_MALEICON,	256,	IDS_TT_MALEICON)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL4,        IDC_FEMALEWORLD,	256,	IDS_TT_FEMALEWORLDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL3,        IDC_FEMALEBIPED,	256,	IDS_TT_FEMALEBIPEDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON2,         IDC_FEMALEICON,	256,	IDS_TT_FEMALEICON)
	ADD_OBRECUIFIELDS( OB_FIELD_BIPED,         IDC_BIPEDPARTS,	0,	IDS_TT_BIPED)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmorView Constructor
 *
 *=========================================================================*/
CObArmorView::CObArmorView() : CObRecordDialog(CObArmorView::IDD) {
  //{{AFX_DATA_INIT(CObArmorView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = OB_ENCHTYPE_APPAREL;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObArmorView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmorView Destructor
 *
 *=========================================================================*/
CObArmorView::~CObArmorView() {

}
/*===========================================================================
 *		End of Class CObArmorView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmorView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObArmorView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObArmorView)
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_TYPE_LIST, m_TypeList);
	DDX_Control(pDX, IDC_BIPEDPARTS_BUTTON, m_BipedButton);
	DDX_Control(pDX, IDC_FEMALEICON, m_FemaleIcon);
	DDX_Control(pDX, IDC_FEMALEWORLD, m_FemaleWorld);
	DDX_Control(pDX, IDC_MALEICON, m_MaleIcon);
	DDX_Control(pDX, IDC_MALEWORLD, m_MaleWorld);
	DDX_Control(pDX, IDC_MALEBIPED, m_MaleBiped);
	DDX_Control(pDX, IDC_PLAYABLE, m_Playable);
	DDX_Control(pDX, IDC_HIDERINGS, m_HideRings);
	DDX_Control(pDX, IDC_HIDEAMULET, m_HideAmulet);
	DDX_Control(pDX, IDC_HEALTH, m_Health);
	DDX_Control(pDX, IDC_ARMOR, m_Armor);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_ENCHANTMENT, m_Enchantment);
	DDX_Control(pDX, IDC_BIPEDPARTS, m_BipedParts);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_FEMALEBIPED, m_FemaleBiped);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObArmorView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObArmorView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObArmorView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObArmorView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObArmorView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmorView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObArmorView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  ObAddComboBoxItem(m_TypeList, "Light", 0); 
  ObAddComboBoxItem(m_TypeList, "Heavy", OB_ARMOFLAG_HEAVYARMOR);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObArmorView::OnInitialUpdate()
 *=========================================================================*/
