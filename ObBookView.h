/*===========================================================================
 *
 * File:	ObBookView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBOOKVIEW_H
#define __OBBOOKVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/obrecorddialog.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBookView Definition
 *
 *=========================================================================*/
class CObBookView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObBookView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObBookView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:

  virtual void GetControlData (void);
  virtual void SetControlData (void);


  //{{AFX_DATA(CObBookView)
	enum { IDD = IDD_BOOK_VIEW };
	CButton	m_QuestItem;
  CButton	m_SelectEnchantButton;
  CButton	m_EditEnchantButton;
  CEdit		m_Enchantment;
  CRichEditCtrl	m_BookText;
  CButton	m_CantBeTaken;
  CButton	m_Scroll;
  CComboBox	m_Teaches;
  CEdit		m_EnchantCharges;
  CEdit		m_Icon;
  CEdit		m_Model;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Script;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
	//}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObBookView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObBookView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObBookView)
  afx_msg void OnScroll();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObBookView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObBookView.H
 *=========================================================================*/
