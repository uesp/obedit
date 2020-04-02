/*===========================================================================
 *
 * File:	Obloaddlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 28, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObLoadDlg.h"


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
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLoadDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CObLoadDlg)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_FILE_LIST, OnColumnclickFileList)
	ON_NOTIFY(NM_DBLCLK, IDC_FILE_LIST, OnDblclkFileList)
	ON_BN_CLICKED(IDC_SETACTIVE, OnSetactive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CObLoadDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_FileListCompare (lParam1, lParam2, lParamSort);
 *
 *=========================================================================*/
int CALLBACK l_FileListCompare (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  obloaddlgfileinfo_t*  pData1    = (obloaddlgfileinfo_t  *) lParam1;
  obloaddlgfileinfo_t*  pData2    = (obloaddlgfileinfo_t  *) lParam2;
  obloadfilesortinfo_t* pSortData = (obloadfilesortinfo_t *) lParamSort;
  int		        Result    = 0;

  if (pData1 == NULL || pData2 == NULL || pSortData == NULL) return (0);

  switch (pSortData->SortType) {
    case OBFILELIST_FILENAME:
        Result = _tcsicmp(pData2->FindData.cFileName, pData1->FindData.cFileName);
	break;
    case OBFILELIST_DATE: {
        CTime Time1(pData1->FindData.ftLastWriteTime);
        CTime Time2(pData2->FindData.ftLastWriteTime);
        CTimeSpan TimeDiff = Time2 - Time1;
	Result = TimeDiff.GetTotalSeconds();
	break; }
    case OBFILELIST_SIZE:
        Result = pData2->FindData.nFileSizeHigh - pData1->FindData.nFileSizeHigh;
	if (Result == 0) Result = pData1->FindData.nFileSizeLow - pData2->FindData.nFileSizeLow;
	break;
    case OBFILELIST_DEFAULTSORT: {
        
	if (pData1->IsMaster != pData2->IsMaster) {
	  Result = pData2->IsMaster - pData1->IsMaster;
	}
	else {
          CTime Time1(pData1->FindData.ftLastWriteTime);
          CTime Time2(pData2->FindData.ftLastWriteTime);
          CTimeSpan TimeDiff = Time2 - Time1;
	  Result = TimeDiff.GetTotalSeconds();
	}

	break; }
  }

  if (pSortData->Reverse) return (-Result);
  return (Result);
}
/*===========================================================================
 *		End of Function l_FileListCompare()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Constructor
 *
 *=========================================================================*/
CObLoadDlg::CObLoadDlg(CWnd* pParent) : CDialog(CObLoadDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CObLoadDlg)
  //}}AFX_DATA_INIT
  m_LastSortReverse = false;
  m_LastSortSubItem = OBFILELIST_FILENAME;
  m_pLastActiveFile = NULL;
 }
/*===========================================================================
 *		End of Class CObLoadDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Method - void AddFile (FindData);
 *
 *=========================================================================*/
void CObLoadDlg::AddFile (WIN32_FIND_DATA& FindData) {
  obloaddlgfileinfo_t* pNewData;
  CString	       Buffer;
  int                  ListIndex;

	/* Create a copy of the find data */
  pNewData  = new obloaddlgfileinfo_t;
  m_FileInfos.Add(pNewData);

  pNewData->FindData = FindData;
  pNewData->IsActive = false;
  pNewData->IsMaster = false;

	/* Add the file to the list control */
  ListIndex = m_FileList.InsertItem(0, FindData.cFileName);
  if (ListIndex < 0) return;
  m_FileList.SetItemData(ListIndex, (DWORD) pNewData);

  if (ObCheckExtension(FindData.cFileName, "esm")) {
    pNewData->IsMaster = true;
  }
  
  UpdateFile(ListIndex, pNewData);
}
/*===========================================================================
 *		End of Class Method CObLoadDlg::AddFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_SortLoadInfosByDate (lParam1, lParam2, lParamSort);
 *
 *=========================================================================*/
int __stdcall l_SortLoadInfosByDate (long lParam1, long lParam2, long lParamSort) {
  obloaddlgfileinfo_t* pFileInfo1 = (obloaddlgfileinfo_t *) lParam1;
  obloaddlgfileinfo_t* pFileInfo2 = (obloaddlgfileinfo_t *) lParam2;

  if (pFileInfo1 == NULL || pFileInfo2 == NULL) return (0);

  CTime Time1(pFileInfo1->FindData.ftLastWriteTime);
  CTime Time2(pFileInfo2->FindData.ftLastWriteTime);
  CTimeSpan TimeDiff = Time1 - Time2;

  return TimeDiff.GetTotalSeconds();
}
/*===========================================================================
 *		End of Function l_SortLoadInfosByDate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Method - void CreateLoadInfo (void);
 *
 *=========================================================================*/
void CObLoadDlg::CreateLoadInfo (void) {
  CObRefLoadDlgFileInfos SortLoadInfos;
  obloaddlgfileinfo_t*	 pFileData;
  CSString*		 pNewString;
  dword			 Index;
  int			 ListIndex;

	/* Clear the current load information */
  m_LoadInfo.m_MasterFilenames.Destroy();
  m_LoadInfo.m_ActiveFilename.Empty();

	/* Iterate through all checked items in the list */
  for (ListIndex = 0; ListIndex < m_FileList.GetItemCount(); ++ListIndex) {
    if (!m_FileList.GetCheck(ListIndex)) continue;

    pFileData = (obloaddlgfileinfo_t *) m_FileList.GetItemData(ListIndex);
    if (pFileData == NULL) continue;

    if (pFileData->IsActive) {
      m_LoadInfo.m_ActiveFilename = m_FilePath + pFileData->FindData.cFileName;
    }
    else if (pFileData->IsMaster) {
      SortLoadInfos.Add(pFileData);
    }
    else {
      AddObGeneralError("Cannot add non-master file '%s' as a dependancy!", pFileData->FindData.cFileName);
    }
  } 

	/* Sort and load the masters according to date */
  SortLoadInfos.Sort(l_SortLoadInfosByDate, 0);

  for (Index = 0; Index < SortLoadInfos.GetSize(); ++Index) {
    pNewString = new CSString;
    m_LoadInfo.m_MasterFilenames.Add(pNewString);
    *pNewString = m_FilePath + SortLoadInfos[Index]->FindData.cFileName;
    //SystemLog.Printf("%d) %s", Index, pNewString->c_str());
  }

}
/*===========================================================================
 *		End of Class Method CObLoadDlg::CreateLoadInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObLoadDlg::DoDataExchange (CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObLoadDlg)
	DDX_Control(pDX, IDC_FILE_LIST, m_FileList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObLoadDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Method - void FillFileList (void);
 *
 *=========================================================================*/
void CObLoadDlg::FillFileList (void) {
  CSString DataPath;
  CSString FileSpec;
  bool     Result;

	/* Clear the current contents */
  m_FileList.DeleteAllItems();
  m_FileInfos.Empty();
  m_pLastActiveFile = NULL;

	/* Attempt to get the Oblivion data path */
  Result = GetObInstallPath(DataPath);
  if (Result) DataPath += "data\\";
  m_FilePath = DataPath;

	/* Find all ESP/ESM files in the path */
  FileSpec = DataPath + "*.esp";
  FillFileList(FileSpec);
  FileSpec = DataPath + "*.esm";
  FillFileList(FileSpec);
}
/*===========================================================================
 *		End of Class Method CObLoadDlg::FillFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Method - int FillFileList (pFileSpec);
 *
 *=========================================================================*/
int CObLoadDlg::FillFileList (const char* pFileSpec) {
  HANDLE	  hFind;
  WIN32_FIND_DATA FindData;
  BOOL		  FindResult;
  int		  Count = 0;

  hFind = FindFirstFile(pFileSpec, &FindData);
  FindResult = (hFind != INVALID_HANDLE_VALUE);

  while (FindResult) {
    ++Count;

    AddFile(FindData);
    
    FindResult = FindNextFile(hFind, &FindData);
  }

  FindClose(hFind);
  return (Count);
}
/*===========================================================================
 *		End of Class Method CObLoadDlg::FillFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Event - void OnColumnclickFileList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObLoadDlg::OnColumnclickFileList(NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW*         pNMListView = (NM_LISTVIEW *) pNMHDR;
  obloadfilesortinfo_t SortData;

  SortData.Reverse  = false;
  SortData.SortType = pNMListView->iSubItem;

  if (pNMListView->iSubItem == m_LastSortSubItem) {
    m_LastSortReverse = !m_LastSortReverse;
    SortData.Reverse  = m_LastSortReverse;
  }
  else {
    m_LastSortSubItem  = pNMListView->iSubItem;
    m_LastSortReverse  = false;
  }

  m_FileList.SortItems(l_FileListCompare, (DWORD) &SortData);
	
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObLoadDlg::OnColumnclickFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Event - void OnDblclkFileList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObLoadDlg::OnDblclkFileList (NMHDR* pNMHDR, LRESULT* pResult) {
  obloaddlgfileinfo_t*	pFileData;
  POSITION		ItemPos;
  int			ListIndex;
  
	/* Get the first, and only, selected item */
  ItemPos = m_FileList.GetFirstSelectedItemPosition();
  if (ItemPos == NULL) return;
  ListIndex = m_FileList.GetNextSelectedItem(ItemPos);
  if (ListIndex < 0) return;
  pFileData = (obloaddlgfileinfo_t *) m_FileList.GetItemData(ListIndex);
  if (pFileData == NULL) return;

	/* Set the check state */
  if (m_FileList.GetCheck(ListIndex)) {
    m_FileList.SetCheck(ListIndex, FALSE);

    if (pFileData->IsActive) { 
      pFileData->IsActive = false; 
      m_pLastActiveFile = NULL;
    }
  }
  else {
    m_FileList.SetCheck(ListIndex, TRUE);

    if (m_pLastActiveFile == NULL && !pFileData->IsMaster) {
      pFileData->IsActive = true;
      m_pLastActiveFile = pFileData;
    }
  }

  UpdateFile(ListIndex, pFileData);
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObLoadDlg::OnDblclkFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObLoadDlg::OnInitDialog() {
  obloadfilesortinfo_t SortData;

  CDialog::OnInitDialog();

	/* Initialize the file list */
  m_FileList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
  m_FileList.InsertColumn(0, _T("Filename"),      LVCFMT_LEFT,   240, OBFILELIST_FILENAME);
  m_FileList.InsertColumn(1, _T("Date"),          LVCFMT_CENTER, 120, OBFILELIST_DATE);
  m_FileList.InsertColumn(2, _T("Size (bytes)"),  LVCFMT_CENTER,  75, OBFILELIST_SIZE);
  m_FileList.InsertColumn(3, _T("Type"),          LVCFMT_CENTER,  90, OBFILELIST_DEFAULTSORT);

  FillFileList();

  SortData.Reverse  = false;
  SortData.SortType = OBFILELIST_DEFAULTSORT;
  m_FileList.SortItems(l_FileListCompare, (DWORD) &SortData);
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObLoadDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CObLoadDlg::OnOK (void) {
  CreateLoadInfo();
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObLoadDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Event - void OnSetactive ();
 *
 *=========================================================================*/
void CObLoadDlg::OnSetactive() {
  obloaddlgfileinfo_t*	pFileData;
  POSITION		ItemPos;
  LVFINDINFO		FindInfo;
  int			ListIndex;
  int			ActiveIndex;
  
	/* Get the first, and only, selected item */
  ItemPos = m_FileList.GetFirstSelectedItemPosition();
  if (ItemPos == NULL) return;
  ListIndex = m_FileList.GetNextSelectedItem(ItemPos);
  if (ListIndex < 0) return;
  pFileData = (obloaddlgfileinfo_t *) m_FileList.GetItemData(ListIndex);
  if (pFileData == NULL) return;

	/* Update the previous active file, if any */
  if (m_pLastActiveFile != NULL) {
    FindInfo.flags       = LVFI_PARAM;
    FindInfo.psz         = NULL;
    FindInfo.lParam      = (long) m_pLastActiveFile;
    FindInfo.vkDirection = 0;

    m_pLastActiveFile->IsActive = false; 
    ActiveIndex = m_FileList.FindItem(&FindInfo, -1);
    if (ActiveIndex >= 0) UpdateFile(ActiveIndex, m_pLastActiveFile);
  }

  if (pFileData->IsActive) { 
    pFileData->IsActive = false; 
    m_pLastActiveFile = NULL;
  }
  else {
    m_FileList.SetCheck(ListIndex, TRUE);
    pFileData->IsActive = true;
    m_pLastActiveFile = pFileData;
    UpdateFile(ListIndex, pFileData);	
  }
 
}
/*===========================================================================
 *		End of Class Event CObLoadDlg::OnSetactive()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLoadDlg Method - void UpdateFile (ListIndex, pFileData);
 *
 *=========================================================================*/
void CObLoadDlg::UpdateFile (const int ListIndex, obloaddlgfileinfo_t* pFileData) {
  CString Buffer;
  int64   FileSize;

  m_FileList.SetItemText(ListIndex, OBFILELIST_FILENAME, pFileData->FindData.cFileName);

  CTime FileTime(pFileData->FindData.ftLastWriteTime);
  m_FileList.SetItemText(ListIndex, OBFILELIST_DATE, FileTime.Format(_T("%c")));
  
  FileSize  = (int64)pFileData->FindData.nFileSizeLow + (((int64) pFileData->FindData.nFileSizeHigh) << 32);
  Buffer.Format(_T("%I64d"), FileSize);
  m_FileList.SetItemText(ListIndex, OBFILELIST_SIZE, Buffer);

  if (pFileData->IsActive) {
    if (pFileData->IsMaster)
      m_FileList.SetItemText(ListIndex, OBFILELIST_DEFAULTSORT, _T("Active Master"));
    else
      m_FileList.SetItemText(ListIndex, OBFILELIST_DEFAULTSORT, _T("Active"));
  }
  else if (pFileData->IsMaster) {
    m_FileList.SetItemText(ListIndex, OBFILELIST_DEFAULTSORT, _T("Master"));
  }
  else {
    m_FileList.SetItemText(ListIndex, OBFILELIST_DEFAULTSORT, _T(""));
  }

}
/*===========================================================================
 *		End of Class Method CObLoadDlg::UpdateFile()
 *=========================================================================*/
