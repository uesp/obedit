/*===========================================================================
 *
 * File:	ChildFrm.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Definition of the CChildFrame class.
 *
 *=========================================================================*/
#ifndef __ChildFrm_H
#define __ChildFrm_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/
  

/*===========================================================================
 *
 * Class CChildFrame Definition
 *
 *=========================================================================*/
class CChildFrame : public CMDIChildWnd {
  DECLARE_DYNCREATE(CChildFrame)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  bool		m_IsFakeMaximized;
  CRect		m_RestoreRect;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class constructor/destructor */
  CChildFrame();
  virtual ~CChildFrame();

  void FakeMaximize (void);

	/* Diagnostics routines */
#ifdef _DEBUG
  virtual void AssertValid () const;
  virtual void Dump (CDumpContext& dc) const;
#endif


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CChildFrame)
public:
  virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  //}}AFX_VIRTUAL


  /*---------- Generated message map functions ------------------*/
protected:
  //{{AFX_MSG(CChildFrame)
  afx_msg void OnSize (UINT nType, int cx, int cy);
  afx_msg void OnWindowPosChanging (WINDOWPOS* pPos);
  afx_msg void OnSysCommand (UINT nID, LPARAM Param);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

};
/*===========================================================================
 *		End of Class CObEditView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ChildFrm.H
 *=========================================================================*/
