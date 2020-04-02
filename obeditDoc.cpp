/*===========================================================================
 *
 * File:	obeditDoc.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Implementation of the CObEditDoc document class.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obeditDoc.h"
#include "modfile/records/obcheckrecord.h"
#include "modfile/obexport.h"
#include "modfile/obimport.h"
#include "common/obutils.h"


/*===========================================================================
 *
 * Begin Location Definitions
 *
 *=========================================================================*/

	/* Debug definitions */
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  IMPLEMENT_DYNCREATE(CObEditDoc, CDocument)

/*===========================================================================
 *		End of Location Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEditDoc Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObEditDoc, CDocument)
  //{{AFX_MSG_MAP(CObEditDoc)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CObEditDoc Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Constructor
 *
 *=========================================================================*/
CObEditDoc::CObEditDoc() {
  m_HasActiveContent = false;
}
/*===========================================================================
 *		End of Class CObEditDoc Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Destructor
 *
 *=========================================================================*/
CObEditDoc::~CObEditDoc() {
  m_RecordHandler.Destroy();
}
/*===========================================================================
 *		End of Class CObEditDoc Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - void DeleteContents ();
 *
 *=========================================================================*/
void CObEditDoc::DeleteContents() {
  m_RecordHandler.Destroy();
  CDocument::DeleteContents();
}
/*===========================================================================
 *		End of Class Method CObEditDoc::DeleteContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Event - BOOL OnNewDocument ();
 *
 *=========================================================================*/
BOOL CObEditDoc::OnNewDocument() {
  if (!CDocument::OnNewDocument()) return FALSE;
  m_HasActiveContent = false;

  m_RecordHandler.NewFile();
  return (TRUE);
 }
/*===========================================================================
 *		End of Class Event CObEditDoc::OnNewDocument()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Event - BOOL OnOpenDocument (lpszPathName);
 *
 *=========================================================================*/
BOOL CObEditDoc::OnOpenDocument (LPCTSTR lpszPathName) {
  obfileloadinfo_t* pLoadInfo    = ((CObEditApp *) AfxGetApp())->GetCurrentLoadInfo();
  CObProgressDlg*   pProgressDlg = ((CObEditApp *) AfxGetApp())->GetCurrentProgressDlg();
  CObCallback*      pCallback    = ((CObEditApp *) AfxGetApp())->GetCurrentLoadCallback();
  bool		    Result;

  if (pLoadInfo == NULL) {
    AddObGeneralError("Invalid load information received!");
    return (FALSE);
  }

  SetModifiedFlag();

  m_HasActiveContent = !pLoadInfo->m_ActiveFilename.IsEmpty();
  
  Result = m_RecordHandler.Load(*pLoadInfo, pCallback);

  if (!Result) {
    DeleteContents();
    return (FALSE); 
   }

  SetModifiedFlag(FALSE);
  //SetTitle(m_RecordHandler.GetActiveFile().GetShortFilename());
  //UpdateAllViews(NULL, OBEDIT_DOC_HINT_UPDATEALL, NULL);
  return (TRUE);
 }
/*===========================================================================
 *		End of Class Event CObEditDoc::OnOpenDocument()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - BOOL DoFileSave ();
 *
 *=========================================================================*/
BOOL CObEditDoc::DoFileSave() {

  if (!m_HasActiveContent) {
    CSString InstallPath;

    GetObInstallPath(InstallPath);
    m_strPathName  = InstallPath;
    m_strPathName += "data\\";
    m_strPathName += m_strTitle;
    m_strPathName += ".esp";
    return DoSave(NULL);
  }

  return CDocument::DoFileSave();
}
/*===========================================================================
 *		End of Class Method CObEditDoc::DoFileSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - bool DoSaveBackup (pFilename);
 *
 *=========================================================================*/
bool CObEditDoc::DoSaveBackup (const TCHAR* pFilename) {

	/* Are backups enabled? */
  if (!CObMultiRecordHandler::GetOptions().EnableBackup)       return (true);
  if (!CObMultiRecordHandler::GetOptions().EnableBackupOnSave) return (true);

  return DoBackup(pFilename);
}
/*===========================================================================
 *		End of Class Method CObEditDoc::DoBackup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - bool CheckBackups (OldestFile, BackupCount, const int64 BackupSize);
 *
 *=========================================================================*/
bool CObEditDoc::CheckBackups (const char* OldestFile, const dword BackupCount, const int64 BackupSize) {
  BOOL Result;
  bool Delete = false;
  
  if (CObMultiRecordHandler::GetOptions().MaxBackupCount > 0 && (int)BackupCount > CObMultiRecordHandler::GetOptions().MaxBackupCount) {
    Delete = true;
  }
  else if (CObMultiRecordHandler::GetOptions().MaxBackupSize > 0 && BackupSize/1000000 > CObMultiRecordHandler::GetOptions().MaxBackupSize) {
    Delete = true;
  }

  if (Delete) {
    Result = DeleteFile(OldestFile);
    if (!Result) return AddObWindowsError("Failed to delete the old backup file '%s'!", OldestFile);
    SystemLog.Printf("Deleted old backup file '%s'.", OldestFile);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDoc::CheckBackups()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - bool MakeBackupFile (OutputFile, InputFile);
 *
 * TODO: Cleanup, better backup cleanup needed
 *
 *=========================================================================*/
bool CObEditDoc::MakeBackupFile (CString& OutputFile, CString& InputFile) {
  WIN32_FIND_DATA FindData;
  CString	  OldestFile;
  FILETIME	  OldestTime;
  CString	  Filename;
  HANDLE	  hFind;
  int		  CharIndex;
  BOOL		  Result;
  int		  MaxBackupIndex = 0;
  int		  BackupIndex;
  dword		  BackupCount = 0;
  int64		  BackupSize  = 0;
  
  Filename = InputFile;
  CharIndex = Filename.ReverseFind('\\'); 
  if (CharIndex >= 0) Filename.Delete(0, CharIndex + 1);

  OutputFile  = CObMultiRecordHandler::GetOptions().FullBackupPath;
  OutputFile += Filename;
  Filename    = OutputFile + ".*";

	/* Find the maximum existing backup index of the current backup file */
  hFind  = FindFirstFile(Filename, &FindData);
  Result = TRUE;
  
  while (hFind != INVALID_HANDLE_VALUE && Result) {
    Filename = FindData.cFileName;

    CharIndex = Filename.ReverseFind('.'); 
    if (CharIndex >= 0) Filename.Delete(0, CharIndex + 1);
    
    BackupIndex = atoi(Filename);
    if (BackupIndex > MaxBackupIndex) MaxBackupIndex = BackupIndex;

    if (OldestFile.IsEmpty() || CompareFileTime(&OldestTime, &FindData.ftLastWriteTime) > 0) {
      OldestFile = FindData.cFileName;
      OldestTime = FindData.ftLastWriteTime;
    }

    ++BackupCount;
    BackupSize += (int64) FindData.nFileSizeLow;
    BackupSize += ((int64) FindData.nFileSizeHigh) << 32;
    Result = FindNextFile(hFind, &FindData);
  }

	/* See if we need to delete the oldest backup file */
  if (!OldestFile.IsEmpty()) {
    Filename  = CObMultiRecordHandler::GetOptions().FullBackupPath;
    Filename += OldestFile;
    CheckBackups(Filename, BackupCount, BackupSize);
  }
  
	/* Create the output filename */
  ++MaxBackupIndex;
  Filename.Format(".%03d", MaxBackupIndex);
  OutputFile += Filename;

  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDoc::MakeBackupFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - bool CreateBackupPath (void);
 *
 *=========================================================================*/
bool CObEditDoc::CreateBackupPath (void) {
  bool Result;
  
  Result = MakePathEx(CObMultiRecordHandler::GetOptions().FullBackupPath);

  if (!Result) {
    AddObGeneralError("Failed to create the backup directory '%s'!", CObMultiRecordHandler::GetOptions().FullBackupPath);
    return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDoc::CreateBackupPath()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - bool DoBackup (pFilename);
 *
 *=========================================================================*/
bool CObEditDoc::DoBackup (const TCHAR* pFilename) {
  CString InputFile;
  CString OutputFile;
  bool    Result;
  BOOL    CopyResult;

	/* Ignore if the file doesn't yet exist */
  InputFile = pFilename;
  if (!FileExists(InputFile)) return (true);

  Result = MakeBackupFile(OutputFile, InputFile);
  if (!Result) return (false);

  Result = CreateBackupPath();
  if (!Result) return (false);

  CopyResult = CopyFile(InputFile, OutputFile, FALSE);

  if (!CopyResult) {
    AddObWindowsError("Failed to backup '%s' to '%s'!", InputFile, OutputFile);
    return (false);
  }

  SystemLog.Printf("Successfully backed up '%s' to '%s'", InputFile, OutputFile);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEditDoc::DoBackup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Event - BOOL OnSaveDocument (lpszPathName);
 *
 *=========================================================================*/
BOOL CObEditDoc::OnSaveDocument (LPCTSTR lpszPathName) {
  CObProgressDlg* pProgressDlg;
  CObCallback     SaveCallback;
  CString	  Filename(lpszPathName);
  int		  CharIndex;
  bool		  Result;

  UpdateAllViews(NULL, OBEDIT_DOC_HINT_GETDATA, NULL);

  DoSaveBackup(lpszPathName);

  CharIndex = Filename.ReverseFind('\\'); 
  if (CharIndex >= 0) Filename.Delete(0, CharIndex + 1);

  pProgressDlg = ShowObProgressDlg(_T("Saving File"), _T("Saving File..."));
  //pProgressDlg->SetCancelMsg(_T("Are you sure you wish to abort this save?"));
  SaveCallback.SetCallbackInterval(100);
  SaveCallback.SetUserPtr((void *) pProgressDlg);
  SaveCallback.SetFunction(ObEditDefaultProgressCallback);
  
  Result = GetActiveFile().Save(lpszPathName, &SaveCallback);

  DestroyObProgressDlg(pProgressDlg);

  if (!Result) {
    ReportSaveLoadException(lpszPathName, NULL, TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
    return (FALSE); 
   }

  m_HasActiveContent = true;
  SetModifiedFlag(FALSE);
  return (TRUE);
 }
/*===========================================================================
 *		End of Class Event CObEditDoc::OnSaveDocument()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Method - void Serialize (ar);
 *
 *=========================================================================*/
void CObEditDoc::Serialize (CArchive& ar) {
  assert(false);
 }
/*===========================================================================
 *		End of Class Method CObEditDoc::Serialize()
 *=========================================================================*/


#ifdef _DEBUG
/*===========================================================================
*
 * Class CObEditDoc Diagnostics
 * 
 *=========================================================================*/
void CObEditDoc::AssertValid() const {
  CDocument::AssertValid();
 }

void CObEditDoc::Dump(CDumpContext& dc) const {
  CDocument::Dump(dc);
 }
/*===========================================================================
 *		End of Class CObEditDoc Diagnostics
 *=========================================================================*/
#endif
