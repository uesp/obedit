/*===========================================================================
 *
 * File:	Obselectrecorddlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 26, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "ObSelectRecordDlg.h"


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
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSelectRecordDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObSelectRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CObSelectRecordDlg)
	ON_BN_CLICKED(ID_CLEAR_BUTTON, OnClearButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RECORDLIST, OnItemchangedRecordlist)
	ON_MESSAGE(ID_OBRECORDLIST_ACTIVATE, OnEditRecord)
	ON_EN_CHANGE(IDC_CURRENT_TEXT, OnChangeCurrentText)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObSelectRecordDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Script Dialog Data
 *
 *=========================================================================*/
static obreclistcolinit_t s_ScptListInit[] = {
	{ OB_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ OB_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
  };


bool s_IsTypeScript (CObRecord* pRecord, long UserData) {
  CObScptRecord* pScript = ObCastClass(CObScptRecord, pRecord);
  if (pScript == NULL) return (false);
  return (pScript->GetType() == (dword)UserData);
}

static obselrecdlginfo_t s_ItemScriptSelDlg = { 
  &OB_NAME_SCPT, NULL, _T("Select Item Script..."), s_ScptListInit, &CObScptRecord::s_FieldMap, OB_FIELD_FLAGS, s_IsTypeScript, OB_SCRIPTTYPE_OBJECT };
  
/*===========================================================================
 *		End of Script Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Enchantment Dialog Data
 *
 *=========================================================================*/
static obreclistcolinit_t s_EnchListInit[] = {
	{ OB_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_CHARGE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_COST,	60,	LVCFMT_CENTER },
	{ OB_FIELD_AUTOCALC,	50,	LVCFMT_CENTER },
	{ OB_FIELD_EFFECTCOUNT,	80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
  };


bool s_IsTypeEnchant (CObRecord* pRecord, long UserData) {
  CObEnchRecord* pEnchant = ObCastClass(CObEnchRecord, pRecord);
  if (pEnchant == NULL) return (false);
  return (pEnchant->GetType() == (dword)UserData);
}


static obselrecdlginfo_t s_ApparelEnchantSelDlg = { 
  &OB_NAME_ENCH, NULL, _T("Select Apparel Enchantment..."), s_EnchListInit, &CObEnchRecord::s_FieldMap, OB_FIELD_FLAGS, s_IsTypeEnchant, OB_ENCHTYPE_APPAREL };

static obselrecdlginfo_t s_ScrollEnchantSelDlg = { 
  &OB_NAME_ENCH, NULL, _T("Select Scroll Enchantment..."), s_EnchListInit, &CObEnchRecord::s_FieldMap, OB_FIELD_FLAGS, s_IsTypeEnchant, OB_ENCHTYPE_SCROLL };

static obselrecdlginfo_t s_StaffEnchantSelDlg = { 
  &OB_NAME_ENCH, NULL, _T("Select Staff Enchantment..."), s_EnchListInit, &CObEnchRecord::s_FieldMap, OB_FIELD_FLAGS, s_IsTypeEnchant, OB_ENCHTYPE_STAFF };

static obselrecdlginfo_t s_WeaponEnchantSelDlg = { 
  &OB_NAME_ENCH, NULL, _T("Select Weapon Enchantment..."), s_EnchListInit, &CObEnchRecord::s_FieldMap, OB_FIELD_FLAGS, s_IsTypeEnchant, OB_ENCHTYPE_WEAPON };

/*===========================================================================
 *		End of Enchantment Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Actor Dialog Data
 *
 *=========================================================================*/
static obreclistcolinit_t s_ActorListInit[] = {
	{ OB_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
  };

static const obrectype_t* s_ActorTypes[] = { &OB_NAME_NPC_, &OB_NAME_CREA, NULL };

static obselrecdlginfo_t s_ActorSelDlg = {
  NULL, s_ActorTypes, _T("Select Actor..."), s_ActorListInit, &CObNpcRecord::s_FieldMap, OB_FIELD_EDITORID, NULL, 0 };
  
/*===========================================================================
 *		End of Actor Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Ingrediant Dialog Data
 *
 *=========================================================================*/
static obreclistcolinit_t s_IngrediantListInit[] = {
	{ OB_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
  };

static obselrecdlginfo_t s_IngrediantSelDlg = {
  &OB_NAME_INGR, NULL, _T("Select Ingrediant..."), s_IngrediantListInit, &CObIngrRecord::s_FieldMap, OB_FIELD_EDITORID, NULL, 0 };
  
/*===========================================================================
 *		End of Ingrediant Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sound Dialog Data
 *
 *=========================================================================*/
static obreclistcolinit_t s_SoundListInit[] = {
	{ OB_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
  };

static obselrecdlginfo_t s_SoundSelDlg = {
  &OB_NAME_SOUN, NULL, _T("Select Sound..."), s_SoundListInit, &CObIdRecord::s_FieldMap, OB_FIELD_EDITORID, NULL, 0 };
  
/*===========================================================================
 *		End of Sound Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Constructor
 *
 *=========================================================================*/
CObSelectRecordDlg::CObSelectRecordDlg (CWnd* pParent) : CDialog(CObSelectRecordDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CObSelectRecordDlg)
  //}}AFX_DATA_INIT

  m_pRecordHandler = NULL;
  m_pPrevRecord    = NULL;
  m_pCurrentRecord = NULL;
  m_IsInitialized  = false;
  m_EditorIDCheck  = OB_CHECKRESULT_NOCHANGE;

  m_UpdateListOnChange = false;

  m_InitialFormID  = OB_FORMID_NULL;
  m_CurrentFormID  = OB_FORMID_NULL;
}
/*===========================================================================
 *		End of Class CObSelectRecordDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObSelectRecordDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObSelectRecordDlg)
	DDX_Control(pDX, IDC_CURRENT_FORMID, m_CurrentFormIDText);
	DDX_Control(pDX, IDC_PREVIOUS_FORMID, m_PreviousFormIDText);
	DDX_Control(pDX, ID_CLEAR_BUTTON, m_ClearButton);
	DDX_Control(pDX, IDC_CURRENT_TEXT, m_CurrentText);
	DDX_Control(pDX, IDC_PREVIOUS_TEXT, m_PreviousText);
	DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - void AddListColumns (void);
 *
 *=========================================================================*/
void CObSelectRecordDlg::AddListColumns (void) {

  m_RecordList.DeleteAllColumns();

  if (m_DlgInfo.pListColumns == NULL || m_DlgInfo.pFieldMap == NULL) return;
  
  if (m_DlgInfo.pRecordType != NULL)
    m_RecordList.SetupList(*m_DlgInfo.pRecordType, m_DlgInfo.pListColumns, m_DlgInfo.pFieldMap);
  else if (m_DlgInfo.ppRecordArray != NULL && m_DlgInfo.ppRecordArray[0] != NULL) 
    m_RecordList.SetupList(*m_DlgInfo.ppRecordArray[0], m_DlgInfo.pListColumns, m_DlgInfo.pFieldMap);

}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::AddListColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - void FillRecordList (RecordType);
 *
 *=========================================================================*/
void CObSelectRecordDlg::FillRecordList (const obrectype_t RecordType) {
  CObTypeGroup*  pGroup;
  CObBaseRecord* pBaseRecord;
  CObRecord*	 pRecord;
  dword		 Index;
  bool           Result;

	/* Get the type group for the given record type */
  pGroup = m_pRecordHandler->GetTopGroup()->GetTypeGroup(RecordType);
  if (pGroup == NULL) return;

	/* Add all matching records in the group */
  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    pRecord     = ObCastRecord(pBaseRecord);
    if (pRecord == NULL) continue;

		/* Use the callback check function if present */
    if (m_DlgInfo.pCheckFunc != NULL) {
      Result = m_DlgInfo.pCheckFunc(pRecord, m_DlgInfo.UserData);
      if (!Result) continue;
    }

		/* Add the record */
    m_RecordList.AddRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - void FillRecordList (void);
 *
 *=========================================================================*/
void CObSelectRecordDlg::FillRecordList (void) {
  dword Index;

  	/* Clear the current content */
  m_RecordList.DeleteAllItems();

	/* Ensure a valid object state */
  if (m_pRecordHandler      == NULL) return;

	/* Add a single record type */
  if (m_DlgInfo.pRecordType != NULL) FillRecordList(*m_DlgInfo.pRecordType);

	/* Add several record types */
  if (m_DlgInfo.ppRecordArray != NULL) {
    for (Index = 0; m_DlgInfo.ppRecordArray[Index] != NULL; ++Index) {
      FillRecordList(*m_DlgInfo.ppRecordArray[Index]);
    }
  }

}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObSelectRecordDlg::GetControlData (void) {
  m_pCurrentRecord = m_RecordList.GetSelectedRecord();

  if (m_pCurrentRecord == NULL) 
    m_CurrentFormID = OB_FORMID_NULL;
  else
    m_CurrentFormID = m_pCurrentRecord->GetFormID();

}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Event - void OnClearButton ();
 *
 *=========================================================================*/
void CObSelectRecordDlg::OnClearButton() {

  m_pCurrentRecord = NULL;
  m_CurrentFormID  = OB_FORMID_NULL;
  m_CurrentEditorID.Empty();

  EndDialog(IDOK);
  //UpdateCurrentRecord();
}
/*===========================================================================
 *		End of Class Event CObSelectRecordDlg::OnClearButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Event - LRESULT OnEditRecord (lParam, wParam);
 *
 *=========================================================================*/
LRESULT CObSelectRecordDlg::OnEditRecord (WPARAM lParam, LPARAM wParam) {
  CObRecord* pRecord = (CObRecord *) lParam;

  OnOK();
  return (0);
}
/*===========================================================================
 *		End of Class Event CObSelectRecordDlg::OnEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObSelectRecordDlg::OnInitDialog() {
  CDialog::OnInitDialog();	

  m_UpdateListOnChange = false;
  SetWindowText(m_DlgInfo.pTitle);
  m_ClearButton.ShowWindow(m_AllowNullRecord ? SW_SHOW : SW_HIDE);

  if (m_pRecordHandler != NULL) {
    if (!m_InitialEditorID.IsEmpty()) {
      m_pPrevRecord = m_pRecordHandler->FindEditorID(m_InitialEditorID);
    }
    else {
      m_pPrevRecord = m_pRecordHandler->FindFormID(m_InitialFormID);
    }

    m_pCurrentRecord = m_pPrevRecord;
  }

	/* Initialize the record list */
  m_RecordList.SetListName("SelectRecordList");
  m_RecordList.DefaultSettings();
  AddListColumns();
  FillRecordList();

  SetControlData();
  m_RecordList.SetFocus();

  m_IsInitialized      = true;
  m_UpdateListOnChange = true;
  return (false);
}
/*===========================================================================
 *		End of Class Event CObSelectRecordDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Event - void OnItemchangedRecordlist (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObSelectRecordDlg::OnItemchangedRecordlist (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

  *pResult = 0;
  if (!m_IsInitialized) return;
  if (!m_UpdateListOnChange) return;

  GetControlData();
  UpdateCurrentRecord();
}
/*===========================================================================
 *		End of Class Event CObSelectRecordDlg::OnItemchangedRecordlist()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CObSelectRecordDlg::OnOK() {
  //GetControlData();

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObSelectRecordDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObSelectRecordDlg::SetControlData (void) {
  CString      Buffer;
  CString      EditorID;
  CObIdRecord* pIdRecord;

  m_RecordList.SortList(OB_FIELD_EDITORID);
  if (m_DlgInfo.SortField != OB_FIELD_EDITORID) m_RecordList.SortList(m_DlgInfo.SortField);

  m_RecordList.SelectRecord(m_pCurrentRecord);

  if (m_pPrevRecord == NULL) {
    m_PreviousText.SetWindowText("");
    m_PreviousFormIDText.SetWindowText("0x00000000");
  }
  else {
    pIdRecord = ObCastClass(CObIdRecord, m_pPrevRecord);
    if (pIdRecord != NULL) EditorID = pIdRecord->GetEditorID();

    Buffer.Format("%s", EditorID);
    m_PreviousText.SetWindowText(Buffer);

    Buffer.Format("0x%08X", m_pPrevRecord->GetFormID());
    m_PreviousFormIDText.SetWindowText(Buffer);
  }

  UpdateCurrentRecord();
}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - void UpdateCurrentRecord (void);
 *
 *=========================================================================*/
void CObSelectRecordDlg::UpdateCurrentRecord (void) { 
  CString      Buffer;
  CObIdRecord* pIdRecord;

  //m_pCurrentRecord = m_RecordList.GetSelectedRecord();
  m_CurrentEditorID.Empty();

  if (m_pCurrentRecord == NULL) {
    m_CurrentText.SetWindowText("");
    m_CurrentFormIDText.SetWindowText("0x00000000");
  }
  else {
    pIdRecord = ObCastClass(CObIdRecord, m_pCurrentRecord);
    if (pIdRecord != NULL) m_CurrentEditorID = pIdRecord->GetEditorID();

    Buffer.Format("%s", m_CurrentEditorID);
    m_CurrentText.SetWindowText(Buffer);

    Buffer.Format("0x%08X", m_pCurrentRecord->GetFormID());
    m_CurrentFormIDText.SetWindowText(Buffer);
  }

}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::UpdateCurrentRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Event - void OnChangeCurrentText ();
 *
 *=========================================================================*/
void CObSelectRecordDlg::OnChangeCurrentText() {
  CString       Buffer;
  int		Result;
  int		ListIndex;
  
  Result = UpdateEditorID();

  if (Result != m_EditorIDCheck) {
    m_EditorIDCheck = Result;
    m_CurrentText.RedrawWindow();
  }

  if (m_UpdateListOnChange) {
    m_UpdateListOnChange = false;
    m_CurrentText.GetWindowText(Buffer);
    
    ListIndex = m_RecordList.FindEditorID(Buffer);

    if (ListIndex >= 0) m_RecordList.SelectRecord(ListIndex);
   /*
    int StartSel;
    int EndSel;
    CObRecord*   pRecord = m_RecordList.GetRecord(ListIndex);
    CObIdRecord* pIdRecord = NULL;
    if (pRecord != NULL) pIdRecord = ObCastClass(CObIdRecord, pRecord);

    if (pIdRecord != NULL) {
      m_CurrentText.GetSel(StartSel, EndSel);
      m_CurrentText.SetWindowText(pIdRecord->GetEditorID());
      m_CurrentText.SetSel(StartSel, -1);
    } /*/

    m_UpdateListOnChange = true;
  }
	
}
/*===========================================================================
 *		End of Class Event CObSelectRecordDlg::OnChangeCurrentText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CObSelectRecordDlg::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
  HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

  if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_CurrentText) {
    switch (m_EditorIDCheck) {
      case OB_CHECKRESULT_NOCHANGE:
        hBrush = CreateSolidBrush(RGB(255,255,255));
        pDC->SetBkColor(RGB(255,255,255));
	break;
      case OB_CHECKRESULT_OK:
        hBrush = CreateSolidBrush(RGB(204,255,204));
        pDC->SetBkColor(RGB(204,255,204));
	break;
      case OB_CHECKRESULT_ERROR:
        hBrush = CreateSolidBrush(RGB(255,204,204));
        pDC->SetBkColor(RGB(255,204,204));
	break;
    }
  }

  return (hBrush);
}
/*===========================================================================
 *		End of Class Event CObSelectRecordDlg::OnCtlColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSelectRecordDlg Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CObSelectRecordDlg::UpdateEditorID (void) {
  CString	Buffer;
  CSString	EditorID;
  CObIdRecord*	pIdRecord;
  int		ListIndex;

  m_CurrentText.GetWindowText(Buffer);
  EditorID = Buffer;

  ObPrepareEditorID(EditorID);

  if (EditorID.IsEmpty()) {
    m_CurrentFormID = 0;
  }
  else {  
    pIdRecord = m_pRecordHandler->FindEditorID(EditorID);
    if (pIdRecord == NULL) return (OB_CHECKRESULT_ERROR);

    ListIndex = m_RecordList.FindRecord(pIdRecord);
    if (ListIndex < 0) return (OB_CHECKRESULT_ERROR);

    m_CurrentFormID = pIdRecord->GetFormID();
  }

  if (m_CurrentFormID == m_InitialFormID) return (OB_CHECKRESULT_NOCHANGE);

  Buffer.Format(_T("0x%08X"), m_CurrentFormID);
  m_CurrentFormIDText.SetWindowText(Buffer);

  return (OB_CHECKRESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObSelectRecordDlg::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectActor (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectActor (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ActorSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectActor()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectItemScript (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectItemScript (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ItemScriptSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectItemScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectIngrediant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectIngrediant (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_IngrediantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectIngrediant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectApparelEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectApparelEnchant (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ApparelEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectApparelEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectScrollEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectScrollEnchant (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ScrollEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectScrollEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectSound (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectSound (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_SoundSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectStaffEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectStaffEnchant (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_StaffEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectStaffEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObSelectWeaponEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool ObSelectWeaponEnchant (CString& EditorID, CObRecordHandler* pRecordHandler) {
  CObSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_WeaponEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function ObSelectWeaponEnchant()
 *=========================================================================*/


