/*===========================================================================
 *
 * File:	UndoBar.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 28, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __UNDOBAR_H
#define __UNDOBAR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obundoitem.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObUndoBar Definition
 *
 *=========================================================================*/
class CObUndoBar : public CSizingControlBarCF {

  /*---------- Protected Class Members -----------------------*/
protected:
  CListBox		m_wndChild;
  CFont			m_font;

  CObUndoItemArray*	m_pLastUndoArray;
  

  /*---------- Public Class Members --------------------------*/
public:

	/* Constructor/Destructor */
  CObUndoBar();
  virtual ~CObUndoBar();

	/* Access the currently selected item */
  CObUndoItem* GetCurrentUndoItem (void);

	/* Prevent updates from being displayed immediately */
  void LockUpdates (const bool Lock);

	/* Update the list from an array of undo items */
  void UpdateList (CObUndoItemArray* pUndoItems);


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObUndoBar)
  //}}AFX_VIRTUAL


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CObUndoBar)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDblclkUndoList (void);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObUndoBar Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File UndoBar.H
 *=========================================================================*/
