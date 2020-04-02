/*===========================================================================
 *
 * File:	Obrecorddialog.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 11, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obrecorddialog.h"
#include "obeditdlghandler.h"
#include "resource.h"
#include "obedit.h"
#include "obeditdoc.h"
#include "obbipedpartsdlg.h"
#include "obbipedpartslistdlg.h"
#include "mainfrm.h"


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

  IMPLEMENT_DYNCREATE(CObRecordDialog, CFormView);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObRecordDialog, CFormView)
	//{{AFX_MSG_MAP(CObRecordDialog)
	ON_WM_DESTROY()
	ON_COMMAND(ID_APPLY_BUTTON, OnApply)
	ON_COMMAND(ID_CANCEL_BUTTON, OnCancel)
	ON_COMMAND(ID_SAVE_BUTTON, OnSave)
	ON_EN_KILLFOCUS(IDC_EDITORID, OnKillfocusEditorid)
	ON_BN_CLICKED(IDC_BIPEDPARTS_BUTTON, OnBipedpartsButton)
	ON_BN_CLICKED(IDC_EDIT_SCRIPT, OnEditScript)
	ON_BN_CLICKED(IDC_EDIT_ENCHANTMENT, OnEditEnchantment)
	ON_BN_CLICKED(IDC_SELECTSCRIPT_BUTTON, OnSelectScript)
	ON_BN_CLICKED(IDC_SELECTENCHANT_BUTTON, OnSelectEnchantment)
	ON_MESSAGE(ID_OBRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_SCRIPT, OnDropScript)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_SCRIPT, OnDropScript)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_ENCHANTMENT, OnDropEnchant)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_ENCHANTMENT, OnDropEnchant)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopy)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECTALL, OnUpdateEditSelectAll)
	ON_WM_HELPINFO()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_MODEL, OnDropModel)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_MODEL, OnDropModel)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_INVENTORYICON, OnDropIcon)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_INVENTORYICON, OnDropIcon)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_SOUNDFILE, OnDropSoundFile)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_SOUNDFILE, OnDropSoundFile)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_MALEICON, OnDropMaleIcon)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_MALEICON, OnDropMaleIcon)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_FEMALEICON, OnDropFemaleIcon)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_FEMALEICON, OnDropFemaleIcon)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_MALEWORLD, OnDropMaleWorldModel)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_MALEWORLD, OnDropMaleWorldModel)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_MALEBIPED, OnDropMaleBipedModel)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_MALEBIPED, OnDropMaleBipedModel)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_FEMALEWORLD, OnDropFemaleWorldModel)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_FEMALEWORLD, OnDropFemaleWorldModel)
	ON_NOTIFY(ID_OBRESOURCE_CHECKDROP, IDC_FEMALEBIPED, OnDropFemaleBipedModel)
	ON_NOTIFY(ID_OBRESOURCE_DROP, IDC_FEMALEBIPED, OnDropFemaleBipedModel)
	ON_COMMAND(IDC_SELECT_MODEL, OnSelectModel)
	ON_COMMAND(IDC_SELECT_ICON, OnSelectIcon)
	ON_COMMAND(IDC_SELECT_SOUNDFILE, OnSelectSoundFile)
	ON_COMMAND(IDC_SELECT_MALEICON, OnSelectMaleIcon)
	ON_COMMAND(IDC_SELECT_FEMALEICON, OnSelectFemaleIcon)
	ON_COMMAND(IDC_SELECT_MALEWORLDMODEL, OnSelectMaleWorldModel)
	ON_COMMAND(IDC_SELECT_MALEBIPEDMODEL, OnSelectMaleBipedModel)
	ON_COMMAND(IDC_SELECT_FEMALEWORLDMODEL, OnSelectFemaleWorldModel)
	ON_COMMAND(IDC_SELECT_FEMALEBIPEDMODEL, OnSelectFemaleBipedModel)
	ON_BN_CLICKED(IDC_SELECTSOUND_BUTTON, OnSelectsoundButton)
	ON_BN_CLICKED(IDC_EDIT_SOUND, OnEditSound)
	ON_NOTIFY(ID_OBRECORDLIST_CHECKDROP, IDC_SOUND, OnDropSound)
	ON_NOTIFY(ID_OBRECORDLIST_DROP, IDC_SOUND, OnDropSound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Default UI Fields
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObRecordDialog)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of Default UI Fields
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Tooltip Definitions
 *
 *=========================================================================*/
struct obrdtooltip_t {
	int ControlID;
	int StringID;
};

static obrdtooltip_t s_ToolTipInfo[] = {
	{ ID_SAVE_BUTTON,		IDS_TT_SAVE },
	{ ID_APPLY_BUTTON,		IDS_TT_APPLY },
	{ ID_CANCEL_BUTTON,		IDS_TT_CANCEL },
	{ IDC_BIPEDPARTS_BUTTON,	IDS_TT_EDITBIPED },
	{ IDC_EDIT_SCRIPT,		IDS_TT_EDITSCRIPT },
	{ IDC_SELECTSCRIPT_BUTTON,	IDS_TT_SELECTSCRIPT },
	{ IDC_EDIT_ENCHANTMENT,		IDS_TT_EDITENCHANT },
	{ IDC_SELECTENCHANT_BUTTON,	IDS_TT_SELECTENCHANT },
	{ IDC_SELECTCREATURE_BUTTON,	IDS_TT_SELECTCREATURE },
	{ IDC_EDIT_CREATURETEMPLATE,	IDS_TT_EDITCREATURE },
	{ IDC_EDIT_SOUND,		IDS_TT_EDITSOUND },
	{ IDC_SELECTSOUND_BUTTON,	IDS_TT_SELECTSOUND },
	{ IDC_EDIT_OPENSOUND,           IDS_TT_EDITSOUND },
	{ IDC_EDIT_CLOSESOUND,          IDS_TT_EDITSOUND },
	{ IDC_SELECTOPENSOUND_BUTTON,   IDS_TT_SELECTSOUND },
	{ IDC_SELECTCLOSESOUND_BUTTON,  IDS_TT_SELECTSOUND },
	{ IDC_EDIT_INGREDIANT,		IDS_TT_EDITINGREDIENT },
	{ IDC_SELECTINGREDIANT_BUTTON,  IDS_TT_SELECTINGREDIENT },
	{ IDC_MINATT_SLIDER,            IDS_TT_MINATTENUATION },
	{ IDC_MAXATT_SLIDER,            IDS_TT_MAXATTENUATION },
	{ IDC_STATATT_SLIDER,           IDS_TT_STATICATTENUATION },
	{ IDC_STARTTIME_SLIDER,         IDS_TT_STARTTIME },
	{ IDC_STOPTIME_SLIDER,          IDS_TT_STOPTIME },
	{ IDC_COLOR,			IDS_TT_COLORBOX },
	{ 0, 0 }
};
/*===========================================================================
 *		End of Tooltip Definitions
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObRecordDialog Constructor
 *
 *=========================================================================*/
CObRecordDialog::CObRecordDialog (const int ID) : CFormView(ID) {
  m_pRecordHandler   = NULL;
  m_pDlgHandler      = NULL;
  m_pEditorIDField   = NULL;
  m_pBipedPartsField = NULL;
  m_pScriptField     = NULL;
  m_pEnchantField    = NULL;
  m_pSoundField      = NULL;
  m_pModelField      = NULL;
  m_pIconField       = NULL;
  m_pSoundFileField  = NULL;

  m_pMaleWorldModelField   = NULL;
  m_pMaleBipedModelField   = NULL;
  m_pFemaleWorldModelField = NULL;
  m_pFemaleBipedModelField = NULL;
  m_pMaleIconField         = NULL;
  m_pFemaleIconField       = NULL;

  m_NoActivateRecord = false;

  m_hAccelerator  = NULL;
  m_AcceleratorID = IDR_DEFAULT_RECORD_ACCEL;

  m_InitialSetData = true;

  m_ScriptType  = 0;
  m_EnchantType = 0;

  m_TitlePrefix = _T("Unknown");
}
/*===========================================================================
 *		End of Class CObRecordDialog Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void ClearControlData (void);
 *
 *=========================================================================*/
void CObRecordDialog::ClearControlData (void) {
  SetTitle(NULL);
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::ClearControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void Close (void);
 *
 *=========================================================================*/
void CObRecordDialog::Close (void) {
  GetParentFrame()->DestroyWindow();
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::Close()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObRecordDialog::DoDataExchange(CDataExchange* pDX) {
  CFormView::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObRecordDialog)
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObRecordDialog::GetControlData (void) {
  CObIdRecord* pIdRecord;

  assert(m_EditInfo.pNewRecord != NULL);
  if (GetOutputRecord() == NULL) return;

	/* Update the editor id if required */
  if (m_EditInfo.HasUpdatedID || m_EditInfo.IsNew) {
    pIdRecord = ObCastClass(CObIdRecord, GetOutputRecord());
    if (pIdRecord != NULL) pIdRecord->SetEditorID(m_EditInfo.NewEditorID);
  }

  UpdateEditorID();
  GetUIFieldData();
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void GetUIFieldData (void);
 *
 *=========================================================================*/
void CObRecordDialog::GetUIFieldData (void) {
  obuirecfields_t* pFields;
  CButton*	   pButton;
  CString	   Buffer;
  CWnd*		   pWnd;
  dword		   Index;
  bool		   Result;

  if (GetOutputRecord() == NULL) return;

  pFields = GetUIFields();
  if (pFields == NULL) return;

  for (Index = 0; pFields[Index].FieldID != OB_FIELD_NONE; ++Index) {
    if (pFields[Index].FieldID == OB_FIELD_FORMID) continue;
    if (pFields[Index].FieldID == OB_FIELD_EDITORID) continue;

    pWnd = GetDlgItem(pFields[Index].ControlID);
    if (pWnd == NULL) continue;

    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      pWnd->GetWindowText(Buffer);

      Result = GetOutputRecord()->SetField(pFields[Index].FieldID, Buffer);
      if (!Result) continue;
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CComboBox))) {
      pWnd->GetWindowText(Buffer);
      
      Result = GetOutputRecord()->SetField(pFields[Index].FieldID, Buffer);
      if (!Result) continue;
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CButton))) {
      pButton = (CButton *) pWnd;
      Buffer = (pButton->GetCheck() != 0) ? "true" : "false" ;
      Result = GetOutputRecord()->SetField(pFields[Index].FieldID, Buffer);
      if (!Result) continue;
    }
  }

}
/*===========================================================================
 *		End of Class Method CObRecordDialog::GetUIFieldData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void InitToolTips (void);
 *
 *=========================================================================*/
void CObRecordDialog::InitToolTips (void) {
  obuirecfields_t* pFields;
  CString	   Buffer;
  CWnd*		   pWnd;
  dword		   Index;
  int		   Result;

  pFields = GetUIFields();
  if (pFields == NULL) return;

  for (Index = 0; pFields[Index].FieldID != OB_FIELD_NONE; ++Index) {
    if (pFields[Index].ToolTipID == 0) continue;

    pWnd = GetDlgItem(pFields[Index].ControlID);
    if (pWnd == NULL) continue;

    Result = Buffer.LoadString(pFields[Index].ToolTipID);
    if (Result) m_ToolTip.AddTool(pWnd, Buffer);
  }

	/* Add more fields */
  for (Index = 0; s_ToolTipInfo[Index].ControlID != 0; ++Index) {
    pWnd = GetDlgItem(s_ToolTipInfo[Index].ControlID);
    if (pWnd == NULL) continue;

    Result = Buffer.LoadString(s_ToolTipInfo[Index].StringID);
    if (Result) m_ToolTip.AddTool(pWnd, Buffer);
  }

  m_ToolTip.SetMaxTipWidth(300);
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::InitToolTips()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDestroy ();
 *
 *=========================================================================*/
void CObRecordDialog::OnDestroy() {
  CFormView::OnDestroy();
  if (m_pDlgHandler != NULL) m_pDlgHandler->RemoveFrame(GetParentFrame());
 }
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnInitialUpdate (void) {

  CFormView::OnInitialUpdate();
  ResizeParentToFit(FALSE);

  m_ToolTip.Create(this, 0);
  InitToolTips();
  m_ToolTip.Activate(TRUE);
  m_ToolTip.SetDelayTime(TTDT_AUTOPOP, 30000);

  assert(m_pDlgHandler != NULL);

	/* Load the accelerator table if present */
  if (m_AcceleratorID != 0) {
    m_hAccelerator = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(m_AcceleratorID));
  }

  m_EditInfo.IsHandled  = false;
  m_EditInfo.NeedsIndex = false;
   
  if (m_InitialSetData) SetControlData();
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - int OnPreSaveRecord (void);
 *
 *=========================================================================*/
int CObRecordDialog::OnPreSaveRecord (void) {
  int Result;

	/* This shouldn't happen... */
  if (m_pDlgHandler == NULL) {
    AddObGeneralError("Parent dialog handler for record dialog has not been set!");
    return (OB_RESULT_ERROR);
  }

         /* Update the editorid from the UI (do not save to record), check for validity */
  Result = UpdateEditorID();
  if (Result < 0) return (Result);
   
  Result = m_pDlgHandler->OnPreSaveRecord(m_EditInfo);
  if (Result < 0) return (Result);

  if (m_pRecordHandler != NULL && !m_EditInfo.IsNew && !m_EditInfo.IsCopy) {
    m_pRecordHandler->GetEventHandler().SendPreUpdateEvent(m_EditInfo.pOldRecord, OB_EVENTFLAG_NONOTIFYSOURCE, (long) this);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnPreSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - int OnPostSaveRecord (void);
 *
 *=========================================================================*/
int CObRecordDialog::OnPostSaveRecord (void) {
  
  if (m_pDlgHandler != NULL) {
    m_pDlgHandler->OnPostSaveRecord(m_EditInfo);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnPostSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - int OnCancelEditRecord (void);
 *
 *=========================================================================*/
int CObRecordDialog::OnCancelEditRecord (void) {
  
  if (m_pDlgHandler != NULL) {
    m_pDlgHandler->OnCancelEditRecord(m_EditInfo);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnCancelEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSave (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSave (void) {
  int Result;

  Result = OnPreSaveRecord();

  if (Result < 0) {
    if (Result != OB_RESULT_USERABORT) ObEditShowLastError("Failed to save the record changes!");
    return;
  }

  GetControlData();

  Result = OnPostSaveRecord();

  if (Result < 0) {
    ObEditShowLastError("Failed to save the record changes!");
    return;
  }

  Close();
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnCancel (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnCancel (void) {
  int Result;

  Result = OnCancelEditRecord();
  if (Result < 0) return;

  Close();
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnApply ();
 *
 *=========================================================================*/
void CObRecordDialog::OnApply() {
  int Result;

  Result = OnPreSaveRecord();

  if (Result < 0) {
    if (Result != OB_RESULT_USERABORT) ObEditShowLastError("Failed to apply the record changes!");
    return;
  }

  GetControlData();

  Result = OnPostSaveRecord();

  if (Result < 0) {
    ObEditShowLastError("Failed to apply the record changes!");
    return;
  }

	/* Reset the edit information */
  m_EditInfo.pOldRecord   = m_EditInfo.pNewRecord;
  m_EditInfo.pNewRecord   = NULL;
  m_EditInfo.HasUpdatedID = false;
  m_EditInfo.IsCopy       = false;
  m_EditInfo.IsRenamed    = false;
  m_EditInfo.IsNew        = false;
  m_EditInfo.IsHandled    = false;
  m_EditInfo.NeedsIndex   = false;

	/* Do another update */
  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnApply()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnUpdate (pSender, lHint, pHint);
 *
 *=========================================================================*/
void CObRecordDialog::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) {

  switch (lHint) {
    case OBEDIT_DOC_HINT_UPDATERECORD:
	break;
    default:
	CFormView::OnUpdate(pSender, lHint, pHint);
	break;
   }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - BOOL PreTranslateMessage (pMsg);
 *
 *=========================================================================*/
BOOL CObRecordDialog::PreTranslateMessage (MSG* pMsg) {
  int Result;

  m_ToolTip.RelayEvent(pMsg);

  if (m_hAccelerator != NULL) {
    if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST && m_hAccelerator != NULL) {
      Result = TranslateAccelerator(m_hWnd, m_hAccelerator, pMsg);
      if (Result != 0) return (Result);
    }
  }
	
  return CFormView::PreTranslateMessage(pMsg);
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::PreTranslateMessage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObRecordDialog::SetControlData (void) { 
  CSString Buffer;
  bool     Result;

  Result = GetInputRecord()->GetField(Buffer, OB_FIELD_EDITORID);

  if (Result)
    SetTitle(Buffer);
  else
    SetTitle("");

	/* Ignore invalid records */
  if (GetInputRecord() == NULL) {
    ClearControlData();
    return;
  }

  SetUIFieldData();
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void SetEditInfo (InputInfo);
 *
 *=========================================================================*/
void CObRecordDialog::SetEditInfo (obeditrecinfo_t& InputInfo) {
  m_EditInfo.HasUpdatedID = InputInfo.HasUpdatedID;
  m_EditInfo.IsCopy       = InputInfo.IsCopy;
  m_EditInfo.IsNew        = InputInfo.IsNew;
  m_EditInfo.IsRenamed    = InputInfo.IsRenamed;
  m_EditInfo.NewEditorID  = InputInfo.NewEditorID;
  m_EditInfo.pNewRecord   = InputInfo.pNewRecord;
  m_EditInfo.pOldRecord   = InputInfo.pOldRecord;
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::SetEditInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void SetTitle (pEditorID);
 *
 *=========================================================================*/
void CObRecordDialog::SetTitle (const SSCHAR* pEditorID) {
  CString Buffer;
  bool    IsActive = false;

  if (GetInputRecord() != NULL) IsActive = GetInputRecord()->IsActive();

  Buffer.Format("%s -- %s -- %s %s", m_pDlgHandler->GetTitle(), GetTitlePrefix(), pEditorID == NULL ? "" : pEditorID, IsActive ? "*" : "");

  //SetWindowText(Buffer);
  //SetInternalWindowText(GetParentFrame()->m_hWnd, Buffer);

  CWnd* pWnd = GetParentFrame();

  if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
    CFrameWnd* pFrame = (CFrameWnd *) pWnd;
    pFrame->SetTitle(Buffer);
    pFrame->SetWindowText(Buffer);
  }


}
/*===========================================================================
 *		End of Class Method CObRecordDialog::SetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - void SetUIFieldData (void);
 *
 *=========================================================================*/
void CObRecordDialog::SetUIFieldData (void) {
  obuirecfields_t* pFields;
  CButton*	   pButton;
  CEdit*	   pEdit;
  CComboBox*	   pComboBox;
  CSString	   Buffer;
  CWnd*		   pWnd;
  dword		   Index;
  bool		   Result;

  pFields = GetUIFields();
  if (pFields == NULL) return;

  for (Index = 0; pFields[Index].FieldID != OB_FIELD_NONE; ++Index) {
    pWnd = GetDlgItem(pFields[Index].ControlID);
    if (pWnd == NULL) continue;

		/* Save special fields for later use */
    switch (pFields[Index].FieldID) {
      case OB_FIELD_EDITORID:    m_pEditorIDField   = pWnd; break;
      case OB_FIELD_BIPED:       m_pBipedPartsField = pWnd; break;
      case OB_FIELD_SCRIPT:      m_pScriptField     = pWnd; break;
      case OB_FIELD_ENCHANTMENT: m_pEnchantField    = pWnd; break;
      case OB_FIELD_MODEL:       m_pModelField      = pWnd; m_pMaleBipedModelField = pWnd; break;
      case OB_FIELD_ICON:        m_pIconField       = pWnd; m_pMaleIconField = pWnd; break;
      case OB_FIELD_SOUNDFILE:   m_pSoundFileField  = pWnd; break;
      case OB_FIELD_SOUND:       m_pSoundField      = pWnd; break;
      case OB_FIELD_MODEL2:      m_pMaleWorldModelField   = pWnd; break;
      case OB_FIELD_MODEL3:      m_pFemaleBipedModelField = pWnd; break;
      case OB_FIELD_MODEL4:      m_pFemaleWorldModelField = pWnd; break;
      case OB_FIELD_ICON2:       m_pFemaleIconField = pWnd; break;
    }

    Result = GetInputRecord()->GetField(Buffer, pFields[Index].FieldID);
    if (!Result) continue;

    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      pEdit = (CEdit *) pWnd;
      if (pFields[Index].MaxLength > 0) pEdit->SetLimitText(pFields[Index].MaxLength);
      pWnd->SetWindowText(Buffer);
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CComboBox))) {
      pComboBox = (CComboBox *) pWnd;
      FindComboBoxString(*pComboBox, Buffer, true);
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CButton))) {
      pButton = (CButton *) pWnd;
      pButton->SetCheck(tolower(Buffer[0]) == 't');
    }
  }

}
/*===========================================================================
 *		End of Class Method CObRecordDialog::SetUIFieldData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CObRecordDialog::UpdateEditorID (void) {
  CString Buffer;

  m_EditInfo.NewEditorID.Empty();
  m_EditInfo.HasUpdatedID = false;

  if (m_pEditorIDField != NULL) {
    m_pEditorIDField->GetWindowText(Buffer);
    m_EditInfo.NewEditorID = Buffer;

    ObPrepareEditorID(m_EditInfo.NewEditorID);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObRecordDialog::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnKillfocusEditorid ();
 *
 *=========================================================================*/
void CObRecordDialog::OnKillfocusEditorid() {
  CString  Buffer;
  CSString TempString;

  if (m_pEditorIDField != NULL) {
    m_pEditorIDField->GetWindowText(Buffer);
    TempString = Buffer;

    ObPrepareEditorID(TempString);

    m_pEditorIDField->SetWindowText(TempString);
  }
	
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnKillfocusEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnBipedpartsButton ();
 *
 *=========================================================================*/
void CObRecordDialog::OnBipedpartsButton() {
  CString  Buffer;
  CSString TempString;
  bool     Result;
  dword    Parts;

  if (m_pBipedPartsField == NULL) return;

  m_pBipedPartsField->GetWindowText(Buffer);
  Parts = ParseObBipedFlagString(Buffer, ",");

  //Result = ObEditBipedParts(Parts);
  Result = ObEditBipedPartsList(Parts);
  
  MakeObBipedFlagString(TempString, Parts, ", ");
  m_pBipedPartsField->SetWindowText(TempString);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnBipedpartsButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditScript ();
 *
 *=========================================================================*/
void CObRecordDialog::OnEditScript() {
  CString    Buffer;
  CObRecord* pRecord;

  if (m_pScriptField == NULL || m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_pScriptField->GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(OB_NAME_SCPT);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditEnchantment ();
 *
 *=========================================================================*/
void CObRecordDialog::OnEditEnchantment() {
  CString    Buffer;
  CObRecord* pRecord;

  if (m_pEnchantField == NULL || m_pDlgHandler == NULL || m_pDlgHandler == NULL) return;
  m_pEnchantField->GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(OB_NAME_ENCH);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditEnchantment()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectScript ();
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectScript() {
  CString    Buffer;
  bool       Result;

  if (m_pScriptField == NULL) return;
  m_pScriptField->GetWindowText(Buffer);
  
  switch (m_ScriptType) {
    case OB_SCRIPTTYPE_OBJECT:      Result = m_pDlgHandler->SelectItemScript(Buffer); break;
    case OB_SCRIPTTYPE_QUEST:       Result = false; break;
    case OB_SCRIPTTYPE_MAGICEFFECT: Result = false; break;
    default:                        Result = false; break;
  }

  if (Result) m_pScriptField->SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectEnchantment ();
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectEnchantment() {
  CString    Buffer;
  bool       Result;

  if (m_pEnchantField == NULL) return;
  m_pEnchantField->GetWindowText(Buffer);
  
  switch (m_EnchantType) {
    case OB_ENCHTYPE_APPAREL: Result = m_pDlgHandler->SelectApparelEnchant(Buffer); break;
    case OB_ENCHTYPE_WEAPON:  Result = m_pDlgHandler->SelectWeaponEnchant(Buffer);  break;
    case OB_ENCHTYPE_STAFF:   Result = m_pDlgHandler->SelectStaffEnchant(Buffer);  break;
    case OB_ENCHTYPE_SCROLL:  Result = m_pDlgHandler->SelectScrollEnchant(Buffer); break;
    default:                  Result = false; break;
  }

  if (Result) m_pEnchantField->SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectEnchantment()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
 *
 *=========================================================================*/
void CObRecordDialog::OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView) {

  if (bActivate && pActivateView != NULL) {
    AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &m_pRecordHandler->GetUndoItems(), 0);
  }
  else if (pActivateView != NULL)  {
  }

  CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnActivateView()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CObRecordDialog Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObRecordDialog::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  CObRecord*      pRecord = (CObRecord *) wParam;
  obeditrecinfo_t EditInfo;

  if (pRecord == NULL) return (0);
  if (m_NoActivateRecord) return (0);
  if (m_pDlgHandler == NULL) return (0);
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = false;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.pOldRecord   = pRecord;
  EditInfo.NewEditorID.Empty();

  m_pDlgHandler->EditRecord(EditInfo);

  return (0);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropScript (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropScript (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;
  CObRecord*	     pRecord;
  CObScptRecord*     pScript;

  *pResult = OBRL_DROPCHECK_ERROR;
  if (m_pScriptField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != OB_NAME_SCPT) return;
  pScript = ObCastClass(CObScptRecord, pRecord);
  if (pScript == NULL) return;
  if (pScript->GetType() != m_ScriptType) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_OBRECORDLIST_DROP) {
    m_pScriptField->SetWindowText(pScript->GetEditorID());
  }

  *pResult = OBRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropEnchant (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropEnchant (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;
  CObRecord*	     pRecord;
  CObEnchRecord*     pEnchant;

  *pResult = OBRL_DROPCHECK_ERROR;
  if (m_pEnchantField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != OB_NAME_ENCH) return;
  pEnchant = ObCastClass(CObEnchRecord, pRecord);
  if (pEnchant == NULL) return;
  if (pEnchant->GetType() != m_EnchantType) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_OBRECORDLIST_DROP) {
    m_pEnchantField->SetWindowText(pEnchant->GetEditorID());
  }

  *pResult = OBRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditCut (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnEditCut (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Cut();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Cut();
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditCut()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditCopy (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnEditCopy (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Copy();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Copy();
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditPaste (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnEditPaste (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Paste();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Paste();
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditPaste()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditSelectAll (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnEditSelectAll (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->SetSel(0, pEdit->GetWindowTextLength());
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->SetSel(0, pRichEdit->GetWindowTextLength());
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
    CListCtrl* pList = (CListCtrl *) pWnd;

    for (int Index = 0; Index < pList->GetItemCount(); ++Index) {
      pList->SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
    }
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditSelectAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnUpdateEditSelectAll (pCmdUI);
 *
 *=========================================================================*/
void CObRecordDialog::OnUpdateEditSelectAll (CCmdUI* pCmdUI) {
  CWnd* pWnd = GetFocus();
  bool  EnableCmd = false;

  if (pWnd != NULL) {
    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
      EnableCmd = true;
    }
  }

  pCmdUI->Enable(EnableCmd);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnUpdateEditSelectAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnUpdateEditPaste (pCmdUI);
 *
 *=========================================================================*/
void CObRecordDialog::OnUpdateEditPaste (CCmdUI* pCmdUI) {
  CWnd* pWnd = GetFocus();
  bool  EnableCmd = false;

  if (pWnd != NULL) {
    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
      EnableCmd = false;
    }
  }

  pCmdUI->Enable(EnableCmd);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnUpdateEditPaste()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnUpdateEditCopy (pCmdUI);
 *
 *=========================================================================*/
void CObRecordDialog::OnUpdateEditCopy (CCmdUI* pCmdUI) {
  CWnd* pWnd = GetFocus();
  bool  EnableCmd = false;

  if (pWnd != NULL) {
    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      CEdit* pEdit = (CEdit *) pWnd;
      int    StartSel;
      int    EndSel;
      pEdit->GetSel(StartSel, EndSel);
      if (EndSel > StartSel) EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
      CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
      if (pRichEdit->GetSelectionType() != SEL_EMPTY) EnableCmd = true;
    }
  }

  pCmdUI->Enable(EnableCmd);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnUpdateEditCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditUndo (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnEditUndo (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Undo();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Undo();
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - BOOL OnHelpInfo (pHelpInfo);
 *
 *=========================================================================*/
BOOL CObRecordDialog::OnHelpInfo (HELPINFO* pHelpInfo) {
  
  m_pDlgHandler->OnHelp(this, pHelpInfo);

  return (true);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnHelpInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnHelp (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnHelp (void) {
  m_pDlgHandler->OnHelp(this, NULL);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropMaleWorldModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropMaleWorldModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pMaleWorldModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pMaleWorldModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropMaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropMaleBipedModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropMaleBipedModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pMaleBipedModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pMaleBipedModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropMaleBipedModel()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropFemaleWorldModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropFemaleWorldModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pFemaleWorldModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pFemaleWorldModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropFemaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropFemaleBipedModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropFemaleBipedModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pFemaleBipedModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pFemaleBipedModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropFemaleBipedModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropIcon (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropIcon (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pIconField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_IMAGE) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_TEXTURES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pIconField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropMaleIcon (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropMaleIcon (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pMaleIconField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_IMAGE) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_TEXTURES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pMaleIconField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropMaleIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropFemaleIcon (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropFemaleIcon (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pFemaleIconField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_IMAGE) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_TEXTURES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pFemaleIconField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropFemaleIcon()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropSoundFile (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropSoundFile (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obresourcedropinfo_t* pDropInfo = (obresourcedropinfo_t *) pNotifyStruct;

  *pResult = OBRESOURCE_DROPCHECK_ERROR;

  if (m_pSoundFileField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != OB_RESOURCETYPE_SOUND) return;
  if (!pDropInfo->pResourceFile->IsInPath(OBRESOURCE_PATH_SOUNDS)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_OBRESOURCE_DROP) {
    m_pSoundFileField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = OBRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropSoundFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectModel (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectModel (void) {
  CString Buffer;

  if (m_pModelField == NULL) return;
  m_pModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectIcon (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectIcon (void) {
  CString Buffer;

  if (m_pIconField == NULL) return;
  m_pIconField->GetWindowText(Buffer);

  m_pDlgHandler->SelectIcon(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectSoundFile (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectSoundFile (void) {
  CString Buffer;

  if (m_pSoundFileField == NULL) return;
  m_pSoundFileField->GetWindowText(Buffer);

  m_pDlgHandler->SelectSoundFile(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectSoundFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectMaleIcon (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectMaleIcon (void) {
  CString Buffer;

  if (m_pMaleIconField == NULL) return;
  m_pMaleIconField->GetWindowText(Buffer);

  m_pDlgHandler->SelectIcon(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectMaleIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectFemaleIcon (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectFemaleIcon (void) {
  CString Buffer;

  if (m_pFemaleIconField == NULL) return;
  m_pFemaleIconField->GetWindowText(Buffer);

  m_pDlgHandler->SelectIcon(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectMaleIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectMaleWorldModel (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectMaleWorldModel (void) {
  CString Buffer;

  if (m_pMaleWorldModelField == NULL) return;
  m_pMaleWorldModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectMaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectMaleBipedModel (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectMaleBipedModel (void) {
  CString Buffer;

  if (m_pMaleBipedModelField == NULL) return;
  m_pMaleBipedModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectMaleBipedModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectFemaleWorldModel (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectFemaleWorldModel (void) {
  CString Buffer;

  if (m_pFemaleWorldModelField == NULL) return;
  m_pFemaleWorldModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectFemaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectFemaleBipedModel (void);
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectFemaleBipedModel (void) {
  CString Buffer;

  if (m_pFemaleBipedModelField == NULL) return;
  m_pFemaleBipedModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectFemaleBipedModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnSelectsoundButton ();
 *
 *=========================================================================*/
void CObRecordDialog::OnSelectsoundButton() {
  CString    Buffer;
  bool       Result;

  if (m_pSoundField == NULL) return;
  m_pSoundField->GetWindowText(Buffer);

  Result = m_pDlgHandler->SelectSound(Buffer);
  if (Result) m_pSoundField->SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnSelectsoundButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnEditSound ();
 *
 *=========================================================================*/
void CObRecordDialog::OnEditSound() {
  CString    Buffer;
  CObRecord* pRecord;

  if (m_pSoundField == NULL) return;
  if (m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_pSoundField->GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(OB_NAME_SOUN);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnEditSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordDialog Event - void OnDropSound (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CObRecordDialog::OnDropSound (NMHDR* pNotifyStruct, LRESULT* pResult) {
  obrldroprecords_t* pDropItems = (obrldroprecords_t *) pNotifyStruct;
  CObRecord*	     pRecord;
  CObIdRecord*       pSound;

  *pResult = OBRL_DROPCHECK_ERROR;
  if (m_pSoundField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != OB_NAME_SOUN) return;
  pSound = ObCastClass(CObIdRecord, pRecord);
  if (pSound == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_OBRECORDLIST_DROP) {
    m_pSoundField->SetWindowText(pSound->GetEditorID());
  }

  *pResult = OBRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CObRecordDialog::OnDropSound()
 *=========================================================================*/
