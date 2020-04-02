/*===========================================================================
 *
 * File:	ObBookview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obbookview.h"
#include "dialogs/obeditdlghandler.h"


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

  IMPLEMENT_DYNCREATE(CObBookView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBookView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObBookView, CObRecordDialog)
	//{{AFX_MSG_MAP(CObBookView)
	ON_BN_CLICKED(IDC_SCROLL, OnScroll)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObBookView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObBookView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		12,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		12,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTPOINTS, IDC_ENCHANTCHARGE,	8,	IDS_TT_ENCHANTPOINTS)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_ENCHANTMENT,   IDC_ENCHANTMENT,	128,	IDS_TT_ENCHANTMENT)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_INVENTORYICON,	256,	IDS_TT_ICON)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_SCROLL,        IDC_SCROLL,          0,	IDS_TT_SCROLL)
	ADD_OBRECUIFIELDS( OB_FIELD_NOTAKE,        IDC_CANTBETAKEN,	0,	IDS_TT_NOTAKE)
	ADD_OBRECUIFIELDS( OB_FIELD_TEACHES,       IDC_TEACHES_LIST,    0,	IDS_TT_TEACHES)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Constructor
 *
 *=========================================================================*/
CObBookView::CObBookView() : CObRecordDialog(CObBookView::IDD) {
  //{{AFX_DATA_INIT(CObBookView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = OB_ENCHTYPE_SCROLL;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObBookView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Destructor
 *
 *=========================================================================*/
CObBookView::~CObBookView() {

}
/*===========================================================================
 *		End of Class CObBookView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObBookView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObBookView)
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_SELECTENCHANT_BUTTON, m_SelectEnchantButton);
	DDX_Control(pDX, IDC_EDIT_ENCHANTMENT, m_EditEnchantButton);
	DDX_Control(pDX, IDC_ENCHANTMENT, m_Enchantment);
	DDX_Control(pDX, IDC_BOOKTEXT, m_BookText);
	DDX_Control(pDX, IDC_CANTBETAKEN, m_CantBeTaken);
	DDX_Control(pDX, IDC_SCROLL, m_Scroll);
	DDX_Control(pDX, IDC_TEACHES_LIST, m_Teaches);
	DDX_Control(pDX, IDC_ENCHANTCHARGE, m_EnchantCharges);
	DDX_Control(pDX, IDC_INVENTORYICON, m_Icon);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObBookView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObBookView::GetControlData (void) {
  CObBookRecord* pBook;
  CString	 Buffer;
  
  CObRecordDialog::GetControlData();

  pBook = ObCastClass(CObBookRecord, m_EditInfo.pNewRecord);

  if (pBook != NULL) { 
    m_BookText.GetWindowText(Buffer);
    pBook->SetBookText(Buffer);
  }

}
/*===========================================================================
 *		End of Class Method CObBookView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBookView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObBookView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObBookView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObBookView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObBookView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  ObAddComboBoxItem(m_Teaches, "None", -1);
  ObFillComboList(m_Teaches, s_ObActorValueSkills, 0);

  m_BookText.SendMessage(EM_SETUNDOLIMIT, 50, 0);
  m_BookText.SendMessage(EM_SETWORDWRAPMODE, WBF_LEVEL1, 0);
  m_BookText.SetOptions(ECOOP_OR, ECO_SAVESEL);
  m_BookText.LimitText(65535);
  m_BookText.SetTargetDevice(NULL, 0);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObBookView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObBookView::SetControlData (void) {
  CObBookRecord* pBook;

  CObRecordDialog::SetControlData();

  pBook = ObCastClass(CObBookRecord, m_EditInfo.pOldRecord);
  if (pBook != NULL) m_BookText.SetWindowText(pBook->GetBookText());

  OnScroll();
}
/*===========================================================================
 *		End of Class Method CObBookView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Event - void OnScroll ();
 *
 *=========================================================================*/
void CObBookView::OnScroll() {
  bool Enable = m_Scroll.GetCheck() != 0;

  m_SelectEnchantButton.EnableWindow(Enable);
  m_EditEnchantButton.EnableWindow(Enable);
}
/*===========================================================================
 *		End of Class Event CObBookView::OnScroll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CObBookView::OnContextMenu(CWnd* pWnd, CPoint Point) {
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_BOOKTEXT) {
    Result = Menu.LoadMenu(IDR_BOOK_MENU);
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
