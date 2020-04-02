/*===========================================================================
 *
 * File:	ObClotView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obclotview.h"
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

  IMPLEMENT_DYNCREATE(CObClotView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClotView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObClotView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObClotView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObClotView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObClotView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTMENT,   IDC_ENCHANTMENT,	64,	IDS_TT_ENCHANTMENT)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		64,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_PLAYABLE,      IDC_PLAYABLE,	0,	IDS_TT_PLAYABLE)
	ADD_OBRECUIFIELDS( OB_FIELD_HIDERINGS,     IDC_HIDERINGS,	0,	IDS_TT_HIDERINGS)
	ADD_OBRECUIFIELDS( OB_FIELD_HIDEAMULET,    IDC_HIDEAMULET,	0,	IDS_TT_HIDEAMULET)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL2,        IDC_MALEWORLD,	0,	IDS_TT_MALEBIPEDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MALEBIPED,	256,	IDS_TT_MALEWORLDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_MALEICON,	256,	IDS_TT_MALEICON)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL4,        IDC_FEMALEWORLD,	256,	IDS_TT_FEMALEBIPEDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL3,        IDC_FEMALEBIPED,	256,	IDS_TT_FEMALEWORLDMODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON2,         IDC_FEMALEICON,	256,	IDS_TT_FEMALEICON)
	ADD_OBRECUIFIELDS( OB_FIELD_BIPED,         IDC_BIPEDPARTS,	0,	IDS_TT_BIPED)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotView Constructor
 *
 *=========================================================================*/
CObClotView::CObClotView() : CObRecordDialog(CObClotView::IDD) {
  //{{AFX_DATA_INIT(CObClotView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = OB_ENCHTYPE_APPAREL;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObClotView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotView Destructor
 *
 *=========================================================================*/
CObClotView::~CObClotView() {

}
/*===========================================================================
 *		End of Class CObClotView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObClotView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObClotView)
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_BIPEDPARTS_BUTTON, m_BipedButton);
	DDX_Control(pDX, IDC_FEMALEICON, m_FemaleIcon);
	DDX_Control(pDX, IDC_FEMALEWORLD, m_FemaleWorld);
	DDX_Control(pDX, IDC_MALEICON, m_MaleIcon);
	DDX_Control(pDX, IDC_MALEWORLD, m_MaleWorld);
	DDX_Control(pDX, IDC_MALEBIPED, m_MaleBiped);
	DDX_Control(pDX, IDC_PLAYABLE, m_Playable);
	DDX_Control(pDX, IDC_HIDERINGS, m_HideRings);
	DDX_Control(pDX, IDC_HIDEAMULET, m_HideAmulet);
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
 *		End of Class Method CObClotView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClotView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObClotView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObClotView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObClotView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObClotView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObClotView::OnInitialUpdate()
 *=========================================================================*/
