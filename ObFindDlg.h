/*===========================================================================
 *
 * File:	Obfinddlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 1, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBFINDDLG_H
#define __OBFINDDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/obrecorddialog.h"
  #include "windows/obrecordvirtuallistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObFindDlg Definition
 *
 *=========================================================================*/
class CObFindDlg : public CObRecordDialog {
  DECLARE_DYNCREATE(CObFindDlg);

  /*---------- Begin Protected Class Members -------------------------*/
protected:
  CString	m_TextData;
  byte*		m_pBinaryData;
  dword		m_BinarySize;

  obfinddata_t	m_FindData;

  CObCallback	m_Callback;


  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Constructor */
  CObFindDlg(CWnd* pParent = NULL);
  virtual ~CObFindDlg();

  	/* Set and get control data */
  virtual void  ClearControlData (void);
  virtual void  GetControlData   (void);
  virtual void  SetControlData   (void);
  virtual void  SetTitle         (const SSCHAR* pEditorID);

  	/* Check if the dialog is editing the given record */
  virtual bool IsEditRecord (CObRecord* pRecord);

	/* Events */
  virtual void OnApply  (void);
  virtual void OnSave	(void);
  virtual void OnCancel	(void);

	/* Listener events */
  virtual int OnListenAddRecord       (CObListenEvent* pEvent);
  virtual int OnListenCleanRecord     (CObListenEvent* pEvent);
  virtual int OnListenUpdateRecord    (CObListenEvent* pEvent);
  virtual int GetListenEvents         (void)                   { return (OB_EVENT_ADDRECORD | OB_EVENT_CLEANRECORD | OB_EVENT_UPDATERECORD); }

	/* Conver the current text data to binary */
  bool ConvertBinaryData (void);

  //{{AFX_DATA(CObFindDlg)
  enum { IDD = IDD_FIND_DLG };
  CStatic	m_FindLabel;
  CButton	m_CaseSensitiveCheck;
  CButton			m_BinaryCheck;
  CComboBox			m_SearchCombo;
  CObRecordVirtualListCtrl	m_FindList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObFindDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObFindDlg)
  afx_msg void OnFindButton();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObFindDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obfinddlg.H
 *=========================================================================*/
