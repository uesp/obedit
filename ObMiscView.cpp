/*===========================================================================
 *
 * File:	ObMiscView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obmiscview.h"
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

  IMPLEMENT_DYNCREATE(CObMiscView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMiscView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObMiscView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObMiscView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObMiscView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObMiscView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_INVENTORYICON,	256,	IDS_TT_ICON)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscView Constructor
 *
 *=========================================================================*/
CObMiscView::CObMiscView() : CObRecordDialog(CObMiscView::IDD) {
  //{{AFX_DATA_INIT(CObMiscView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObMiscView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscView Destructor
 *
 *=========================================================================*/
CObMiscView::~CObMiscView() {

}
/*===========================================================================
 *		End of Class CObMiscView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObMiscView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObMiscView)
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
 *		End of Class Method CObMiscView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMiscView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObMiscView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObMiscView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObMiscView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObMiscView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObMiscView::OnInitialUpdate()
 *=========================================================================*/
