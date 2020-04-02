/*===========================================================================
 *
 * File:	ObActiView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obactiview.h"
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

  IMPLEMENT_DYNCREATE(CObActiView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObActiView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObActiView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObActiView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObActiView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObActiView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_SOUND,	   IDC_SOUND,		128,	IDS_TT_SOUND)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_DANGEROUS,     IDC_DANGEROUS,	0,	IDS_TT_DANGEROUS)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiView Constructor
 *
 *=========================================================================*/
CObActiView::CObActiView() : CObRecordDialog(CObActiView::IDD) {
  //{{AFX_DATA_INIT(CObActiView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObActiView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiView Destructor
 *
 *=========================================================================*/
CObActiView::~CObActiView() {

}
/*===========================================================================
 *		End of Class CObActiView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObActiView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObActiView)
	DDX_Control(pDX, IDC_SOUND, m_Sound);
	DDX_Control(pDX, IDC_DANGEROUS, m_Dangerous);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObActiView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObActiView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObActiView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObActiView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObActiView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObActiView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObActiView::OnInitialUpdate()
 *=========================================================================*/

