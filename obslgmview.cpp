/*===========================================================================
 *
 * File:	ObSlgmView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 11, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obslgmview.h"
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

  IMPLEMENT_DYNCREATE(CObSlgmView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSlgmView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObSlgmView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObSlgmView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObSlgmView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObSlgmView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_INVENTORYICON,	256,	IDS_TT_ICON)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_CAPACITY,      IDC_CAPACITY,	32,	IDS_TT_CAPACITY)
	ADD_OBRECUIFIELDS( OB_FIELD_SOUL,          IDC_SOUL,		32,	IDS_TT_SOUL)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmView Constructor
 *
 *=========================================================================*/
CObSlgmView::CObSlgmView() : CObRecordDialog(CObSlgmView::IDD) {
  //{{AFX_DATA_INIT(CObSlgmView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObSlgmView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmView Destructor
 *
 *=========================================================================*/
CObSlgmView::~CObSlgmView() {

}
/*===========================================================================
 *		End of Class CObSlgmView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObSlgmView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObSlgmView)
	DDX_Control(pDX, IDC_SOUL, m_Soul);
	DDX_Control(pDX, IDC_CAPACITY, m_Capacity);
	DDX_Control(pDX, IDC_INVENTORYICON, m_Icon);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObSlgmView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSlgmView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObSlgmView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObSlgmView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObSlgmView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObSlgmView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  ObFillComboList(m_Capacity, s_ObSoulGems,     0);
  ObFillComboList(m_Soul,     s_ObSoulGemsNone, 0);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObSlgmView::OnInitialUpdate()
 *=========================================================================*/
