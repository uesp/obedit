/*===========================================================================
 *
 * File:	Obfiletreedlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 4, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObFileTreeDlg.h"


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
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObFileTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CObFileTreeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Constructor
 *
 *=========================================================================*/
CObFileTreeDlg::CObFileTreeDlg(CWnd* pParent) : CDialog(CObFileTreeDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CObFileTreeDlg)
	//}}AFX_DATA_INIT

  //m_pEspFile = NULL;
  m_pTopGroup = NULL;
}
/*===========================================================================
 *		End of Class CObFileTreeDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void CreateTree (void);
 *
 *=========================================================================*/
void CObFileTreeDlg::CreateTree (void) {

	/* Clear the current contents */  
  m_FileTree.DeleteAllItems();
  if (m_pTopGroup == NULL) return;

  CreateTree(m_pTopGroup, m_FileTree.GetRootItem());
}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::CreateTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void CreateTree (pTopGroup, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::CreateTree (CObGroup* pTopGroup, HTREEITEM hParent) {
  CObBaseRecord* pBaseRecord;
  dword          Index;
  HTREEITEM      hFile;

	/* Add the file node */
  hFile = m_FileTree.InsertItem("Filename TODO", hParent);
    
	/* Add the file contents */
  for (Index = 0; Index < pTopGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pTopGroup->GetRecord(Index);
    if (pBaseRecord == NULL) continue;
    
    AddTreeRecord(pBaseRecord, hFile);
  }

}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::CreateTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void AddTreeRecord (pBaseRecord, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::AddTreeRecord (CObBaseRecord* pBaseRecord, HTREEITEM hParent) {
  CObGroup*       pGroup;
  CObTypeGroup*   pTypeGroup;
  CObGridGroup*   pGridGroup;
  CObBlockGroup*  pBlockGroup;
  CObFormIDGroup* pFormIDGroup;
  int test = pBaseRecord->GetMyClassType();
  
	/* Determine the type of the record */
  switch (pBaseRecord->GetMyClassType()) {
     case OBCLASS_CObGroup:
        pGroup = ObCastClass(CObGroup, pBaseRecord);
	AddTreeGroup(pGroup, hParent);
	break;
     case OBCLASS_CObTypeGroup:
        pTypeGroup = ObCastClass(CObTypeGroup, pBaseRecord);
	AddTreeTypeGroup(pTypeGroup, hParent);
	break;
     case OBCLASS_CObFormIDGroup:
        pFormIDGroup = ObCastClass(CObFormIDGroup, pBaseRecord);
	AddTreeFormIDGroup(pFormIDGroup, hParent);
	break;
     case OBCLASS_CObBlockGroup:
        pBlockGroup = ObCastClass(CObBlockGroup, pBaseRecord);
	AddTreeBlockGroup(pBlockGroup, hParent);
	break;
     case OBCLASS_CObGridGroup:
        pGridGroup = ObCastClass(CObGridGroup, pBaseRecord);
	AddTreeGridGroup(pGridGroup, hParent);
	break;
     case OBCLASS_CObBaseRecord:
     case OBCLASS_CObRecord:
     default:
	break;
  }

}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::AddTreeRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void AddTreeGroupChildren (pGroup, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::AddTreeGroupChildren (CObGroup* pGroup, HTREEITEM hParent) {
  CObBaseRecord* pBaseRecord;
  dword          Index;
   
	/* Add the group contents */
  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    if (pBaseRecord == NULL) continue;
    
    AddTreeRecord(pBaseRecord, hParent);
  }

}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::AddTreeGroupChildren()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void AddTreeGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::AddTreeGroup (CObGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  Buffer.Format(_T("General Group -- %u records"), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::AddTreeGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void AddTreeTypeGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::AddTreeTypeGroup (CObTypeGroup* pGroup, HTREEITEM hParent) {
  CString Buffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  Buffer.Format(_T("Type Group (%4.4s)-- %u records"), pGroup->GetContainsType().Name, pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::AddTreeTypeGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void AddTreeFormIDGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::AddTreeFormIDGroup (CObFormIDGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  CString   TypeBuffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  switch (pGroup->GetType()) {
    case OB_GROUP_WORLDCHILD: TypeBuffer = "World Child"; break;
    case OB_GROUP_CELLCHILD: TypeBuffer = "Cell Child"; break;
    case OB_GROUP_TOPICCHILD: TypeBuffer = "Topic Child"; break;
    case OB_GROUP_CELLPERSIST: TypeBuffer = "Cell Persist"; break;
    case OB_GROUP_CELLTEMP: TypeBuffer = "Cell Temp"; break;
    case OB_GROUP_CELLDISTANT: TypeBuffer = "Cell Distance"; break;
    default: TypeBuffer = "Unknown"; break;
  }
  
  Buffer.Format(_T("%s Group (0x%08X) -- %u records"), TypeBuffer, pGroup->GetParentFormID(), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::AddTreeFormIDGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void AddTreeBlockGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::AddTreeBlockGroup (CObBlockGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  CString   TypeBuffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  switch (pGroup->GetType()) {
    case OB_GROUP_INTCELL: TypeBuffer = "Interior Cell"; break;
    case OB_GROUP_INTSUBCELL: TypeBuffer = "Interior Sub-Cell"; break;
    default: TypeBuffer = "Unknown"; break;
  }

  Buffer.Format(_T("%s Group (%d) -- %u records"), TypeBuffer, pGroup->GetBlock(), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::AddTreeBlockGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void AddTreeGridGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CObFileTreeDlg::AddTreeGridGroup (CObGridGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  CString   TypeBuffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  switch (pGroup->GetType()) {
    case OB_GROUP_EXTCELL: TypeBuffer = "Exterior Cell"; break;
    case OB_GROUP_EXTSUBCELL: TypeBuffer = "Exterior Sub-Cell"; break;
    default: TypeBuffer = "Unknown"; break;
  }

  Buffer.Format(_T("%s Group (%d, %d) -- %u records"), TypeBuffer, pGroup->GetGridX(), pGroup->GetGridY(), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::AddTreeGridGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObFileTreeDlg::DoDataExchange (CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CObFileTreeDlg)
  DDX_Control(pDX, IDC_TREECTRL, m_FileTree);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObFileTreeDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFileTreeDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObFileTreeDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  CreateTree();
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObFileTreeDlg::OnInitDialog()
 *=========================================================================*/
