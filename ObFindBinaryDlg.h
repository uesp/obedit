/*===========================================================================
 *
 * File:	Obfindbinarydlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 29, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBFINDBINARYDLG_H
#define __OBFINDBINARYDLG_H


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
 * Begin Class CObFindBinaryDlg Definition
 *
 *=========================================================================*/
class CObFindBinaryDlg : public CDialog {

  /*---------- Begin Protected Class Members -----------------------------*/
protected:
  CString	m_BinaryData;


  /*---------- Public Class Methods --------------------------------------*/
public:

	/* Constructor */
  CObFindBinaryDlg(CWnd* pParent = NULL);

	/* Get class members */
  const TCHAR* GetBinaryData (void) { return (m_BinaryData); }

	/* Dialog Data */
  //{{AFX_DATA(CObFindBinaryDlg)
  enum { IDD = IDD_FINDBINARY_DLG };
  CEdit		m_BinaryDataText;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObFindBinaryDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObFindBinaryDlg)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObFindBinaryDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obfindbinarydlg.H
 *=========================================================================*/
