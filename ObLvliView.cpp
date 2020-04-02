/*===========================================================================
 *
 * File:	Oblvliview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 1, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObLvliView.h"
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

  IMPLEMENT_DYNCREATE(CObLvliView, CObRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObLvliView, CObRecordDialog)
	//{{AFX_MSG_MAP(CObLvliView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LVLLIST_EDIT, OnLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDIT, OnUpdateLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_DELETE, OnUpdateLvllistDelete)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDITRECORD, OnUpdateLvllistEdit)
	ON_COMMAND(ID_LVLLIST_ADD, OnLvllistAdd)
	ON_COMMAND(ID_LVLLIST_DELETE, OnLvllistDelete)
	ON_COMMAND(ID_MINUS_COUNT, OnMinusCount)
	ON_COMMAND(ID_ADD_COUNT, OnAddCount)
	ON_COMMAND(ID_MINUS_LEVEL, OnMinusLevel)
	ON_COMMAND(ID_ADD_LEVEL, OnAddLevel)
	ON_MESSAGE(ID_OBRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_OBRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_COMMAND(ID_DELETE_ITEM, OnLvllistDelete)
	ON_COMMAND(ID_LVLLIST_EDITRECORD, OnLvlEditrecord)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_OBRECORDLIST_KEYDOWN, IDC_ITEM_LIST, OnKeydownItemList)
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
BEGIN_OBRECUIFIELDS(CObLvliView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID2,		16,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_CALCULATEEACH, IDC_CALCULATEEACH,	0,	IDS_TT_CALCEACH)
	ADD_OBRECUIFIELDS( OB_FIELD_CALCULATEALL,  IDC_CALCULATEALL,	0,	IDS_TT_CALCALL)
	ADD_OBRECUIFIELDS( OB_FIELD_CHANCENONE,	   IDC_CHANCENONE,	16,	IDS_TT_CHANCENONE)
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
  CObLvloSubrecord* pItem1 = ObCastClass(CObLvloSubrecord, pCustomData1->pSubrecords[0]);
  CObLvloSubrecord* pItem2 = ObCastClass(CObLvloSubrecord, pCustomData2->pSubrecords[0]);

  if (pItem1 == NULL || pItem2 == NULL) return (0);
  
  if (pSortData->Reverse) return -(pItem1->GetCount() - pItem2->GetCount());
  return (pItem1->GetCount() - pItem2->GetCount());
 }


static int CALLBACK s_ItemLevelRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
  CObLvloSubrecord* pItem1 = ObCastClass(CObLvloSubrecord, pCustomData1->pSubrecords[0]);
  CObLvloSubrecord* pItem2 = ObCastClass(CObLvloSubrecord, pCustomData2->pSubrecords[0]);
  
  if (pItem1 == NULL || pItem2 == NULL) return (0);

  if (pSortData->Reverse) return -(pItem1->GetLevel() - pItem2->GetLevel());
  return (pItem1->GetLevel() - pItem2->GetLevel());
 }


static int CALLBACK s_ItemFormIDRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
  CObLvloSubrecord* pItem1 = ObCastClass(CObLvloSubrecord, pCustomData1->pSubrecords[0]);
  CObLvloSubrecord* pItem2 = ObCastClass(CObLvloSubrecord, pCustomData2->pSubrecords[0]);
  
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
static obreclistcolinit_t s_LevelListInit[] = {
	{ OB_FIELD_EDITORID,	170,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT,  s_ItemFormIDRecListSort},
	{ OB_FIELD_FLAGS,	40,	LVCFMT_CENTER },
	{ OB_FIELD_LEVEL,	50,	LVCFMT_CENTER, s_ItemLevelRecListSort},
	{ OB_FIELD_ITEMCOUNT,	50,	LVCFMT_CENTER, s_ItemCountRecListSort},
	{ OB_FIELD_ITEMNAME,	210,	LVCFMT_LEFT },
	{ OB_FIELD_RECORDTYPE,	80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obrecfield_t s_LevelListFields[] = {
	{ "Item Name",	OB_FIELD_ITEMNAME,  0, NULL },
	{ "Count",	OB_FIELD_ITEMCOUNT, 0, NULL },
	{ "Level",	OB_FIELD_LEVEL,     0, NULL },
	{ NULL,		OB_FIELD_NONE,      0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Constructor
 *
 *=========================================================================*/
CObLvliView::CObLvliView() : CObRecordDialog(CObLvliView::IDD) {
	//{{AFX_DATA_INIT(CObLvliView)
	//}}AFX_DATA_INIT

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObLvliView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Destructor
 *
 *=========================================================================*/
CObLvliView::~CObLvliView() {
  if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CObLvliView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObLvliView::DoDataExchange (CDataExchange* pDX) {
	CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObLvliView)
	DDX_Control(pDX, IDC_CALCULATEEACH, m_CalculateEach);
	DDX_Control(pDX, IDC_CALCULATEALL, m_CalculateAll);
	DDX_Control(pDX, IDC_CHANCENONE, m_ChanceNone);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID2, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObLvliView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObLvliView::GetControlData (void) {
  CObLvliRecord*    pLevelItem;
  CObLvloSubrecord* pItem;
  int               ItemPos;

  CObRecordDialog::GetControlData();
  if (m_EditInfo.pNewRecord == NULL) return;

  pLevelItem = ObCastClass(CObLvliRecord, m_EditInfo.pNewRecord);
  if (pLevelItem == NULL) return;

	/* Copy all subrecords into the new record */
  pLevelItem->DeleteSubrecords(OB_NAME_LVLO);

  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) {
    pLevelItem->AddItem(pItem->GetFormID(), pItem->GetLevel(), pItem->GetCount());
  }

}
/*===========================================================================
 *		End of Class Method CObLvliView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvliView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObLvliView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObLvliView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObLvliView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObLvliView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

	/* Setup the list */
  m_ItemList.SetListName("LvliList");
  m_ItemList.DefaultSettings();
  m_ItemList.SetupCustomList(s_LevelListInit, &CObLvliRecord::s_FieldMap, s_LevelListFields);
  m_ItemList.SetOwner(this);
  m_ItemList.SetDragType(OB_RLDRAG_CUSTOM | OB_RLDRAG_RECORD);

  m_pRecordHandler->GetEventHandler().AddListener(this);

  SaveSubrecords();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Method - void SaveSubrecords (void);
 *
 *=========================================================================*/
void CObLvliView::SaveSubrecords (void) {
  m_CopyRecord.Destroy();
  m_CopyRecord.Copy(m_EditInfo.pOldRecord);
}
/*===========================================================================
 *		End of Class Method CObLvliView::SaveSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObLvliView::SetControlData (void) {
  CObRecordDialog::SetControlData();

  FillItemList();
}
/*===========================================================================
 *		End of Class Method CObLvliView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CObLvliView::FillItemList (void) {
  CObLvloSubrecord* pItem;
  int               ItemPos;

  m_ItemList.DeleteAllItems();
  
  	/* Add items */
  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) {
    AddItemList(pItem);
  }

}
/*===========================================================================
 *		End of Class Method CObLvliView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Method - int AddItemList (pItem);
 *
 *=========================================================================*/
int CObLvliView::AddItemList (CObLvloSubrecord* pItem) {
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
 *		End of Class Method CObLvliView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Method - void UpdateItem (ListIndex, pItem);
 *
 *=========================================================================*/
void CObLvliView::UpdateItem (const int ListIndex, CObLvloSubrecord* pItem) {
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
  Buffer.Format("%u", (dword) pItem->GetLevel());
  m_ItemList.SetCustomField(ListIndex, OB_FIELD_LEVEL, Buffer);

  Buffer.Format("%u", (dword) pItem->GetCount());
  m_ItemList.SetCustomField(ListIndex, OB_FIELD_ITEMCOUNT, Buffer);
}
/*===========================================================================
 *		End of Class Method CObLvliView::UpdateItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObLvliView::OnContextMenu (CWnd* pWnd, CPoint Point) {
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
 *		End of Class Event CObLvliView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnLvllistEdit ();
 *
 *=========================================================================*/
void CObLvliView::OnLvllistEdit() {
  CObLvloSubrecord* pSubrecord;
  obrlcustomdata_t* pCustomData;
  int		    ListIndex;
  int		    Result;

  ListIndex = m_ItemList.GetSelectedItem();
  if (ListIndex < 0) return;

  pCustomData = m_ItemList.GetCustomData(ListIndex);
  if (pCustomData == NULL) return;

  pSubrecord = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
  if (pSubrecord == NULL) return;

  Result = ObEditLvlItemDlg (pSubrecord, m_pRecordHandler, m_CopyRecord.GetFormID());
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
 *		End of Class Event CObLvliView::OnLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObLvliView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnLvllistEdit();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnLvllistAdd ();
 *
 *=========================================================================*/
void CObLvliView::OnLvllistAdd() {
  CObLvloSubrecord* pItem;
  int		    Result;

  pItem = m_CopyRecord.AddItem(0, 1, 1);
  Result = ObEditLvlItemDlg (pItem, m_pRecordHandler, m_CopyRecord.GetFormID());

  if (Result == OB_LVLEDITDLG_RESULT_CANCEL || Result == OB_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteItem(pItem);
    return;
  }

  AddItemList(pItem);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnLvllistAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnLvllistDelete ();
 *
 *=========================================================================*/
void CObLvliView::OnLvllistDelete() {
  obrlcustomdata_t*	pCustomData;
  CObLvloSubrecord*	pItem;
  POSITION		ListPos;
  int			ListIndex;

	/* Delete all items in the record first */
  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);

    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem != NULL) m_CopyRecord.DeleteItem(pItem);
  }

	/* Redraw the list */
  FillItemList();
  m_ItemList.SelectRecord(0);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnUpdateLvllistDelete (pCmdUI);
 *
 *=========================================================================*/
void CObLvliView::OnUpdateLvllistDelete (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnUpdateLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnUpdateLvllistEdit (pCmdUI);
 *
 *=========================================================================*/
void CObLvliView::OnUpdateLvllistEdit (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnUpdateLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnAddCount ();
 *
 *=========================================================================*/
void CObLvliView::OnAddCount() {
  obrlcustomdata_t*	pCustomData;
  CObLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() >= 32768) continue;
    pItem->SetCount(pItem->GetCount() + 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, OB_FIELD_ITEMCOUNT, Buffer);
  }
	
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnAddCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnMinusCount ();
 *
 *=========================================================================*/
void CObLvliView::OnMinusCount() {
  obrlcustomdata_t*	pCustomData;
  CObLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() == 0) continue;
    pItem->SetCount(pItem->GetCount() - 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, OB_FIELD_ITEMCOUNT, Buffer);
  }

}
/*===========================================================================
 *		End of Class Event CObLvliView::OnMinusCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnAddLevel ();
 *
 *=========================================================================*/
void CObLvliView::OnAddLevel() {
  obrlcustomdata_t*	pCustomData;
  CObLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetLevel() >= 32768) continue;
    pItem->SetLevel(pItem->GetLevel() + 1);

    Buffer.Format("%u", (dword) pItem->GetLevel());
    m_ItemList.SetCustomField(ListIndex, OB_FIELD_LEVEL, Buffer);
  }
	
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnAddLevel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnMinusLevel ();
 *
 *=========================================================================*/
void CObLvliView::OnMinusLevel() {
  obrlcustomdata_t*	pCustomData;
  CObLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetLevel() == 0) continue;
    pItem->SetLevel(pItem->GetLevel() - 1);

    Buffer.Format("%u", (dword) pItem->GetLevel());
    m_ItemList.SetCustomField(ListIndex, OB_FIELD_LEVEL, Buffer);
  }

}
/*===========================================================================
 *		End of Class Event CObLvliView::OnMinusLevel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CObLvliView::OnListenCleanRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObLvliView::OnListenUpdateRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnLvlEditrecord ();
 *
 *=========================================================================*/
void CObLvliView::OnLvlEditrecord() {
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
 *		End of Class Event CObLvliView::OnLvlEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - LRESULT OnEditBaseRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObLvliView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnLvlEditrecord();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnEditBaseRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObLvliView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult) {
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
 *		End of Class Event CObLvliView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - int OnDropCustomData (DropItems);
 *
 *=========================================================================*/
int CObLvliView::OnDropCustomData (obrldroprecords_t& DropItems) {
  CObLvloSubrecord*  pItem;
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
    pItem = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) return (OBRL_DROPCHECK_ERROR);
    
		/* If we're just checking */
    if (DropItems.Notify.code == ID_OBRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddItem(pItem->GetFormID(), pItem->GetLevel(), pItem->GetCount());
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (OBRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnDropCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CObLvliView::OnDropRecords (obrldroprecords_t& DropItems) {
  CObLvloSubrecord*  pItem;
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

    pItem = m_CopyRecord.AddItem(pRecord->GetFormID(), 1, 1);
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (OBRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CObLvliView::OnDropRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliView Event - void OnKeydownItemList (pHdr, lResult);
 *
 *=========================================================================*/
void CObLvliView::OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult) {
  obrlkeydown_t* pNotify = (obrlkeydown_t *) pHdr;
  *lResult = 0;
	
  if (pNotify->KeyDown.nVKey == VK_DELETE || pNotify->KeyDown.nVKey == VK_BACK) {
    if (!pNotify->Ctrl && !pNotify->Alt) OnLvllistDelete();
  }
  else if (pNotify->KeyDown.nVKey == VK_ADD) {
    if (pNotify->Shift) 
      OnAddCount();
    else
      OnAddLevel();
  }
  else if (pNotify->KeyDown.nVKey == VK_SUBTRACT) {
    if (pNotify->Shift) 
      OnMinusCount();
    else
      OnMinusLevel();
  }

}
/*===========================================================================
 *		End of Class Event CObLvliView::OnKeydownItemList()
 *=========================================================================*/
