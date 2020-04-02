/*===========================================================================
 *
 * File:	ObFlorView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obflorview.h"
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

  IMPLEMENT_DYNCREATE(CObFlorView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFlorView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObFlorView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObFlorView)
	ON_BN_CLICKED(IDC_EDIT_INGREDIANT, OnEditIngrediant)
	ON_BN_CLICKED(IDC_SELECTINGREDIANT_BUTTON, OnSelectingrediantButton)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_INGREDIANT, OnDropIngrediant)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_INGREDIANT, OnDropIngrediant)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObFlorView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObFlorView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_SPRING,	   IDC_SPRING,		8,	IDS_TT_SPRING)
	ADD_OBRECUIFIELDS( OB_FIELD_SUMMER,	   IDC_SUMMER,		8,	IDS_TT_SUMMER)
	ADD_OBRECUIFIELDS( OB_FIELD_FALL,	   IDC_FALL,		8,	IDS_TT_FALL)
	ADD_OBRECUIFIELDS( OB_FIELD_WINTER,	   IDC_WINTER,		8,	IDS_TT_WINTER)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_INGREDIANT,    IDC_INGREDIANT,	128,	IDS_TT_INGREDIENT)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorView Constructor
 *
 *=========================================================================*/
CObFlorView::CObFlorView() : CObRecordDialog(CObFlorView::IDD) {
  //{{AFX_DATA_INIT(CObFlorView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObFlorView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorView Destructor
 *
 *=========================================================================*/
CObFlorView::~CObFlorView() {

}
/*===========================================================================
 *		End of Class CObFlorView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObFlorView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObFlorView)
	DDX_Control(pDX, IDC_WINTER, m_Winter);
	DDX_Control(pDX, IDC_FALL, m_Fall);
	DDX_Control(pDX, IDC_SUMMER, m_Summer);
	DDX_Control(pDX, IDC_SPRING, m_Spring);
	DDX_Control(pDX, IDC_INGREDIANT, m_Ingrediant);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObFlorView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFlorView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObFlorView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObFlorView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObFlorView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObFlorView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObFlorView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorView Event - void OnEditIngrediant ();
 *
 *=========================================================================*/
void CObFlorView::OnEditIngrediant() {
  CString    Buffer;
  CObRecord* pRecord;

  if (m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_Ingrediant.GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(OB_NAME_INGR);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CObFlorView::OnEditIngrediant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorView Event - void OnSelectingrediantButton ();
 *
 *=========================================================================*/
void CObFlorView::OnSelectingrediantButton() {
  CString    Buffer;
  bool       Result;

  m_Ingrediant.GetWindowText(Buffer);
  
  Result = m_pDlgHandler->SelectIngrediant(Buffer);
  if (Result) m_Ingrediant.SetWindowText(Buffer);	
}
/*===========================================================================
 *		End of Class Event CObFlorView::OnSelectingrediantButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorView Event - void OnDropIngrediant (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObFlorView::OnDropIngrediant (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;
  CObRecord*	     pRecord;
  CObIngrRecord*     pIngrediant;

  *pResult = OBRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != OB_NAME_INGR) return;
  pIngrediant = ObCastClass(CObIngrRecord, pRecord);
  if (pIngrediant == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_OBRECORDLIST_DROP) {
    m_Ingrediant.SetWindowText(pIngrediant->GetEditorID());
  }

  *pResult = OBRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObFlorView::OnDropIngrediant()
 *=========================================================================*/