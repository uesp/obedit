/*===========================================================================
 *
 * File:	ObBatchlistctrl.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 30, 2006
 *
 * Implements the CObBatchListCtrl class
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "ObBatchListCtrl.h"


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
 * Begin CObBatchListCtrl Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObBatchListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CObBatchListCtrl)
	ON_NOTIFY_REFLECT(HDN_ITEMCLICK, OnItemclick)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//ON_NOTIFY_REFLECT(NM_RCLICK, OnClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObBatchListCtrl Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int CALLBACK s_DefaultBatchListSort (lParam1, lParam2, lParamSort);
 *
 * Default callback function for batch list sorting.
 *
 *=========================================================================*/
int CALLBACK s_DefaultBatchListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  obbatchfieldinfo_t* pInfo1 = (obbatchfieldinfo_t *) lParam1;
  obbatchfieldinfo_t* pInfo2 = (obbatchfieldinfo_t *) lParam2;
  obbatchlistsort_t*  pSort  = (obbatchlistsort_t  *) lParamSort;
  long		      Result;

  switch (pSort->iSubItem) {
    case OB_BATCHEDIT_SUBITEM_FIELD:
        Result = stricmp(pInfo1->Title, pInfo2->Title);
	break;
    case OB_BATCHEDIT_SUBITEM_VALUE:
        Result = stricmp(pInfo1->Value, pInfo2->Value);
	break;
    default:
	Result = 0;
	break;
  }
  
  if (pSort->Reverse) return (-Result);
  return (Result);
}
/*===========================================================================
 *		End of Function CALLBACK s_DefaultBatchListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Constructor
 *
 *=========================================================================*/
CObBatchListCtrl::CObBatchListCtrl() {
  m_SortSubItem = -1;
  m_SortReverse = 0;
}
/*===========================================================================
 *		End of Class CObBatchListCtrl Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Destructor
 *
 *=========================================================================*/
CObBatchListCtrl::~CObBatchListCtrl() {
}
/*===========================================================================
 *		End of Class CObBatchListCtrl Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnColumnclick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnColumnclick (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW*       pNMListView = (NM_LISTVIEW*)pNMHDR;
  obbatchlistsort_t  SortData;
  int	             SubItem;

  *pResult = 0;
  SubItem  = pNMListView->iSubItem;

  if (SubItem == m_SortSubItem) {
    m_SortReverse = !m_SortReverse;
  }
  else {
    m_SortReverse = false;
    m_SortSubItem = SubItem;
  }

  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);

  SortData.iSubItem = m_SortSubItem;
  SortData.Reverse  = m_SortReverse;
  SortItems(s_DefaultBatchListSort, (DWORD) &SortData);
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnColumnclick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnDblclk (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnDblclk (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnDblclk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnClick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnClick (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnClick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnLButtonDown (nFlags, Point);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnLButtonDown (UINT nFlags, CPoint Point) {
  LVHITTESTINFO HitTest;
  int		Result;

  CListCtrl::OnLButtonDown(nFlags, Point);

  HitTest.pt    = Point;
  HitTest.flags = 0;
  HitTest.iItem = -1;

  Result = SubItemHitTest(&HitTest);

  if (Result < 0) {
    GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);
    return;
  }
  
  SetItem(Result, 0, LVIF_STATE, "", 0, LVIS_SELECTED, LVIS_SELECTED, 0);
  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, Result, 0);
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnLButtonDown()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnItemclick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnItemclick (NMHDR* pNMHDR, LRESULT* pResult) {
  HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnItemclick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnSize (UINT nType, int cx, int cy) {
  CListCtrl::OnSize(nType, cx, cy);
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnVScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);

  CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnVScroll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBatchListCtrl Event - void OnHScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CObBatchListCtrl::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);

  CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}
/*===========================================================================
 *		End of Class Event CObBatchListCtrl::OnHScroll()
 *=========================================================================*/