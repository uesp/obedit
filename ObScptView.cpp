/*===========================================================================
 *
 * File:	Obscptview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 5, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObScptView.h"
#include "dialogs/obeditdlghandler.h"
#include "obscripterrorview.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  IMPLEMENT_DYNCREATE(CObScptView, CObRecordDialog);

  obscptoptions_t CObScptView::m_Options;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObScptView, CObRecordDialog)
	//{{AFX_MSG_MAP(CObScptView)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(ID_COMPILE_BUTTON, OnCompileButton)
	ON_NOTIFY(EN_SELCHANGE, IDC_SCRIPT_TEXT, OnSelchangeScriptText)
	ON_EN_CHANGE(IDC_SCRIPT_TEXT, OnChangeScriptText)
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
BEGIN_OBRECUIFIELDS(CObScptView)
	ADD_OBRECUIFIELDS( OB_FIELD_TYPE,	   IDC_TYPE_LIST,	0,	IDS_TT_SCPTTYPE)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Constructor
 *
 *=========================================================================*/
CObScptView::CObScptView() : CObRecordDialog(CObScptView::IDD) {
	//{{AFX_DATA_INIT(CObScptView)
	//}}AFX_DATA_INIT

  m_InitialSetData = false;
  m_pErrorView     = NULL;

  	/* Use a custom font if needed */
  if (!m_Options.FontName.IsEmpty()) {
    m_Font.CreatePointFont(((m_Options.FontSize > 0) ? m_Options.FontSize : 90), m_Options.FontName, NULL);
  }
  else {
    m_Font.CreatePointFont(90, _T("FixedSys"), NULL);
  }

}
/*===========================================================================
 *		End of Class CObScptView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Destructor
 *
 *=========================================================================*/
CObScptView::~CObScptView() {
}
/*===========================================================================
 *		End of Class CObScptView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObScptView::DoDataExchange(CDataExchange* pDX) {
	CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObScptView)
	DDX_Control(pDX, IDC_STATUS_TEXT, m_StatusText);
	DDX_Control(pDX, IDC_TYPE_LIST, m_TypeList);
	DDX_Control(pDX, IDC_SCRIPT_TEXT, m_ScriptText);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObScptView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObScptView::GetControlData (void) {
  CObScptRecord*    pScript;
  CScanSourceString ScanSource;
  CString           Buffer;
  bool              Result;

  CObRecordDialog::GetControlData();
  if (m_EditInfo.pNewRecord == NULL) return;

  pScript = ObCastClass(CObScptRecord, m_EditInfo.pNewRecord);
  if (pScript == NULL) return;

  m_ScriptText.GetWindowText(Buffer);
  pScript->SetScriptText(Buffer);
  ScanSource.SetString(Buffer);

  m_CopyRecord.Copy(m_EditInfo.pOldRecord);
  m_CopyRecord.SetScriptText(Buffer);

  Result = m_Compiler.Compile(&m_CopyRecord);

	/* Don't set compiled data if the compile failed */
  if (Result) GetCompileData(pScript);


 
}
/*===========================================================================
 *		End of Class Method CObScptView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Method - void GetCompileData (pScript);
 *
 *=========================================================================*/
void CObScptView::GetCompileData (CObScptRecord* pScript) {
  CObParseLocalArray* pLocals = &m_Compiler.GetParser().GetLocalVarData();
  CObParseRefArray*   pReferences = &m_Compiler.GetParser().GetReferenceData();
  obparselocal_t*     pLocalVar;
  obparseref_t*       pLocalRef;
  dword               Index;
  dword		      MaxVarIndex = 0;
  dword		      MaxRefIndex = 0;

	/* Set the compiled data */
  pScript->SetScriptData(m_Compiler.GetParser().GetOutputData(), (word) m_Compiler.GetParser().GetOutputDataSize());

	/* Delete existing local variable data */
  pScript->DeleteSubrecords(OB_NAME_SLSD);
  pScript->DeleteSubrecords(OB_NAME_SCVR);
  pScript->DeleteSubrecords(OB_NAME_SCRV);
  pScript->SetVariableCount(0);

	/* Delete references */
  pScript->DeleteSubrecords(OB_NAME_SCRO);
  pScript->SetRefCount(0);

	/* Add all local variable definitions */
  for (Index = 0; Index < pLocals->GetSize(); ++Index) {
    pLocalVar = pLocals->GetAt(Index);
    if (pLocalVar->Index > (int)MaxVarIndex) MaxVarIndex = pLocalVar->Index;

    pScript->AddVariable(pLocalVar->Name, pLocalVar->Index, pLocalVar->Flags);
  }

  pScript->SetVariableCount(MaxVarIndex + 1);

	/* Add all references */
  for (Index = 0; Index < pReferences->GetSize(); ++Index) {
    pLocalRef = pReferences->GetAt(Index);
    if (pLocalRef->FormID > MaxRefIndex) MaxRefIndex = pLocalRef->RefIndex;

    if (pLocalRef->FormID != OB_FORMID_NULL)
      pScript->AddReference(pLocalRef->FormID);
    else
      pScript->AddRefVariable(pLocalRef->LocalIndex);
  }

  pScript->SetRefCount(MaxRefIndex + 1);
}
/*===========================================================================
 *		End of Class Method CObScptView::GetCompileData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Method - void GetCurrentWord (Buffer);
 *
 *=========================================================================*/
void CObScptView::GetCurrentWord (CString& Buffer) {
  CString      LineBuffer;
  CSString     TmpBuffer;
  int          LineSize;
  int	       Index;
  int          CurrentLine;
  int          LineChar;
  long         StartSel;
  long         EndSel;

  Buffer.Empty();

  LineSize = m_ScriptText.LineLength(-1);
  if (LineSize == 0) return;

  CurrentLine = m_ScriptText.LineFromChar(-1);

  m_ScriptText.GetLine(CurrentLine, Buffer.GetBuffer(LineSize + 4));
  Buffer.ReleaseBuffer(LineSize);
  if (Buffer.IsEmpty()) return;

  LineChar = m_ScriptText.LineIndex(-1);
  m_ScriptText.GetSel(StartSel, EndSel);

  if (LineChar > StartSel || LineChar + LineSize < StartSel) {
    Buffer.Empty();
    return;
  }

  Index = StartSel - LineChar;
  
  while (Index > 0) {
    --Index;

    if (!isalnum(Buffer.GetAt(Index))) {
      Buffer.Delete(0, Index);
      break;
    } 
  }

  Index = 0;

  while (Index < Buffer.GetLength()) {
    if (!isalnum(Buffer.GetAt(Index))) {
      Buffer.Delete(Index, Buffer.GetLength() - Index + 1);
      break;
    } 
    ++Index;
  }

}
/*===========================================================================
 *		End of Class Method CObScptView::GetCurrentWord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScptView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObScptView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObScptView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of Class CObScptView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObScptView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();
  SetScrollSizes(MM_TEXT, CSize(0,0));

  	/* This stops the richedit control from selecting all text at startup */
  GetParentFrame()->SetWindowPos(NULL, 0, 0, 640, 400, SWP_NOMOVE | SWP_NOZORDER);

  m_ToolTip.AddTool(&m_ScriptText, "test tool tip");

  ObAddComboBoxItem(m_TypeList, "Object",       OB_SCRIPTTYPE_OBJECT);
  ObAddComboBoxItem(m_TypeList, "Quest",        OB_SCRIPTTYPE_QUEST);
  ObAddComboBoxItem(m_TypeList, "Magic Effect", OB_SCRIPTTYPE_MAGICEFFECT);
  m_TypeList.SetCurSel(0);

  m_ScriptText.LimitText(65535);
  m_ScriptText.SetFont(&m_Font);
  m_ScriptText.SetEventMask(m_ScriptText.GetEventMask() | ENM_SELCHANGE | ENM_CHANGE);

  m_Compiler.Load("testtable1.dat");
  m_Compiler.SetRecordHandler(m_pRecordHandler);
  GetObEditApp().UpdateScriptColorOptions(m_Compiler, true);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObScptView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Event - void OnSize (Type, cx, cy);
 *
 *=========================================================================*/
void CObScptView::OnSize (UINT Type, int cx, int cy) {
  CObRecordDialog::OnSize(Type, cx, cy);

  if (IsWindow(m_ScriptText.m_hWnd)) {
    m_ScriptText.SetWindowPos(NULL, 0, 0, cx, cy-28-20, SWP_NOMOVE | SWP_NOZORDER);
  }

  if (IsWindow(m_StatusText.m_hWnd)) {
    m_StatusText.SetWindowPos(NULL, 0, cy-28+11, cx, 16, SWP_NOZORDER);
  }

}
/*===========================================================================
 *		End of Class Event CObScptView::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObScptView::SetControlData (void) {
  CObScptRecord* pScript;

  CObRecordDialog::SetControlData();
  if (m_EditInfo.pOldRecord == NULL) return;

  pScript = ObCastClass(CObScptRecord, m_EditInfo.pOldRecord);
  if (pScript == NULL) return;

  m_ScriptText.SetWindowText(pScript->GetScriptText());

  m_ScriptText.SetSel(0, 0);
}
/*===========================================================================
 *		End of Class Method CObScptView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Method - bool FindScriptEditorID (Buffer);
 *
 *=========================================================================*/
bool CObScptView::FindScriptEditorID (CString& Buffer) {
  CString      LineBuffer;
  CSString     TmpBuffer;
  const TCHAR* pParse;
  int          LineNum;
  int          LineSize;
  int	       Index;

  for (LineNum = 0; LineNum < m_ScriptText.GetLineCount(); ++LineNum) {
    LineSize = m_ScriptText.LineLength(m_ScriptText.LineIndex(LineNum));
    if (LineSize == 0) continue;

    m_ScriptText.GetLine(LineNum, LineBuffer.GetBuffer(LineSize + 4));
    LineBuffer.ReleaseBuffer(LineSize);

    LineBuffer.TrimLeft(" \t\n\r");
    
    if (strnicmp(LineBuffer, "scriptname", 10) == 0) {
      LineBuffer.Delete(0, 10);
    }
    else if (strnicmp(LineBuffer, "scn", 3) == 0) {
      LineBuffer.Delete(0, 3);
    }
    else {
      continue;
    }
    
    if (LineBuffer.IsEmpty()) continue;
    if (!isspace(LineBuffer.GetAt(0))) continue;

    LineBuffer.TrimLeft(" \t\n\r");
    pParse = LineBuffer;
    Index  = 0;

    while (isalnum(*pParse)) {
      ++pParse;
      ++Index;
    }

    LineBuffer.Delete(Index, LineBuffer.GetLength() - Index);
    Buffer = LineBuffer;
    return (true);
  }
  
  Buffer.Empty();
  return (false);
}
/*===========================================================================
 *		End of Class Method CObScptView::FindScriptEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CObScptView::UpdateEditorID (void) {
  CString Buffer;
  bool    Result;

  m_EditInfo.NewEditorID.Empty();
  m_EditInfo.HasUpdatedID = false;

  Result = FindScriptEditorID(Buffer);

  if (!Result) {
    AddObGeneralError("The script editorid could not be found!");
    return (OB_RESULT_ERROR);
  }

  m_EditInfo.NewEditorID = Buffer;
  ObPrepareEditorID(m_EditInfo.NewEditorID);
  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObScptView::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObScptView::OnContextMenu(CWnd* pWnd, CPoint Point) {
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_SCRIPT_TEXT) {
    Result = Menu.LoadMenu(IDR_SCRIPT_MENU);
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
 *		End of Class Event CObBookView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Event - void OnCompileButton ();
 *
 *=========================================================================*/
void CObScptView::OnCompileButton() {	
  CScanSourceString ScanSource;
  CString           Buffer;
  obtimer_t         Timer;
  double            DeltaTime;
  bool              Result;

  if (m_pErrorView != NULL) {
    m_pErrorView->ClearErrors();
    m_pErrorView->AddMessage("Compiling Script...");
  }

  m_ScriptText.GetWindowText(Buffer);
  ScanSource.SetString(Buffer);

  m_CopyRecord.Copy(m_EditInfo.pOldRecord);
  m_CopyRecord.SetScriptText(Buffer);

  ObStartTimer(Timer);
  Result = m_Compiler.Compile(&m_CopyRecord);
  DeltaTime = ObEndTimer(Timer);

  if (m_pErrorView != NULL) {
    m_pErrorView->AddErrors(m_Compiler.GetErrors());

    if (!Result) 
      m_pErrorView->AddMessage("Failed to compile script with %u errors and %u warnings in %g seconds!", m_Compiler.GetErrorCount(), m_Compiler.GetWarningCount(), DeltaTime);
    else
      m_pErrorView->AddMessage("Successfully compiled script with %u errors and %u warnings in %g seconds!", m_Compiler.GetErrorCount(), m_Compiler.GetWarningCount(), DeltaTime);
  }

}
/*===========================================================================
 *		End of Class Event CObScptView::OnCompileButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Event - void OnSelchangeScriptText (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObScptView::OnSelchangeScriptText(NMHDR* pNMHDR, LRESULT* pResult) {
  SELCHANGE *pSelChange = reinterpret_cast<SELCHANGE *>(pNMHDR);

  OnChangeScriptText();

  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObScptView::OnSelchangeScriptText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Event - void OnChangeScriptText ();
 *
 *=========================================================================*/
void CObScptView::OnChangeScriptText() {
  CString    Buffer;
  CHARRANGE  SelRange;
  long       LineNum;
  long       LineStart;

  m_ScriptText.GetSel(SelRange);
  
  LineNum   = m_ScriptText.LineFromChar(SelRange.cpMin);
  LineStart = m_ScriptText.LineIndex(LineNum);
  Buffer.Format("%d, %d", LineNum + 1, SelRange.cpMin - LineStart + 1);

  m_StatusText.SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObScptView::OnChangeScriptText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptView Event - void SelectFromError (pError);
 *
 *=========================================================================*/
void CObScptView::SelectFromError (CObScriptError* pError) {
  long            StartSel;
  long            EndSel;
  int             Position;

	/* Ignore invalid input */
  if (pError == NULL) return;

  Position = m_ScriptText.LineIndex(pError->GetLinePos()); 
  if (Position < 0) return;
  StartSel  = Position + pError->GetCharPos();
  EndSel    = StartSel;

  if (pError->GetToken() != NULL) {
    EndSel = m_ScriptText.LineIndex(pError->GetToken()->EndPos.LinePos);

    if (EndSel < 0)
      EndSel = StartSel;
    else
      EndSel += pError->GetToken()->EndPos.CharPos;
  }

  m_ScriptText.SetSel(StartSel, EndSel);
	
  m_ScriptText.SetActiveWindow();
  m_ScriptText.SetFocus();
}
/*===========================================================================
 *		End of Class Event CObScptView::OnChangeScriptText()
 *=========================================================================*/


