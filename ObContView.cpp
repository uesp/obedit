/*===========================================================================
 *
 * File:	ObContView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObContView.h"
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

  IMPLEMENT_DYNCREATE(CObContView, CObRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObContView, CObRecordDialog)
	//{{AFX_MSG_MAP(CObContView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LVLLIST_EDIT, OnLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDIT, OnUpdateLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_DELETE, OnUpdateLvllistDelete)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDITRECORD, OnUpdateLvllistEdit)
	ON_COMMAND(ID_LVLLIST_ADD, OnLvllistAdd)
	ON_COMMAND(ID_LVLLIST_DELETE, OnLvllistDelete)
	ON_COMMAND(ID_MINUS_COUNT, OnMinusCount)
	ON_COMMAND(ID_ADD_COUNT, OnAddCount)
	ON_MESSAGE(ID_OBRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_OBRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_COMMAND(ID_DELETE_ITEM, OnLvllistDelete)
	ON_COMMAND(ID_LVLLIST_EDITRECORD, OnLvlEditrecord)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_OBRECORDLIST_KEYDOWN, IDC_ITEM_LIST, OnKeydownItemList)
	ON_BN_CLICKED(IDC_SELECTCLOSESOUND_BUTTON, OnSelectClosesoundButton)
	ON_BN_CLICKED(IDC_EDIT_CLOSESOUND, OnEditCloseSound)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_CLOSESOUND, OnDropCloseSound)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_CLOSESOUND, OnDropCloseSound)
	ON_BN_CLICKED(IDC_SELECTOPENSOUND_BUTTON, OnSelectOpensoundButton)
	ON_BN_CLICKED(IDC_EDIT_OPENSOUND, OnEditOpenSound)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_OPENSOUND, OnDropOpenSound)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_OPENSOUND, OnDropOpenSound)
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
BEGIN_OBRECUIFIELDS(CObContView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		16,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_RESPAWNS,      IDC_RESPAWNS,	0,	IDS_TT_CONTRESPAWNS)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,          8,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_OPENSOUND,	   IDC_OPENSOUND,       128,	IDS_TT_OPENSOUND)
	ADD_OBRECUIFIELDS( OB_FIELD_CLOSESOUND,	   IDC_CLOSESOUND,      128,	IDS_TT_CLOSESOUND)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,          128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,            64,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,	   IDC_MODEL,           256,	IDS_TT_MODEL)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Special callback functions for list sorting.
 *
 *=========================================================================*/
static int CALLBACK s_ItemCountRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
  CObCntoSubrecord* pItem1 = ObCastClass(CObCntoSubrecord, pCustomData1->pSubrecords[0]);
  CObCntoSubrecord* pItem2 = ObCastClass(CObCntoSubrecord, pCustomData2->pSubrecords[0]);

  if (pItem1 == NULL || pItem2 == NULL) return (0);
  
  if (pSortData->Reverse) return -(int)(pItem1->GetCount() - pItem2->GetCount());
  return (pItem1->GetCount() - pItem2->GetCount());
 }


static int CALLBACK s_ItemFormIDRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
  CObCntoSubrecord* pItem1 = ObCastClass(CObCntoSubrecord, pCustomData1->pSubrecords[0]);
  CObCntoSubrecord* pItem2 = ObCastClass(CObCntoSubrecord, pCustomData2->pSubrecords[0]);
  
  if (pItem1 == NULL || pItem2 == NULL) return (0);

  if (pSortData->Reverse) return -(int)(pItem1->GetFormID() - pItem2->GetFormID());
  return (int)(pItem1->GetFormID() - pItem2->GetFormID());
 }
/*===========================================================================
 *		End of Function CALLBACK s_DefaultRecListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static obreclistcolinit_t s_ContainerInit[] = {
	{ OB_FIELD_EDITORID,	170,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT,  s_ItemFormIDRecListSort},
	{ OB_FIELD_FLAGS,	40,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMCOUNT,	50,	LVCFMT_CENTER, s_ItemCountRecListSort},
	{ OB_FIELD_ITEMNAME,	210,	LVCFMT_LEFT },
	{ OB_FIELD_RECORDTYPE,	80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obrecfield_t s_ContainerFields[] = {
	{ "Item Name",	OB_FIELD_ITEMNAME,  0, NULL },
	{ "Count",	OB_FIELD_ITEMCOUNT, 0, NULL },
	{ NULL,		OB_FIELD_NONE,      0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Constructor
 *
 *=========================================================================*/
CObContView::CObContView() : CObRecordDialog(CObContView::IDD) {
	//{{AFX_DATA_INIT(CObContView)
	//}}AFX_DATA_INIT

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObContView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Destructor
 *
 *=========================================================================*/
CObContView::~CObContView() {
  if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CObContView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObContView::DoDataExchange (CDataExchange* pDX) {
	CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObContView)
	DDX_Control(pDX, IDC_RESPAWNS, m_Respawns);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_NAME, m_FullName);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_OPENSOUND, m_OpenSound);
	DDX_Control(pDX, IDC_CLOSESOUND, m_ClosingSound);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObContView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObContView::GetControlData (void) {
  CObContRecord*    pLevelItem;
  CObCntoSubrecord* pItem;
  int               ItemPos;

  CObRecordDialog::GetControlData();
  if (m_EditInfo.pNewRecord == NULL) return;

  pLevelItem = ObCastClass(CObContRecord, m_EditInfo.pNewRecord);
  if (pLevelItem == NULL) return;

	/* Copy all subrecords into the new record */
  pLevelItem->DeleteSubrecords(OB_NAME_CNTO);

  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) {
    pLevelItem->AddItem(pItem->GetFormID(), pItem->GetCount());
  }

}
/*===========================================================================
 *		End of Class Method CObContView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObContView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObContView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObContView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObContView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObContView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

	/* Setup the list */
  m_ItemList.DefaultSettings();
  m_ItemList.SetupCustomList(s_ContainerInit, &CObContRecord::s_FieldMap, s_ContainerFields);
  m_ItemList.SetOwner(this);
  m_ItemList.SetDragType(OB_RLDRAG_CUSTOM | OB_RLDRAG_RECORD);

  m_pRecordHandler->GetEventHandler().AddListener(this);

  SaveSubrecords();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObContView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Method - void SaveSubrecords (void);
 *
 *=========================================================================*/
void CObContView::SaveSubrecords (void) {
  m_CopyRecord.Destroy();
  m_CopyRecord.Copy(m_EditInfo.pOldRecord);
}
/*===========================================================================
 *		End of Class Method CObContView::SaveSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObContView::SetControlData (void) {
  CObRecordDialog::SetControlData();

  FillItemList();
}
/*===========================================================================
 *		End of Class Method CObContView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CObContView::FillItemList (void) {
  CObCntoSubrecord* pItem;
  int               ItemPos;

  m_ItemList.DeleteAllItems();
  
  	/* Add items */
  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) {
    AddItemList(pItem);
  }

}
/*===========================================================================
 *		End of Class Method CObContView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Method - int AddItemList (pItem);
 *
 *=========================================================================*/
int CObContView::AddItemList (CObCntoSubrecord* pItem) {
  CObBaseRecord*    pBaseRecord;
  CObIdRecord*	    pIdRecord;
  obrlcustomdata_t  CustomData = { 0 };
  int               ListIndex;

  pBaseRecord = m_pRecordHandler->FindFormID(pItem->GetFormID());
  pIdRecord   = NULL;
  if (pBaseRecord != NULL) pIdRecord = ObCastClass(CObIdRecord, pBaseRecord);

  CustomData.pRecord        = pIdRecord;
  CustomData.pSubrecords[0] = pItem;

  ListIndex = m_ItemList.AddCustomRecord(CustomData);
  if (ListIndex < 0) return (-1);

  UpdateItem(ListIndex, pItem);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CObContView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Method - void UpdateItem (ListIndex, pItem);
 *
 *=========================================================================*/
void CObContView::UpdateItem (const int ListIndex, CObCntoSubrecord* pItem) {
  CObBaseRecord*    pBaseRecord;
  CObIdRecord*	    pRecord = NULL;
  CString           Buffer;

  m_ItemList.UpdateRecord(ListIndex);

  pBaseRecord = m_pRecordHandler->FindFormID(pItem->GetFormID());
  if (pBaseRecord != NULL) pRecord = ObCastClass(CObIdRecord, pBaseRecord);
  
  if (pRecord == NULL) {
    Buffer.Format("0x%08X", pItem->GetFormID());
    m_ItemList.SetCustomField(ListIndex, OB_FIELD_FORMID, Buffer);

    m_ItemList.SetCustomField(ListIndex, OB_FIELD_EDITORID, "");
  }

		/* Set custom fields */
  Buffer.Format("%u", (dword) pItem->GetCount());
  m_ItemList.SetCustomField(ListIndex, OB_FIELD_ITEMCOUNT, Buffer);
}
/*===========================================================================
 *		End of Class Method CObContView::UpdateItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObContView::OnContextMenu (CWnd* pWnd, CPoint Point) {
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_ITEM_LIST) {
    Result = Menu.LoadMenu(IDR_LVLITEMLIST_MENU);
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
 *		End of Class Event CObContView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnLvllistEdit ();
 *
 *=========================================================================*/
void CObContView::OnLvllistEdit() {
  CObCntoSubrecord* pSubrecord;
  obrlcustomdata_t* pCustomData;
  int		    ListIndex;
  int		    Result;

  ListIndex = m_ItemList.GetSelectedItem();
  if (ListIndex < 0) return;

  pCustomData = m_ItemList.GetCustomData(ListIndex);
  if (pCustomData == NULL) return;

  pSubrecord = ObCastClass(CObCntoSubrecord, pCustomData->pSubrecords[0]);
  if (pSubrecord == NULL) return;

  Result = ObEditContainerItemDlg (pSubrecord, m_pRecordHandler);
  if (Result == OB_LVLEDITDLG_RESULT_CANCEL) return;

  if (Result == OB_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteItem(pSubrecord);
    m_ItemList.RemoveItem(ListIndex);
    return;
  }
  
  pCustomData->pRecord = m_pRecordHandler->FindFormID(pSubrecord->GetFormID());
  UpdateItem(ListIndex, pSubrecord); 
}
/*===========================================================================
 *		End of Class Event CObContView::OnLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObContView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnLvllistEdit();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObContView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnLvllistAdd ();
 *
 *=========================================================================*/
void CObContView::OnLvllistAdd() {
  CObCntoSubrecord* pItem;
  int		    Result;

  pItem = m_CopyRecord.AddItem(0, 1);
  Result = ObEditContainerItemDlg (pItem, m_pRecordHandler);

  if (Result == OB_LVLEDITDLG_RESULT_CANCEL || Result == OB_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteItem(pItem);
    return;
  }

  AddItemList(pItem);
}
/*===========================================================================
 *		End of Class Event CObContView::OnLvllistAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnLvllistDelete ();
 *
 *=========================================================================*/
void CObContView::OnLvllistDelete() {
  obrlcustomdata_t*	pCustomData;
  CObCntoSubrecord*	pItem;
  POSITION		ListPos;
  int			ListIndex;

	/* Delete all items in the record first */
  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);

    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem != NULL) m_CopyRecord.DeleteItem(pItem);
  }

	/* Redraw the list */
  FillItemList();
  m_ItemList.SelectRecord(0);
}
/*===========================================================================
 *		End of Class Event CObContView::OnLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnUpdateLvllistDelete (pCmdUI);
 *
 *=========================================================================*/
void CObContView::OnUpdateLvllistDelete (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CObContView::OnUpdateLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnUpdateLvllistEdit (pCmdUI);
 *
 *=========================================================================*/
void CObContView::OnUpdateLvllistEdit (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CObContView::OnUpdateLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnAddCount ();
 *
 *=========================================================================*/
void CObContView::OnAddCount() {
  obrlcustomdata_t*	pCustomData;
  CObCntoSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() >= 32768) continue;
    pItem->SetCount(pItem->GetCount() + 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, OB_FIELD_ITEMCOUNT, Buffer);
  }
	
}
/*===========================================================================
 *		End of Class Event CObContView::OnAddCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnMinusCount ();
 *
 *=========================================================================*/
void CObContView::OnMinusCount() {
  obrlcustomdata_t*	pCustomData;
  CObCntoSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() == 0) continue;
    pItem->SetCount(pItem->GetCount() - 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, OB_FIELD_ITEMCOUNT, Buffer);
  }

}
/*===========================================================================
 *		End of Class Event CObContView::OnMinusCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CObContView::OnListenCleanRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObContView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObContView::OnListenUpdateRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObContView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnLvlEditrecord ();
 *
 *=========================================================================*/
void CObContView::OnLvlEditrecord() {
  CObRecord* pRecord;
  CWnd*      pWnd;

  pRecord = m_ItemList.GetSelectedRecord();
  if (pRecord == NULL) return;
  
  pWnd = GetOwner();

  if (pWnd != NULL) {
    m_pDlgHandler->EditRecord(pRecord);
  }
	
}
/*===========================================================================
 *		End of Class Event CObContView::OnLvlEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - LRESULT OnEditBaseRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObContView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnLvlEditrecord();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObContView::OnEditBaseRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObContView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;

  *pResult = OBRL_DROPCHECK_ERROR;
  
	/* Check for custom data */
  if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) {
    *pResult = OnDropCustomData(*pDropItems);
  }	/* Check for records */
  else if (pDropItems->pRecords != NULL) {
    *pResult = OnDropRecords(*pDropItems);
  } 

}
/*===========================================================================
 *		End of Class Event CObContView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - int OnDropCustomData (DropItems);
 *
 *=========================================================================*/
int CObContView::OnDropCustomData (obrldroprecords_t& DropItems) {
  CObCntoSubrecord*  pItem;
  CObLvliRecord*     pRecord;
  obrlcustomdata_t*  pCustomData;
  dword		     Index;

	/* Check all custom data dropped */
  for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) {
    pCustomData = DropItems.pCustomDatas->GetAt(Index);

    if (pCustomData->pRecord        == NULL) return (OBRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords    == NULL) return (OBRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords[0] == NULL) return (OBRL_DROPCHECK_ERROR);

		/* Check for dragging another lvlo record */
    pRecord = ObCastClass(CObLvliRecord, pCustomData->pRecord);
    if (pRecord == NULL) return (OBRL_DROPCHECK_ERROR);
    pItem = ObCastClass(CObCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) return (OBRL_DROPCHECK_ERROR);
    
		/* If we're just checking */
    if (DropItems.Notify.code == ID_OBRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddItem(pItem->GetFormID(), pItem->GetCount());
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (OBRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CObContView::OnDropCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CObContView::OnDropRecords (obrldroprecords_t& DropItems) {
  CObCntoSubrecord*  pItem;
  CObRecord*	     pRecord;
  dword		     Index;

  for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) {
    pRecord = DropItems.pRecords->GetAt(Index);
    
		/* Don't drag onto ourself */
    if (pRecord == m_EditInfo.pOldRecord) return (OBRL_DROPCHECK_ERROR);
    if (pRecord->GetFormID() == m_EditInfo.pOldRecord->GetFormID()) return (OBRL_DROPCHECK_ERROR);

		/* Ignore any invalid record types */
    if (!ObIsValidLvliRecord(pRecord->GetRecordType())) return (OBRL_DROPCHECK_ERROR);

		/* If we're just checking */
    if (DropItems.Notify.code == ID_OBRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddItem(pRecord->GetFormID(), 1);
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (OBRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CObContView::OnDropRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnKeydownItemList (pHdr, lResult);
 *
 *=========================================================================*/
void CObContView::OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult) {
  obrlkeydown_t* pNotify = (obrlkeydown_t *) pHdr;
  *lResult = 0;
	
  if (pNotify->KeyDown.nVKey == VK_DELETE || pNotify->KeyDown.nVKey == VK_BACK) {
    if (!pNotify->Ctrl && !pNotify->Alt) OnLvllistDelete();
  }
  else if (pNotify->KeyDown.nVKey == VK_ADD) {
    OnAddCount();
  }
  else if (pNotify->KeyDown.nVKey == VK_SUBTRACT) {
    OnMinusCount();
  }

}
/*===========================================================================
 *		End of Class Event CObContView::OnKeydownItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnSelectClosesoundButton ();
 *
 *=========================================================================*/
void CObContView::OnSelectClosesoundButton() {
  CString    Buffer;
  bool       Result;

  m_ClosingSound.GetWindowText(Buffer);

  Result = m_pDlgHandler->SelectSound(Buffer);
  if (Result) m_ClosingSound.SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObContView::OnSelectClosesoundButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnEditCloseSound ();
 *
 *=========================================================================*/
void CObContView::OnEditCloseSound() {
  CString    Buffer;
  CObRecord* pRecord;

  if (m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_ClosingSound.GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(OB_NAME_SOUN);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CObContView::OnEditCloseSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnDropCloseSound (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObContView::OnDropCloseSound (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;
  CObRecord*	     pRecord;
  CObIdRecord*       pSound;

  *pResult = OBRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != OB_NAME_SOUN) return;
  pSound = ObCastClass(CObIdRecord, pRecord);
  if (pSound == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_OBRECORDLIST_DROP) {
    m_ClosingSound.SetWindowText(pSound->GetEditorID());
  }

  *pResult = OBRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObContView::OnDropCloseSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnSelectOpensoundButton ();
 *
 *=========================================================================*/
void CObContView::OnSelectOpensoundButton() {
  CString    Buffer;
  bool       Result;

  m_OpenSound.GetWindowText(Buffer);

  Result = m_pDlgHandler->SelectSound(Buffer);
  if (Result) m_OpenSound.SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObContView::OnSelectOpensoundButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnEditOpenSound ();
 *
 *=========================================================================*/
void CObContView::OnEditOpenSound() {
  CString    Buffer;
  CObRecord* pRecord;

  if (m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_OpenSound.GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(OB_NAME_SOUN);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CObContView::OnEditOpenSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContView Event - void OnDropOpenSound (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObContView::OnDropOpenSound (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;
  CObRecord*	     pRecord;
  CObIdRecord*       pSound;

  *pResult = OBRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != OB_NAME_SOUN) return;
  pSound = ObCastClass(CObIdRecord, pRecord);
  if (pSound == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_OBRECORDLIST_DROP) {
    m_OpenSound.SetWindowText(pSound->GetEditorID());
  }

  *pResult = OBRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObContView::OnDropOpenSound()
 *=========================================================================*/

