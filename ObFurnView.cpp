/*===========================================================================
 *
 * File:	ObFurnView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obfurnview.h"
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

  IMPLEMENT_DYNCREATE(CObFurnView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFurnView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObFurnView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObFurnView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObFurnView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObFurnView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnView Constructor
 *
 *=========================================================================*/
CObFurnView::CObFurnView() : CObRecordDialog(CObFurnView::IDD) {
  //{{AFX_DATA_INIT(CObFurnView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObFurnView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnView Destructor
 *
 *=========================================================================*/
CObFurnView::~CObFurnView() {

}
/*===========================================================================
 *		End of Class CObFurnView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObFurnView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObFurnView)
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObFurnView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFurnView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObFurnView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObFurnView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObFurnView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObFurnView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObFurnView::OnInitialUpdate()
 *=========================================================================*/

