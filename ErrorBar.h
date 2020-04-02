/*===========================================================================
 *
 * File:	Errorbar.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ERRORBAR_H
#define __ERRORBAR_H


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
 * Begin Class CObErrorBar Definition
 *
 *=========================================================================*/
class CObErrorBar : public CSizingControlBarCF {

  /*---------- Protected Class Members -----------------------*/
protected:
  CRichEditCtrl m_wndChild;
  CFont		m_font;
  CHARFORMAT	m_BoldFormat;
  CHARFORMAT	m_DefaultFormat;


  /*---------- Public Class Members --------------------------*/
public:

	/* Constructor/Destructor */
  CObErrorBar();
 virtual ~CObErrorBar();

	/* Add a line of text to the end of the error bar */
  void AddText     (const TCHAR* pString);
  void AddBoldText (const TCHAR* pString);


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObErrorBar)
  //}}AFX_VIRTUAL


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CObErrorBar)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObErrorBar Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Errorbar.H
 *=========================================================================*/
