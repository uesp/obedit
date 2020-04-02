/*===========================================================================
 *
 * File:	ObFlorView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBFLORVIEW_H
#define __OBFLORVIEW_H


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
 * Begin Class CObFlorView Definition
 *
 *=========================================================================*/
class CObFlorView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObFlorView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObFlorView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObFlorView)
  enum { IDD = IDD_FLOR_VIEW };
  CEdit		m_Winter;
  CEdit		m_Fall;
  CEdit		m_Summer;
  CEdit		m_Spring;
  CEdit		m_Ingrediant;
  CEdit		m_Model;
  CEdit		m_Script;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CButton	m_QuestItem;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObFlorView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObFlorView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObFlorView)
  afx_msg void OnEditIngrediant();
  afx_msg void OnSelectingrediantButton();
  afx_msg void OnDropIngrediant (NMHDR* pNotifyStruct, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObFlorView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObFlorView.H
 *=========================================================================*/
