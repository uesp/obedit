/*===========================================================================
 *
 * File:	ObKeymView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBKEYMVIEW_H
#define __OBKEYMVIEW_H


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
 * Begin Class CObKeymView Definition
 *
 *=========================================================================*/
class CObKeymView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObKeymView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObKeymView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObKeymView)
  enum { IDD = IDD_KEYM_VIEW };
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
  //{{AFX_VIRTUAL(CObKeymView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObKeymView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObKeymView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObKeymView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obarmorview.H
 *=========================================================================*/
