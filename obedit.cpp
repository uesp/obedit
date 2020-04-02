/*===========================================================================
 *
 * File:	obedit.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Defines the class behaviors for the application.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "obeditDoc.h"
#include "obeditView.h"
#include "obloaddlg.h"
#include "stdarg.h"
#include "aboutdlg.h"
#include "modfile/compiler/obscriptfunctions.h"
#include "obscptview.h"
#include "shlwapi.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Debug definitions */
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

	/* Main application object */
  CObEditApp theApp;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObEditApp Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObEditApp, CWinApp)
  //{{AFX_MSG_MAP(CObEditApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
  //}}AFX_MSG_MAP

	/* Standard file based document commands */
  ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
  ON_COMMAND(ID_FILE_OPEN, OnFileOpen)

END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObEditApp Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Constructor
 *
 *=========================================================================*/
CObEditApp::CObEditApp() {
  //CSString Test1("test\n-'-\"-%-");
  //Test1.Escape();
  //Test1.Unescape();
  m_pCurrentLoadInfo     = NULL;
  m_pCurrentProgressDlg  = NULL;
  m_pCurrentLoadCallback = NULL;
  m_NewFileIndex         = 1;
  m_InitResourceHandler  = false;
  m_pMainFrame           = NULL;
}
/*===========================================================================
 *		End of Class CObEditApp Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Destructor
 *
 *=========================================================================*/
CObEditApp::~CObEditApp() {
}
/*===========================================================================
 *		End of Class CObEditApp Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - BOOL InitInstance ();
 *
 *=========================================================================*/
BOOL CObEditApp::InitInstance() {
  TCHAR    Buffer[_MAX_PATH + 8];
  CSString PathBuffer;
  bool     Result;

  SystemLog.Open("obedit.log");

  CSString Test;
  CObItem1Record TestItem;
  
  TestItem.SetItemName("ItemNameABC123");
  Test = "testing123";
  SystemLog.Printf("%s", Test);
  const char * pTest = TestItem.GetItemName();
  SystemLog.Printf("%s", TestItem.GetItemName());
  TestItem.GetField(Test, OB_FIELD_ITEMNAME);
  SystemLog.Printf("%s", Test);
  

  AfxEnableControlContainer();
  AfxInitRichEdit();

#ifdef _AFXDLL
  Enable3dControls();
#else
  Enable3dControlsStatic();
#endif

	/* Register custom window classes */
  WNDCLASSEX ClassInfo;
  ClassInfo.cbSize = sizeof(ClassInfo);
  ClassInfo.style = 0;
  ClassInfo.lpfnWndProc = DefWindowProc;
  ClassInfo.cbClsExtra = 0;
  ClassInfo.cbWndExtra = 0;
  ClassInfo.hInstance = m_hInstance;
  ClassInfo.hIcon = NULL;
  ClassInfo.hCursor = NULL;
  ClassInfo.hbrBackground = NULL;
  ClassInfo.hIconSm = NULL;
  ClassInfo.lpszMenuName = NULL;
  ClassInfo.lpszClassName = "PreviewImageClass";
  RegisterClassEx(&ClassInfo);

	/* Initialize the image library */
  ilInit();
  iluInit();
  ilutInit();

	/* Load the standard display filters file */
  GetCurrentDirectory(_MAX_PATH, Buffer);
  m_AppPath = Buffer;
  TerminatePathString(m_AppPath);

	/* Change the registry key under which our settings are stored. */
  SetRegistryKey(_T("UESP"));

	/* Load standard INI file options (including MRU) */
  LoadStdProfileSettings(); 

	/* Register document templates */
  CMultiDocTemplate* pDocTemplate;
  pDocTemplate = new CMultiDocTemplate(IDR_OBEDITTYPE,
		RUNTIME_CLASS(CObEditDoc),
		RUNTIME_CLASS(CChildFrame), /* Custom MDI child frame */
		RUNTIME_CLASS(CObEditView));
  AddDocTemplate(pDocTemplate);

	/* Create main MDI Frame window */
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME)) return FALSE;
  m_pMainWnd   = pMainFrame;
  m_pMainFrame = pMainFrame;

  	/* Load the default config file */
  LoadOptions(OBEDIT_OPTIONS_FILE);

	/* Change to the data file path */ /*
  Result = GetObInstallPath(PathBuffer);

  if (Result) {
    PathBuffer += "data\\";
    SetCurrentDirectory(PathBuffer);
  } //*/

	/* Parse command line for standard shell commands, DDE, file open */
  CCommandLineInfo cmdInfo;
  cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
  ParseCommandLine(cmdInfo);

	/* Dispatch commands specified on the command line */
  if (!ProcessShellCommand(cmdInfo)) return FALSE;

	/* The main window has been initialized, so show and update it. */
  pMainFrame->ShowWindow(m_nCmdShow);
  pMainFrame->UpdateWindow();

	/* Display the about box initially if required */
  m_ConfigFile.GetBoolean(Result, "DisplayAboutOnLoad", true);
  if (Result) OnAppAbout();

  ObLoadScriptFunctions("functions.dat");
  //SystemLog.Printf("Loaded %u functions...", Functions.GetNumFunctions());
  
	/* Resource handler and view initialization */
  //InitResourceHandler();
  //OpenResourceView();

  return TRUE;
}
/*===========================================================================
 *		End of Class Method CObEditApp::InitInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - int ExitInstance ();
 *
 *=========================================================================*/
int CObEditApp::ExitInstance() {

  CObMultiRecordHandler::m_OblivionMaster.Destroy();

  m_ResourceHandler.Destroy();
  m_BsaFiles.Destroy();

  return CWinApp::ExitInstance();
}
/*===========================================================================
 *		End of Class Method CObEditApp::ExitInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Event - void OnAppAbout ();
 *
 * Application command to run the about dialog.
 *
 *=========================================================================*/
void CObEditApp::OnAppAbout() {
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}
/*===========================================================================
 *		End of Class Event CObEditApp::OnAppAbout()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Event - void OnFileOpen (void);
 *
 *=========================================================================*/
void CObEditApp::OnFileOpen (void) {
  CObProgressDlg*     pProgressDlg;
  CObCallback	      LoadCallback;
  CDocument*	      pDocument;
  CObLoadDlg          LoadDlg;
  obfileloadinfo_t*   pLoadInfo;
  CString	      Buffer;
  bool		      NotActive;
  int                 Result;
	
	/* Prompt the user to select the files */
  Result = LoadDlg.DoModal();
  if (Result != IDOK) return;

  pLoadInfo = &LoadDlg.GetLoadInfo();
  
	/* Initialize the progress dialog */
  pProgressDlg = ShowObProgressDlg(_T("Loading Plugin"), _T("Loading..."));
  //pProgressDlg->SetCancelMsg(_T("Are you sure you wish to abort loading this plugin?"));
  LoadCallback.SetCallbackInterval(10000);
  LoadCallback.SetFunction(ObEditDefaultProgressCallback);
  LoadCallback.SetUserPtr((void *) pProgressDlg);
  LoadCallback.Reset();
	
  Buffer    = pLoadInfo->m_ActiveFilename;
  NotActive = Buffer.IsEmpty() != 0;
  if (NotActive) Buffer.Format(_T("noname%u"), m_NewFileIndex++);

	/* Load the file */
  m_pCurrentLoadInfo     = pLoadInfo;
  m_pCurrentProgressDlg  = pProgressDlg;
  m_pCurrentLoadCallback = &LoadCallback;

  pDocument = OpenDocumentFile(Buffer);

  m_pCurrentLoadInfo     = NULL;
  m_pCurrentProgressDlg  = NULL;
  m_pCurrentLoadCallback = NULL;

  DestroyObProgressDlg(pProgressDlg);

  if (pDocument == NULL) ObEditShowLastError(_T("Failed to load the requested plugin(s)!"));
}
/*===========================================================================
 *		End of Class Event CObEditApp::OnFileOpen()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - CDocument* OpenDocumentFile (lpszFileName);
 *
 *=========================================================================*/
CDocument* CObEditApp::OpenDocumentFile (LPCTSTR lpszFileName) {
  return CWinApp::OpenDocumentFile(lpszFileName);
}
/*===========================================================================
 *		End of Class Method CObEditApp::OpenDocumentFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - bool LoadOptions (pFilename);
 *
 *=========================================================================*/
bool CObEditApp::LoadOptions (const TCHAR* pFilename) {
  bool Result;

  Result = m_ConfigFile.Load(pFilename);
  if (!Result) return (false);

	/* Update all settings */
  UpdateOptions(false);
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditApp::LoadOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - bool SaveOptions (pFilename);
 *
 *=========================================================================*/
bool CObEditApp::SaveOptions (const TCHAR* pFilename) {
  bool Result;

  	/* Update all settings */
  UpdateOptions(false);

  Result = m_ConfigFile.Save(pFilename);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditApp::SaveOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - void UpdateOptions (SetConfigFile);
 *
 * If Set is true the configfile values are updated from the option
 * data.
 *
 *=========================================================================*/
void CObEditApp::UpdateOptions (const bool Set) {

	/* Record list options */
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableColors",		CObRecordListCtrl::GetOptions().EnableColors);
  m_ConfigFile.UpdateBoolean(Set, "RecordListSaveState",		CObRecordListCtrl::GetOptions().SaveState);

  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableActiveColor",	CObRecordListCtrl::GetOptions().ActiveColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableDeletedColor",	CObRecordListCtrl::GetOptions().DeletedColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableIgnoredColor",	CObRecordListCtrl::GetOptions().IgnoredColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableDangerousColor",	CObRecordListCtrl::GetOptions().DangerousColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableQuestColor",		CObRecordListCtrl::GetOptions().QuestColor.Enable);

  m_ConfigFile.UpdateInteger(Set, "RecordListActiveColorOrder",		CObRecordListCtrl::GetOptions().ActiveColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListDeletedColorOrder",	CObRecordListCtrl::GetOptions().DeletedColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListIgnoredColorOrder",	CObRecordListCtrl::GetOptions().IgnoredColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListDangerousColorOrder",	CObRecordListCtrl::GetOptions().DangerousColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListQuestColorOrder",		CObRecordListCtrl::GetOptions().QuestColor.Order);

  m_ConfigFile.UpdateDword(Set, "RecordListActiveColor",		CObRecordListCtrl::GetOptions().ActiveColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListDeletedColor",		CObRecordListCtrl::GetOptions().DeletedColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListIgnoredColor",		CObRecordListCtrl::GetOptions().IgnoredColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListDangerousColor",		CObRecordListCtrl::GetOptions().DangerousColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListQuestColor",			CObRecordListCtrl::GetOptions().QuestColor.Color);

	/* Record tree options */
  m_ConfigFile.UpdateBoolean(Set, "RecordTreeEnableCounts", CObRecordTreeCtrl::GetOptions().EnableCounts);
  m_ConfigFile.UpdateString (Set, "RecordTreeFilterFile",   CObRecordTreeCtrl::GetOptions().FilterFile);

	/* Undo options */
  m_ConfigFile.UpdateBoolean(Set, "EnableUndo", CObMultiRecordHandler::GetOptions().Undo.EnableUndo);
  m_ConfigFile.UpdateDword  (Set, "UndoLimit",  CObMultiRecordHandler::GetOptions().Undo.UndoLimit);

  	/* Backup options */
  m_ConfigFile.UpdateBoolean(Set, "EnableBackup",       CObMultiRecordHandler::GetOptions().EnableBackup);
  m_ConfigFile.UpdateBoolean(Set, "EnableBackupOnSave", CObMultiRecordHandler::GetOptions().EnableBackupOnSave);
  m_ConfigFile.UpdateInteger(Set, "MaximumBackupSize",  CObMultiRecordHandler::GetOptions().MaxBackupSize);
  m_ConfigFile.UpdateInteger(Set, "MaximumBackupCount", CObMultiRecordHandler::GetOptions().MaxBackupCount);
  m_ConfigFile.UpdateString (Set, "BackupPath",         CObMultiRecordHandler::GetOptions().BackupPath);
  m_ConfigFile.UpdateBoolean(Set, "EnableAutoBackup",   CObMultiRecordHandler::GetOptions().EnableAutoBackup);
  m_ConfigFile.UpdateInteger(Set, "AutoBackupTime",     CObMultiRecordHandler::GetOptions().AutoBackupTime);

	/* Performance settings */
  m_ConfigFile.UpdateBoolean(Set, "EnableCaching",     CObMultiRecordHandler::GetOptions().EnableCaching);

	/* Dialog options */
  m_ConfigFile.UpdateBoolean(Set, "EnableWebHelp",   CObEditDlgHandler::GetOptions().EnableWebHelp);
  m_ConfigFile.UpdateBoolean(Set, "UseUESPWikiHelp", CObEditDlgHandler::GetOptions().UseUESPWikiHelp);
  m_ConfigFile.UpdateString(Set,  "CSWikiPrefix",    CObEditDlgHandler::GetOptions().CSWikiPrefix);
  m_ConfigFile.UpdateString(Set,  "UESPWikiPrefix",  CObEditDlgHandler::GetOptions().UESPWikiPrefix);
  m_ConfigFile.UpdateString(Set,  "DefaultCSPage",   CObEditDlgHandler::GetOptions().DefaultCSPage);
  m_ConfigFile.UpdateString(Set,  "DefaultUESPPage", CObEditDlgHandler::GetOptions().DefaultUESPPage);

	/* Script options */
  m_ConfigFile.UpdateString (Set, "ScriptFontName", CObScptView::m_Options.FontName);
  m_ConfigFile.UpdateInteger(Set, "ScriptFontSize", CObScptView::m_Options.FontSize);
  m_ConfigFile.UpdateDword  (Set, "ScriptForeColor[]", CObScptView::m_Options.DefaultForeColor);
  m_ConfigFile.UpdateDword  (Set, "ScriptBackColor[]", CObScptView::m_Options.DefaultBackColor);
  m_ConfigFile.UpdateInteger(Set, "ScriptTabSize", CObScptView::m_Options.TabSize);

  UpdateScriptErrorOptions(Set);

	/* Force a redraw */
  if (!Set) {
    ResolveOptionPaths();

    CWnd* pWnd = AfxGetMainWnd();
    if (pWnd != NULL) pWnd->RedrawWindow();
  }

}
/*===========================================================================
 *		End of Class Method CObEditApp::UpdateOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - void UpdateScriptColorOptions (Compiler, Set);
 *
 *=========================================================================*/
void CObEditApp::UpdateScriptColorOptions (CCustomCompiler& Compiler, const bool Set) {
  CTokenTypeArray* pTokens = &Compiler.GetTokenTypes();
  CSString         Buffer;
  CTokenType*      pToken;
  dword            Index;
  bool             Result;

  for (Index = 0; Index < pTokens->GetNumRecords(); ++Index) {
    pToken = pTokens->GetRecord(Index);

    Buffer.Format("ScriptForeColor[%s]", pToken->GetName());
    Result = m_ConfigFile.UpdateDword(Set, Buffer, pToken->GetForeColorRef());
    if (!Result && Set) pToken->GetForeColorRef() = CObScptView::m_Options.DefaultForeColor;

    Buffer.Format("ScriptBackColor[%s]", pToken->GetName());
    Result = m_ConfigFile.UpdateDword(Set, Buffer, pToken->GetBackColorRef());
    if (!Result && Set) pToken->GetBackColorRef() = CObScptView::m_Options.DefaultBackColor;
  }

}
/*===========================================================================
 *		End of Class Method CObEditApp::UpdateScriptColorOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - void UpdateScriptErrorOptions (Set);
 *
 *=========================================================================*/
void CObEditApp::UpdateScriptErrorOptions (const bool Set) {
  CString Buffer;
  dword   Index;

  for (Index = 0; g_ObScriptErrorDefs[Index].pName != NULL; ++Index) {
    Buffer.Format("ScriptError[%s]", g_ObScriptErrorDefs[Index].pName);
    m_ConfigFile.UpdateInteger(Set, Buffer, g_ObScriptErrorDefs[Index].Level);
  }

}
/*===========================================================================
 *		End of Class Method CObEditApp::UpdateScriptErrorOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - void ResolveOptionPaths (void);
 *
 *=========================================================================*/
void CObEditApp::ResolveOptionPaths (void) {
  char  Buffer[_MAX_PATH + 8];
  dword Result;
  bool  HasPath = false;

  if (CObMultiRecordHandler::GetOptions().BackupPath[0] != '\\' &&
      CObMultiRecordHandler::GetOptions().BackupPath[1] != ':') {

    Result = GetObInstallPath(CObMultiRecordHandler::GetOptions().FullBackupPath);

    if (Result) {
      CObMultiRecordHandler::GetOptions().FullBackupPath += "data\\";
      CObMultiRecordHandler::GetOptions().FullBackupPath += CObMultiRecordHandler::GetOptions().BackupPath;
      TerminatePathString(CObMultiRecordHandler::GetOptions().FullBackupPath);
      HasPath = true;
    }
  }

  if (!HasPath) {
    Result = GetFullPathName(CObMultiRecordHandler::GetOptions().BackupPath, _MAX_PATH, Buffer, NULL);

    if (Result)
      CObMultiRecordHandler::GetOptions().FullBackupPath = Buffer;
    else
      CObMultiRecordHandler::GetOptions().FullBackupPath = CObMultiRecordHandler::GetOptions().BackupPath;
  }

	/* Create the fulll display filter path */
  CObRecordTreeCtrl::GetOptions().FullFilterFile  = m_AppPath;
  CObRecordTreeCtrl::GetOptions().FullFilterFile += CObRecordTreeCtrl::GetOptions().FilterFile;

  SystemLog.Printf("Full backup path: %s", CObMultiRecordHandler::GetOptions().FullBackupPath.c_str());
}
/*===========================================================================
 *		End of Class Method CObEditApp::ResolveOptionPaths()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Event - bool OpenWebHelp (pPage);
 *
 *=========================================================================*/
bool CObEditApp::OpenWebHelp (const char* pPage) {
  CSString	 Buffer;

	/* Ignore if web help is disabled */
  if (!CObEditDlgHandler::GetOptions().EnableWebHelp) return (false);
  
  if (CObEditDlgHandler::GetOptions().UseUESPWikiHelp) {
    Buffer = CObEditDlgHandler::GetOptions().UESPWikiPrefix;
    if (pPage == NULL) pPage = CObEditDlgHandler::GetOptions().DefaultUESPPage;
   }
  else {
    Buffer = CObEditDlgHandler::GetOptions().CSWikiPrefix;
    if (pPage == NULL) pPage = CObEditDlgHandler::GetOptions().DefaultCSPage;
  }
 
  if (pPage != NULL) Buffer += pPage;
  OpenWebPage(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Event CObEditApp::OpenWebHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - CFrameWnd* FindResourceView (void);
 *
 *=========================================================================*/
CFrameWnd* CObEditApp::FindResourceView (void) {
  CWnd* pWnd;
  CWnd* pWnd1;
  HWND  hWnd;

  hWnd = GetWindow(m_pMainFrame->m_hWndMDIClient, GW_CHILD);

  while (hWnd != NULL) {
    pWnd = CWnd::FromHandle(hWnd);

    if (pWnd != NULL) {
      pWnd1 = pWnd->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);

      if (pWnd1 != NULL && pWnd1->IsKindOf(RUNTIME_CLASS(CObResourceView))) {
        if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) return (CFrameWnd *) pWnd;
      }
    }
   
    hWnd = GetWindow(hWnd, GW_HWNDNEXT);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObEditApp::FindResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - void OpenResourceView (pResource);
 *
 *=========================================================================*/
void CObEditApp::OpenResourceView (const char* pResource) {
  CObResourceView* pView;
  
  pView = OpenResourceView();
  if (pView == NULL) return;

  pView->SelectResource(pResource);
}
/*===========================================================================
 *		End of Class Method CObEditApp::OpenResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - CObResourceView* CreateResourceView (void);
 *
 *=========================================================================*/
CObResourceView* CObEditApp::CreateResourceView (void) {
  CObResourceView* pView;
  CCreateContext   Context;
  CFrameWnd*       pFrame;
  CWnd*		   pWnd;

  if (m_pCurrentProgressDlg == NULL) {
    m_pCurrentProgressDlg = ShowObProgressDlg(_T("Resource Viewer"), _T("Initializing Resources..."));
    m_pCurrentProgressDlg->Update(50);
  }

	/* Initialize the context structure */
  Context.m_pCurrentDoc     = NULL;
  Context.m_pCurrentFrame   = NULL;
  Context.m_pNewDocTemplate = NULL;
  Context.m_pLastView       = NULL;
  Context.m_pNewViewClass   = RUNTIME_CLASS(CObResourceView);

	/* Create the dialog parent frame */  
  pFrame = (CFrameWnd *) RUNTIME_CLASS(CChildFrame)->CreateObject();
  ASSERT_KINDOF(CFrameWnd, pFrame);

	/* Create new form view from resource */
  pFrame->LoadFrame(IDD_RESOURCE_VIEW, WS_OVERLAPPEDWINDOW, m_pMainWnd, &Context);

  	/* Attempt to initialize the new view */
  pWnd = pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);

  if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CObResourceView))) {
    pView = (CObResourceView *) pWnd;
    pView->SetResourceHandler(&m_ResourceHandler);
    pView->SetBsaFileArray(&m_BsaFiles);
  }
  
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(75);

  pFrame->InitialUpdateFrame(NULL, TRUE);
  pFrame->ActivateFrame(SW_SHOWNORMAL);
  pFrame->SetWindowText(_T("Resource Viewer"));

  return (pView);
}
/*===========================================================================
 *		End of Class Method CObEditApp::CreateResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - CObResourceView* OpenResourceView (void);
 *
 *=========================================================================*/
CObResourceView* CObEditApp::OpenResourceView (void) {
  CObResourceView* pView = NULL;
  CFrameWnd*       pFrame;
  CWnd*            pWnd;
  
	/* Force the initialization of the resource handler if required */
  if (!m_InitResourceHandler) {
    m_pCurrentProgressDlg = ShowObProgressDlg(_T("Resource Viewer"), _T("Initializing Resources..."));
    m_pCurrentProgressDlg->Update(0);
    
    InitResourceHandler();
  }

	/* Find an already open view */
  pFrame = FindResourceView();

  if (pFrame != NULL) {
    pFrame->ActivateFrame(SW_RESTORE);

    pWnd = pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
    if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CObResourceView))) pView = (CObResourceView *) pWnd;
  }
  else {
    pView = CreateResourceView();
  }

  if (m_pCurrentProgressDlg) {
    DestroyObProgressDlg(m_pCurrentProgressDlg);
    m_pCurrentProgressDlg = NULL;
  }

  return (pView);
}
/*===========================================================================
 *		End of Class Method CObEditApp::OpenResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - bool InitResourceHandler (void);
 *
 *=========================================================================*/
bool CObEditApp::InitResourceHandler (void) {
  CSString        Buffer;
  CSString        Buffer1;
  CSString        Filename;
  obtimer_t       Timer;
  bool            Result;

	/* Clear any current content */
  m_BsaFiles.Destroy();
  m_ResourceHandler.Destroy();
  m_InitResourceHandler = false;

	/* Get the current Oblivion path */
  Result = GetObInstallPath(Buffer);
  if (!Result) return AddObGeneralError("Failed to find the Oblivion install path!");

  Buffer += "data\\";
  m_ResourceHandler.SetBasePath(Buffer);

	/* Add files in the data file path */  
  ObStartTimer(Timer);
/*
  Buffer1 = Buffer + "textures\\";
  m_ResourceHandler.AddPathContents(Buffer1, false);

  Buffer1 = Buffer + "menus\\";
  m_ResourceHandler.AddPathContents(Buffer1, false);

  Buffer1 = Buffer + "fonts\\";
  m_ResourceHandler.AddPathContents(Buffer1, false);

  Buffer1 = Buffer + "facegen\\";
  m_ResourceHandler.AddPathContents(Buffer1, false);

  Buffer1 = Buffer + "video\\";
  m_ResourceHandler.AddPathContents(Buffer1, false); //*/

  //Buffer1 = "H:\\Oblivion\\bsacmd\\out\\";
  //m_ResourceHandler.AddPathContents(Buffer1, false);

  m_ResourceHandler.AddPathContents(Buffer, false);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(10);
  
  ObEndTimer(Timer, "Added path contents in ");

	/* Add known BSA files for now */
  Filename = Buffer + "Oblivion - Misc.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(20);

  Filename = Buffer + "Oblivion - Meshes.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(30);

  Filename = Buffer + "Oblivion - Sounds.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(40);

  //Filename = Buffer + "Oblivion - Voices1.bsa";
  //AddBsaFile(Filename);
  //Filename = Buffer + "Oblivion - Voices2.bsa";
  //AddBsaFile(Filename);

  Filename = Buffer + "Oblivion - Textures - Compressed.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(50);
  
  m_InitResourceHandler = true;
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditApp::InitResourceHandler()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - bool AddBsaFile (pFilename);
 *
 *=========================================================================*/
bool CObEditApp::AddBsaFile (const char* pFilename) {
  CObBsaFile* pBsaFile;
  bool        Result;
  obtimer_t   Timer;

  pBsaFile = new CObBsaFile;
  m_BsaFiles.Add(pBsaFile);

  ObStartTimer(Timer);
  Result = pBsaFile->Load(pFilename);
  ObEndTimer(Timer, "Loaded BSA file in ");

  if (!Result) {
    m_BsaFiles.Delete(pBsaFile);
    return (false);
  }

  ObStartTimer(Timer);
  m_ResourceHandler.AddBsaFile(pBsaFile);
  ObEndTimer(Timer, "Added BSA records in ");
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditApp::AddBsaFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditApp Method - void ResetListState (void);
 *
 *=========================================================================*/
void CObEditApp::ResetListState (void) {
  CString Section;
  dword   Result;

  Result = MessageBox(NULL, "This action will delete the state and restore all lists in ObEdit to their default settings.\r\nAre you sure you wish to proceed?", "Reset List State", MB_YESNO | MB_ICONQUESTION);
  if (Result != IDYES) return;

	/* The registry section to delete */
  Section.Format("%s%s\\", OBEDIT_REGISTRY_BASE, OBRL_REGKEY_ROOT);

  Result = SHDeleteKey(HKEY_CURRENT_USER, Section);

  if (Result != ERROR_SUCCESS) {
    AddObWindowsError("Failed to delete the registry section '%s' and all its sub-keys!", Section);
  }
	
}
/*===========================================================================
 *		End of Class Method CObEditApp::ResetListState()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CObEditApp& GetObEditApp (void);
 *
 *=========================================================================*/
CObEditApp& GetObEditApp (void) {
  return theApp;
}


CObConfigFile& GetObEditConfigFile (void) {
  return theApp.GetConfigFile();
}
/*===========================================================================
 *		End of Function GetObEditApp()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObEditShowError (Flags, pTitle, pString, ...);
 *
 * Displays a modal error dialog showing error message. Returns false.
 *
 *=========================================================================*/
bool ObEditShowError (const dword Flags, const TCHAR* pTitle, const TCHAR* pString, ...) {
  CObErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(Flags);
  ErrorDlg.SetTitle(pTitle);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}


bool ObEditShowError (const TCHAR* pTitle, const TCHAR* pString, ...) {
  CObErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(OBERRDLG_SHOWUNTAGGEDERRORS);
  ErrorDlg.SetTitle(pTitle);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}


bool ObEditShowError (const TCHAR* pString, ...) {
  CObErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(OBERRDLG_SHOWUNTAGGEDERRORS);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}


bool ObEditShowLastError (const TCHAR* pString, ...) {
  CObErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(0);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}
/*===========================================================================
 *		End of Function ObEditShowError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void WINAPI SetInternalWindowText (hwnd, lpText);
 *
 *=========================================================================*/
void WINAPI SetInternalWindowText(HWND hwnd, LPCTSTR lpText) {

	/* Turn off WS_VISIBLE if necessary to avoid painting */
  DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
  if (dwStyle & WS_VISIBLE) ::SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_VISIBLE);
    
	/* Call DefWindowProc directly to set internal window text */
  DefWindowProc(hwnd, WM_SETTEXT, 0, (LPARAM)lpText);

	/* Restore parent visible state */
  if (dwStyle & WS_VISIBLE) ::SetWindowLong(hwnd, GWL_STYLE, dwStyle);
 }
/*===========================================================================
 *		End of Function WINAPI SetInternalWindowText()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool OpenWebPage (pAddress);
 *
 *=========================================================================*/
bool OpenWebPage (const char* pAddress) {
  BOOL		   Result;
  SHELLEXECUTEINFO ShellInfo;

	/* Initialize the shellinfo structure */
  ShellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
  ShellInfo.fMask  = SEE_MASK_NOCLOSEPROCESS;
  ShellInfo.hwnd   = NULL;
  ShellInfo.lpFile = pAddress;
  ShellInfo.lpVerb = _T("open");
  ShellInfo.lpClass      = NULL;
  ShellInfo.lpDirectory  = NULL;
  ShellInfo.lpIDList     = NULL;
  ShellInfo.lpParameters = NULL;
  ShellInfo.nShow        = SW_SHOWNORMAL;

	/* Attempt to open the file/page */
  Result = ShellExecuteEx(&ShellInfo);
  if (!Result) return (false);
    
  //hResult = ShellExecute (NULL, _T("open"), pSiteAddress, NULL, NULL, SW_SHOWNORMAL); 
  return (true);
}
/*===========================================================================
 *		End of Function OpenWebPage()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ObLockUndoUpdates (Lock);
 *
 *=========================================================================*/
void ObLockUndoUpdates (const bool Lock) {
  theApp.GetMainWnd()->SendMessage(OBE_MSG_LOCKUNDO, (int)Lock, 0);
}
/*===========================================================================
 *		End of Function ObLockUndoUpdates()
 *=========================================================================*/
