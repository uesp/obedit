/*===========================================================================/*===========================================================================
 *
 * File:	ObSgstview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obsgstview.h"
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

  IMPLEMENT_DYNCREATE(CObSgstView, CObRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObSgstView, CObRecordDialog)
	//{{AFX_MSG_MAP(CObSgstView)
	ON_COMMAND(ID_EFFECTLIST_EDIT, OnEffectlistEdit)
	ON_UPDATE_COMMAND_UI(ID_EFFECTLIST_EDIT, OnUpdateEffectlistEdit)
	ON_COMMAND(ID_EFFECTLIST_ADD, OnEffectlistAdd)
	ON_COMMAND(ID_EFFECTLIST_DELETE, OnEffectlistDelete)
	ON_MESSAGE(ID_OBRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_OBRECORDLIST_ALTACTIVATE, OnAltEditRecordMsg)
	ON_COMMAND(ID_EFFECTLIST_EDITSCRIPT, OnEffectlistEditscript)
	ON_UPDATE_COMMAND_UI(ID_EFFECTLIST_EDITSCRIPT, OnUpdateEffectlistEditscript)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_UPDATE_COMMAND_UI(ID_EFFECTLIST_DELETE, OnUpdateEffectlistEdit)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_NOTIFY(ID_OBRECORDLIST_KEYDOWN, IDC_EFFECT_LIST, OnKeydownEffectList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObSgstView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_FULLNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		8,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		8,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,	   IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_USES,	   IDC_USES,		8,	IDS_TT_USES)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,	   IDC_MODEL,		128,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,	   IDC_INVENTORYICON,	128,	IDS_TT_ICON)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Special callback functions for list sorting.
 *
 *=========================================================================*/
static int CALLBACK s_EffectRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
  //CObEnchRecord*    pEnchant1 = ObCastClass(CObEnchRecord, pRecord1); 
  //CObEnchRecord*    pEnchant2 = ObCastClass(CObEnchRecord, pRecord2); 
  CObEfidSubrecord* pEffect1  = ObCastClass(CObEfidSubrecord, pCustomData1->pSubrecords[0]);
  CObEfidSubrecord* pEffect2  = ObCastClass(CObEfidSubrecord, pCustomData2->pSubrecords[0]);
  int               Value = 0;

  switch (pSortData->FieldID) {
    case OB_FIELD_SCRIPT: 
        if (pCustomData1->pSubrecords[2] == NULL) {
	  Value = (pCustomData2->pSubrecords[2] == NULL) ? 0 : -1;
	 }
	else if (pCustomData2->pSubrecords[2] == NULL) {
	  Value = 1;
	 }
        else {
	  CObScitSubrecord* pScit1 = ObCastClass(CObScitSubrecord, pCustomData1->pSubrecords[2]);
	  CObScitSubrecord* pScit2 = ObCastClass(CObScitSubrecord, pCustomData2->pSubrecords[2]);

          if (pScit1 == NULL) {
	    Value = (pScit2 == NULL) ? 0 : -1;
	   }
          else if (pScit2 == NULL) {
	    Value = 1;
	   }
	  else {	    
	    Value = pScit1->GetScriptFormID() - pScit1->GetScriptFormID();
	   }
         }
        break;
    };
  
  if (pSortData->Reverse) return (-Value);
  return (Value);
 }
/*===========================================================================
 *		End of Function CALLBACK s_DefaultRecListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static obreclistcolinit_t s_EffectInit[] = {
	{ OB_FIELD_EFFECTID,	 5,	LVCFMT_LEFT },
	{ OB_FIELD_EFFECTDESC,	 120,	LVCFMT_CENTER },
	{ OB_FIELD_MAGNITUDE,	 40,	LVCFMT_CENTER },
	{ OB_FIELD_AREA,	 40,	LVCFMT_CENTER },
	{ OB_FIELD_DURATION,	 40,	LVCFMT_CENTER },
	{ OB_FIELD_RANGE,	 50,	LVCFMT_CENTER },
	{ OB_FIELD_ACTORVALUE,	 75,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	 90,	LVCFMT_CENTER,	s_EffectRecListSort },
	{ OB_FIELD_EFFECTNAME,	 90,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPTSCHOOL, 75,	LVCFMT_CENTER },
	{ OB_FIELD_VISUALNAME,   45,	LVCFMT_CENTER },
	{ OB_FIELD_HOSTILE,      45,	LVCFMT_CENTER },
	//{ OB_FIELD_COST,	 60,	LVCFMT_CENTER },
	//{ OB_FIELD_SCHOOL,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obrecfield_t s_EffectFields[] = {
	{ "Effect",		OB_FIELD_EFFECTID,	0, NULL },
	{ "Effect Description", OB_FIELD_EFFECTDESC,	0, NULL },
	{ "Mag",		OB_FIELD_MAGNITUDE,	0, NULL },
	{ "Area",		OB_FIELD_AREA,		0, NULL },
	{ "Dur",		OB_FIELD_DURATION,	0, NULL },
	{ "Range",		OB_FIELD_RANGE,		0, NULL },
	{ "Cost",		OB_FIELD_COST,		0, NULL },
	{ "School",		OB_FIELD_SCHOOL,	0, NULL },
	{ "Actor Value",	OB_FIELD_ACTORVALUE,	0, NULL },
	{ "Effect Name",	OB_FIELD_EFFECTNAME,	0, NULL },
	{ "Script School",	OB_FIELD_SCRIPTSCHOOL,	0, NULL },
	{ "Visual",		OB_FIELD_VISUALNAME,	0, NULL },
	{ "Hostile",		OB_FIELD_HOSTILE,	0, NULL },
	{ "Script",		OB_FIELD_SCRIPT,	0, NULL },
	{ NULL,			OB_FIELD_NONE,		0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Constructor
 *
 *=========================================================================*/
CObSgstView::CObSgstView() : CObRecordDialog(CObSgstView::IDD) {
	//{{AFX_DATA_INIT(CObSgstView)
	//}}AFX_DATA_INIT

  m_InitialSetData = false;
  m_ScriptType     = OB_SCRIPTTYPE_OBJECT;
}
/*===========================================================================
 *		End of Class CObSgstView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Destructor
 *
 *=========================================================================*/
CObSgstView::~CObSgstView() {
}
/*===========================================================================
 *		End of Class CObSgstView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObSgstView::DoDataExchange(CDataExchange* pDX) {
	CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObSgstView)
	DDX_Control(pDX, IDC_INVENTORYICON, m_Icon);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_NAME, m_FullName);
	DDX_Control(pDX, IDC_EFFECT_LIST, m_EffectList);
	DDX_Control(pDX, IDC_USES, m_Uses);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObSgstView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Method - void ClearControlData (void);
 *
 *=========================================================================*/
void CObSgstView::ClearControlData (void) { 

  m_EffectList.DeleteAllItems();

  CObRecordDialog::ClearControlData();
}
/*===========================================================================
 *		End of Class Method CObSgstView::ClearControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObSgstView::GetControlData (void) {
  CObSgstRecord* pSigilStone;

  CObRecordDialog::GetControlData();
  if (m_EditInfo.pNewRecord == NULL) return;

  pSigilStone = ObCastClass(CObSgstRecord, m_EditInfo.pNewRecord);
  if (pSigilStone == NULL) return;

	/* Copy all subrecords into the new record */
  pSigilStone->DeleteAllEffects();
  pSigilStone->CopyEffects(&m_CopyRecord);

}
/*===========================================================================
 *		End of Class Method CObSgstView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObSgstView::AssertValid() const {
	CObRecordDialog::AssertValid();
}


void CObSgstView::Dump(CDumpContext& dc) const {
	CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of Class Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObSgstView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();
 
  	/* Setup the list */
  m_EffectList.SetListName("SgstEffectList");
  m_EffectList.SetDragEnable(true);
  m_EffectList.DefaultSettings();
  m_EffectList.SetupCustomList(s_EffectInit, NULL, s_EffectFields);
  m_EffectList.SetOwner(this);
  m_EffectList.SetColorEnable(false);
  m_EffectList.SetDragType(OB_RLDRAG_CUSTOM);
  //m_EffectList.SetActivateType(OB_RLACTIVATE_NONE);

  m_CopyRecord.Destroy();
  m_CopyRecord.Copy(m_EditInfo.pOldRecord);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObSgstView::SetControlData (void) {

  CObRecordDialog::SetControlData();
  
  SetEffectList();
}
/*===========================================================================
 *		End of Class Method CObSgstView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Method - void SetEffectList (void);
 *
 *=========================================================================*/
void CObSgstView::SetEffectList (void) {
  CObEfidSubrecord*     pEffect;
  int                   ItemPos;

  m_EffectList.DeleteAllItems();

	/* Add all effects in enchantment */
  for (pEffect = m_CopyRecord.GetFirstEffect(ItemPos);  pEffect != NULL; pEffect = m_CopyRecord.GetNextEffect(ItemPos)) {
    AddEffectList(pEffect);
  }

}
/*===========================================================================
 *		End of Class Method CObSgstView::SetEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Method - int AddEffectList (pEffect);
 *
 *=========================================================================*/
int CObSgstView::AddEffectList (CObEfidSubrecord* pEffect) {
  CObEfitSubrecord*     pEfit;
  CObScitSubrecord*     pScit;
  CObFullSubrecord*     pFull;
  obrlcustomdata_t	CustomData = { 0 };
  CString               Buffer;
  int		        ListIndex;

  CustomData.pRecord = &m_CopyRecord;

	/* Get the effect data subrecord */
  pEfit = m_CopyRecord.GetEffectData(pEffect);
  if (pEfit == NULL) return (-1);

	/* Setup the custom data structure for the list */
  CustomData.pSubrecords[0] = pEffect;
  CustomData.pSubrecords[1] = pEfit;
    
  if (pEffect->GetDataName() == OB_MGEF_SEFF) {
    pScit = m_CopyRecord.GetScriptEffectData(pEffect);
    pFull = m_CopyRecord.GetScriptEffectNameData(pEffect);   
  }
  else {
    pScit = NULL;
    pFull = NULL;
  }

  CustomData.pSubrecords[2] = pScit;
  CustomData.pSubrecords[3] = pFull;

	/* Add the custom record to the list */
  ListIndex = m_EffectList.AddCustomRecord(CustomData);
  if (ListIndex < 0) return (-1);

  UpdateEffectList(ListIndex, false);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CObSgstView::AddEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Method - void UpdateEffectList (ListIndex);
 *
 *=========================================================================*/
void CObSgstView::UpdateEffectList (const int ListIndex, const bool Update) {
  obrlcustomdata_t* pCustomData;
  CObScitSubrecord* pScit;
  CObBaseRecord*    pBaseRecord;
  CObScptRecord*    pScript = NULL;
  CString	    Buffer;

  pCustomData = m_EffectList.GetCustomData(ListIndex);
  if (pCustomData == NULL) return;

  if (Update) m_EffectList.UpdateRecord(ListIndex);

  if (pCustomData->pSubrecords[2] == NULL) return;
  pScit = ObCastClass(CObScitSubrecord, pCustomData->pSubrecords[2]);
  if (pScit == NULL) return;

  pBaseRecord = m_pRecordHandler->FindFormID(pScit->GetScriptFormID());
  if (pBaseRecord != NULL) pScript = ObCastClass(CObScptRecord, pBaseRecord);

  if (pScript != NULL) {
    m_EffectList.SetCustomField(ListIndex, OB_FIELD_SCRIPT, pScript->GetEditorID());
  }
  else if ( pScit->GetScriptFormID() == 0) {
    m_EffectList.SetCustomField(ListIndex, OB_FIELD_SCRIPT, "");
  }
  else {
    Buffer.Format(_T("0x%08X"), pScit->GetScriptFormID());
    m_EffectList.SetCustomField(ListIndex, OB_FIELD_SCRIPT, Buffer);
  }

}
/*===========================================================================
 *		End of Class Method CObSgstView::UpdateEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnUpdateEffectlistEdit (pCmdUI);
 *
 *=========================================================================*/
void CObSgstView::OnUpdateEffectlistEdit (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_EffectList.GetSelectedCount() > 0);
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnUpdateEffectlistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObSgstView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnEffectlistEdit();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - LRESULT OnAltEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObSgstView::OnAltEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnEffectlistEditscript();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnAltEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnEffectlistAdd ();
 *
 *=========================================================================*/
void CObSgstView::OnEffectlistAdd() {
  CObNameSubrecord* pEffect;
  int		    Result;

  pEffect = m_CopyRecord.AddEffect(OB_MGEF_ABAT);
  Result  = ObEditSigilStoneEffectDlg(&m_CopyRecord, pEffect, m_pRecordHandler);

  if (Result == OB_LVLEDITDLG_RESULT_CANCEL || Result == OB_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteEffect(pEffect);
    return;
  }

  AddEffectList(pEffect);
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnEffectlistAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnEffectlistDelete ();
 *
 *=========================================================================*/
void CObSgstView::OnEffectlistDelete() {
  CObEfidSubrecord*     pEffect;
  obrlcustomdata_t*	pCustomData;
  POSITION		ListPos;
  int			ListIndex;

	/* Delete all items in the record first */
  ListPos = m_EffectList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_EffectList.GetNextSelectedItem(ListPos);

    pCustomData = m_EffectList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pEffect = ObCastClass(CObEfidSubrecord, pCustomData->pSubrecords[0]);
    if (pEffect != NULL) m_CopyRecord.DeleteEffect(pEffect);
  }

	/* Redraw the list */
  SetEffectList();
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnEffectlistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnEffectlistEdit ();
 *
 *=========================================================================*/
void CObSgstView::OnEffectlistEdit() {
  CObEfidSubrecord*     pEffect;
  obrlcustomdata_t*     pCustomData;
  int			Result;
  int			ListIndex;

  ListIndex   = m_EffectList.GetSelectedItem();
  pCustomData = m_EffectList.GetSelectedCustomData();
  if (pCustomData == NULL) return;

  pEffect = ObCastClass(CObEfidSubrecord, pCustomData->pSubrecords[0]);
  if (pEffect == NULL) return;

  Result = ObEditSigilStoneEffectDlg(&m_CopyRecord, pEffect, m_pRecordHandler);
  if (Result == OB_EFFECTEDITDLG_RESULT_CANCEL) return;

  if (Result == OB_EFFECTEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteEffect(pEffect);
    m_EffectList.RemoveItem(ListIndex);
    return;
  }

  pCustomData->pSubrecords[1] = m_CopyRecord.GetEffectData(pEffect);
  pCustomData->pSubrecords[2] = m_CopyRecord.GetScriptEffectData(pEffect);
  pCustomData->pSubrecords[3] = m_CopyRecord.GetScriptEffectNameData(pEffect);

  UpdateEffectList(ListIndex);
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnEffectlistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnEffectlistEditscript ();
 *
 *=========================================================================*/
void CObSgstView::OnEffectlistEditscript() {
  obrlcustomdata_t* pCustomData;
  CObScitSubrecord* pScit;

  pCustomData = m_EffectList.GetSelectedCustomData();
  if (pCustomData == NULL) return;

  if (pCustomData->pSubrecords[2] == NULL) return;
  pScit = ObCastClass(CObScitSubrecord, pCustomData->pSubrecords[2]);
  if (pScit == NULL) return;

  m_pDlgHandler->EditRecord(pScit->GetScriptFormID());
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnEffectlistEditscript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnUpdateEffectlistEditscript (CCmdUI* pCmdUI);
 *
 *=========================================================================*/
void CObSgstView::OnUpdateEffectlistEditscript(CCmdUI* pCmdUI) {
  obrlcustomdata_t* pCustomData;
  CObScitSubrecord* pScit = NULL;
  
  pCustomData = m_EffectList.GetSelectedCustomData();

  if (pCustomData != NULL) {
    if (pCustomData->pSubrecords[2] != NULL) {
      pScit = ObCastClass(CObScitSubrecord, pCustomData->pSubrecords[2]);
    }
  }

  pCmdUI->Enable(pScit != NULL);
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnUpdateEffectlistEditscript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObSgstView::OnContextMenu(CWnd* pWnd, CPoint Point) {
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_EFFECT_LIST) {
    Result = Menu.LoadMenu(IDR_EFFECTLIST_MENU);
    if (!Result) return;

    pSubMenu = Menu.GetSubMenu(0);
    if (pSubMenu == NULL) return;

    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
  }
  else {  
    CObRecordDialog::OnContextMenu(pWnd, Point);
  }
    	
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - int OnDropCustomData (DropItems);
 *
 *=========================================================================*/
int CObSgstView::OnDropCustomData (obrldroprecords_t& DropItems) {
  CObEfidSubrecord*    pEfid1;
  CObEfidSubrecord*    pEfid2;
  CObEfitSubrecord*    pEfit;
  CObScitSubrecord*    pScit = NULL;
  CObFullSubrecord*    pFull = NULL;
  obrlcustomdata_t*    pCustomData;
  CObEffectItemRecord* pRecord;
  dword		       Index;

	/* Check all custom data dropped */
  for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) {
    pCustomData = DropItems.pCustomDatas->GetAt(Index);

    if (pCustomData->pRecord        == NULL) return (OBRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords    == NULL) return (OBRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords[0] == NULL) return (OBRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords[1] == NULL) return (OBRL_DROPCHECK_ERROR);

		/* Check for dragging another effect record */
    pRecord = ObCastClass(CObEffectItemRecord, pCustomData->pRecord);
    if (pRecord == NULL) return (OBRL_DROPCHECK_ERROR);
    pEfid1 = ObCastClass(CObEfidSubrecord, pCustomData->pSubrecords[0]);
    if (pEfid1 == NULL) return (OBRL_DROPCHECK_ERROR);
    pEfit = ObCastClass(CObEfitSubrecord, pCustomData->pSubrecords[1]);
    if (pEfit == NULL) return (OBRL_DROPCHECK_ERROR);

    if (pCustomData->pSubrecords[2] != NULL) pScit = ObCastClass(CObScitSubrecord, pCustomData->pSubrecords[2]);
    if (pCustomData->pSubrecords[3] != NULL) pFull = ObCastClass(CObFullSubrecord, pCustomData->pSubrecords[3]);

		/* TODO: Check for valid effect data? */
        
		/* If we're just checking */
    if (DropItems.Notify.code == ID_OBRECORDLIST_CHECKDROP) continue;

		/* Add effect */
    pEfid2 = m_CopyRecord.AddEffect(pEfid1->GetDataName());
    if (pEfid2 == NULL) continue;

    m_CopyRecord.SetEffectData(pEfid2, pEfit->GetEffectType(), pEfit->GetMagnitude(), pEfit->GetArea(), pEfit->GetDuration(), pEfit->GetActorValue());

    if (pScit != NULL) {
      m_CopyRecord.SetScriptEffectData(pEfid2, pScit->GetScriptFormID(), pScit->GetSchool(), pScit->GetVisualEffect(), pScit->IsHostile());
      m_CopyRecord.SetScriptEffectName(pEfid2, pFull ? pFull->GetString().c_str() : "");
    }
    
    AddEffectList(pEfid2);
  }

  return (OBRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CObSgstView::OnDropCustomData()
 *=========================================================================*/


 /*===========================================================================
 *
 * Class CObSgstView Event - void OnDropEffectList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObSgstView::OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;

  *pResult = OBRL_DROPCHECK_ERROR;
  
	/* Check for custom data */
  if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) {
    *pResult = OnDropCustomData(*pDropItems);
  }	/* Check for records */
  else if (pDropItems->pRecords != NULL) {
    *pResult = OBRL_DROPCHECK_ERROR;
  } 

}
/*===========================================================================
 *		End of Class Event CObSgstView::OnDropEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstView Event - void OnKeydownEffectList (pHdr, lResult);
 *
 *=========================================================================*/
void CObSgstView::OnKeydownEffectList (NMHDR* pHdr, LRESULT* lResult) {
  NMKEY* pNotify = (NMKEY *) pHdr;
  *lResult = 0;

	/* Ignore if ALT key is pressed */
  if ((pNotify->uFlags & 0x2000) != 0) return;

  if (pNotify->nVKey == VK_DELETE || pNotify->nVKey == VK_BACK) {
    OnEffectlistDelete();
  }

}
/*===========================================================================
 *		End of Class Event CObSgstView::OnKeydownEffectList()
 *=========================================================================*/

