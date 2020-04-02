/*===========================================================================
 *
 * File:	obeditView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Implementation of the CObEditView class.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obeditDoc.h"
#include "obeditView.h"
#include "obloaddlg.h"
#include "obprogressdlg.h"
#include "common/csvfile.h"
#include "obfiletreedlg.h"
#include "obfindbinarydlg.h"
#include "common/obtime.h"
#include "modfile/obexport.h"
#include "modfile/compiler/customcompiler.h"
#include "mainfrm.h"
#include "modfile/compiler/obscriptutils.h"


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

  IMPLEMENT_DYNCREATE(CObEditView, CFormView);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEditView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObEditView, CFormView)
  //{{AFX_MSG_MAP(CObEditView)
  ON_WM_SIZE()
  ON_NOTIFY(TVN_SELCHANGED, IDC_RECORDTREE, OnSelchangedRecordtree)
  ON_COMMAND(ID_FILE_IMPORT_CSV, OnFileImportCsv)
  ON_COMMAND(ID_FILE_EXPORTCSV_SELECTEDITEMS, OnFileExportcsvSelecteditems)
  ON_COMMAND(ID_RECORDTREE_RELOAD, OnRecordtreeReload)
  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_FILE_EXPORTCSV_ITEMTYPE, OnRecordtreeExporttocsv)
  ON_COMMAND(ID_VIEW_FILESTRUCTURE, OnViewFilestructure)
  ON_COMMAND(ID_FILE_EXPORT_CSVEXTERIORLOCATIONS, OnFileExportCsvexteriorlocations)
  ON_COMMAND(ID_FILE_EXPORT_CSVEXTMAPMARKERS, OnFileExportCsvExtMapMarkers)
  ON_COMMAND(ID_HELP_TESTFIELDLOOKUP, OnHelpTestfieldlookup)
  ON_COMMAND(ID_FILE_EXPORT_CSVEXPORTEXTERIORPLANTS, OnFileExportCsvexportexteriorplants)
  ON_COMMAND(ID_EDIT_FINDBINARYDATA, OnEditFindbinarydata)
  ON_COMMAND(ID_HELP_TESTFINDFORMID, OnHelpTestfindformid)
  ON_COMMAND(ID_TEST_MEMORYSPEED, OnTestMemoryspeed)
  ON_COMMAND(ID_TEST_TOKENSCRIPTS, OnTestTokenscripts)
  ON_COMMAND(ID_RECORD_CLEAN, OnRecordClean)
  ON_UPDATE_COMMAND_UI(ID_RECORD_CLEAN, OnUpdateHasSelectedRecords)
  ON_COMMAND(ID_RECORD_MOVEACTIVE, OnRecordMoveactive)
  ON_MESSAGE(ID_OBRECORDLIST_ACTIVATE, OnEditRecordMsg)
  ON_WM_DESTROY()
  ON_COMMAND(ID_MENU_EDITRECORD, OnMenuEditrecord)
  ON_COMMAND(ID_EDIT_NEWRECORD, OnEditNewrecord)
  ON_COMMAND(ID_RECORD_TOGGLEQUEST, OnRecordTogglequest)
  ON_COMMAND(ID_RECORD_TOGGLEIGNORE, OnRecordToggleignore)
  ON_COMMAND(ID_RECORD_TOGGLEDELETE, OnRecordToggledelete)
  ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
  ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
  ON_COMMAND(ID_RECORD_RENAME, OnRecordRename)
  ON_COMMAND(ID_RECORD_CREATECOPY, OnRecordCreatecopy)
  ON_COMMAND(ID_RECORD_BATCHEDIT, OnRecordBatchedit)
  ON_COMMAND(ID_EDIT_FIND, OnEditFind)
  ON_COMMAND(ID_HELP_TESTOUTPUTEFFECTS, OnHelpTestoutputeffects)
  ON_COMMAND(ID_HELP_TESTRECORDSIZE, OnHelpTestrecordsize)
  ON_COMMAND(ID_TEST_CLEANRECOMPILEALL, OnTestCleanrecompileall)
	ON_COMMAND(ID_TEST_RECOMPILEALL, OnTestRecompileall)
	ON_COMMAND(ID_HELP_TESTCOMPARESCRIPTS, OnHelpTestcomparescripts)
  ON_COMMAND(ID_RECORDTREE_EXPORTTOCSV, OnRecordtreeExporttocsv)
  ON_UPDATE_COMMAND_UI(ID_RECORD_MOVEACTIVE, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_TOGGLEQUEST, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_TOGGLEIGNORE, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_TOGGLEDELETE, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_CREATECOPY, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_RENAME, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_BATCHEDIT, OnUpdateHasSelectedRecords)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CObEditView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG
void CObEditView::AssertValid() const {
  CFormView::AssertValid();
 }

void CObEditView::Dump(CDumpContext& dc) const  {
  CFormView::Dump(dc);
 }

CObEditDoc* CObEditView::GetDocument() {
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CObEditDoc)));
  return (CObEditDoc*)m_pDocument;
 }
#endif
/*===========================================================================
 *		End of Class Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_RenamePromptFunc (EditInfo, UserData);
 *
 * Used to prompt when renaming a record.
 *
 *=========================================================================*/
int l_RenamePromptFunc (obeditrecinfo_t& EditInfo, long UserData) {
  CObEditDlgHandler* pDlgHandler = (CObEditDlgHandler *) UserData;

  if (pDlgHandler == NULL) return (0);
  return pDlgHandler->PromptRenameCopy(EditInfo);
}
/*===========================================================================
 *		End of Function l_RenamePromptFunc()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Constructor
 *
 *=========================================================================*/
CObEditView::CObEditView() : CFormView(CObEditView::IDD) {
  //{{AFX_DATA_INIT(CObEditView)
  //}}AFX_DATA_INIT

  m_IsInitialized  = false;
  m_pCurrentFilter = NULL;
 }
/*===========================================================================
 *		End of Class CObEditView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Destructor
 *
 *=========================================================================*/
CObEditView::~CObEditView() {
 
}
/*===========================================================================
 *		End of Class CObEditView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObEditView::DoDataExchange(CDataExchange* pDX) {
  CFormView::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObEditView)
  DDX_Control(pDX, IDC_VEDGE, m_VertEdge);
  DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
  DDX_Control(pDX, IDC_RECORDTREE, m_RecordTree);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObEditView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObEditView::OnContextMenu(CWnd* pWnd, CPoint Point) {
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_RECORDTREE) {
    Result = Menu.LoadMenu(IDR_RECORDTREE_MENU);
    if (!Result) return;

    pSubMenu = Menu.GetSubMenu(0);
    if (pSubMenu == NULL) return;

    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
  }
  else if (pWnd->GetDlgCtrlID() == IDC_RECORDLIST) {
    Result = Menu.LoadMenu(IDR_RECORDLIST_MENU);
    if (!Result) return;

    pSubMenu = Menu.GetSubMenu(0);
    if (pSubMenu == NULL) return;

    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
  }

}
/*===========================================================================
 *		End of Class Event CObEditView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnFileExportCsvexportexteriorplants ();
 *
 *=========================================================================*/
void CObEditView::OnFileExportCsvexportexteriorplants() {
  obexportinfo_t ExportInfo = g_ExportCsvPlants;
  CString        Buffer;
  
	/* Prompt user for output filename */
  Buffer.Format(_T("Select CSV File to Export Exterior Plant Locations..."));
  ExportInfo.GroupFormID = 0;

  OnCsvExport(ExportInfo, Buffer);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnFileExportCsvexportexteriorplants()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnFileExportCsvexteriorlocations ();
 *
 *=========================================================================*/
void CObEditView::OnFileExportCsvexteriorlocations() {
  obexportinfo_t ExportInfo = g_ExportCsvExtLocations;
  CString        Buffer;
  
  Buffer.Format(_T("Select CSV File to Export Exterior Locations..."));
  ExportInfo.GroupFormID = 0;

  OnCsvExport(ExportInfo, Buffer);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnFileExportCsvexteriorlocations()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnFileExportCsvExtMapMarkers ();
 *
 *=========================================================================*/
void CObEditView::OnFileExportCsvExtMapMarkers() {
  obexportinfo_t ExportInfo = g_ExportCsvMapMarkers;
  CString        Buffer;
  
  Buffer.Format(_T("Select CSV File to Export Exterior Map Markers..."));
  ExportInfo.GroupFormID = 0;

  OnCsvExport(ExportInfo, Buffer);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnFileExportCsvExtMapMarkers()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - bool OnCsvExport (ExportInfo, pDialogTitle);
 *
 *=========================================================================*/
bool CObEditView::OnCsvExport (obexportinfo_t& ExportInfo, const TCHAR* pDialogTitle) {
  CFileDialog  OpenDlg(FALSE, OBEDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OBEDIT_CSV_FILTER, this);
  int          Result;

	/* Prompt user for output filename */
  if (pDialogTitle != NULL) OpenDlg.m_ofn.lpstrTitle = pDialogTitle;
  Result = OpenDlg.DoModal();
  if (Result != IDOK) return (true);

  Result = ObCsvExport(OpenDlg.GetPathName(), GetDocument()->GetActiveFile(), ExportInfo);

  if (Result != 0) {
    ObEditShowError(_T("CSV Error"), _T("Error exporting records to the CSV file '%s'!"), OpenDlg.GetPathName());
  }

  return (Result != 0);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnCsvExport()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnFileExportcsvSelecteditems ();
 *
 *=========================================================================*/
void CObEditView::OnFileExportcsvSelecteditems() {
  CFileDialog  OpenDlg(FALSE, OBEDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OBEDIT_CSV_FILTER, this);
  POSITION     ItemPos;
  CObRecord*   pRecord;
  CObRecord*   pFirstRecord;
  obcsvinfo_t  CsvInfo;
  CCsvFile     CsvFile;
  CString      Buffer;
  int          ListIndex;
  int          Result;

	/* Ignore if no records to export */
  ItemPos = m_RecordList.GetFirstSelectedItemPosition();
  if (ItemPos == NULL) return;

	/* Prompt user for output filename */
  Buffer.Format(_T("Select CSV File to Export %d Records..."), m_RecordList.GetSelectedCount());
  OpenDlg.m_ofn.lpstrTitle = Buffer;
  Result = OpenDlg.DoModal();
  if (Result != IDOK) return;

  CsvInfo.pCsvFile = &CsvFile;

	/* Output all selected records in the current list */
  while (ItemPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ItemPos);
    pRecord = m_RecordList.GetRecord(ListIndex);
    if (pRecord == NULL) continue;

		/* Initialize the CSV file on the first record */
    if (CsvFile.GetNumRows() == 0) {
      pFirstRecord = pRecord;
      Result = PrepareObCsvExport(CsvInfo, pRecord->GetFieldMap());
      if (!Result) return;
     }
	
		/* Ensure all records are the same type */
    if (pFirstRecord->GetRecordType() != pRecord->GetRecordType()) continue;

    pRecord->ExportCsv(CsvInfo);
  }

  Result = CsvFile.Save(OpenDlg.GetPathName());

  if (!Result) {
    ObEditShowError(_T("CSV Error"), _T("Error saving the CSV file '%s'!"), OpenDlg.GetPathName());
  }
	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnFileExportcsvSelecteditems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordtreeExporttocsv ();
 *
 *=========================================================================*/
void CObEditView::OnRecordtreeExporttocsv() {
  CFileDialog  OpenDlg(FALSE, OBEDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OBEDIT_CSV_FILTER, this);
  CObRecord*   pRecord;
  CObRecord*   pFirstRecord;
  obcsvinfo_t  CsvInfo;
  CCsvFile     CsvFile;
  CString      Buffer;
  int          ListIndex;
  int          Result;

	/* Ignore if no filter currently in use or no records to export */
  if (m_pCurrentFilter == NULL) return;	
  if (m_RecordList.GetItemCount() <= 0) return;

	/* Prompt user for output filename */
  Buffer.Format(_T("Select CSV File to Export %d Records..."), m_RecordList.GetItemCount());
  OpenDlg.m_ofn.lpstrTitle = Buffer;
  Result = OpenDlg.DoModal();
  if (Result != IDOK) return;

  CsvInfo.pCsvFile = &CsvFile;

	/* Output all records in the current list */
  for (ListIndex = 0; ListIndex < m_RecordList.GetItemCount(); ++ListIndex) {
    pRecord = m_RecordList.GetRecord(ListIndex);
    if (pRecord == NULL) continue;

		/* Initialize the CSV file on the first record */
    if (CsvFile.GetNumRows() == 0) {
      pFirstRecord = pRecord;
      Result = PrepareObCsvExport(CsvInfo, pRecord->GetFieldMap());
      if (!Result) return;
    }
	
		/* Ensure all records are the same type */
    if (pFirstRecord->GetRecordType() != pRecord->GetRecordType()) continue;
    pRecord->ExportCsv(CsvInfo);
  }

  Result = CsvFile.Save(OpenDlg.GetPathName());

  if (!Result) {
    ObEditShowError(_T("Error saving the CSV file '%s'!"), OpenDlg.GetPathName());
  }

}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordtreeExporttocsv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnFileImportCsv ();
 *
 *=========================================================================*/
void CObEditView::OnFileImportCsv() {
  CFileDialog OpenDlg(TRUE, OBEDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, OBEDIT_CSV_FILTER, this);
  CString     Buffer;
  CCsvFile    CsvFile;
  dword       NewRecords;
  int         Result;

  OpenDlg.m_ofn.lpstrTitle = _T("Select CSV File to Import...");

  Result = OpenDlg.DoModal();
  if (Result != IDOK) return;

  Result = CsvFile.Load(OpenDlg.GetPathName());

  if (!Result) {
    ObEditShowError(_T("Failed to load the file '%s'!"), OpenDlg.GetPathName());
    return;
  }

  Buffer.Format(_T("Loaded %d rows from csv file"), CsvFile.GetNumRows());
  MessageBox(Buffer);

  Result = GetDocument()->GetRecordHandler().ImportCsv(NewRecords, CsvFile);
  if (NewRecords > 0) GetDocument()->SetModifiedFlag(TRUE);

  if (!Result) ObEditShowError(_T("Error importing CSV file!"));
}
/*===========================================================================
 *		End of Class Event CObEditView::OnFileImportCsv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CObEditView::OnInitialUpdate() {

	/* Call the base class method first */
  CFormView::OnInitialUpdate();

  m_DlgHandler.SetDocument(GetDocument());
  GetDocument()->GetRecordHandler().GetEventHandler().AddListener(this);
  GetDocument()->GetRecordHandler().GetEventHandler().AddListener(&m_DlgHandler);
  
	/* Setup the tree control */
  m_RecordTree.Initialize(CObRecordTreeCtrl::GetOptions().FullFilterFile);
  
	/* Setup the list control */
  m_RecordList.SetListName("MainList");
  m_RecordList.DefaultSettings();
  //m_RecordList.SetupList(OB_NAME_ARMO);
  m_RecordList.SetOwner(this);

  ResizeParentToFit();

  m_RecordList.SetAutoResizeOffset();
  m_RecordList.SetAutoResize(true);
  
  m_IsInitialized = true;

	/* Disable the view scroll bars */
  SetScrollSizes(MM_TEXT, CSize(0, 0) );

  //GetParentFrame()->RecalcLayout();
  //ResizeParentToFit();
  
  UpdateContents();
}
/*===========================================================================
 *		End of Class Event CObEditView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnEditFindbinarydata ();
 *
 *=========================================================================*/
void CObEditView::OnEditFindbinarydata() {
  CObProgressDlg*  pProgressDlg;
  CObCallback	   ObEditFindCallback;
  CObFindBinaryDlg FindDlg;
  CString          Buffer;
  const TCHAR*     pParse;
  dword		   Index;
  obfinddata_t	   FindData;
  dword		   Count;
  int		   Result;
  obtimer_t	   Timer;
  double	   DeltaTime;
  byte*		   pNewData = NULL;

  Result = FindDlg.DoModal();
  if (Result != IDOK) return;

	/* Initialize the find data */
  FindData.Flags = OB_FIND_OUTPUTLOG /*| OB_FIND_ALLHEADERS*/;
  FindData.DataSize  = _tcslen(FindDlg.GetBinaryData())/2;
  if (FindData.DataSize == 0) return;
  pNewData = new byte[FindData.DataSize + 4];
  FindData.pData = pNewData;

	/* Parse the binary data text */
  Index  = 0;
  pParse = FindDlg.GetBinaryData();

  while (Index < FindData.DataSize*2) {
    pNewData[Index/2] = ConvertFromHexByte(pParse + Index);
    Index += 2;
  }

  Buffer.Empty();

  for (Index = 0; Index < FindData.DataSize; ++Index) {
    Buffer += ConvertByteToHexChar(FindData.pData[Index]);
  }

  SystemLog.Printf("Searching for binary data '%s' (%.*s)...", Buffer, FindData.DataSize, FindData.pData);

  pProgressDlg = ShowObProgressDlg(_T("Find Data"), _T("Finding binary data..."));
  ObEditFindCallback.SetCallbackInterval(1);
  ObEditFindCallback.SetFunction(ObEditDefaultProgressCallback);
  ObEditFindCallback.SetUserPtr((void *) pProgressDlg);
  ObEditFindCallback.Reset();
  ObEditFindCallback.ForceCallback(0);
  
  ObStartTimer(Timer);
 
	/* Perform the find */
  Count = GetDocument()->Find(FindData, &ObEditFindCallback);
  
  DeltaTime = ObEndTimer(Timer);
  SystemLog.Printf("Found %u matches in %u files, %u groups, %u records, and %u subrecords in %f seconds!", Count, 
		FindData.FileCount, FindData.GroupCount, FindData.RecordCount, FindData.SubrecordCount, DeltaTime);

  DestroyObProgressDlg(pProgressDlg);

	/* Cleanup the find data */
  delete[] pNewData;	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnEditFindbinarydata()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnHelpTestfindformid ();
 *
 *=========================================================================*/
void CObEditView::OnHelpTestfindformid() {
  CObProgressDlg*    pProgressDlg;
  CString            Buffer;
  CObRecord*	     pRecord;
  obfinddata_t	     FindData;
  CObCallback	     ObEditFindCallback;
  dword		     Count = 0;
  dword		     TotalCount;
  dword		     LimitCount = 200;
  dword              Index;
  obrectype_t	     ExcludeNames[] = { OB_NAME_LAND, OB_NAME_PGRD, OB_NAME_NULL };
  byte*		     pNewData = NULL;

  CObGroup* pGroup = GetDocument()->GetTopGroup()->GetTypeGroup(OB_NAME_ARMO);
  if (pGroup == NULL) return;

  TotalCount = pGroup->GetNumRecords();
  TotalCount = LimitCount;

  pProgressDlg = ShowObProgressDlg(_T("Find FormID"), _T("Finding formid..."));
  ObEditFindCallback.SetCallbackInterval(1);
  ObEditFindCallback.SetFunction(ObEditDefaultProgressCallback);
  ObEditFindCallback.SetUserPtr((void *) pProgressDlg);
  ObEditFindCallback.SetTotalRecords(TotalCount);
  ObEditFindCallback.Reset();
  
	/* Initialize the find data */
  FindData.Flags = OB_FIND_OUTPUTLOG /*| OB_FIND_ALLHEADERS*/;
  FindData.DataSize = 4;
  pNewData = new byte[8];
  FindData.pData = pNewData;
  FindData.pExcludeRecords = &ExcludeNames[0];

  Index = 0;
  pRecord = ObCastClassNull(CObRecord, pGroup->GetRecord(Index));
  
  while (pRecord) {
    Buffer.Format("Finding formId 0x%08X... (%4.4s)", pRecord->GetFormID(), pRecord->GetRecordType().Name);
    SystemLog.Printf(Buffer);
    pProgressDlg->SetLabel(Buffer);
    pProgressDlg->SetProgress((float)Count*100.0f / (float) TotalCount);
    ++Count;
    ++Index;
    if (Count > LimitCount) break;

    *(dword *)(pNewData) = pRecord->GetFormID();

    GetDocument()->GetActiveFile().Find(FindData, &ObEditFindCallback);

    pRecord = ObCastClassNull(CObRecord, pGroup->GetRecord(Index));
  }
  
  DestroyObProgressDlg(pProgressDlg);

	/* Cleanup the find data */
  delete[] pNewData;
}
/*===========================================================================
 *		End of Class Event CObEditView::OnHelpTestfindformid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordtreeReload ();
 *
 *=========================================================================*/
void CObEditView::OnRecordtreeReload() {
  m_RecordTree.LoadFilters(CObRecordTreeCtrl::GetOptions().FullFilterFile);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordtreeReload()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnSize (nType, CX, CY);
 *
 *=========================================================================*/
void CObEditView::OnSize (UINT nType, int CX, int CY) {
  CFormView::OnSize(nType, CX, CY);

  if (m_IsInitialized) {
    m_RecordList.AutoResize();
    m_RecordTree.SetWindowPos(NULL, 0, 0, 170, CY, SWP_NOMOVE | SWP_NOZORDER);
    m_VertEdge.SetWindowPos(NULL, 0, 0, 3, CY+2, SWP_NOMOVE | SWP_NOZORDER);
   }
	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnSelchangedRecordtree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObEditView::OnSelchangedRecordtree (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_TREEVIEW*     pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  CObRecordFilter* pFilter;
  DWORD            Value;

  *pResult = 0;
  Value = m_RecordTree.GetItemData(pNMTreeView->itemNew.hItem);
  if (Value == 0) return;

  pFilter = (CObRecordFilter *) Value;
  if (pFilter == m_pCurrentFilter) return;

  if (pFilter->IsFlagEmpty() || pFilter->GetRecordType() == OB_NAME_NULL) pFilter = NULL;

  m_pCurrentFilter = pFilter;
  
  m_RecordList.SetupList(m_pCurrentFilter);
  m_RecordList.AddAllRecords(GetDocument()->GetTopGroup());
}
/*===========================================================================
 *		End of Class Event CObEditView::OnSelchangedRecordtree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnUpdate (pSender, lHint, pHint);
 *
 *=========================================================================*/
void CObEditView::OnUpdate (CView* pSender, LPARAM lHint, CObject* pHint) {
  obrecupdateinfo_t*	pUpdateInfo = (obrecupdateinfo_t *) pHint;

  switch (lHint) {
    case OBEDIT_DOC_HINT_UPDATEALL:
        UpdateContents();
	break;
    case OBEDIT_DOC_HINT_UPDATERECORD:
        m_RecordList.UpdateRecord(pUpdateInfo->pNewRecord, pUpdateInfo->pOldRecord);
        m_RecordTree.UpdateFilterCounts(GetDocument()->GetTopGroup());
	break;
    case OBEDIT_DOC_HINT_ADDRECORD:
        m_RecordList.AddRecord(pUpdateInfo->pNewRecord);
        m_RecordTree.IncludeInCounts(pUpdateInfo->pNewRecord);
	break;
    case OBEDIT_DOC_HINT_GETDATA:
	/* TODO */
	break;
    case OBEDIT_DOC_HINT_CLEARFILTERS: {
	break; }
    case OBEDIT_DOC_HINT_UPDATEFILTERS: {
	break; }
    default:
	CView::OnUpdate(pSender, lHint, pHint);
	break;
  }
	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnViewFilestructure ();
 *
 *=========================================================================*/
void CObEditView::OnViewFilestructure() {
  CObFileTreeDlg TreeDlg;

  TreeDlg.SetTopGroup(GetDocument()->GetTopGroup());
  TreeDlg.DoModal();
	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnViewFilestructure()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CObEditView::PreCreateWindow (CREATESTRUCT& cs) {
  return CFormView::PreCreateWindow(cs);
 }
/*===========================================================================
 *		End of Class Method CObEditView::PreCreateWindow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnHelpTestfieldlookup ();
 *
   1096769 Records
	09:17:59 (24609) - Iteration Time = 0.013028 secs
	09:17:59 (24718) - Iteration Time with Class Cast = 0.095499 secs
	09:17:59 (25234) - Find WEIGHT Field = 0.522570 secs
	09:18:00 (25781) - Get WEIGHT String = 0.551424 secs
	09:18:00 (26234) - Find EDITORID Field = 0.452844 secs
	09:18:01 (26750) - Get EDITORID String = 0.511969 secs
	09:18:01 (26984) - Find WEIGHT Field1 = 0.232224 secs
	09:18:01 (27218) - Find EDITORID Field1 = 0.228567 secs
	09:18:01 (27468) - Get WEIGHT String1 = 0.251833 secs
	09:18:02 (27718) - Get EDITORID String1 = 0.255710 secs
	09:18:05 (30984) - Iteration Time = 0.013076 secs
	09:18:05 (31078) - Iteration Time with Class Cast = 0.095586 secs
	09:18:06 (31593) - Find WEIGHT Field = 0.508603 secs
	09:18:06 (32015) - Get WEIGHT String = 0.425909 secs
	09:18:06 (32453) - Find EDITORID Field = 0.439205 secs
	09:18:07 (32859) - Get EDITORID String = 0.393132 secs
	09:18:07 (33031) - Find WEIGHT Field1 = 0.173945 secs
	09:18:07 (33187) - Find EDITORID Field1 = 0.166808 secs
	09:18:07 (33375) - Get WEIGHT String1 = 0.181755 secs
	09:18:08 (33609) - Get EDITORID String1 = 0.233427 secs

  1023759 Records using GetFirst/GetNext...
	11:36:29 (26968) - Iteration Time = 0.102827 secs
	11:36:29 (27093) - Iteration Time with Class Cast = 0.139105 secs
	11:36:29 (27312) - Find WEIGHT Field = 0.217886 secs
	11:36:30 (27562) - Get WEIGHT String = 0.247051 secs
	11:36:30 (27781) - Find EDITORID Field = 0.212212 secs
	11:36:30 (28078) - Get EDITORID String = 0.292917 secs
	11:36:30 (28218) - Find WEIGHT Field1 = 0.140716 secs
	11:36:30 (28359) - Find EDITORID Field1 = 0.140012 secs
	11:36:30 (28500) - Get WEIGHT String1 = 0.141654 secs
	11:36:31 (28640) - Get EDITORID String1 = 0.139036 secs
	11:36:31 (28640) - Record Count = 1023759

   Using Switch Compare
	10:03:11 (30968) - Compare WEIGHT Field = 0.173250 secs
	10:03:11 (31140) - Compare EDITORID Field = 0.175900 secs

   Using Field Map Compare
	01:06:38 (72687) - Compare WEIGHT Field = 0.239074 secs
	01:06:39 (72984) - Compare EDITORID Field = 0.303329 secs

 *=========================================================================*/
void CObEditView::OnHelpTestfieldlookup() {
  obtimer_t		Timer;
  CObRecordHandler*	pHandler = &(GetDocument()->GetRecordHandler());
  //CObEspFile*		pFile = &(GetDocument()->GetEspFile());
  CObBaseRecord*	pBaseRecord;
  const obrecfield_t*	pField;
  CSString		Buffer;
  CObRecord*		pRecord;
  CObWeapRecord		TestRecord;
  OBMAPPOS		RecordPos;
  dword			Count = 0;

  TestRecord.InitializeNew();
  TestRecord.SetEditorID("testeditorid01");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		++Count;
		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Iteration Time");
  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Iteration Time with Class Cast");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			pField = pRecord->FindField(OB_FIELD_WEIGHT);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Find WEIGHT Field");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			pRecord->GetField(Buffer, OB_FIELD_WEIGHT);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Get WEIGHT String");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			pField = pRecord->FindField(OB_FIELD_EDITORID);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Find EDITORID Field");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			pRecord->GetField(Buffer, OB_FIELD_EDITORID);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Get EDITORID String");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(OB_FIELD_WEIGHT);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Find WEIGHT Field1");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(OB_FIELD_EDITORID);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Find EDITORID Field1");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(OB_FIELD_WEIGHT);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Get WEIGHT String1");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(OB_FIELD_EDITORID);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Get EDITORID String1");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			pRecord->CompareFields(OB_FIELD_WEIGHT, &TestRecord);
			//pField = pRecord->GetField1(OB_FIELD_EDITORID);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Compare WEIGHT Field");

  ObStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = ObCastClass(CObRecord, pBaseRecord);

		if (pRecord) {
			pRecord->CompareFields(OB_FIELD_EDITORID, &TestRecord);
			//pField = pRecord->GetField1(OB_FIELD_EDITORID);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  ObEndTimer(Timer, "Compare EDITORID Field");

  SystemLog.Printf("Record Count = %d", Count);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnHelpTestfieldlookup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnTestMemoryspeed ();
 *
 *=========================================================================*/
#define TEST_MEMORY_SIZE	1000000
#define TEST_MEMORY_ARRAYSIZE	1000

  CObRecord* pRecords[TEST_MEMORY_SIZE];
  CSString*  pStrings[TEST_MEMORY_SIZE];
  CObRecord* pRecordArray[TEST_MEMORY_ARRAYSIZE];
  CSString*  pStringArray[TEST_MEMORY_ARRAYSIZE];

void CObEditView::OnTestMemoryspeed() {
  DWORD     Index;
  obtimer_t Timer;

  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    pRecords[Index] = new CObRecord;
  }

  ObEndTimer(Timer, "Allocated 1000000 CObRecords in ");
  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    pStrings[Index] = new CSString;
  }

  ObEndTimer(Timer, "Allocated 1000000 CSStrings in ");
  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    pRecordArray[Index] = new CObRecord[TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE];
  }

  ObEndTimer(Timer, "Allocated 1000 CObRecords[1000] in ");
  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    pStringArray[Index] = new CSString[TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE];
  }

  ObEndTimer(Timer, "Allocated 1000 CSStrings[1000] in ");
  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    delete pRecords[Index];
  }

  ObEndTimer(Timer, "Deleted 1000000 CObRecords in ");
  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    delete pStrings[Index];
  }

  ObEndTimer(Timer, "Deleted 1000000 CSStrings in ");
  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    delete[] pRecordArray[Index];
  }

  ObEndTimer(Timer, "Deleted 1000 CObRecords[1000] in ");
  ObStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    delete[] pStringArray[Index];
  }

  ObEndTimer(Timer, "Deleted 1000 CSStrings[1000] in ");
	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnTestMemoryspeed()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnTestTokenscripts ();
 *
 *=========================================================================*/
void CObEditView::OnTestTokenscripts() {
  CCustomCompiler   Compiler;
  CScanSourceString ScanSource;
  CObBaseRecord*    pBaseRecord;
  CObScptRecord*    pScript;
  CObTypeGroup*	    pScriptGroup;
  bool		    Result;
  dword		    ScriptCount = 0;
  dword		    ErrorCount = 0;
  dword		    ByteCount = 0;
  dword		    LineCount = 0;
  obtimer_t	    Timer;
  double	    DeltaTime;
  dword		    Index;

  Result = Compiler.Load("testtable1.dat");
  if (!Result) return;
  GetObEditApp().UpdateScriptColorOptions(Compiler, true);
  ObStartTimer(Timer);

  //ScanSource.SetString("end");
  //Compiler.Tokenize(&ScanSource);

  pScriptGroup = GetDocument()->GetRecordHandler().GetTopGroup()->GetTypeGroup(OB_NAME_SCPT);
  if (pScriptGroup == NULL) return;

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pScriptGroup->GetRecord(Index);
    pScript = ObCastClass(CObScptRecord, pBaseRecord);
    if (pScript == NULL) continue;

    //SystemLog.Printf("Tokenizing script %s...", pScript->GetEditorID());

    ScanSource.SetString(pScript->GetScriptText());

    Result = Compiler.Tokenize(&ScanSource);
    if (!Result) ++ErrorCount;

    ++ScriptCount;
    ByteCount += pScript->GetScriptSize();
    LineCount += pScript->GetNumLines();
  }

  DeltaTime = ObEndTimer(Timer);
  SystemLog.Printf("Succesfully tokenized %u of %u scripts (%u lines, %u bytes) in %f seconds.", ScriptCount - ErrorCount, ScriptCount, LineCount, ByteCount, DeltaTime);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnTestTokenscripts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordClean ();
 *
 *=========================================================================*/
void CObEditView::OnRecordClean() {
  CObProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  CObRecord*      pRecord;
  CObRecord*      pNewRecord;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();
  int             ListIndex;

  if (SelectedCount > OBEDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowObProgressDlg("Clean Records", "Cleaning selected records from active file...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  ObLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    pRecord   = m_RecordList.GetRecord(ListIndex);
    ++Count;
    if (pRecord == NULL) continue;

    	/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }

		/* Ignore non-active records */
    if (!pRecord->IsActive()) continue;

		/* Perform the clean */
    pNewRecord = GetDocument()->GetRecordHandler().CleanRecord(pRecord);
    GetDocument()->SetModifiedFlag(TRUE);
  }

  DestroyObProgressDlg(pProgressDlg);
  ObLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordClean()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Method - void UpdateContents (void);
 *
 *=========================================================================*/
void CObEditView::UpdateContents (void) {
  m_RecordList.DeleteAllItems();
  m_RecordList.AddAllRecords(GetDocument()->GetRecordHandler().GetTopGroup());
  m_RecordTree.UpdateFilterCounts(GetDocument()->GetRecordHandler().GetTopGroup());
  AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);
}
/*===========================================================================
 *		End of Class Method CObEditView::UpdateContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordMoveactive ();
 *
 *=========================================================================*/
void CObEditView::OnRecordMoveactive() {
  CObProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  CObRecord*      pRecord;
  bool	          Result;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();
  int             ListIndex;

  if (SelectedCount > OBEDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowObProgressDlg("Move Active", "Moving selected records to active file...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  ObLockUndoUpdates(true);
  
  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    pRecord   = m_RecordList.GetRecord(ListIndex);
    ++Count;
    if (pRecord == NULL) continue;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }

		/* Ignore active records */
    if (pRecord->IsActive()) continue;

		/* Perform the move */
    Result = GetDocument()->GetRecordHandler().MakeRecordActive(pRecord);
    if (Result) GetDocument()->SetModifiedFlag(TRUE);
  }

  DestroyObProgressDlg(pProgressDlg);
  ObLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordMoveactive()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnUpdateHasSelectedRecords (pCmdUI);
 *
 *=========================================================================*/
void CObEditView::OnUpdateHasSelectedRecords (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_RecordList.GetSelectedCount() > 0); 	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnUpdateHasSelectedRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CObEditView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  CObRecord* pRecord = (CObRecord *) wParam;
  OnEditRecord(pRecord);

  return (0);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnEditRecord (pRecord);
 *
 *=========================================================================*/
void CObEditView::OnEditRecord (CObRecord* pRecord) {
  obeditrecinfo_t EditInfo;

  if (pRecord == NULL) return;
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = false;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.pOldRecord   = pRecord;
  EditInfo.NewEditorID.Empty();
  
  m_DlgHandler.EditRecord(EditInfo);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnDestroy (void);
 *
 *=========================================================================*/
void CObEditView::OnDestroy (void) {
  m_DlgHandler.CloseAll();

  CFormView::OnDestroy();
}
/*===========================================================================
 *		End of Class Event CObEditView::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnMenuEditrecord ();
 *
 *=========================================================================*/
void CObEditView::OnMenuEditrecord() {
  POSITION ListPos;
  int      ListIndex;

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  if (ListPos == NULL) return;
  ListIndex = m_RecordList.GetNextSelectedItem(ListPos);

  OnEditRecord(m_RecordList.GetRecord(ListIndex));
}
/*===========================================================================
 *		End of Class Event CObEditView::OnMenuEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnEditNewrecord ();
 *
 *=========================================================================*/
void CObEditView::OnEditNewrecord() {
  const obrectype_t* pRecordType;
  obeditrecinfo_t    EditInfo;

  pRecordType = m_RecordList.GetCurrentRecordType();
  if (pRecordType == NULL) return;

  m_DlgHandler.EditNewRecord(*pRecordType);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnEditNewrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordTogglequest ();
 *
 *=========================================================================*/
void CObEditView::OnRecordTogglequest() {
  CObProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  int             ListIndex;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();

  if (SelectedCount > OBEDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowObProgressDlg("Toggle Quest", "Toggling quest flag of selected records...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  ObLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    OnToggleQuestRecord(m_RecordList.GetRecord(ListIndex));
    ++Count;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }
  }

  DestroyObProgressDlg(pProgressDlg);
  ObLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordTogglequest()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordToggleignore ();
 *
 *=========================================================================*/
void CObEditView::OnRecordToggleignore() {
  CObProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  int             ListIndex;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();

  if (SelectedCount > OBEDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowObProgressDlg("Toggle Ignore", "Toggling ignore flag of selected records...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  ObLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    OnToggleIgnoreRecord(m_RecordList.GetRecord(ListIndex));
    ++Count;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }
  }

  DestroyObProgressDlg(pProgressDlg);
  ObLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordToggleignore()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordToggledelete ();
 *
 *=========================================================================*/
void CObEditView::OnRecordToggledelete() {
  CObProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  int             ListIndex;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();

  if (SelectedCount > OBEDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowObProgressDlg("Toggle Delete", "Toggling delete flag of selected records...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  ObLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    OnToggleDeleteRecord(m_RecordList.GetRecord(ListIndex));
    ++Count;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }
  }

  DestroyObProgressDlg(pProgressDlg);
  ObLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordToggledelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - bool OnToggleQuestRecord (pRecord);
 *
 *=========================================================================*/
bool CObEditView::OnToggleQuestRecord (CObRecord* pRecord) {
  CObRecord* pNewRecord;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  pNewRecord = GetDocument()->GetRecordHandler().ToggleQuestFlag(pRecord);
  if (pNewRecord != NULL) GetDocument()->SetModifiedFlag(TRUE);

  return (true);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnToggleQuestRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - bool OnToggleIgnoreRecord (pRecord);
 *
 *=========================================================================*/
bool CObEditView::OnToggleIgnoreRecord (CObRecord* pRecord) {
  CObRecord* pNewRecord;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  pNewRecord = GetDocument()->GetRecordHandler().ToggleIgnoreFlag(pRecord);
  if (pNewRecord != NULL) GetDocument()->SetModifiedFlag(TRUE);

  return (true);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnToggleIgnoreRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - bool OnToggleDeleteRecord (pRecord);
 *
 *=========================================================================*/
bool CObEditView::OnToggleDeleteRecord (CObRecord* pRecord) {
  CObRecord* pNewRecord;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  pNewRecord = GetDocument()->GetRecordHandler().ToggleDeleteFlag(pRecord);
  if (pNewRecord != NULL) GetDocument()->SetModifiedFlag(TRUE);

  return (true);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnToggleDeleteRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnEditUndo ();
 *
 *=========================================================================*/
void CObEditView::OnEditUndo() {
  CObUndoItem* pUndoItem;
  CObRecord*   pRecord;

	/* Get the item to undo, if any */
  pUndoItem = GetDocument()->GetRecordHandler().GetTopUndoItem();
  if (pUndoItem == NULL) return;

	/* TODO: Do in proper event handler? */
  pRecord = GetDocument()->GetRecordHandler().FindFormID(pUndoItem->GetNewFormID());
  //if (pRecord) m_DlgHandler.CloseAll(pRecord);

  if (pUndoItem->GetRecord() != NULL) {
    pRecord = GetDocument()->GetRecordHandler().FindFormID(pUndoItem->GetRecord()->GetFormID());
    //if (pRecord) m_DlgHandler.CloseAll(pRecord);
  }

  GetDocument()->GetRecordHandler().PerformUndo();
  //AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);
  
	/* TODO: Update by proper event handler? */
  UpdateContents();
}
/*===========================================================================
 *		End of Class Event CObEditView::OnEditUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnUpdateEditUndo (pCmdUI);
 *
 *=========================================================================*/
void CObEditView::OnUpdateEditUndo (CCmdUI* pCmdUI) {
  pCmdUI->Enable(GetDocument()->GetRecordHandler().GetNumUndoItems());
}
/*===========================================================================
 *		End of Class Event CObEditView::OnUpdateEditUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
 *
 *=========================================================================*/
void CObEditView::OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView) {
/*  CDocument* pDoc1 = NULL;
  CDocument* pDoc2 = NULL;

  SystemLog.Printf("%s, Active = %p, Deactive = %p", bActivate ? "Activate" : "Deactivate", pActivateView, pDeactiveView);
  
  if (pActivateView != NULL) pDoc1 = pActivateView->GetDocument();
  if (pDeactiveView != NULL) pDoc2 = pDeactiveView->GetDocument();

  if (pDoc1 == NULL) {
     AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) NULL, 0);
  }
  else if (bActivate) {
    //AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &(((CObEditDoc *)pDoc1)->GetRecordHandler().GetUndoItems()), 0);
  } //*/

//*	
  if (bActivate && pActivateView != NULL) {
    AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);
  }
  else if (pActivateView != NULL)  {
    //AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) 0, 0);
  } //*/

  CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnActivateView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - int OnListenAddRecord (pEvent);
 *
 *=========================================================================*/
int CObEditView::OnListenAddRecord (CObListenEvent* pEvent) {
  
  m_RecordList.UpdateRecord(pEvent->GetNewRecord(), NULL);
  m_RecordTree.IncludeInCounts(pEvent->GetNewRecord());

  AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnListenAddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CObEditView::OnListenCleanRecord (CObListenEvent* pEvent) {

  m_RecordList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  //if (pEvent->GetOldRecord() != NULL) m_RecordTree.RemoveFromCounts(pEvent->GetOldRecord());
  if (pEvent->GetNewRecord() != NULL) m_RecordTree.IncludeInCounts(pEvent->GetNewRecord());

  AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObEditView::OnListenUpdateRecord (CObListenEvent* pEvent) {

  m_RecordList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  if (pEvent->GetNewRecord() != NULL) m_RecordTree.IncludeInCounts(pEvent->GetNewRecord());

  AfxGetMainWnd()->SendMessage(OBE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - int OnListenPreUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObEditView::OnListenPreUpdateRecord (CObListenEvent* pEvent) {
  
  m_RecordTree.RemoveFromCounts(pEvent->GetOldRecord());
  
  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnListenPreUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_CheckRenameID (pString, pOrigString UserData);
 *
 * Callback function used by the input dialog called from OnRecordRename().
 *
 *=========================================================================*/
int l_CheckRenameID (const char* pString, const char* pOrigString, long UserData) {
  CObMultiRecordHandler* pHandler = (CObMultiRecordHandler *) UserData;
  CSString		 Buffer = pString;
  CObRecord*		 pRecord;

  if (pHandler == NULL) return (OB_INPUTDLG_CHECK_OK);
  ObPrepareEditorID(Buffer);

  if (Buffer.CompareNoCase(pOrigString) == 0) return (OB_INPUTDLG_CHECK_NOCHANGE);

  pRecord = pHandler->FindEditorID(Buffer);
  if (pRecord != NULL) return (OB_INPUTDLG_CHECK_ERROR);

  return (OB_INPUTDLG_CHECK_OK);
}
/*===========================================================================
 *		End of Function l_CheckRenameID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordRename ();
 *
 *=========================================================================*/
void CObEditView::OnRecordRename() {
  CObRecord*	pRecord;
  CObIdRecord*	pIdRecord;
  CString	Buffer;
  CSString	EditorID;
  bool		Result;

  pRecord = m_RecordList.GetSelectedRecord();
  if (pRecord == NULL) return;
  pIdRecord = ObCastClass(CObIdRecord, pRecord);
  if (pIdRecord == NULL) return;
  Buffer = pIdRecord->GetEditorID();

	/* Prompt user for a new editorid */
  Result = ObInputDialogValidate(Buffer, _T("Enter New EditorID"), _T("Enter a new editorid for the renamed record:"), l_CheckRenameID, (long) &GetDocument()->GetRecordHandler(), isalnum);
  if (!Result) return;

	/* Perform initial preparations on the new id */
  EditorID = Buffer;
  ObPrepareEditorID(EditorID);

	/* Ensure it has actually changed */
  if (pIdRecord->IsEditorID(EditorID)) return;
  
	/* Check for a valid editorid */
  Result = GetDocument()->GetRecordHandler().IsValidNewEditorID(Buffer);

  if (!Result) {
    ObEditShowLastError(_T("The new editorid is not valid!"));
    return;
  }

	/* Perform the rename */
  Result = GetDocument()->GetRecordHandler().RenameIDRecord(pIdRecord, EditorID);	
  if (Result) GetDocument()->SetModifiedFlag(TRUE);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordRename()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_CheckCopyID (pString, pOrigString, UserData);
 *
 * Callback function used by the input dialog called from OnRecordCreatecopy().
 *
 *=========================================================================*/
int l_CheckCopyID (const char* pString, const char* pOrigString, long UserData) {
  CObMultiRecordHandler* pHandler = (CObMultiRecordHandler *) UserData;
  CSString		 Buffer = pString;
  CObRecord*		 pRecord;

  if (pHandler == NULL) return (OB_INPUTDLG_CHECK_OK);
  ObPrepareEditorID(Buffer);

  pRecord = pHandler->FindEditorID(Buffer);
  if (pRecord != NULL) return (OB_INPUTDLG_CHECK_ERROR);

  return (OB_INPUTDLG_CHECK_OK);
}
/*===========================================================================
 *		End of Function l_CheckCopyID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordCreatecopy ();
 *
 *=========================================================================*/
void CObEditView::OnRecordCreatecopy() {
  CObRecord*	pRecord;
  CObIdRecord*	pIdRecord;
  CString	Buffer;
  CSString	EditorID;
  bool		Result;

  pRecord = m_RecordList.GetSelectedRecord();
  if (pRecord == NULL) return;
  pIdRecord = ObCastClass(CObIdRecord, pRecord);
  if (pIdRecord == NULL) return;
  Buffer = pIdRecord->GetEditorID();
  
	/* Prompt user for a new editorid */
  Result = ObInputDialogValidate(Buffer, _T("Enter New EditorID"), _T("Enter a new editorid for the record copy:"), l_CheckCopyID, (long) &GetDocument()->GetRecordHandler(), isalnum);
  
  if (!Result) return;

  	/* Perform initial preparations on the new id */
  EditorID = Buffer;
  ObPrepareEditorID(EditorID);

	/* Check for a valid editorid */
  Result = GetDocument()->GetRecordHandler().IsValidNewEditorID(Buffer);

  if (!Result) {
    ObEditShowLastError(_T("The new editorid is not valid!"));
    return;
  }

	/* Perform the rename */
  Result = GetDocument()->GetRecordHandler().CreateIDRecordCopy(pIdRecord, EditorID);	
  if (Result) GetDocument()->SetModifiedFlag(TRUE);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordCreatecopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnRecordBatchedit ();
 *
 *=========================================================================*/
void CObEditView::OnRecordBatchedit() {
  CObRefRecordArray Records;
  CObRecord*	    pRecord;
  POSITION	    ListPos;
  int		    ListIndex;

	/* Get the records to edit */
  ListPos = m_RecordList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    pRecord   = m_RecordList.GetRecord(ListIndex);
    if (pRecord != NULL) Records.Add(pRecord);
  }

	/* Ignore if no records to edit */
  if (Records.GetSize() == 0) return;

  m_DlgHandler.BatchEdit(Records);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnRecordBatchedit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnEditFind ();
 *
 *=========================================================================*/
void CObEditView::OnEditFind() {
  m_DlgHandler.OpenFind();	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnEditFind()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnHelpTestoutputeffects ();
 *
 *=========================================================================*/
void CObEditView::OnHelpTestoutputeffects() {
  CObFile	 OutputFile;
  CObBaseRecord* pBaseRecord;
  CObMgefRecord* pEffect;
  CObTypeGroup*  pEffectGroup;
  obmgefdata_t*  pEffectData;
  dword		 Index;
  bool		 Result;

  pEffectGroup = GetDocument()->GetTopGroup()->GetTypeGroup(OB_NAME_MGEF);
  if (pEffectGroup == NULL) return;

  Result = OutputFile.Open("effects.csv", "wt");
  if (!Result) return;

  for (Index = 0; Index < pEffectGroup->GetNumRecords(); ++Index){
    pBaseRecord = pEffectGroup->GetRecord(Index); 

    pEffect = ObCastClass(CObMgefRecord, pBaseRecord);
    if (pEffect == NULL) continue;

    pEffectData = pEffect->GetEffectData();
    if (pEffectData == NULL) continue;

    //OutputFile.Printf("%s, %s, ", pEffect->GetEditorID(), pEffect->GetFullName());
    //OutputFile.Printf("0x%08X, %f\n", pEffectData->Flags, pEffectData->BaseCost);
    //ADD_EFFECTVALUE( OB_MGEF_BAHE, "Bound Helmet")
    OutputFile.Printf("\tADD_EFFECTVALUE( OB_MGEF_%4.4s, \"%s\", 0x%08X )\n", pEffect->GetEditorID(), pEffect->GetFullName(), pEffectData->Flags);

  }

}
/*===========================================================================
 *		End of Class Event CObEditView::OnHelpTestoutputeffects()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnHelpTestrecordsize ();
 *
 *=========================================================================*/
void CObEditView::OnHelpTestrecordsize() {
  TGenPtrMap<obrectype_t, dword, dword > RecordSizes;
  CObRecord*   pRecord;
  obrectype_t* pRecType;
  OBMAPPOS     Pos;
  MAPPOSITION  MapPos;
  dword*       pNewValue;
  dword	       TotalSize = 0;

  pRecord = GetDocument()->GetRecordHandler().GetFirstRecord(Pos);

  while (pRecord != NULL) {
    pNewValue = RecordSizes.Lookup(pRecord->GetRecordType());

    if (pNewValue != NULL) {
      //*pNewValue += pRecord->GetHeader().Size;
      *pNewValue += pRecord->GetSubrecordSize();
    }
    else {
      pNewValue  = new dword;
      //*pNewValue = pRecord->GetHeader().Size;
      *pNewValue = pRecord->GetSubrecordSize();
      RecordSizes.SetAt(pRecord->GetRecordType(), pNewValue);
    }

    //TotalSize += pRecord->GetHeader().Size;
    TotalSize += pRecord->GetSubrecordSize();
    pRecord = GetDocument()->GetRecordHandler().GetNextRecord(Pos);
  }

  pNewValue = RecordSizes.GetFirstRecord(MapPos);
  //TotalSize = 0;

  while (pNewValue != NULL) {
    pRecType = RecordSizes.GetPosKey(MapPos);
    //TotalSize += *pNewValue;

    if (pRecType != NULL) {
      float Ratio = (float) (((double)(*pNewValue)) / (double)TotalSize * 100.0);
      SystemLog.Printf("%4.4s = %u kb (%.1f%%)", pRecType->Name, *pNewValue/1000, Ratio);
    }
      
    pNewValue = RecordSizes.GetNextRecord(MapPos);
  }

  SystemLog.Printf("Total Size = %u kb", (dword)(TotalSize/1000));
}
/*===========================================================================
 *		End of Class Event CObEditView::OnHelpTestrecordsize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnTestCleanrecompileall ();
 *
 *=========================================================================*/
void CObEditView::OnTestCleanrecompileall() {
  CObTypeGroup*     pScriptGroup;
  CObBaseRecord*    pBaseRecord;
  CObScptRecord*    pScript;
  CCustomCompiler   Compiler;
  obtimer_t         Timer;
  dword             Index;
  double            DeltaTime;
  bool              Result;
  dword		    TotalCount = 0;
  dword		    FailCount  = 0;

  pScriptGroup = GetDocument()->GetRecordHandler().GetTypeGroup(OB_NAME_SCPT);

  if (pScriptGroup == NULL) {
    AddObGeneralError("No scripts in active file!");
    return;
  }

  ObStartTimer(Timer);

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pScriptGroup->GetRecord(Index);
    pScript = ObCastClass(CObScptRecord, pBaseRecord);
    if (pScript == NULL) continue;

    Result = Compiler.Compile(pScript);
    if (!Result) ++FailCount;
    ++TotalCount;
  }

  DeltaTime = ObEndTimer(Timer);
  SystemLog.Printf("Compiled %u of %u scripts in active file in %g secs!", TotalCount-FailCount, TotalCount, DeltaTime);	
}
/*===========================================================================
 *		End of Class Event CObEditView::OnTestCleanrecompileall()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnTestRecompileall ();
 *
 *=========================================================================*/
void CObEditView::OnTestRecompileall() {
  CObTypeGroup*     pScriptGroup;
  CObBaseRecord*    pBaseRecord;
  CObScptRecord*    pScript;
  CCustomCompiler   Compiler;
  obtimer_t         Timer;
  dword             Index;
  double            DeltaTime;
  bool              Result;
  dword		    TotalCount = 0;
  dword		    FailCount  = 0;

  pScriptGroup = GetDocument()->GetRecordHandler().GetTypeGroup(OB_NAME_SCPT);

  if (pScriptGroup == NULL) {
    AddObGeneralError("No scripts in active file!");
    return;
  }

  Compiler.SetRecordHandler(&GetDocument()->GetRecordHandler());
  Compiler.Load("testtable1.dat");
  GetObEditApp().UpdateScriptColorOptions(Compiler, true);
  
  ObStartTimer(Timer);

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pScriptGroup->GetRecord(Index);
    pScript = ObCastClass(CObScptRecord, pBaseRecord);
    if (pScript == NULL) continue;

    SystemLog.Printf("Compiling %s...", pScript->GetEditorID());

    Result = Compiler.Compile(pScript);

    ObOutputScriptErrorsToLog(Compiler.GetErrors());

    if (!Result) {
      SystemLog.Printf("Failed to compile script (%u errors, %u warnings)!", Compiler.GetErrorCount(), Compiler.GetWarningCount());
      ++FailCount;
    }
    else {
      SystemLog.Printf("Successfully compiled script (%u errors, %u warnings)!", Compiler.GetErrorCount(), Compiler.GetWarningCount());
    }

    ++TotalCount;
  }

  DeltaTime = ObEndTimer(Timer);
  SystemLog.Printf("Compiled %u of %u scripts in active file in %g secs!", TotalCount-FailCount, TotalCount, DeltaTime);
}
/*===========================================================================
 *		End of Class Event CObEditView::OnTestRecompileall()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnHelpTestcomparescripts ();
 *
 *=========================================================================*/
void CObEditView::OnHelpTestcomparescripts() {
  CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, 
			"Plugin Files (*.esp)|*.esp|Master Files (*.esm)|*.esm|All Files (*.*)|*.*||", this);
  CObSimpleRecordHandler EspFile;
  CObCallback	         LoadCallback;
  CObProgressDlg*        pProgressDlg;
  CObTypeGroup*          pScriptGroup;
  CObBaseRecord*         pRecord;
  CObScptRecord*         pScript;
  obtimer_t              CompareTimer;
  obscriptcompare_t      CompareInfo;
  int                    DlgResult;  
  dword                  Index;
  int                    ScriptCount = 0;
  int                    ErrorCount  = 0;
  bool			 Result;

  FileDlg.m_ofn.lpstrTitle = "Select Plugin With Scripts To Compare";
  DlgResult = FileDlg.DoModal();
  if (DlgResult != IDOK) return;

  pProgressDlg = ShowObProgressDlg(_T("Load"), _T("Loading Plugin File..."));
  LoadCallback.SetCallbackInterval(1);
  LoadCallback.SetFunction(ObEditDefaultProgressCallback);
  LoadCallback.SetUserPtr((void *) pProgressDlg);
  LoadCallback.Reset();
  LoadCallback.ForceCallback(0);

  Result = EspFile.Load(FileDlg.GetPathName(), &LoadCallback);
  DestroyObProgressDlg(pProgressDlg);
  if (!Result) return;

  SystemLog.Printf("Comparing all scripts in file '%s'...", FileDlg.GetPathName());
  ObStartTimer(CompareTimer);

	/* Iterate through all scripts in the selected file */
  pScriptGroup = EspFile.GetTopGroup()->GetTypeGroup(OB_NAME_SCPT);

  if (pScriptGroup == NULL) {
    SystemLog.Printf("No scripts in file to compare!");
    return;
  }

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pRecord = pScriptGroup->GetRecord(Index);
    pScript = ObCastClass(CObScptRecord, pRecord);
    if (pScript == NULL) continue;

    CompareInfo.pScript2 = pScript;

    pRecord = GetDocument()->GetRecordHandler().FindEditorID(pScript->GetEditorID());

    if (pRecord == NULL) {
      continue;
    }

    CompareInfo.pScript1 = ObCastClass(CObScptRecord, pRecord);
    
    SystemLog.Printf("Comparing script %s (0x%06X, 0x%06X)...", pScript->GetEditorID(), pScript->GetFormID(), CompareInfo.pScript2->GetFormID());
    Result = ObCompareScripts(CompareInfo);

    if (!Result) {
      ++ErrorCount;
      SystemLog.Printf("\tERROR comparing script data!");
    }
    else {
      SystemLog.Printf("\tSuccessfully compared script data!");
    }

    ++ScriptCount;
  }

  SystemLog.Printf("Finished comparing %u scripts with %u errors in %g seconds.", ScriptCount, ErrorCount, ObEndTimer(CompareTimer));
}
/*===========================================================================
 *		End of Class Event CObEditView::OnHelpTestcomparescripts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditView Event - void OnEditSelectall ();
 *
 *=========================================================================*/
void CObEditView::OnEditSelectall() {
  int Index;

  for (Index = 0; Index < m_RecordList.GetItemCount(); ++Index) {
    m_RecordList.SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
  }

  m_RecordList.SetFocus();
}
/*===========================================================================
 *		End of Class Event CObEditView::OnEditSelectall()
 *=========================================================================*/