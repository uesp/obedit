/*===========================================================================
 *
 * File:	Errorbar.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 10, 2006
 *
 * Implements the dockable error control bar in the main frame.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "errorbar.h"


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
 * Begin CObErrorBar Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObErrorBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CObErrorBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObErrorBar Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorBar Constructor
 *
 *=========================================================================*/
CObErrorBar::CObErrorBar() {

  m_BoldFormat.cbSize    = sizeof(this);
  m_BoldFormat.dwMask    = CFM_BOLD;
  m_BoldFormat.dwEffects = CFE_BOLD;

}
/*===========================================================================
 *		End of Class CObErrorBar Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorBar Destructor
 *
 *=========================================================================*/
CObErrorBar::~CObErrorBar() {
}
/*===========================================================================
 *		End of Class CObErrorBar Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorBar Method - void AddText (pString);
 *
 * Add a line of text to the end of the error log.
 *
 *=========================================================================*/
void CObErrorBar::AddText (const TCHAR* pString) {
  int Length;

  if (pString == NULL) return;
  Length = m_wndChild.GetWindowTextLength();

  if (Length > 60000) {
    m_wndChild.SetSel(0, 10000);
    m_wndChild.ReplaceSel(_T(""), FALSE); 
    Length = m_wndChild.GetWindowTextLength();
  }

  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(pString, FALSE);

  Length = m_wndChild.GetWindowTextLength();
  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(_T("\r\n"), FALSE);

}
/*===========================================================================
 *		End of Class Method CObErrorBar::AddText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorBar Method - void AddBoldText (pString);
 *
 * Add a line of bolded text to the end of the error log.
 *
 *=========================================================================*/
void CObErrorBar::AddBoldText (const TCHAR* pString) {
  int Length;

  if (pString == NULL) return;
  Length = m_wndChild.GetWindowTextLength();

  if (Length > 60000) {
    m_wndChild.SetSel(0, 10000);
    m_wndChild.ReplaceSel(_T(""), FALSE); 
    Length = m_wndChild.GetWindowTextLength();
  }

  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(pString, FALSE);

  m_wndChild.SetSel(Length, Length + strlen(pString));
  m_wndChild.SetSelectionCharFormat(m_BoldFormat);

  Length = m_wndChild.GetWindowTextLength();
  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(_T("\r\n"), FALSE);
  m_wndChild.SetSel(Length, Length+2);
  m_wndChild.SetSelectionCharFormat(m_DefaultFormat);

}
/*===========================================================================
 *		End of Class Method CObErrorBar::AddBoldText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorBar Event - int OnCreate (lpCreateStruct);
 *
 *=========================================================================*/
int CObErrorBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1) return -1;
  SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

  if (!m_wndChild.Create(WS_CHILD|WS_VISIBLE|
			ES_MULTILINE|ES_WANTRETURN|ES_AUTOHSCROLL|ES_READONLY|WS_VSCROLL,
			CRect(0,0,0,0), this, 123)) {
    return -1;
  }

  m_wndChild.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

  if (!m_font.CreateStockObject(DEFAULT_GUI_FONT)) {
    if (!m_font.CreatePointFont(80, "MS Sans Serif")) {
      return -1;
    }
  }

  m_wndChild.SetBackgroundColor(FALSE, RGB(212,208,200));
  m_wndChild.GetDefaultCharFormat(m_DefaultFormat);
  m_wndChild.SetFont(&m_font);
  return 0;
}
/*===========================================================================
 *		End of Class Event CObErrorBar::OnCreate()
 *=========================================================================*/
