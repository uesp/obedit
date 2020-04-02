/*===========================================================================
 *
 * File:	ObAppaview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obappaview.h"
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

  IMPLEMENT_DYNCREATE(CObAppaView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAppaView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObAppaView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObAppaView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObAppaView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObAppaView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_QUALITY,	   IDC_QUALITY,		8,	IDS_TT_QUALITY)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_INVENTORYICON,	256,	IDS_TT_ICON)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_TYPE,          IDC_TYPE,		32,	IDS_TT_APPATYPE)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaView Constructor
 *
 *=========================================================================*/
CObAppaView::CObAppaView() : CObRecordDialog(CObAppaView::IDD) {
  //{{AFX_DATA_INIT(CObAppaView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObAppaView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaView Destructor
 *
 *=========================================================================*/
CObAppaView::~CObAppaView() {

}
/*===========================================================================
 *		End of Class CObAppaView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObAppaView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObAppaView)
	DDX_Control(pDX, IDC_INVENTORYICON, m_Icon);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_QUALITY, m_Quality);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObAppaView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAppaView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObAppaView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObAppaView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObAppaView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObAppaView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  ObFillComboList(m_Type, s_ObApparatusTypes, 0);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObAppaView::OnInitialUpdate()
 *=========================================================================*/
