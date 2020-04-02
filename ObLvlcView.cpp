/*===========================================================================
 *
 * File:	Oblvlcview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 9, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObLvlcView.h"
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

  IMPLEMENT_DYNCREATE(CObLvlcView, CObRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObLvlcView, CObRecordDialog)
	//{{AFX_MSG_MAP(CObLvlcView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LVLLIST_EDIT, OnLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDIT, OnUpdateLvllistEdit)
	ON_COMMAND(ID_LVLLIST_ADD, OnLvllistAdd)
	ON_COMMAND(ID_LVLLIST_DELETE, OnLvllistDelete)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_DELETE, OnUpdateLvllistDelete)
	ON_COMMAND(ID_MINUS_COUNT, OnMinusCount)
	ON_COMMAND(ID_ADD_COUNT, OnAddCount)
	ON_COMMAND(ID_MINUS_LEVEL, OnMinusLevel)
	ON_COMMAND(ID_ADD_LEVEL, OnAddLevel)
	ON_MESSAGE(ID_OBRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_OBRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_COMMAND(ID_LVLLIST_EDITRECORD, OnLvlEditrecord)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_BN_CLICKED(IDC_EDIT_CREATURETEMPLATE, OnEditCreaturetemplate)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDITRECORD, OnUpdateLvllistEdit)
	ON_COMMAND(ID_DELETE_ITEM, OnLvllistDelete)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_BN_CLICKED(IDC_SELECTCREATURE_BUTTON, OnSelectcreatureButton)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_CREATURETEMPLATE, OnDropCreatureTemplate)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_CREATURETEMPLATE, OnDropCreatureTemplate)
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
BEGIN_OBRECUIFIELDS(CObLvlcView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	 128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID2,		 16,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_CALCULATEEACH, IDC_CALCULATEEACH,	 0,	IDS_TT_CALCEACH)
	ADD_OBRECUIFIELDS( OB_FIELD_CALCULATEALL,  IDC_CALCULATEALL,	 0,	IDS_TT_CALCALL)
	ADD_OBRECUIFIELDS( OB_FIELD_CHANCENONE,	   IDC_CHANCENONE,	 16,	IDS_TT_CHANCENONE)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		 128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_TEMPLATE,	   IDC_CREATURETEMPLATE, 128,	IDS_TT_CREATURETEMPLATE)
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
 * Class CObLvlcView Constructor
 *
 *=========================================================================*/
CObLvlcView::CObLvlcView() : CObRecordDialog(CObLvlcView::IDD) {
	//{{AFX_DATA_INIT(CObLvlcView)
	//}}AFX_DATA_INIT

  m_ScriptType     = OB_SCRIPTTYPE_OBJECT;
  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObLvlcView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Destructor
 *
 *=========================================================================*/
CObLvlcView::~CObLvlcView() {
  if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CObLvlcView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObLvlcView::DoDataExchange (CDataExchange* pDX) {
	CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObLvlcView)
	DDX_Control(pDX, IDC_CREATURETEMPLATE, m_CreatureTemplate);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_CALCULATEEACH, m_CalculateEach);
	DDX_Control(pDX, IDC_CALCULATEALL, m_CalculateAll);
	DDX_Control(pDX, IDC_CHANCENONE, m_ChanceNone);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID2, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObLvlcView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObLvlcView::GetControlData (void) {
  CObLvlcRecord*    pLevelCreature;
  CObLvloSubrecord* pItem;
  int               ItemPos;

  CObRecordDialog::GetControlData();
  if (m_EditInfo.pNewRecord == NULL) return;

  pLevelCreature = ObCastClass(CObLvlcRecord, m_EditInfo.pNewRecord);
  if (pLevelCreature == NULL) return;

	/* Copy all subrecords into the new record */
  pLevelCreature->DeleteSubrecords(OB_NAME_LVLO);

  for (pItem = m_CopyRecord.GetFirstCreature(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextCreature(ItemPos)) {
    pLevelCreature->AddCreature(pItem->GetFormID(), pItem->GetLevel(), pItem->GetCount());
  }

}
/*===========================================================================
 *		End of Class Method CObLvlcView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvlcView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObLvlcView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObLvlcView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObLvlcView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObLvlcView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

	/* Setup the list */
  m_ItemList.SetListName("LvlcList");
  m_ItemList.DefaultSettings();
  m_ItemList.SetupCustomList(s_LevelListInit, &CObLvliRecord::s_FieldMap, s_LevelListFields);
  m_ItemList.SetOwner(this);
  m_ItemList.SetDragType(OB_RLDRAG_CUSTOM | OB_RLDRAG_RECORD);

  m_pRecordHandler->GetEventHandler().AddListener(this);

  SaveSubrecords();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Method - void SaveSubrecords (void);
 *
 *=========================================================================*/
void CObLvlcView::SaveSubrecords (void) {
  m_CopyRecord.Destroy();
  m_CopyRecord.Copy(m_EditInfo.pOldRecord);
}
/*===========================================================================
 *		End of Class Method CObLvlcView::SaveSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObLvlcView::SetControlData (void) {
  CObRecordDialog::SetControlData();

  FillItemList();
}
/*===========================================================================
 *		End of Class Method CObLvlcView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CObLvlcView::FillItemList (void) {
  CObLvloSubrecord* pItem;
  int               ItemPos;

  m_ItemList.DeleteAllItems();
  
  	/* Add items */
  for (pItem = m_CopyRecord.GetFirstCreature(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextCreature(ItemPos)) {
    AddItemList(pItem);
  }

}
/*===========================================================================
 *		End of Class Method CObLvlcView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Method - int AddItemList (pItem);
 *
 *=========================================================================*/
int CObLvlcView::AddItemList (CObLvloSubrecord* pItem) {
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
 *		End of Class Method CObLvlcView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Method - void UpdateItem (ListIndex, pItem);
 *
 *=========================================================================*/
void CObLvlcView::UpdateItem (const int ListIndex, CObLvloSubrecord* pItem) {
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
 *		End of Class Method CObLvlcView::UpdateItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObLvlcView::OnContextMenu (CWnd* pWnd, CPoint Point) {
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
 *		End of Class Event CObLvlcView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnLvllistEdit ();
 *
 *=========================================================================*/
void CObLvlcView::OnLvllistEdit() {
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

  Result = ObEditLvlCreatureDlg (pSubrecord, m_pRecordHandler, m_CopyRecord.GetFormID());
  if (Result == OB_LVLEDITDLG_RESULT_CANCEL) return;

  if (Result == OB_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteCreature(pSubrecord);
    m_ItemList.RemoveItem(ListIndex);
    return;
  }
  
  pCustomData->pRecord = m_pRecordHandler->FindFormID(pSubrecord->GetFormID());
  UpdateItem(ListIndex, pSubrecord); 
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObLvlcView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnLvllistEdit();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnLvllistAdd ();
 *
 *=========================================================================*/
void CObLvlcView::OnLvllistAdd() {
  CObLvloSubrecord* pItem;
  int		    Result;

  pItem = m_CopyRecord.AddCreature(0, 1, 1);
  Result = ObEditLvlCreatureDlg (pItem, m_pRecordHandler, m_CopyRecord.GetFormID());

  if (Result == OB_LVLEDITDLG_RESULT_CANCEL || Result == OB_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteCreature(pItem);
    return;
  }

  AddItemList(pItem);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnLvllistAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnLvllistDelete ();
 *
 *=========================================================================*/
void CObLvlcView::OnLvllistDelete() {
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
    if (pItem != NULL) m_CopyRecord.DeleteCreature(pItem);
  }

	/* Redraw the list */
  FillItemList();
  m_ItemList.SelectRecord(0);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnUpdateLvllistDelete (pCmdUI);
 *
 *=========================================================================*/
void CObLvlcView::OnUpdateLvllistDelete (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnUpdateLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnUpdateLvllistEdit (pCmdUI);
 *
 *=========================================================================*/
void CObLvlcView::OnUpdateLvllistEdit (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnUpdateLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnAddCount ();
 *
 *=========================================================================*/
void CObLvlcView::OnAddCount() {
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
 *		End of Class Event CObLvlcView::OnAddCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnMinusCount ();
 *
 *=========================================================================*/
void CObLvlcView::OnMinusCount() {
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
 *		End of Class Event CObLvlcView::OnMinusCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnAddLevel ();
 *
 *=========================================================================*/
void CObLvlcView::OnAddLevel() {
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
 *		End of Class Event CObLvlcView::OnAddLevel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnMinusLevel ();
 *
 *=========================================================================*/
void CObLvlcView::OnMinusLevel() {
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
 *		End of Class Event CObLvlcView::OnMinusLevel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CObLvlcView::OnListenCleanRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObLvlcView::OnListenUpdateRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnLvlEditrecord ();
 *
 *=========================================================================*/
void CObLvlcView::OnLvlEditrecord() {
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
 *		End of Class Event CObLvlcView::OnLvlEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - LRESULT OnEditBaseRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObLvlcView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) {
  OnLvlEditrecord();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnEditBaseRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObLvlcView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult) {
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
 *		End of Class Event CObLvlcView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - int OnDropCustomData (DropItems);
 *
 *=========================================================================*/
int CObLvlcView::OnDropCustomData (obrldroprecords_t& DropItems) {
  CObLvloSubrecord*  pItem;
  CObLvlcRecord*     pRecord;
  obrlcustomdata_t*  pCustomData;
  dword		     Index;

	/* Check all custom data dropped */
  for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) {
    pCustomData = DropItems.pCustomDatas->GetAt(Index);

    if (pCustomData->pRecord        == NULL) return (OBRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords    == NULL) return (OBRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords[0] == NULL) return (OBRL_DROPCHECK_ERROR);

		/* Check for dragging another lvlo record from a creature list */
    pRecord = ObCastClass(CObLvlcRecord, pCustomData->pRecord);
    if (pRecord == NULL) return (OBRL_DROPCHECK_ERROR);
    pItem = ObCastClass(CObLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) return (OBRL_DROPCHECK_ERROR);
    
		/* If we're just checking */
    if (DropItems.Notify.code == ID_OBRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddCreature(pItem->GetFormID(), pItem->GetLevel(), pItem->GetCount());
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (OBRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnDropCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CObLvlcView::OnDropRecords (obrldroprecords_t& DropItems) {
  CObLvloSubrecord*  pItem;
  CObRecord*	     pRecord;
  dword		     Index;

  for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) {
    pRecord = DropItems.pRecords->GetAt(Index);
    
		/* Don't drag onto ourself */
    if (pRecord == m_EditInfo.pOldRecord) return (OBRL_DROPCHECK_ERROR);
    if (pRecord->GetFormID() == m_EditInfo.pOldRecord->GetFormID()) return (OBRL_DROPCHECK_ERROR);

		/* Ignore any invalid record types */
    if (!ObIsValidLvlcRecord(pRecord->GetRecordType())) return (OBRL_DROPCHECK_ERROR);

		/* If we're just checking */
    if (DropItems.Notify.code == ID_OBRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddCreature(pRecord->GetFormID(), 1, 1);
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (OBRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnDropRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnEditCreaturetemplate ();
 *
 *=========================================================================*/
void CObLvlcView::OnEditCreaturetemplate() {
  CString    Buffer;
  CObRecord* pRecord;

  if (m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_CreatureTemplate.GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    //m_pDlgHandler->EditNewRecord(OB_NAME_SCPT);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }
  	
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnEditCreaturetemplate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnSelectcreatureButton ();
 *
 *=========================================================================*/
void CObLvlcView::OnSelectcreatureButton() {
  CString    Buffer;
  bool       Result;

  m_CreatureTemplate.GetWindowText(Buffer);
  
  Result = m_pDlgHandler->SelectActor(Buffer);
  if (Result) m_CreatureTemplate.SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnSelectcreatureButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnDropCreatureTemplate (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObLvlcView::OnDropCreatureTemplate (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;
  CObRecord*	     pRecord;
  CObIdRecord*       pIdRecord;

  *pResult = OBRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != OB_NAME_NPC_ && pRecord->GetRecordType() != OB_NAME_CREA) return;

  pIdRecord = ObCastClass(CObIdRecord, pRecord);
  if (pIdRecord == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_OBRECORDLIST_DROP) {
    m_CreatureTemplate.SetWindowText(pIdRecord->GetEditorID());
  }

  *pResult = OBRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObLvlcView::OnDropCreatureTemplate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcView Event - void OnKeydownItemList (pHdr, lResult);
 *
 *=========================================================================*/
void CObLvlcView::OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult) {
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
 *		End of Class Event CObLvlcView::OnKeydownItemList()
 *=========================================================================*/
