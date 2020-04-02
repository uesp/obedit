/*===========================================================================
 *
 * File:	ObStatView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obstatview.h"
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

  IMPLEMENT_DYNCREATE(CObStatView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObStatView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObStatView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObStatView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObStatView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObStatView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatView Constructor
 *
 *=========================================================================*/
CObStatView::CObStatView() : CObRecordDialog(CObStatView::IDD) {
  //{{AFX_DATA_INIT(CObStatView)
  //}}AFX_DATA_INIT

  m_ScriptType  = 0;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObStatView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatView Destructor
 *
 *=========================================================================*/
CObStatView::~CObStatView() {

}
/*===========================================================================
 *		End of Class CObStatView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObStatView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObStatView)
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObStatView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObStatView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObStatView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObStatView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObStatView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObStatView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObStatView::OnInitialUpdate()
 *=========================================================================*/
