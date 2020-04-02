/*===========================================================================
 *
 * File:	Obbatcheditdlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 30, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObBatchEditDlg.h"
#include "dialogs/obeditdlghandler.h"
#include "obeditdoc.h"


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

  IMPLEMENT_DYNCREATE(CObBatchEditDlg, CObRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Field Information
 *
 * Fields that will not be seen in the batch edit dialog.
 *
 *=========================================================================*/
obfieldid_t l_BadBatchFields[] = {
	OB_FIELD_FORMID,
	OB_FIELD_EDITORID,
	OB_FIELD_USERDATA,
	OB_FIELD_RECORDTYPE,
	OB_FIELD_ARMOR,		/* Use REALARMOR instead */
	OB_FIELD_NONE		/* Must be last */
};


bool l_IsBadBatchField (const obfieldid_t Field) {
  dword Index;

  for (Index = 0; l_BadBatchFields[Index] != OB_FIELD_NONE; ++Index) {
    if (l_BadBatchFields[Index] == Field) return (true);
  }

  return (false);
}
/*===========================================================================
 *		End of Field Information
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObBatchEditDlg, CObRecordDialog)
	//{{AFX_MSG_MAP(CObBatchEditDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FIELD_LIST, OnItemchangedFieldList)
	ON_NOTIFY(NM_KILLFOCUS, IDC_FIELD_LIST, OnKillfocusFieldList)
	ON_NOTIFY(NM_SETFOCUS, IDC_FIELD_LIST, OnSetfocusFieldList)
	ON_EN_CHANGE(IDC_BATCH_EDIT, OnChangeEditCtrl)
	ON_BN_CLICKED(ID_UNCHECKALL_BUTTON, OnUncheckAll)
	ON_BN_CLICKED(ID_CHECKALL_BUTTON, OnCheckAll)
	ON_WM_VSCROLL()
	ON_NOTIFY(NM_CLICK, IDC_FIELD_LIST, OnClickFieldList)
	ON_MESSAGE(ID_BATCHEDIT_MSG_UPDATE, OnEditUpdate)
	ON_EN_KILLFOCUS(IDC_BATCH_EDIT, OnKillfocusBatchEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Constructor
 *
 *=========================================================================*/	
CObBatchEditDlg::CObBatchEditDlg(CWnd* pParent)	: CObRecordDialog(CObBatchEditDlg::IDD) {
	//{{AFX_DATA_INIT(CObBatchEditDlg)
	//}}AFX_DATA_INIT

	m_InitialSetData  = false;
	m_SavedFieldCount = 0;
	m_CurrentEditItem = -1;
	m_Initialized     = false;
	m_IsChanging      = false;
}
/*===========================================================================
 *		End of Class CObBatchEditDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObBatchEditDlg::DoDataExchange(CDataExchange* pDX) {
	CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObBatchEditDlg)
	DDX_Control(pDX, IDC_FIELD_LIST, m_FieldList);
	DDX_Control(pDX, IDC_BATCH_EDIT, m_EditCtrl);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void AddEditRecords (Records);
 *
 *=========================================================================*/
void CObBatchEditDlg::AddEditRecords (CObRefRecordArray& Records) {
  dword Index;

  for (Index = 0; Index < Records.GetSize(); ++Index) {
    m_Records.Add(Records[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::AddEditRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void AddEditRecords (Records);
 *
 *=========================================================================*/
void CObBatchEditDlg::AddEditRecords (CObRecordArray& Records) {
  dword Index;

  for (Index = 0; Index < Records.GetSize(); ++Index) {
    m_Records.Add(Records[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::AddEditRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void AddFields (pRecord);
 *
 *=========================================================================*/
void CObBatchEditDlg::AddFields (CObRecord* pRecord) {
  const obrecfieldmap_t* pFieldMap;
  const obrecfield_t*	 pField;
  obbatchfieldinfo_t*	 pBatchInfo;
  dword			 Index;

	/* Enumerate all fields in the record */
  for (pFieldMap = pRecord->GetFieldMap(); pFieldMap != NULL; pFieldMap = pFieldMap->pBaseFieldMap) {
    assert(pFieldMap != pFieldMap->pBaseFieldMap);

    for (Index = 0; pFieldMap->pField[Index].GetMethod != NULL; ++Index) {
      pField = &pFieldMap->pField[Index];

		/* Don't add some fields */
      if (l_IsBadBatchField(pField->FieldID)) continue;
      if (pField->SetMethod == NULL) continue;
      if (pField->GetMethod == NULL) continue;

      pBatchInfo = new obbatchfieldinfo_t;
      m_Fields.Add(pBatchInfo);

      pBatchInfo->FieldID = pField->FieldID;
      pBatchInfo->Title   = pField->pName;
      
      (pRecord->*pField->GetMethod)(pBatchInfo->Value, 0);
    }
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::AddFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void ClearControlData (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::ClearControlData (void) {

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::ClearControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void CreateFieldArray (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::CreateFieldArray (void) {
  dword Index;

	/* Clear the current fields */
  m_Fields.Destroy();
  if (m_Records.GetSize() == 0) return;

  AddFields(m_Records[0]);

  for (Index = 1; Index < m_Records.GetSize(); ++Index) {
    RemoveMissingFields(m_Records[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::CreateFieldArray()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void FillFieldList (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::FillFieldList (void) {
  obbatchfieldinfo_t*	pBatchInfo;
  dword			Index;
  int			ListIndex;

	/* Clear the current contents */
  m_FieldList.DeleteAllItems();

  for (Index = 0; Index < m_Fields.GetSize(); ++Index) {
    pBatchInfo = m_Fields[Index];

    ListIndex = m_FieldList.InsertItem(Index, "");
    if (ListIndex < 0) continue;

    m_FieldList.SetItemData(ListIndex, (long) pBatchInfo);

    m_FieldList.SetItemText(ListIndex, OB_BATCHEDIT_SUBITEM_FIELD, pBatchInfo->Title);
    m_FieldList.SetItemText(ListIndex, OB_BATCHEDIT_SUBITEM_VALUE, pBatchInfo->Value);
    m_FieldList.SetCheck(ListIndex, pBatchInfo->Save);
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::FillFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::GetControlData (void) {
  CObRecord* pRecord;
  CObRecord* pNewRecord;
  dword      Index;
  bool	     Result;

  UpdateEditCtrl(-1);
    
	/* Get information from the list */
  UpdateSaveFields();

	/* Update all records */
  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pRecord = m_Records[Index];

		/* Prepare the record for saving */
    pNewRecord = PrepareRecord(pRecord);

    Result = UpdateFields(pNewRecord);
    if (!Result) AddObGeneralError("Some errors occurred setting fields for record 0x%08X!", pRecord->GetFormID());
    m_Records.SetAt(Index, pNewRecord);

		/* Update listeners */
    if (m_pRecordHandler != NULL) {
      m_pRecordHandler->GetEventHandler().SendUpdateEvent(pNewRecord, pRecord);
    }
  }

  if (m_pDlgHandler != NULL) {
    m_pDlgHandler->GetDocument()->SetModifiedFlag(TRUE);
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - bool IsEditRecord (pRecord);
 *
 *=========================================================================*/
bool CObBatchEditDlg::IsEditRecord (CObRecord* pRecord) {
  dword Index;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    if (m_Records[Index] == pRecord) return (true);
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::IsEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  //m_EditCtrl.Create(ES_WANTRETURN | WS_CHILD | ES_AUTOHSCROLL, CRect(0, 0, 10, 12), this, ID_BATCH_EDITCTRL);
  //m_EditCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE, 0);

  //m_FieldList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
  m_FieldList.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
  m_FieldList.InsertColumn(0, "Field", LVCFMT_LEFT, 150, OB_BATCHEDIT_SUBITEM_FIELD);
  m_FieldList.InsertColumn(1, "Value", LVCFMT_LEFT, 200, OB_BATCHEDIT_SUBITEM_VALUE);

  m_EditInfo.pNewRecord = NULL;
  m_EditInfo.pOldRecord = NULL;

  CreateFieldArray();

	/* Check for no common fields to batch edit */
  if (m_Fields.GetSize() == 0) {
    AddObGeneralError("There were no common fields in the %u records to batch edit!", m_Records.GetSize());
    Close();
    return;
  }
  
  SetTitle("");
  FillFieldList();

  m_FieldList.SetItem(0, 0, LVIF_STATE, "", 0, LVIS_SELECTED, LVIS_SELECTED, 0);
  UpdateEditCtrl(-1);

  SetControlData();

  m_Initialized = true;
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnSave (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnSave (void) {
  GetControlData();

	/* Close the window */
  Close();
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnCancel (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnCancel (void) {
  Close();
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnApply ();
 *
 *=========================================================================*/
void CObBatchEditDlg::OnApply() {

  GetControlData();

	/* Do another update */
  //SetControlData();
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnApply()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - CObRecord* PrepareRecord (pRecord);
 *
 *=========================================================================*/
CObRecord* CObBatchEditDlg::PrepareRecord (CObRecord* pRecord) {
  CObRecord* pNewRecord;
	
  if (m_pRecordHandler == NULL) return (NULL);

	/* Do a preupdate */
  m_pRecordHandler->GetEventHandler().SendPreUpdateEvent(pRecord, OB_EVENTFLAG_NONOTIFYSOURCE, (long) this);    

	/* Ensure the record is active  */
  if (pRecord->IsActive()) {
    pNewRecord = pRecord;
  }
  else {
    pNewRecord = m_pRecordHandler->MakeRecordActivePriv(pRecord, true);
  }

	/* Create the undo event */
  m_pRecordHandler->CreateUndoUpdate(pRecord);
  
  return (pNewRecord);
}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::PrepareRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void RemoveMissingFields (pRecord);
 *
 *=========================================================================*/
void CObBatchEditDlg::RemoveMissingFields (CObRecord* pRecord) {
  obbatchfieldinfo_t*	pBatchInfo;
  const obrecfield_t*	pField;
  int			Index;

  for (Index = (int) m_Fields.GetSize() - 1; Index >= 0; --Index) {
    pBatchInfo = m_Fields[Index];

    pField = pRecord->FindField(pBatchInfo->FieldID);
    if (pField == NULL) m_Fields.Delete(Index);
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::RemoveMissingFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::SetControlData (void) { 

	/* TODO: Update data? */

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void SetTitle (pEditorID);
 *
 *=========================================================================*/
void CObBatchEditDlg::SetTitle (const SSCHAR* pEditorID) {
  CString Buffer;

  Buffer.Format("%s -- Batch Edit %u Record%s", m_pDlgHandler->GetTitle(), GetNumRecords(), GetNumRecords() > 1 ? "s" : "");
  SetWindowText(Buffer);
  SetInternalWindowText(GetParentFrame()->m_hWnd, Buffer);
}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::SetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void UpdateFields (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::UpdateSaveFields (void) {
  obbatchfieldinfo_t*	pBatchInfo;
  int			Index;

  m_SavedFieldCount = 0;

  for (Index = 0; Index < m_FieldList.GetItemCount(); ++Index) {
    pBatchInfo = (obbatchfieldinfo_t *) m_FieldList.GetItemData(Index);
    if (pBatchInfo == NULL) continue;

    pBatchInfo->Save  = m_FieldList.GetCheck(Index) != 0;
    pBatchInfo->Value = m_FieldList.GetItemText(Index, OB_BATCHEDIT_SUBITEM_VALUE);
    ++m_SavedFieldCount;
  }

}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::UpdateSaveFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - bool UpdateFields (pRecord);
 *
 * Updates all checked fields for the given record.
 *
 *=========================================================================*/
bool CObBatchEditDlg::UpdateFields (CObRecord* pRecord) {
  obbatchfieldinfo_t*	pBatchInfo;
  dword			Index;
  bool			Result = true;
    
	/* Update each checked field */
  for (Index = 0; Index < m_Fields.GetSize(); ++Index) {
    pBatchInfo = m_Fields[Index];
    if (!pBatchInfo->Save) continue;

    Result &= pRecord->SetField(pBatchInfo->FieldID, pBatchInfo->Value);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::UpdateFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnItemchangedFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnItemchangedFieldList (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW *) pNMHDR;
  *pResult = 0;

  if (!m_Initialized) return;

  UpdateEditCtrl(pNMListView->iItem);
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnItemchangedFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Method - void UpdateEditCtrl (NewIndex);
 *
 *=========================================================================*/
void CObBatchEditDlg::UpdateEditCtrl (const int NewIndex) {
  obbatchfieldinfo_t*	pBatchInfo;
  CString Buffer;
  CString Buffer1;
  CRect   ItemRect;
  CRect   ListRect;
  CSize   ScrollSize;
  BOOL    Result;
  int     XPos;
  int     YPos;
  int     Height;
  int     Width1;
  int     Width2;

  m_IsChanging = true;

  if (m_CurrentEditItem >= 0) {
    m_EditCtrl.GetWindowText(Buffer);
    m_FieldList.SetItemText(m_CurrentEditItem, OB_BATCHEDIT_SUBITEM_VALUE, Buffer);
    pBatchInfo = (obbatchfieldinfo_t *) m_FieldList.GetItemData(m_CurrentEditItem);
    pBatchInfo->Value = Buffer;
  }

  m_CurrentEditItem = NewIndex;

  if (m_CurrentEditItem < 0) {  
    m_EditCtrl.ShowWindow(SW_HIDE);
    m_EditCtrl.SetWindowText("");
    m_IsChanging = false;
    return;
  }

	/* Ensure the item is completely visible */
  m_FieldList.EnsureVisible(m_CurrentEditItem, FALSE);

	/* TODO: Need better control positioning */
  Width1 = m_FieldList.GetColumnWidth(0);
  Width2 = m_FieldList.GetColumnWidth(1);
  Result = m_FieldList.GetItemRect(m_CurrentEditItem, &ItemRect, LVIR_BOUNDS);
  m_FieldList.GetWindowRect(ListRect);
  ScreenToClient(ListRect);
  
  if (!Result) {
    XPos   = 0;
    YPos   = 0;
    Height = 20;
  }
  else {
    XPos    = ItemRect.left + Width1 + ListRect.left + 5;
    YPos    = ItemRect.top  + ListRect.top + 1;
    Height  = ItemRect.Height() + 2;
    Width2 -= 5;
  }

  if (XPos + Width2 >= ListRect.right) {
    Width2 = ListRect.right - XPos - 20;
  }
    
  if (YPos + 20 > ListRect.bottom || YPos < ListRect.top + 18) {
    m_CurrentEditItem = -1;
    m_EditCtrl.ShowWindow(SW_HIDE);
    m_EditCtrl.SetWindowText("");
    m_FieldList.SetFocus();
    m_IsChanging = false;
    return;
  }
  
  m_EditCtrl.SetWindowText(m_FieldList.GetItemText(m_CurrentEditItem, OB_BATCHEDIT_SUBITEM_VALUE));
  m_EditCtrl.SetWindowPos(&m_FieldList, XPos, YPos, Width2, Height, SWP_SHOWWINDOW | SWP_NOZORDER);

  m_EditCtrl.SetFocus();
  //m_EditCtrl.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME);
  m_IsChanging = false;
}
/*===========================================================================
 *		End of Class Method CObBatchEditDlg::UpdateEditCtrl()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnKillfocusFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnKillfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnKillfocusFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnKillfocusBatchEdit (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnKillfocusBatchEdit (void) {
  UpdateEditCtrl(-1);
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnKillfocusBatchEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnSetfocusFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnSetfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;

  if (!m_Initialized) return;
  //m_IsChanging = true;

  //m_EditCtrl.SetFocus();
  //m_EditCtrl.RedrawWindow();

  //m_IsChanging = false;
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnSetfocusFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnChangeEditCtrl (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnChangeEditCtrl (void) {
  //if (m_IsChanging) return;
  //if (m_CurrentEditItem >= 0) m_FieldList.SetCheck(m_CurrentEditItem, TRUE);
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnChangeEditCtrl()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnUncheckAll (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnUncheckAll (void) {
  int Index;

  for (Index = 0; Index < m_FieldList.GetItemCount(); ++Index) {
    m_FieldList.SetCheck(Index, FALSE);
  }

}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnUncheckAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnCheckAll (void);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnCheckAll (void) {
  int Index;

  for (Index = 0; Index < m_FieldList.GetItemCount(); ++Index) {
    m_FieldList.SetCheck(Index, TRUE);
  }

}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnCheckAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnVScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  CObRecordDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnVScroll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - void OnClickFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchEditDlg::OnClickFieldList (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;

  m_EditCtrl.SetFocus();
  m_EditCtrl.RedrawWindow();
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnClickFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchEditDlg Event - LRESULT OnEditUpdate (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObBatchEditDlg::OnEditUpdate (WPARAM wParam, LPARAM lParam) {
  UpdateEditCtrl(wParam);
  return (0);
}
/*===========================================================================
 *		End of Class Event CObBatchEditDlg::OnEditUpdate()
 *=========================================================================*/

