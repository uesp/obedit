/*===========================================================================
 *
 * File:	UndoBar.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 28, 2006
 *
 * Implements the dockable undo control bar in the main frame.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "undobar.h"
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
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObUndoBar Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObUndoBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CObUndoBar)
	ON_WM_CREATE()
	ON_LBN_DBLCLK(12345, OnDblclkUndoList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObUndoBar Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoBar Constructor
 *
 *=========================================================================*/
CObUndoBar::CObUndoBar() {

  m_pLastUndoArray = NULL;

}
/*===========================================================================
 *		End of Class CObUndoBar Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoBar Destructor
 *
 *=========================================================================*/
CObUndoBar::~CObUndoBar() {
}
/*===========================================================================
 *		End of Class CObUndoBar Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoBar Event - int OnCreate (lpCreateStruct);
 *
 *=========================================================================*/
int CObUndoBar::OnCreate (LPCREATESTRUCT lpCreateStruct) {
  if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1) return -1;
  SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

  if (!m_wndChild.Create(WS_CHILD|WS_VISIBLE| LBS_HASSTRINGS | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
			CRect(0,0,0,0), this, 12345)) {
    return -1;
  }

  m_wndChild.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

  if (!m_font.CreateStockObject(DEFAULT_GUI_FONT)) {
    if (!m_font.CreatePointFont(80, "MS Sans Serif")) {
      return -1;
    }
  }

  m_wndChild.SetFont(&m_font);
  return 0;
}
/*===========================================================================
 *		End of Class Event CObUndoBar::OnCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoBar Method - void UpdateList (pUndoItems);
 *
 *=========================================================================*/
void CObUndoBar::UpdateList (CObUndoItemArray* pUndoItems) {
  CObUndoItem* pItem;
  CSString     Buffer;
  int          Index;
  int          ListIndex;

  m_pLastUndoArray = pUndoItems;

	/* Clear the current content */
  m_wndChild.ResetContent();
  if (pUndoItems == NULL) return;

  for (Index = (int)pUndoItems->GetSize() - 1; Index >= 0; --Index) {
    pItem = pUndoItems->GetAt(Index);

    ListIndex = m_wndChild.AddString(pItem->MakeString(Buffer));
    if (ListIndex >= 0) m_wndChild.SetItemData(ListIndex, (DWORD) pItem);
  }

  //int ID = m_wndChild.GetDlgCtrlID();
}
/*===========================================================================
 *		End of Class Method CObUndoBar::UpdateList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoBar Method - CObUndoItem* GetCurrentUndoItem (void);
 *
 *=========================================================================*/
CObUndoItem* CObUndoBar::GetCurrentUndoItem (void) {
  CObUndoItem* pItem;
  int          ListIndex;

  ListIndex = m_wndChild.GetCurSel();
  if (ListIndex < 0) return (NULL);

  pItem = (CObUndoItem *) m_wndChild.GetItemData(ListIndex);
  return (pItem);
}
/*===========================================================================
 *		End of Class Method CObUndoBar::GetCurrentUndoItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoBar Method - void LockUpdates (Lock);
 *
 *=========================================================================*/
void CObUndoBar::LockUpdates (const bool Lock) {

  if (Lock) {
    m_wndChild.SetRedraw(FALSE);
  }
  else {
    m_wndChild.SetRedraw(TRUE);
    m_wndChild.RedrawWindow();
  }

}
/*===========================================================================
 *		End of Class Method CObUndoBar::LockUpdates()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoBar Event - void OnDblclkUndoList (void);
 *
 *=========================================================================*/
void CObUndoBar::OnDblclkUndoList (void) {
  AfxGetMainWnd()->SendMessage(OBE_MSG_UNDOITEMS, 0, 0);
}
/*===========================================================================
 *		End of Class Event CObUndoBar::OnDblclkUndoList()
 *=========================================================================*/
