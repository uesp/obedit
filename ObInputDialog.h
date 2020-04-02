/*===========================================================================
 *
 * File:	Obinputdialog.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 30, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBINPUTDIALOG_H
#define __OBINPUTDIALOG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "common/oberrorhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Function used to determine if an input string is valid or not */
  typedef int (*INPUTDLGCHECKFUNC) ( const char* pString, const char* pOrigString, long UserData );

	/* Check validation codes */
  #define OB_INPUTDLG_CHECK_OK		 0
  #define OB_INPUTDLG_CHECK_NOCHANGE	 1
  #define OB_INPUTDLG_CHECK_ERROR	-1

	/* Validation colors */
  #define OB_INPUTDLG_NOCHANGECOLOR RGB(255,255,255)
  #define OB_INPUTDLG_OKCOLOR       RGB(204,255,204)
  #define OB_INPUTDLG_ERRORCOLOR    RGB(255,204,204)

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObInputDialog Definition
 *
 *=========================================================================*/
class CObInputDialog : public CDialog {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CString		m_LabelValue;
  CString		m_TextValue;
  CString		m_OrigTextValue;
  CString		m_TitleValue;
  INPUTDLGCHECKFUNC	m_CheckFunction;

  long			m_CheckUserData;
  int			m_CheckCode;

  ISCHARFUNC		m_ValidCharFunc;


  /*---------- Begin Public Class Methods -----------------------------*/
public:

	/* Constructor */
  CObInputDialog(CWnd* pParent = NULL);

	/* Get class members */
  const TCHAR* GetTextValue (void) { return m_TextValue; }

	/* Set class members */
  void SetTitleValue (const TCHAR* pString) { m_TitleValue = pString; }
  void SetTextValue  (const TCHAR* pString) { m_TextValue  = pString; }
  void SetLabelValue (const TCHAR* pString) { m_LabelValue = pString; }

  void SetCheckFunction (INPUTDLGCHECKFUNC Function, const long UserData) { m_CheckFunction = Function; m_CheckUserData = UserData; }
  void SetValidCharFunc (ISCHARFUNC        Function) { m_ValidCharFunc = Function; }

  //{{AFX_DATA(CObInputDialog)
  enum { IDD = IDD_INPUT_DLG };
  CStatic	m_Label;
  CEdit		m_InputText;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObInputDialog)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObInputDialog)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnChangeInputText (void);
  afx_msg HBRUSH OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObInputDialog Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* Main input dialog access */
  bool ObInputDialog         (CString& Buffer, const TCHAR* pTitle, const TCHAR* pLabel);
  bool ObInputDialogValidate (CString& Buffer, const TCHAR* pTitle, const TCHAR* pLabel, INPUTDLGCHECKFUNC FheckFunc, const long UserData, ISCHARFUNC ValidFunc);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/



//{{AFX_INSERT_LOCATION}}
//}}AFF_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obinputdialog.H
 *=========================================================================*/
