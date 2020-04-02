 /*===========================================================================
 *
 * File:	Obeditdlghandler.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 25, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obeditdlghandler.h"
#include "../obeditdoc.h"
#include "mainfrm.h"
#include "childfrmfix.h"
#include "childfrmscript.h"
#include "obedit.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Static class options member */
  obdlghandleroptions_t CObEditDlgHandler::m_Options;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Dialog Creation Info
 *
 *=========================================================================*/
obdlgcreateinfo_t l_ObDlgCreateInfo[] = {
        { &OB_NAME_ALCH, "Potion",	     CObAlchView::IDD,   RUNTIME_CLASS(CObAlchView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Potion"),		_T("Potion") },
	{ &OB_NAME_ACTI, "Activator",	     CObActiView::IDD,   RUNTIME_CLASS(CObActiView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Activator"),		_T("Activator") },
	{ &OB_NAME_AMMO, "Ammo",	     CObAmmoView::IDD,   RUNTIME_CLASS(CObAmmoView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Ammunition"),		_T("Ammo") },
	{ &OB_NAME_APPA, "Apparatus",	     CObAppaView::IDD,   RUNTIME_CLASS(CObAppaView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Apparatus"),		_T("Apparatus") },
	{ &OB_NAME_ARMO, "Armor",	     CObArmorView::IDD,  RUNTIME_CLASS(CObArmorView), RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Armor"),		_T("Armor") },
	{ &OB_NAME_BOOK, "Book",	     CObBookView::IDD,   RUNTIME_CLASS(CObBookView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Book"),		_T("Book") },
	{ &OB_NAME_CLOT, "Clothing",	     CObClotView::IDD,   RUNTIME_CLASS(CObClotView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Clothing"),		_T("Clothing") },
	{ &OB_NAME_CONT, "Container",	     CObContView::IDD,   RUNTIME_CLASS(CObContView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Container"),		_T("Container") },
	{ &OB_NAME_ENCH, "Enchantment",	     CObEnchView::IDD,   RUNTIME_CLASS(CObEnchView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Enchantment"),	_T("Enchantment") },
	{ &OB_NAME_FLOR, "Flora",	     CObFlorView::IDD,   RUNTIME_CLASS(CObFlorView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Flora"),		_T("Flora") },
	{ &OB_NAME_FURN, "Furniture",	     CObFurnView::IDD,   RUNTIME_CLASS(CObFurnView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Furniture"),		_T("Furniture") },
	{ &OB_NAME_INGR, "Ingredient",	     CObIngrView::IDD,   RUNTIME_CLASS(CObIngrView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Ingredient"),		_T("Ingredient") },
	{ &OB_NAME_KEYM, "Key",		     CObKeymView::IDD,   RUNTIME_CLASS(CObKeymView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Key"),		_T("Key") },
	{ &OB_NAME_LVLC, "Leveled Creature", CObLvlcView::IDD,   RUNTIME_CLASS(CObLvlcView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Leveled_Creature"),	_T("Leveled_Creature") },
	{ &OB_NAME_LVLI, "Leveled Item",     CObLvliView::IDD,   RUNTIME_CLASS(CObLvliView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Leveled_Item"),	_T("Leveled_Item") },
	{ &OB_NAME_LVSP, "Leveled Spell",    CObLvspView::IDD,   RUNTIME_CLASS(CObLvspView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Leveled_Spell"),	_T("Leveled_Spell") },
	{ &OB_NAME_LIGH, "Light",	     CObLighView::IDD,   RUNTIME_CLASS(CObLighView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Light"),		_T("Light") },
	{ &OB_NAME_MISC, "Misc",	     CObMiscView::IDD,   RUNTIME_CLASS(CObMiscView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Misc_Item"),		_T("Miscellaneous_Items") },
	{ &OB_NAME_SGST, "Sigil Stone",      CObSgstView::IDD,   RUNTIME_CLASS(CObSgstView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Sigil_Stone"),	_T("Sigil_Stone") },
	{ &OB_NAME_SLGM, "Soul Gem",         CObSlgmView::IDD,   RUNTIME_CLASS(CObSlgmView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Soul_Gem"),		_T("Soul_Gem") },
	{ &OB_NAME_SOUN, "Sound",            CObSounView::IDD,   RUNTIME_CLASS(CObSounView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Sound"),		_T("Sound") },
	{ &OB_NAME_SPEL, "Spell",            CObSpelView::IDD,   RUNTIME_CLASS(CObSpelView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Spell"),		_T("Spell") },
	{ &OB_NAME_STAT, "Static",           CObStatView::IDD,   RUNTIME_CLASS(CObStatView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes4Mod:ObEdit/User_Interface/Static"),		_T("Static") },
	{ &OB_NAME_SCPT, "Script",           CObScptView::IDD,   RUNTIME_CLASS(CObScptView),  RUNTIME_CLASS(CChildFrameScript),	_T("Tes4Mod:ObEdit/User_Interface/Script"),		_T("Category:Scripting") },
	{ &OB_NAME_WEAP, "Weapon",           CObWeapView::IDD,   RUNTIME_CLASS(CObWeapView),  RUNTIME_CLASS(CChildFrame),	_T("Tes4Mod:ObEdit/User_Interface/Weapon"),		_T("Weapon") },
	{ &OB_NAME_NULL, NULL, 0, NULL, NULL,	NULL,	NULL }	/* Must be last */
};


obdlgcreateinfo_t l_ObBatchEditCreateInfo = {
	&OB_NAME_NULL, "Batch Edit",	CObBatchEditDlg::IDD,  RUNTIME_CLASS(CObBatchEditDlg), RUNTIME_CLASS(CChildFrameFix), _T("Tes4Mod:ObEdit/User_Interface/Batch_Edit"), NULL
};


obdlgcreateinfo_t l_ObFindCreateInfo = {
	&OB_NAME_NULL, "Find",	CObFindDlg::IDD,  RUNTIME_CLASS(CObFindDlg), RUNTIME_CLASS(CChildFrameFix), _T("Tes4Mod:ObEdit/User_Interface/Find"), NULL
};
/*===========================================================================
 *		End of Dialog Creation Info
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Constructor
 *
 *=========================================================================*/
CObEditDlgHandler::CObEditDlgHandler () {
  m_pDocument = NULL;
}
/*===========================================================================
 *		End of Class CObEditDlgHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - void Destroy (void);
 *
 *=========================================================================*/
void CObEditDlgHandler::Destroy (void) {

	/* Force all currently open dialogs to close */  CloseAll();

}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool BatchEdit (Records);
 *
 * Opens a new batch edit window for the given group of records. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CObEditDlgHandler::BatchEdit (CObRefRecordArray& Records) {
  obdlginfo_t* pDlgInfo;

	/* Ignore if nothing to edit */
  if (Records.GetSize() == 0) return (false);

	/* Create the new window */
  pDlgInfo = CreateDlg(l_ObBatchEditCreateInfo);

  if (pDlgInfo == NULL) {
    ObEditShowLastError("Failed to create the batch edit dialog!");
    return (false);
  }

	/* Initialize the batch window */
  if (pDlgInfo->pRecordDlg != NULL && pDlgInfo->pRecordDlg->IsKindOf(RUNTIME_CLASS(CObBatchEditDlg))) {
    CObBatchEditDlg* pBatchEditDlg = (CObBatchEditDlg *) pDlgInfo->pRecordDlg;
    pBatchEditDlg->AddEditRecords(Records);
  }

  pDlgInfo->pFrameWnd->InitialUpdateFrame(m_pDocument, TRUE);
  pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::BatchEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - void CloseAll (void);
 *
 * Closes all currently open dialogs. No record information is saved and
 * the user is not prompted.
 *
 *=========================================================================*/
void CObEditDlgHandler::CloseAll (void) {
  obdlginfo_t* pDlgInfo;

	/* Pop dialogs before destroying to prevent objects from being deleted
	   twice from the CObRecordDialog::OnDestroy() event */
  while (m_OpenDialogs.GetSize() > 0) {
    pDlgInfo = m_OpenDialogs.Remove((dword)0);
    Close(pDlgInfo);
    delete pDlgInfo;
  }

  m_OpenDialogs.Destroy();
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::CloseAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - dword CloseAll (pRecord, Source);
 *
 * Closes all currently open dialogs that are editing the given record.
 * No changes are saved and no prompts are given to the user. Returns
 * the number of dialogs closed.
 *
 *=========================================================================*/
dword CObEditDlgHandler::CloseAll (CObRecord* pRecord, const long Source) {
  obdlginfo_t* pDlgInfo;
  int          Index;
  dword	       Count = 0;

  for (Index = (int) m_OpenDialogs.GetSize() - 1; Index >= 0; --Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);

    if (pDlgInfo->pRecordDlg == NULL) continue;
    if (Source != 0 && Source == (long) pDlgInfo->pRecordDlg) continue;
    if (!pDlgInfo->pRecordDlg->IsEditRecord(pRecord)) continue;

    pDlgInfo = m_OpenDialogs.Remove(Index);
    Close(pDlgInfo);
    delete pDlgInfo;

    ++Count;
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::CloseAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - void Close (pDlgInfo);
 *
 *=========================================================================*/
void CObEditDlgHandler::Close (obdlginfo_t* pDlgInfo) {
  pDlgInfo->pFrameWnd->CloseWindow();
  pDlgInfo->pFrameWnd->DestroyWindow();
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::Close()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlginfo_t* CreateDlg (CreateInfo);
 *
 * Creates a new dialog window according to the input creation information.
 * Returns the new dialog information or NULL on any error.
 *
 *=========================================================================*/
obdlginfo_t* CObEditDlgHandler::CreateDlg (obdlgcreateinfo_t& CreateInfo) {
  obdlginfo_t*     pDlgInfo;
  CCreateContext   Context;
  CFrameWnd*       pFrame;
  CObRecordDialog* pRecordDlg = NULL;
  CWnd*		   pWnd;

	/* Initialize the context structure */
  Context.m_pCurrentDoc     = (CDocument *) m_pDocument;
  Context.m_pCurrentFrame   = NULL;
  Context.m_pNewDocTemplate = NULL;
  Context.m_pLastView       = NULL;
  Context.m_pNewViewClass   = CreateInfo.pViewClass;

	/* Create the dialog parent frame */  
  pFrame = (CFrameWnd *) CreateInfo.pFrameClass->CreateObject();
  ASSERT_KINDOF(CFrameWnd, pFrame);

	/* Create new form view from resource */
  pFrame->LoadFrame(CreateInfo.ResourceID, WS_OVERLAPPEDWINDOW, NULL, &Context);

  	/* Attempt to initialize the new view */
  pWnd = pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);

  if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CObRecordDialog))) {
    pRecordDlg = (CObRecordDialog *) pWnd;

    pRecordDlg->SetDlgHandler(this);
    pRecordDlg->SetRecordHandler(&m_pDocument->GetRecordHandler());
    pRecordDlg->SetTitlePrefix(CreateInfo.pTitlePrefix);
  }

	/* Create and initialize the new dialog info object */
  pDlgInfo = new obdlginfo_t;
  m_OpenDialogs.Add(pDlgInfo);

  pDlgInfo->pCreateInfo = &CreateInfo;
  pDlgInfo->pFrameWnd   = pFrame;
  pDlgInfo->pRecordDlg  = pRecordDlg;

  return (pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::CreateDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlginfo_t* CreateDlg (RecordType);
 *
 * Create a new dialog according to a record type. Returns NULL on any
 * error.
 *
 *=========================================================================*/
obdlginfo_t* CObEditDlgHandler::CreateDlg (const obrectype_t RecordType) {
  obdlginfo_t*       pDlgInfo;
  obdlgcreateinfo_t* pCreateInfo;

	/* Attempt to find a matching creation info */
  pCreateInfo = FindCreateInfo(RecordType);

  if (pCreateInfo == NULL) {
    AddObGeneralError("Failed to create a new dialog for record type %4.4s!", RecordType.Name);
    return (NULL);
  }

	/* Create the new dialog */
  pDlgInfo = CreateDlg(*pCreateInfo);
  return (pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::CreateDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlginfo_t* CreateDlg (EditInfo);
 *
 * Creates a dialog according to the input record. Returns NULL on any
 * error. If a dialog for the given record is already open, the existing
 * dialog object is returned.
 *
 *=========================================================================*/
obdlginfo_t* CObEditDlgHandler::CreateDlg (obeditrecinfo_t& EditInfo) {
  obdlginfo_t* pDlgInfo;

	/* Ignore invalid input */
  if (EditInfo.pOldRecord == NULL) return (NULL);

	/* Search for an existing open dialog */
  pDlgInfo = FindOpenDlg(EditInfo.pOldRecord);
  if (pDlgInfo != NULL) return (pDlgInfo);

	/* Create a new dialog */
  pDlgInfo = CreateDlg(EditInfo.pOldRecord->GetRecordType());
  if (pDlgInfo == NULL) return (NULL);

	/* Initialize the record dialog object some more */
  if (pDlgInfo->pRecordDlg != NULL) {
    pDlgInfo->pRecordDlg->SetEditInfo(EditInfo);
  }

  return (pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::CreateDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool EditRecord (EditInfo);
 *
 * Display a dialog to edit the given record.  The current dialogs that are
 * open are checked to see if the record is already being edited.  If it 
 * is, the dialog is activated.  Otherwise a new dialog is created and
 * displayed to edit the record.
 *
 *=========================================================================*/
bool CObEditDlgHandler::EditRecord (obeditrecinfo_t& EditInfo) {
  obdlginfo_t* pDlgInfo;

	/* Ignore invalid input */
  if (EditInfo.pOldRecord == NULL) return (true);

	/* See if record is already being edited */
  pDlgInfo = FindOpenDlg(EditInfo.pOldRecord);

  if (pDlgInfo != NULL) {
    pDlgInfo->pFrameWnd->ActivateFrame(SW_RESTORE);
    return (true);
  }  

	/* Create a new dialog to edit the item */
  pDlgInfo = CreateDlg(EditInfo);
  if (pDlgInfo == NULL) return (false);

  pDlgInfo->pFrameWnd->InitialUpdateFrame(m_pDocument, TRUE);
  pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);
 
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::EditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool EditRecord (FormID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::EditRecord (const obformid_t FormID) {
  CObRecord* pRecord;

  pRecord = m_pDocument->GetRecordHandler().FindFormID(FormID);
  if (pRecord == NULL) return (false);
  
  return EditRecord(pRecord);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::EditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool EditRecord (pRecord);
 *
 *=========================================================================*/
bool CObEditDlgHandler::EditRecord (CObRecord* pRecord) {
  obeditrecinfo_t EditInfo;

  if (pRecord == NULL) return (false);
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = false;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.pOldRecord   = pRecord;
  EditInfo.NewEditorID.Empty();

  return EditRecord(EditInfo);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::EditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool EditNewRecord (RecordType);
 *
 *=========================================================================*/
bool CObEditDlgHandler::EditNewRecord (const obrectype_t RecordType) {
  obeditrecinfo_t    EditInfo;

  if (m_pDocument == NULL) return (false);
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = true;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.NewEditorID.Empty();

  EditInfo.pOldRecord = m_pDocument->GetRecordHandler().PrepareNewRecord(RecordType);
  if (EditInfo.pOldRecord == NULL) return (false);

  return EditRecord(EditInfo);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::EditNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlgcreateinfo_t* FindCreateInfo (RecordType);
 *
 * Static class method to find a creation object for the mathcing record
 * type. Returns NULL if not found.
 *
 *=========================================================================*/
obdlgcreateinfo_t* CObEditDlgHandler::FindCreateInfo (const obrectype_t RecordType) {
  obdlgcreateinfo_t* pCreateInfo;
  dword		     Index;

  for (Index = 0; *l_ObDlgCreateInfo[Index].pRecordType != OB_NAME_NULL; ++Index) {
    pCreateInfo = &l_ObDlgCreateInfo[Index];
    if (*pCreateInfo->pRecordType == RecordType) return (pCreateInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::FindCreateInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlginfo_t* FindOpenDlg (pRecordDlg);
 *
 *=========================================================================*/
obdlginfo_t* CObEditDlgHandler::FindOpenDlg (CObRecordDialog* pRecordDlg) {
  obdlginfo_t* pDlgInfo;
  dword        Index;

	/* Ignore invalid input */
  if (pRecordDlg == NULL) return (NULL);

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pRecordDlg == pRecordDlg) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlginfo_t* FindOpenDlg (pRecord);
 *
 * Finds an open dialog for the given record. Returns NULL if not found.
 *
 *=========================================================================*/
obdlginfo_t* CObEditDlgHandler::FindOpenDlg (CObRecord* pRecord) {
  obdlginfo_t* pDlgInfo;
  dword        Index;

	/* Ignore invalid input */
  if (pRecord == NULL) return (NULL);

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pRecordDlg == NULL) continue;
    if (pDlgInfo->pRecordDlg->GetInputRecord() == pRecord) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlginfo_t* FindOpenDlg (pFrameWnd);
 *
 * Find a currently open dialog according to its frame window. Returns NULL
 * if not found.
 *
 *=========================================================================*/
obdlginfo_t* CObEditDlgHandler::FindOpenDlg (CFrameWnd* pFrameWnd) {
  obdlginfo_t* pDlgInfo;
  dword        Index;

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pFrameWnd == pFrameWnd) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - obdlginfo_t* FindOpenDlg (pRuntimeClass);
 *
 * Find a currently open dialog according to its runtime class. Returns NULL
 * if not found.
 *
 *=========================================================================*/
obdlginfo_t* CObEditDlgHandler::FindOpenDlg (CRuntimeClass* pRuntimeClass) {
  obdlginfo_t* pDlgInfo;
  dword        Index;

  if (pRuntimeClass == NULL) return (NULL);

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pRecordDlg == NULL) continue;
    if (pDlgInfo->pRecordDlg->IsKindOf(pRuntimeClass)) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - const TCHAR* GetTitle (void);
 *
 *=========================================================================*/
const TCHAR* CObEditDlgHandler::GetTitle (void) { 
   return m_pDocument ? m_pDocument->GetTitle() : ""; 
}
/*===========================================================================
 *		End of Class Method TCHAR* CObEditDlgHandler::GetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - int OnPreSaveRecord (EditInfo);
 *
 *=========================================================================*/
int CObEditDlgHandler::OnPreSaveRecord (obeditrecinfo_t& EditInfo) {
  int Result;

  if (m_pDocument == NULL) return (OB_RESULT_ERROR);

	/* Check for a changed and valid editorid */
  Result = m_pDocument->GetRecordHandler().OnPreSaveCheckEditorID(EditInfo);
  if (Result < 0) return (Result);
   
       /* Prompt for a rename/copy if needed */
  if (Result == OB_RESULT_PROMPTRENAMECOPY) {
    Result = PromptRenameCopy(EditInfo);
    if (Result == OBEDIT_RECORDPROMPT_CANCEL) return (OB_RESULT_USERABORT);

    if (Result == OBEDIT_RECORDPROMPT_COPY) {
      EditInfo.IsRenamed  = false;
      EditInfo.IsCopy     = true;
      EditInfo.IsHandled  = false;
      EditInfo.NeedsIndex = true;
    }
    else if (Result == OBEDIT_RECORDPROMPT_RENAME) {
      EditInfo.IsRenamed  = true;
      EditInfo.IsCopy     = false;
      EditInfo.IsHandled  = false;
      EditInfo.NeedsIndex = true;
    }
  }
   
	/* Finish the presave */
  Result =  m_pDocument->GetRecordHandler().OnPreSaveRecord(EditInfo);
  if (Result < 0) return (Result);

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnPreSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - int OnPostSaveRecord (EditInfo);
 *
 *=========================================================================*/
int CObEditDlgHandler::OnPostSaveRecord (obeditrecinfo_t& EditInfo) {

  if (m_pDocument != NULL) {
    m_pDocument->GetRecordHandler().OnPostSaveRecord(EditInfo);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnPostSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - int OnCancelEditRecord (EditInfo);
 *
 *=========================================================================*/
int CObEditDlgHandler::OnCancelEditRecord (obeditrecinfo_t& EditInfo) {

  if (m_pDocument != NULL) {
    m_pDocument->GetRecordHandler().OnCancelEditRecord(EditInfo);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnCancelEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool OpenFind (void);
 *
 * Opens a new find or re-activates an existing find window.
 *
 *=========================================================================*/
bool CObEditDlgHandler::OpenFind (void) {
  obdlginfo_t* pDlgInfo;
  
	/* Find an existing open find window */
  pDlgInfo = FindOpenDlg(RUNTIME_CLASS(CObFindDlg));

  if (pDlgInfo != NULL) {
    pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);
    return (true);
  }

  	/* Create a new find window */
  pDlgInfo = CreateDlg(l_ObFindCreateInfo);

  if (pDlgInfo == NULL) {
    ObEditShowLastError("Failed to create the find dialog!");
    return (false);
  }

	/* Initialize the batch window */
  if (pDlgInfo->pRecordDlg != NULL && pDlgInfo->pRecordDlg->IsKindOf(RUNTIME_CLASS(CObFindDlg))) {
    CObFindDlg* pFindDlg = (CObFindDlg *) pDlgInfo->pRecordDlg;
  }

  pDlgInfo->pFrameWnd->InitialUpdateFrame(m_pDocument, TRUE);
  pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::OpenFind()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - void RemoveFrame (pFrameWnd);
 *
 * Simply removes the given frame window from the list of currently
 * opened ones.
 *
 *=========================================================================*/
void CObEditDlgHandler::RemoveFrame (CFrameWnd* pFrameWnd) {
  obdlginfo_t*	pDlgInfo;

	/* Find the dialog by its frame window */
  pDlgInfo = FindOpenDlg(pFrameWnd);
  if (pDlgInfo == NULL) return;

  m_OpenDialogs.Delete(pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::RemoveFrame()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectItemScript (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectItemScript (CString& EditorID) { 
  if (m_pDocument == NULL) return (false);
  return ObSelectItemScript(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectItemScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectActor (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectActor (CString& EditorID) { 
  if (m_pDocument == NULL) return (false);
  return ObSelectActor(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectActor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectApparelEnchant (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectApparelEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return ObSelectApparelEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectApparelEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectIngrediant (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectIngrediant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return ObSelectIngrediant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectIngrediant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectScrollEnchant (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectScrollEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return ObSelectScrollEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectScrollEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectSound (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectSound (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return ObSelectSound(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectStaffEnchant (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectStaffEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return ObSelectStaffEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectStaffEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectWeaponEnchant (EditorID);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectWeaponEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return ObSelectWeaponEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectWeaponEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - int PromptRenameCopy (EditInfo);
 *
 * Standard prompt for rename/copy/cancel a record.
 *
 *=========================================================================*/
int CObEditDlgHandler::PromptRenameCopy (obeditrecinfo_t& EditInfo) {
  CString  Buffer;
  //CSString EditorID;
  int      Result;

  //EditInfo.pOldRecord->GetField(EditorID, OB_FIELD_EDITORID);
  Buffer.Format(_T("The editorid has changed to %s.\r\n\r\nDo you wish to create a new copy or rename the record?"), EditInfo.NewEditorID);

  Result = ShowObPromptDlg ("Rename/Copy Record", Buffer, "Copy", "Rename", "Cancel");
  if (Result == 3) Result = 0;

  switch (Result) {
    case 1: return (OBEDIT_RECORDPROMPT_COPY);
    case 2: return (OBEDIT_RECORDPROMPT_RENAME);
  }

  return (OBEDIT_RECORDPROMPT_CANCEL);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::PromptRenameCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - int OnListenAddRecord (pEvent);
 *
 *=========================================================================*/
int CObEditDlgHandler::OnListenAddRecord (CObListenEvent* pEvent) {
  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnListenAddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CObEditDlgHandler::OnListenCleanRecord (CObListenEvent* pEvent) {
  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObEditDlgHandler::OnListenUpdateRecord (CObListenEvent* pEvent) {
  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - int OnListenPreUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObEditDlgHandler::OnListenPreUpdateRecord (CObListenEvent* pEvent) {

  if (!pEvent->IsFlagNoClosePreUpdate()) {

    if (pEvent->IsFlagNoNotifySource()) {
      CloseAll(pEvent->GetOldRecord(), pEvent->GetSource());
    }
    else {
      CloseAll(pEvent->GetOldRecord());
    }
  }

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnListenPreUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Event - bool OnHelp (pDialog, pHelpInfo);
 *
 *=========================================================================*/
bool CObEditDlgHandler::OnHelp (CObRecordDialog* pDialog, HELPINFO* pHelpInfo) {
  obdlginfo_t*   pDlgInfo = NULL;
  CSString	 Buffer;

  if (pDialog != NULL) pDlgInfo = FindOpenDlg(pDialog);

	/* Ignore if web help is disabled */
  if (!m_Options.EnableWebHelp) return (false);
  
  if (m_Options.UseUESPWikiHelp) {
    if (pDlgInfo != NULL && pDlgInfo->pCreateInfo->pUESPPage != NULL) 
      Buffer = pDlgInfo->pCreateInfo->pUESPPage;
    else
      Buffer = m_Options.DefaultUESPPage;
  }
  else {
    if (pDlgInfo != NULL && pDlgInfo->pCreateInfo->pCSPage != NULL) 
      Buffer = pDlgInfo->pCreateInfo->pCSPage;
    else
      Buffer = m_Options.DefaultCSPage;

  }
 
  GetObEditApp().OpenWebHelp(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Event CObEditDlgHandler::OnHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectModel (pString);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectModel (const char* pString) {
  CString Buffer(OBRESOURCE_PATH_MESHES);

  Buffer += pString;

  GetObEditApp().OpenResourceView(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectIcon (pString);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectIcon (const char* pString) {
  CString Buffer(OBRESOURCE_PATH_TEXTURES);

  Buffer += pString;

  GetObEditApp().OpenResourceView(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDlgHandler Method - bool SelectSoundFile (pString);
 *
 *=========================================================================*/
bool CObEditDlgHandler::SelectSoundFile (const char* pString) {
  CString Buffer(OBRESOURCE_PATH_SOUNDS);

  Buffer += pString;

  GetObEditApp().OpenResourceView(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDlgHandler::SelectSoundFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindListBoxItemData (ListBox, ItemData, SelectItem);
 *
 * Looks for a specific item data in the given listbox. Returns the list
 * index if found or -1 on any error. Selects the found item if the
 * SelectItem parameter is true.
 *
 *=========================================================================*/
int FindListBoxItemData (CListBox& ListBox, const dword ItemData, const bool SelectItem) {
  int Index;

  for (Index = 0; Index < ListBox.GetCount(); ++Index) {

    if (ListBox.GetItemData(Index) == ItemData) {
      if (SelectItem) ListBox.SetCurSel(Index);
      return (Index);
    }
  }

	/* Not found */
  if (SelectItem) ListBox.SetCurSel(-1);
  return (-1);
}
/*===========================================================================
 *		End of Function FindListBoxItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindComboBoxItemData (ComboBox, ItemData, SelectItem);
 *
 * Looks for a specific item data in the given combobox. Returns the list
 * index if found or -1 on any error. Selects the found item if the
 * SelectItem parameter is true.
 *
 *=========================================================================*/
int FindComboBoxItemData (CComboBox& ComboBox, const dword ItemData, const bool SelectItem) {
  int Index;

  for (Index = 0; Index < ComboBox.GetCount(); ++Index) {

    if (ComboBox.GetItemData(Index) == ItemData) {
      if (SelectItem) ComboBox.SetCurSel(Index);
      return (Index);
    }
  }

	/* Not found */
  if (SelectItem) ComboBox.SetCurSel(-1);
  return (-1);
}
/*===========================================================================
 *		End of Function FindComboBoxItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindComboBoxEffect (ComboBox, EffectType, SelectItem);
 *
 *=========================================================================*/
int FindComboBoxEffect (CComboBox& ComboBox, const obrectype_t EffectType, const bool SelectItem) {
  obeffectdata_t* pEffectData;
  int             Index;

  for (Index = 0; Index < ComboBox.GetCount(); ++Index) {
    pEffectData = (obeffectdata_t *) ComboBox.GetItemData(Index);
    if (pEffectData == NULL) continue;

    if (*pEffectData->pName == EffectType) {
      if (SelectItem) ComboBox.SetCurSel(Index);
      return (Index);
    }
  }

	/* Not found */
  if (SelectItem) ComboBox.SetCurSel(-1);
  return (-1);
}
/*===========================================================================
 *		End of Function FindComboBoxEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindComboBoxString (ComboBox, pString, SelectItem);
 *
 * Looks for a string in the given combobox. Returns the list index if
 * found or -1 on any error. Selects the found item if the SelectItem 
 * parameter is true.
 *
 *=========================================================================*/
int FindComboBoxString (CComboBox& ComboBox, const TCHAR* pString, const bool SelectItem) {
  int ListIndex;

  ListIndex = ComboBox.FindStringExact(-1, pString);
  if (SelectItem) ComboBox.SetCurSel(ListIndex);

  return (ListIndex);
}
/*===========================================================================
 *		End of Function FindComboBoxString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - long GetComboBoxSelItemData (ComboBox, Default);
 *
 *=========================================================================*/
dword GetComboBoxSelItemData (CComboBox& ComboBox, const dword Default) {
  int ListIndex;

  ListIndex = ComboBox.GetCurSel();
  if (ListIndex < 0) return (Default);

  return ComboBox.GetItemData(ListIndex);
}
/*===========================================================================
 *		End of Function GetComboBoxSelItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - long GetListBoxSelItemData (ListBox, Default);
 *
 *=========================================================================*/
dword GetListBoxSelItemData (CListBox& ListBox, const dword Default) {
  int ListIndex;

  ListIndex = ListBox.GetCurSel();
  if (ListIndex < 0) return (Default);

  return ListBox.GetItemData(ListIndex);
}
/*===========================================================================
 *		End of Function GetListBoxSelItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObAddComboBoxItem (ComboBox, pString, ItemData);
 *
 * Adds an item to a combobox. Returns the new item list index on success.
 *
 *=========================================================================*/
int ObAddComboBoxItem (CComboBox& ComboBox, const TCHAR* pString, const dword ItemData) {
  int ListIndex;

  ListIndex = ComboBox.AddString(pString);
  if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, ItemData);

  return (ListIndex);
}
/*===========================================================================
 *		End of Function ObAddComboBoxItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObAddListBoxItem (ListBox, pString, ItemData);
 *
 * Adds an item to a listbox. Returns the new item list index on success.
 *
 *=========================================================================*/
int ObAddListBoxItem (CListBox& ListBox, const TCHAR* pString, const dword ItemData) {
  int ListIndex;

  ListIndex = ListBox.AddString(pString);
  if (ListIndex >= 0) ListBox.SetItemData(ListIndex, ItemData);

  return (ListIndex);
}
/*===========================================================================
 *		End of Function ObAddListBoxItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObFillComboList (ComboBox, pStringValues);
 *
 * Fills the given combobox control with the given string values array.
 *
 *=========================================================================*/
bool ObFillComboList (CComboBox& ComboBox, const stringvalue_t* pStringValues, const dword Flags) {
  dword Index;
  bool  NoDuplicates = (Flags & OBE_FILLCOMBO_NODUPLICATES) != 0;
  int   ListIndex;

	/* Clear the combobox if required */
  if ((Flags & OBE_FILLCOMBO_FORCEEMPTY) != 0) ComboBox.ResetContent();

	/* Ignore invalid input */
  if (pStringValues == NULL) return (false);

	/* Include a NULL value if needed */
  if ((Flags & OBE_FILLCOMBO_INCLUDENULL) != 0) {
    ListIndex = ComboBox.AddString("");
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, 0);
  }

	/* Add all strings in the array */
  for (Index = 0; pStringValues[Index].pString != NULL; ++Index) {

		/* Check for duplicate items if required */
    if (NoDuplicates) {
      ListIndex = FindComboBoxItemData(ComboBox, pStringValues[Index].Value);
      if (ListIndex >= 0) continue;
    }

		/* Add the item */
    ListIndex = ComboBox.AddString(pStringValues[Index].pString);
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, pStringValues[Index].Value);
  }

  return (true);
}
/*===========================================================================
 *		End of Function ObFillComboList()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObFillEffectComboList (ComboBox, Flags, EffectFlagMask, InvalidEffectFlagMask);
 *
 * Fills the given combobox control with a list of magic effects.
 *
 *=========================================================================*/
bool ObFillEffectComboList (CComboBox& ComboBox, const dword Flags, const dword EffectFlagMask, const dword InvalidEffectFlagMask) {
  dword Index;
  bool  NoDuplicates = (Flags & OBE_FILLCOMBO_NODUPLICATES) != 0;
  int   ListIndex;

	/* Clear the combobox if required */
  if ((Flags & OBE_FILLCOMBO_FORCEEMPTY) != 0) ComboBox.ResetContent();

	/* Include a NULL value if needed */
  if ((Flags & OBE_FILLCOMBO_INCLUDENULL) != 0) {
    ListIndex = ComboBox.AddString("");
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, 0);
  }

	/* Add all strings in the array */
  for (Index = 0; l_EffectData[Index].pName != NULL; ++Index) {
    if (EffectFlagMask != 0 && (l_EffectData[Index].DefaultFlags & EffectFlagMask) == 0) continue;
    if ((l_EffectData[Index].DefaultFlags & InvalidEffectFlagMask) != 0) continue;

		/* Check for duplicate items if required */
    if (NoDuplicates) {
      ListIndex = FindComboBoxItemData(ComboBox, l_EffectData[Index].pName->Value);
      if (ListIndex >= 0) continue;
    }

		/* Add the item */
    ListIndex = ComboBox.AddString(l_EffectData[Index].pDescription);
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, (long) &l_EffectData[Index]);
  }

  return (true);
}
/*===========================================================================
 *		End of Function ObFillComboList()
 *=========================================================================*/

