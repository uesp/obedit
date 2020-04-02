/*===========================================================================
 *
 * File:	ObSlgmView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 11, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSLGMVIEW_H
#define __OBSLGMVIEW_H


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
 * Begin Class CObSlgmView Definition
 *
 *=========================================================================*/
class CObSlgmView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObSlgmView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObSlgmView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObSlgmView)
	enum { IDD = IDD_SLGM_VIEW };
	CComboBox	m_Soul;
	CComboBox	m_Capacity;
  CEdit		m_Icon;
  CEdit		m_Model;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Script;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CButton	m_QuestItem;
	//}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObSlgmView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObSlgmView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObSlgmView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObSlgmView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObSlgmView.H
 *=========================================================================*/
