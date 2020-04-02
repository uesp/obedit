/*===========================================================================
 *
 * File:	Obresourceview.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 5, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obresourceview.h"
#include "dialogs/obeditdlghandler.h"


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

  IMPLEMENT_DYNCREATE(CObResourceView, CFormView)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObResourceView, CFormView)
	//{{AFX_MSG_MAP(CObResourceView)
	ON_NOTIFY(NM_DBLCLK, IDC_RESOURCE_TREE, OnDblclkResourceTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_RESOURCE_TREE, OnSelchangedResourceTree)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(TVN_BEGINDRAG, IDC_RESOURCE_TREE, OnBegindragResourceTree)
	ON_WM_CAPTURECHANGED()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Constructor
 *
 *=========================================================================*/
CObResourceView::CObResourceView() : CFormView(CObResourceView::IDD) {
	//{{AFX_DATA_INIT(CObResourceView)
	//}}AFX_DATA_INIT

  m_pCurrentInstance = NULL;
  m_pDragResource    = NULL;
  m_pDragImage       = NULL;
  m_IsDragging       = false;
  m_hGoodDropCursor  = NULL;
  m_EnablePreview    = true;

  m_pBsaFiles        = NULL;
  m_pResourceHandler = NULL;
  
  m_hBadDropCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_NO));
}
/*===========================================================================
 *		End of Class CObResourceView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Destructor
 *
 *=========================================================================*/
CObResourceView::~CObResourceView() {

  if (m_pDragImage != NULL) {
    delete m_pDragImage;
    m_pDragImage = NULL;
  }

}
/*===========================================================================
 *		End of Class CObResourceView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObResourceView::DoDataExchange(CDataExchange* pDX) {
	CFormView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObResourceView)
	DDX_Control(pDX, IDC_PREVIEW_RICHEDIT, m_PreviewText);
	DDX_Control(pDX, IDC_FILETIME, m_Filetime);
	DDX_Control(pDX, IDC_FILESIZE, m_Filesize);
	DDX_Control(pDX, IDC_FILENAME, m_Filename);
	DDX_Control(pDX, IDC_HBAR, m_HBar);
	DDX_Control(pDX, IDC_RESOURCE_TREE, m_ResourceTree);
	DDX_Control(pDX, IDC_PREVIEW_IMAGE, m_PreviewImage);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObResourceView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - HTREEITEM AddResourceTree (pFile, hParent);
 *
 *=========================================================================*/
HTREEITEM CObResourceView::AddResourceTree (CObResourceFile* pFile, HTREEITEM hParent) {
  HTREEITEM hNewItem;

  if (pFile == NULL) return (NULL);
  
  hNewItem = m_ResourceTree.InsertItem("", 1, 1, hParent);
  if (hNewItem == NULL) return (NULL);

  m_ResourceTree.SetItemData(hNewItem, (DWORD) pFile);
  pFile->SetUserDataPtr(hNewItem);

  UpdateResourceTree(pFile, hNewItem);
  return (hNewItem);
}
/*===========================================================================
 *		End of Class Method CObResourceView::AddResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void UpdateResourceTree (pFile, hItem);
 *
 *=========================================================================*/
void CObResourceView::UpdateResourceTree (CObResourceFile* pFile, HTREEITEM hItem) {
  CString Buffer;

  if (pFile == NULL) {
    m_ResourceTree.SetItemText(hItem, "");
    return;
  }

  if (pFile->GetNumInstances() > 1)
    Buffer.Format("%s (%u)", pFile->GetName(), pFile->GetNumInstances());
  else
    Buffer.Format("%s", pFile->GetName());

  m_ResourceTree.SetItemText(hItem, Buffer);
}
/*===========================================================================
 *		End of Class Method CObResourceView::UpdateResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_DefaultTreeCompare (lParam1, lParam2, lParamSort);
 *
 *=========================================================================*/
int CALLBACK l_DefaultTreeCompare (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  CObResourceBase* pBase1 = (CObResourceBase *) lParam1;
  CObResourceBase* pBase2 = (CObResourceBase *) lParam2;

  if (pBase1->IsFolder() && pBase2->IsFolder()) {
    CObResourceFolder* pFolder1 = (CObResourceFolder *) pBase1;
    CObResourceFolder* pFolder2 = (CObResourceFolder *) pBase2;
    return stricmp(pFolder1->GetName(), pFolder2->GetName());
  }
  else if (pBase1->IsFolder()) {
    return (-1);
  }
  else if (pBase2->IsFolder()) {
    return (1);
  }
  else {
    CObResourceFile* pFile1 = (CObResourceFile *) pBase1;
    CObResourceFile* pFile2 = (CObResourceFile *) pBase2;
    return stricmp(pFile1->GetName(), pFile2->GetName());
  }

  return (0);
}
/*===========================================================================
 *		End of Function CALLBACK l_DefaultTreeCompare()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void FillResourceTree (pFolder, hParent);
 *
 *=========================================================================*/
void CObResourceView::FillResourceTree (CObResourceFolder* pFolder, HTREEITEM hParent) {
  CObResourceBase*   pBase;
  CObResourceFolder* pNewFolder;
  CObResourceFile*   pFile;
  MAPPOSITION	     Position;
  TVSORTCB	     SortInfo;
  HTREEITEM	     hNewItem;

  if (pFolder == NULL) return;

  pBase = pFolder->GetResources().GetFirstRecord(Position);

  while (pBase != NULL) {

    if (pBase->IsFolder()) {
      pNewFolder = (CObResourceFolder *) pBase;
      hNewItem = m_ResourceTree.InsertItem(pNewFolder->GetName(), 0, 0, hParent);

      m_ResourceTree.SetItemData(hNewItem, (DWORD) pNewFolder);
      pNewFolder->SetUserDataPtr(hNewItem);

      FillResourceTree(pNewFolder, hNewItem);
    }
    else {
      pFile = (CObResourceFile *) pBase;
      AddResourceTree(pFile, hParent);
    }

    pBase = pFolder->GetResources().GetNextRecord(Position);
  }

  SortInfo.hParent     = hParent;
  SortInfo.lParam      = (long) this;
  SortInfo.lpfnCompare = l_DefaultTreeCompare;
 
  m_ResourceTree.SortChildrenCB(&SortInfo);
}
/*===========================================================================
 *		End of Class Method CObResourceView::FillResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void FillResourceTree (void);
 *
 *=========================================================================*/
void CObResourceView::FillResourceTree (void) {
  //m_ResourceTree.LockWindowUpdate();

	/* Clear the current tree */
  m_ResourceTree.DeleteAllItems();

  if (m_pResourceHandler != NULL) {
    FillResourceTree(&m_pResourceHandler->GetRootFolder(), m_ResourceTree.GetRootItem());
  }

  //m_ResourceTree.UnlockWindowUpdate();
}
/*===========================================================================
 *		End of Class Method CObResourceView::FillResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CObResourceView::PreCreateWindow(CREATESTRUCT& cs) {
  return CFormView::PreCreateWindow(cs);
}
/*===========================================================================
 *		End of Class Method CObResourceView::PreCreateWindow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CObResourceView::OnInitialUpdate() {

  CFormView::OnInitialUpdate();
  ResizeParentToFit();

  this->SetScrollSizes(MM_TEXT, CSize(0, 0));

  m_Bitmaps[0].LoadBitmap(IDB_FOLDER);
  m_Bitmaps[1].LoadBitmap(IDB_FILE);
  m_ImageList.Create(16, 16, ILC_COLOR16, 64, 8);
  //m_ImageList.Create(IDB_FOLDER, 16, 10, RGB(0,0,0));
  m_ImageList.Add(&m_Bitmaps[0], (CBitmap *)NULL);
  m_ImageList.Add(&m_Bitmaps[1], (CBitmap *)NULL);
  m_ResourceTree.SetImageList(&m_ImageList, TVSIL_NORMAL);

  m_PreviewImage.OnInitialUpdate();
  m_PreviewImage.ShowWindow(SW_HIDE);
  
  m_PreviewText.SetBackgroundColor(FALSE, RGB(214,209,204));
  m_PreviewText.LimitText(0);

  FillResourceTree();
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObResourceView::AssertValid() const {
  CFormView::AssertValid();
}


void CObResourceView::Dump(CDumpContext& dc) const {
  CFormView::Dump(dc);
}


#endif
/*===========================================================================
 *		End of Class Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnDblclkResourceTree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObResourceView::OnDblclkResourceTree (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnDblclkResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnSelchangedResourceTree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObResourceView::OnSelchangedResourceTree (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_TREEVIEW*     pNMTreeView = (NM_TREEVIEW *) pNMHDR;
  CObResourceBase* pBase;
  CObResourceFile* pFile = NULL;
  HTREEITEM        hTree;
  *pResult = 0;

  hTree = m_ResourceTree.GetSelectedItem();

  if (hTree == NULL) {
    m_pCurrentInstance = NULL;
  }
  else {
    pBase = (CObResourceBase *) m_ResourceTree.GetItemData(hTree);
    if (pBase != NULL && !pBase->IsFolder()) pFile = (CObResourceFile *) pBase;

    if (pFile == NULL)
      m_pCurrentInstance = NULL;
    else
      m_pCurrentInstance = pFile->GetMainInstance();
  }

  UpdateDisplayedInstance();
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnSelchangedResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CObResourceView::OnSize(UINT nType, int cx, int cy) {
  CFormView::OnSize(nType, cx, cy);

	/* Update the available client size */
  CRect ClientRect;
  GetClientRect(&ClientRect);
  cx = ClientRect.Width();
  cy = ClientRect.Height();

  if (IsWindow(m_ResourceTree.m_hWnd)) {
    m_ResourceTree.SetWindowPos(NULL, 0, 0, 250, cy - 0, SWP_NOMOVE | SWP_NOZORDER);
  }

  if (IsWindow(m_HBar.m_hWnd)) {
    m_HBar.SetWindowPos(NULL, 250, 100, cx - 250, 1, SWP_NOZORDER);
  }

  if (IsWindow(m_PreviewText.m_hWnd)) {
    m_PreviewText.SetWindowPos(NULL, 250, 102, cx - 250, cy - 102, SWP_NOZORDER);
  }

  if (IsWindow(m_PreviewImage.m_hWnd)) {
    m_PreviewImage.SetWindowPos(NULL, 250, 102, cx - 250, cy - 102, SWP_NOZORDER);
  }
	
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void ClearDisplayedInstance (void);
 *
 *=========================================================================*/
void CObResourceView::ClearDisplayedInstance (void) {
  m_Filename.SetWindowText("");
  m_Filesize.SetWindowText("");
  m_Filetime.SetWindowText("");

  ClearPreview();
}
/*===========================================================================
 *		End of Class Method CObResourceView::ClearDisplayedInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void UpdateDisplayedInstance (void);
 *
 *=========================================================================*/
void CObResourceView::UpdateDisplayedInstance (void) {
  CString  Buffer;
  FILETIME FileTime;

  if (m_pCurrentInstance == NULL) {
    ClearDisplayedInstance();
    return;
  }

  m_Filename.SetWindowText(m_pCurrentInstance->GetFilename());

  if (!m_pCurrentInstance->HasFilesize()) {
   m_Filetime.SetWindowText("n/a");
  }
  else {
    Buffer.Format("%I64d bytes", m_pCurrentInstance->GetFilesize());
    m_Filesize.SetWindowText(Buffer);
  }

  if (!m_pCurrentInstance->HasFiletime()) {
    m_Filetime.SetWindowText("n/a");
  }
  else {
    FileTime.dwHighDateTime = (dword) (m_pCurrentInstance->GetFiletime() >> 32);
    FileTime.dwLowDateTime  = (dword) (m_pCurrentInstance->GetFiletime() & 0xffffffff);

    CTime TmpTime(FileTime);
    m_Filetime.SetWindowText(TmpTime.Format("%c"));
  }

  PreviewInstance(m_pCurrentInstance);
}
/*===========================================================================
 *		End of Class Method CObResourceView::UpdateDisplayedInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void ClearPreview (void);
 *
 *=========================================================================*/
void CObResourceView::ClearPreview (void) {
  m_PreviewText.ShowWindow(SW_HIDE);
  m_PreviewImage.ShowWindow(SW_HIDE);
}
/*===========================================================================
 *		End of Class Method CObResourceView::ClearPreview()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void PreviewText (pInstance, PreviewInfo);
 *
 *=========================================================================*/
void CObResourceView::PreviewText (CObResourceInstance* pInstance, obrespreviewinfo_t& PreviewInfo) {
  CObFile  File;
  CString  Buffer;
  long     Filesize;
  bool     Result;
  
  Result = File.Open(PreviewInfo.Filename, "rb");

  if (!Result) {
    Buffer.Format("Error trying to read the text file '%s'!", PreviewInfo.Filename);
    m_PreviewText.SetWindowText(Buffer); 
    m_PreviewText.ShowWindow(SW_SHOW);
    return;
  }

  if (PreviewInfo.Filesize > 256000) {
    Buffer.Format("File size of %I64d bytes too large to preview!", PreviewInfo.Filesize);
    m_PreviewText.SetWindowText(Buffer); 
    m_PreviewText.ShowWindow(SW_SHOW);
    return;
  }

	/* Jump to start of data */
  Result = File.Seek((long)PreviewInfo.StartOffset);

  if (!Result) {
    Buffer.Format("Error trying to read the text file '%s'!", PreviewInfo.Filename);
    m_PreviewText.SetWindowText(Buffer); 
    m_PreviewText.ShowWindow(SW_SHOW);
    return;
  }

  Filesize = (long) PreviewInfo.Filesize;
  Result   = File.Read(Buffer.GetBuffer(Filesize + 10), Filesize);
  Buffer.ReleaseBuffer(Filesize);
  File.Close();

  m_PreviewText.SetWindowText(Buffer);

  m_PreviewText.SetSel(0, 0);
  m_PreviewText.ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class Method CObResourceView::PreviewText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void PreviewImage (pInstance, PreviewInfo);
 *
 *=========================================================================*/
void CObResourceView::PreviewImage (CObResourceInstance* pInstance, obrespreviewinfo_t& PreviewInfo) {
  FILE* pFile;

  if (PreviewInfo.PlainFile) {
    m_PreviewImage.Load(PreviewInfo.Filename);
  }
  else {
    pFile = fopen(PreviewInfo.Filename, "rb");

    if (pFile != NULL) {
      m_PreviewImage.Load(pFile, (long)PreviewInfo.Filesize, (long)PreviewInfo.StartOffset);
      fclose(pFile);
    }
  }

  m_PreviewImage.ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class Method CObResourceView::PreviewImage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void PreviewUnknown (pInstance, PreviewInfo);
 *
 *=========================================================================*/
void CObResourceView::PreviewUnknown (CObResourceInstance* pInstance, obrespreviewinfo_t& PreviewInfo) {

  m_PreviewText.SetWindowText("Unknown file type!");

  m_PreviewText.ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class Method CObResourceView::PreviewUnknown()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void PreviewInstance (pInstance);
 *
 *=========================================================================*/
void CObResourceView::PreviewInstance (CObResourceInstance* pInstance) {
  obrespreviewinfo_t PreviewInfo;
  CSString           TmpFilename;
  bool	             Result;
  int		     Type;

  ClearPreview();
  if (pInstance == NULL || !m_EnablePreview) return;

  PreviewInfo.Filename    = pInstance->GetFullFilenameAbs();
  PreviewInfo.Filesize    = pInstance->GetFilesize();
  PreviewInfo.StartOffset = 0;
  PreviewInfo.pInstance   = pInstance;

	/* Use a temporary file for BSA resources */
	/* TODO: Reuse temporary output files */
	/* TODO: Read directly from BSA? */
  if (pInstance->GetBsaRecord() != NULL) {
    //TmpFilename = _tempnam("", "bsatmp");
    //Result = pInstance->GetBsaRecord()->SaveTempFile(TmpFilename, "tmpfiles\\");
    Result = pInstance->GetBsaRecord()->GetExistingTempFile(TmpFilename, "tmpfiles\\");
    if (!Result) return;
    //PreviewInfo.StartOffset = (int64)(uint64) pInstance->GetBsaRecord()->GetOffset();
    //PreviewInfo.Filename    = pInstance->GetBsaRecord()->GetParentFile()->GetFilename();
    PreviewInfo.Filename    = TmpFilename;
    PreviewInfo.StartOffset = 0;
    PreviewInfo.PlainFile   = true;
  }
  else {
	/* TODO: Update size from current file */
    PreviewInfo.Filesize  = pInstance->GetFilesize();
    PreviewInfo.PlainFile = true;
  }

  Type = pInstance->GetResourceType();

  switch (Type) {
    case OB_RESOURCETYPE_TEXT:
    case OB_RESOURCETYPE_HTML:
    case OB_RESOURCETYPE_XML:
        PreviewText(pInstance, PreviewInfo);
	break;
   case OB_RESOURCETYPE_IMAGE:
        PreviewImage(pInstance, PreviewInfo);
	break;
    default:
        PreviewUnknown(pInstance, PreviewInfo);
	break;
  }

}
/*===========================================================================
 *		End of Class Method CObResourceView::PreviewInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObResourceView::OnContextMenu (CWnd* pWnd, CPoint Point) {
	
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnBegindragResourceTree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObResourceView::OnBegindragResourceTree (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_TREEVIEW*     pNMTreeView = (NM_TREEVIEW *) pNMHDR;
  CObResourceBase* pBase;
  HTREEITEM        hSelItem;

  hSelItem = pNMTreeView->itemNew.hItem;
  if (hSelItem == NULL) return;

  m_ResourceTree.Select(hSelItem, TVGN_CARET);

  pBase = (CObResourceBase *) m_ResourceTree.GetItemData(hSelItem);
  if (pBase == NULL || pBase->IsFolder()) return;
  m_pDragResource = (CObResourceFile *) pBase;
  if (m_pDragResource == NULL) return;

  m_hGoodDropCursor = GetCursor();
  SetCursor(m_hBadDropCursor);

  m_pDragImage = m_ResourceTree.CreateDragImage(hSelItem);
  if (m_pDragImage == NULL) return;

  m_IsDragging    = true;
  m_LastDropValid = false;

  m_pDragImage->BeginDrag(0, CPoint(10, 10));
  m_pDragImage->DragEnter(GetDesktopWindow(), pNMTreeView->ptDrag);

  SetCapture();
	
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnBegindragResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - void CleanupDrag (void);
 *
 *=========================================================================*/
void CObResourceView::CleanupDrag (void) {

  if (!m_IsDragging) return;

  if (m_pDragImage != NULL) {
    delete m_pDragImage;
    m_pDragImage = NULL;
  }

  m_pDragResource = NULL;
  m_IsDragging    = false;
  m_LastDropValid = false;
}
/*===========================================================================
 *		End of Class Method CObResourceView::CleanupDrag()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnCaptureChanged (pWnd);
 *
 *=========================================================================*/
void CObResourceView::OnCaptureChanged(CWnd *pWnd) {
  CFormView::OnCaptureChanged(pWnd);

  CleanupDrag();

}
/*===========================================================================
 *		End of Class Event CObResourceView::OnCaptureChanged()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnLButtonUp (nFlags, Point);
 *
 *=========================================================================*/
void CObResourceView::OnLButtonUp (UINT nFlags, CPoint Point) {

  if (!m_IsDragging) {
    CFormView::OnLButtonUp(nFlags, Point);
    return;
  }  

  CPoint MousePt(Point);
  ClientToScreen(&MousePt);

  m_pDragImage->DragLeave(GetDesktopWindow());
  m_pDragImage->EndDrag();

	/* Drop the resource if required */
  if (m_LastDropValid) {
    SendDropNotify(MousePt, ID_OBRESOURCE_DROP);
  }

  ReleaseCapture();
  CleanupDrag();
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnLButtonUp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnMouseMove (nFlags, Point);
 *
 *=========================================================================*/
void CObResourceView::OnMouseMove (UINT nFlags, CPoint Point) {
  int    Result;

  if (!m_IsDragging) {
    CFormView::OnMouseMove(nFlags, Point);
    return;
  }

  CPoint MousePt(Point);
  ClientToScreen(&MousePt);

  m_pDragImage->DragMove(MousePt);
  m_pDragImage->DragShowNolock(false);

	/* Check the current drop window */
  Result = SendDropNotify(MousePt, ID_OBRESOURCE_CHECKDROP);

  if (Result == OBRESOURCE_DROPCHECK_OK) {
    m_LastDropValid = true;
    SetCursor(m_hGoodDropCursor);
  }
  else if (Result == OBRESOURCE_DROPCHECK_NOCHANGE) {
	/* do nothing */   
  }
  else {
    m_LastDropValid = false;
    SetCursor(m_hBadDropCursor);
  }

  m_pDragImage->DragShowNolock(true);
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnMouseMove()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - int SendDropNotify (Point, MessageID);
 *
 *=========================================================================*/
int CObResourceView::SendDropNotify (CPoint Point, const int MessageID) {
  obresourcedropinfo_t NotifyData;
  CWnd*	               pDropWnd;
  CWnd*		       pParentWnd = NULL;
  int		       Result = 0;

  	/* Get the CWnd pointer of the window that is under the given location */
  pDropWnd = WindowFromPoint(Point);
  if (pDropWnd == NULL) return (OBRESOURCE_DROPCHECK_ERROR);
  if (pDropWnd == this) return (OBRESOURCE_DROPCHECK_ERROR);

	/* Don't drag outside this application */
  dword Test1 = GetWindowThreadProcessId(m_hWnd, NULL);
  dword Test2 = GetWindowThreadProcessId(pDropWnd->m_hWnd, NULL);
  if (Test1 != Test2) return (OBRESOURCE_DROPCHECK_ERROR);
 
	/* Don't do anything if the window has not changed */
  if (m_pLastDropWnd == pDropWnd && MessageID != ID_OBRESOURCE_DROP) return (OBRESOURCE_DROPCHECK_NOCHANGE);

  m_pLastDropWnd = pDropWnd;
  if (pDropWnd == NULL) return (OBRESOURCE_DROPCHECK_ERROR);

	/* Send a notify message to the potential drop window */
  NotifyData.Notify.code     = MessageID;
  NotifyData.Notify.hwndFrom = pDropWnd->m_hWnd;
  NotifyData.Notify.idFrom   = pDropWnd->GetDlgCtrlID();
  NotifyData.pResourceFile   = m_pDragResource;

  pParentWnd = pDropWnd->GetParent();
  if (pParentWnd == NULL) return (OBRESOURCE_DROPCHECK_ERROR);

  Result = pParentWnd->SendMessage(WM_NOTIFY, NotifyData.Notify.idFrom, (LPARAM) &NotifyData);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObResourceView::SendDropNotify()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Method - bool SelectResource (pResource);
 *
 *=========================================================================*/
bool CObResourceView::SelectResource (const char* pResource) {
  CObResourceBase* pBase;
  HTREEITEM        hTree;

  if (m_pResourceHandler == NULL) return (false);
  
  pBase = m_pResourceHandler->FindName(pResource);
  if (pBase == NULL) return (false);

  hTree = (HTREEITEM) pBase->GetUserDataPtr();
  if (hTree == NULL) return (false);

  m_ResourceTree.Expand(hTree, TVE_EXPAND);
  m_ResourceTree.EnsureVisible(hTree);
  m_ResourceTree.SelectItem(hTree);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObResourceView::SelectResource()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceView Event - void OnHelp (void);
 *
 *=========================================================================*/
void CObResourceView::OnHelp (void) {
  CString Buffer;

	/* Ignore if web help is disabled */
  if (!CObEditDlgHandler::GetOptions().EnableWebHelp) return;
  
  Buffer  = CObEditDlgHandler::GetOptions().UESPWikiPrefix;
  Buffer += "Tes4Mod:User_Interface/Resource_Viewer";

  OpenWebPage(Buffer);
}
/*===========================================================================
 *		End of Class Event CObResourceView::OnHelp()
 *=========================================================================*/

