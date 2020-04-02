/*===========================================================================
 *
 * File:	Oblvleditdlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 2, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObLvlEditDlg.h"


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
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObLvlEditDlg, CDialog)
	//{{AFX_MSG_MAP(CObLvlEditDlg)
	ON_BN_CLICKED(ID_DELETE_BUTTON, OnDeleteButton)
	ON_EN_CHANGE(IDC_EDITORID, OnChangeEditorid)
	ON_EN_KILLFOCUS(IDC_EDITORID, OnKillfocusEditorid)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RECORDLIST, OnItemchangedRecordlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Record List Data
 *
 *=========================================================================*/
static obreclistcolinit_t s_LvlListInit[] = {
	{ OB_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ OB_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
  };
/*===========================================================================
 *		End of Record List Data
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Constructor
 *
 *=========================================================================*/
CObLvlEditDlg::CObLvlEditDlg(CWnd* pParent) : CDialog(CObLvlEditDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CObLvlEditDlg)
	//}}AFX_DATA_INIT

  m_TitleValue      = _T("Edit Leveled Object");
  m_pSubrecord      = NULL;
  m_pRecordHandler  = NULL;
  m_EditorIDCheck   = OB_CHECKRESULT_NOCHANGE;
  m_pRecordTypes    = NULL;
  m_ParentFormID    = OB_FORMID_NULL;

  m_UpdateListOnChange = false;
}
/*===========================================================================
 *		End of Class CObLvlEditDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Method - void DoDataExchange ( pDX);
 *
 *=========================================================================*/
void CObLvlEditDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObLvlEditDlg)
	DDX_Control(pDX, IDC_OBJECT_FORMID, m_FormID);
	DDX_Control(pDX, IDC_LEVEL, m_Level);
	DDX_Control(pDX, IDC_COUNT, m_Count);
	DDX_Control(pDX, IDC_EDITORID, m_ObjectID);
	DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObLvlEditDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Method - void AddListColumns (void);
 *
 *=========================================================================*/
void CObLvlEditDlg::AddListColumns (void) {

  m_RecordList.DeleteAllColumns();    
  m_RecordList.SetupList(OB_NAME_NULL, s_LvlListInit, NULL);
}
/*===========================================================================
 *		End of Class Method CObLvlEditDlg::AddListColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Method - void FillRecordList (void);
 *
 *=========================================================================*/
void CObLvlEditDlg::FillRecordList (void) {
  dword		 Index;

	/* Clear the current content */
  m_RecordList.DeleteAllItems();

	/* Add all matching records */
  for (Index = 0; m_pRecordTypes[Index] != OB_NAME_NULL; ++Index) {
    FillRecordList(m_pRecordTypes[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CObLvlEditDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Method - void FillRecordList (RecordType);
 *
 *=========================================================================*/
void CObLvlEditDlg::FillRecordList (const obrectype_t RecordType) {
  CObTypeGroup*  pGroup;
  CObBaseRecord* pBaseRecord;
  CObRecord*	 pRecord;
  dword          Index;

  	/* Get the type group for the given record type */
  pGroup = m_pRecordHandler->GetTopGroup()->GetTypeGroup(RecordType);
  if (pGroup == NULL) return;

	/* Add all matching records in the group */
  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    pRecord     = ObCastRecord(pBaseRecord);
    if (pRecord == NULL) continue;
    if (pRecord->GetFormID() == m_ParentFormID) continue;

		/* Add the record */
    m_RecordList.AddRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Method CObLvlEditDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObLvlEditDlg::GetControlData (void) {
  CString	Buffer;
  word		Value;
  bool		Result;

  if (m_pSubrecord == NULL) return;

  m_Count.GetWindowText(Buffer);
  Result = ObFieldConvertWord(Buffer, Value);
  if (Result) m_pSubrecord->SetCount(Value);

  m_Level.GetWindowText(Buffer);
  Result = ObFieldConvertWord(Buffer, Value);
  if (Result) m_pSubrecord->SetLevel(Value);
  
  m_pSubrecord->SetFormID(m_ObjectFormID);
}
/*===========================================================================
 *		End of Class Method CObLvlEditDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CObLvlEditDlg::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
  HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

  if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_ObjectID) {
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
 *		End of Class Event CObLvlEditDlg::OnCtlColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Event - void OnDeleteButton ();
 *
 *=========================================================================*/
void CObLvlEditDlg::OnDeleteButton() {
  EndDialog(OB_LVLEDITDLG_RESULT_DELETE);
}
/*===========================================================================
 *		End of Class Event CObLvlEditDlg::OnDeleteButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObLvlEditDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  assert(m_pRecordHandler != NULL);
  m_UpdateListOnChange = false;

  SetWindowText(m_TitleValue);

  	/* Initialize the record list */
  m_RecordList.SetListName("LvlEditList");
  m_RecordList.DefaultSettings();
  AddListColumns();
  FillRecordList();
  m_RecordList.SortList(OB_FIELD_EDITORID);

  m_Count.SetLimitText(8);
  m_Level.SetLimitText(8);
  m_ObjectID.SetLimitText(128);

  SetControlData();

  m_UpdateListOnChange = true;
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObLvlEditDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CObLvlEditDlg::OnOK() {
  GetControlData();
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObLvlEditDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Event - void OnChangeEditorid ();
 *
 *=========================================================================*/
void CObLvlEditDlg::OnChangeEditorid() {
  CString       Buffer;
  int		Result;
  int		ListIndex;
  
  Result = UpdateEditorID();

  if (Result != m_EditorIDCheck) {
    m_EditorIDCheck = Result;
    m_ObjectID.RedrawWindow();
  }

  if (m_UpdateListOnChange) {
    m_UpdateListOnChange = false;
    m_ObjectID.GetWindowText(Buffer);
    
    ListIndex = m_RecordList.FindEditorID(Buffer);

    if (ListIndex >= 0) m_RecordList.SelectRecord(ListIndex);
    m_UpdateListOnChange = true;
  }

}
/*===========================================================================
 *		End of Class Event CObLvlEditDlg::OnChangeEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Event - void OnKillfocusEditorid ();
 *
 *=========================================================================*/
void CObLvlEditDlg::OnKillfocusEditorid() {

}
/*===========================================================================
 *		End of Class Event CObLvlEditDlg::OnKillfocusEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObLvlEditDlg::SetControlData (void) {
  CString Buffer;

  if (m_pSubrecord == NULL) return;

  Buffer.Format(_T("%u"), (dword) m_pSubrecord->GetCount());
  m_Count.SetWindowText(Buffer);

  Buffer.Format(_T("%u"), (dword) m_pSubrecord->GetLevel());
  m_Level.SetWindowText(Buffer);

  m_ObjectFormID = m_pSubrecord->GetFormID();
  Buffer.Format(_T("0x%08X"), m_ObjectFormID);
  m_FormID.SetWindowText(Buffer);

  Buffer = m_pRecordHandler->GetEditorID(m_ObjectFormID);  
  m_ObjectID.SetWindowText(Buffer);

  m_RecordList.SelectRecord(m_pRecordHandler->FindFormID(m_ObjectFormID));
}
/*===========================================================================
 *		End of Class Method CObLvlEditDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CObLvlEditDlg::UpdateEditorID (void) {
  CString	Buffer;
  CSString	EditorID;
  CObIdRecord*	pIdRecord;
  bool		Result;
  int		ListIndex;

  m_ObjectID.GetWindowText(Buffer);
  EditorID = Buffer;

  Result = ObPrepareEditorID(EditorID);
  if (!Result) return (OB_CHECKRESULT_ERROR);

  pIdRecord = m_pRecordHandler->FindEditorID(EditorID);
  if (pIdRecord == NULL) return (OB_CHECKRESULT_ERROR);
  if (pIdRecord->GetFormID() == m_ParentFormID) return (OB_CHECKRESULT_ERROR);

  ListIndex = m_RecordList.FindRecord(pIdRecord);
  if (ListIndex < 0) return (OB_CHECKRESULT_ERROR);

  m_ObjectFormID = pIdRecord->GetFormID();
  if (m_ObjectFormID == m_pSubrecord->GetFormID()) return (OB_CHECKRESULT_NOCHANGE);

  Buffer.Format(_T("0x%08X"), m_ObjectFormID);
  m_FormID.SetWindowText(Buffer);

  return (OB_CHECKRESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObLvlEditDlg::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlEditDlg Event - void OnItemchangedRecordlist (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObLvlEditDlg::OnItemchangedRecordlist (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW *) pNMHDR;
  CObRecord*   pRecord;
  CSString     Buffer;
  *pResult = 0;

  if (!m_UpdateListOnChange) return;

  pRecord = m_RecordList.GetSelectedRecord();
  if (pRecord == NULL) return;

  m_UpdateListOnChange = false;
  pRecord->GetField(Buffer, OB_FIELD_EDITORID);
  m_ObjectID.SetWindowText(Buffer);
  m_UpdateListOnChange = true;
}
/*===========================================================================
 *		End of Class Event CObLvlEditDlg::OnItemchangedRecordlist()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditLvlItemDlg (pSubrecord, ParentFormID);
 *
 * Displays a modal edit lvlo edit dialog for a leveled item.
 *
 *=========================================================================*/
int ObEditLvlItemDlg (CObLvloSubrecord* pSubrecord, CObRecordHandler* pHandler, const obformid_t ParentFormID) {
  static const obrectype_t s_LvliRecordTypes[] = {
	OB_NAME_ALCH,	OB_NAME_AMMO,	OB_NAME_APPA,	OB_NAME_ARMO,	OB_NAME_BOOK,	OB_NAME_CLOT,
	OB_NAME_INGR,	OB_NAME_KEYM,	OB_NAME_LVLI,	OB_NAME_MISC,	OB_NAME_SGST,	OB_NAME_SLGM,
	OB_NAME_WEAP,	OB_NAME_NULL };

  CObLvlEditDlg Dlg;
  int		Result;

  Dlg.SetRecordHandler(pHandler);
  Dlg.SetSubrecord(pSubrecord);
  Dlg.SetTitleValue(_T("Edit Leveled Item Entry"));
  Dlg.SetRecordTypes(s_LvliRecordTypes);
  Dlg.SetParentFormID(ParentFormID);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditLvlItemDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditLvlSpellDlg (pSubrecord, ParentFormID);
 *
 * Displays a modal edit lvlo edit dialog for a leveled spell.
 *
 *=========================================================================*/
int ObEditLvlSpellDlg (CObLvloSubrecord* pSubrecord, CObRecordHandler* pHandler, const obformid_t ParentFormID) {
  static const obrectype_t s_LvspRecordTypes[] = { OB_NAME_LVSP, OB_NAME_SPEL, OB_NAME_NULL };
  CObLvlEditDlg Dlg;
  int		Result;

  Dlg.SetRecordHandler(pHandler);
  Dlg.SetSubrecord(pSubrecord);
  Dlg.SetTitleValue(_T("Edit Leveled Spell Entry"));
  Dlg.SetRecordTypes(s_LvspRecordTypes);
  Dlg.SetParentFormID(ParentFormID);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditLvlSpellDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditLvlCreatureDlg (pSubrecord, ParentFormID);
 *
 * Displays a modal edit lvlo edit dialog for a leveled creature.
 *
 *=========================================================================*/
int ObEditLvlCreatureDlg (CObLvloSubrecord* pSubrecord, CObRecordHandler* pHandler, const obformid_t ParentFormID) {
  static const obrectype_t s_LvlcRecordTypes[] = { OB_NAME_LVLC, OB_NAME_NPC_, OB_NAME_CREA, OB_NAME_NULL };
  CObLvlEditDlg Dlg;
  int		Result;

  Dlg.SetRecordHandler(pHandler);
  Dlg.SetSubrecord(pSubrecord);
  Dlg.SetTitleValue(_T("Edit Leveled Creature Entry"));
  Dlg.SetRecordTypes(s_LvlcRecordTypes);
  Dlg.SetParentFormID(ParentFormID);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditLvlCreatureDlg()
 *=========================================================================*/


