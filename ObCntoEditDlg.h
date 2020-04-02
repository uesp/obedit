/*===========================================================================
 *
 * File:	ObCntoEditDlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCNTOEDITDLG_H
#define __OBCNTOEDITDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "windows/obrecordvirtuallistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Return results */
  #define OB_CNTOEDITDLG_RESULT_OK	IDOK
  #define OB_CNTOEDITDLG_RESULT_CANCEL	IDCANCEL
  #define OB_CNTOEDITDLG_RESULT_DELETE	201

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObCntoEditDlg Definition
 *
 *=========================================================================*/
class CObCntoEditDlg : public CDialog {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CObCntoSubrecord*	m_pSubrecord;	/* Item being edited */
  CString		m_TitleValue;
  
  CObRecordHandler*	m_pRecordHandler;

  const obrectype_t*	m_pRecordTypes;

  bool			m_UpdateListOnChange;

  int			m_EditorIDCheck;
  obformid_t		m_ObjectFormID;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:

	/* Helper initialize methods */
  void AddListColumns (void);
  void FillRecordList (void);
  void FillRecordList (const obrectype_t RecordType);
  int  UpdateEditorID (void);
  

  /*---------- Begin Public Class Methods -----------------------------*/
public:

	/* Constructor */
  CObCntoEditDlg(CWnd* pParent = NULL);

	/* Get class members */
  CObCntoSubrecord* GetSubrecord (void) { return (m_pSubrecord); }

	/* Set class members */
  void SetSubrecord       (CObCntoSubrecord* pSubrecord) { m_pSubrecord      = pSubrecord; }
  void SetTitleValue      (const TCHAR*         pString) { m_TitleValue      = pString; }
  void SetRecordHandler   (CObRecordHandler*   pHandler) { m_pRecordHandler  = pHandler; }
  void SetRecordTypes     ( const obrectype_t*   pTypes) { m_pRecordTypes    = pTypes; }

	/* Set/get control data */
  void GetControlData (void);
  void SetControlData (void);
  

  //{{AFX_DATA(CObCntoEditDlg)
  enum { IDD = IDD_CNTOEDIT_DLG };
  CEdit				m_FormID;
  CEdit				m_Count;
  CEdit				m_ObjectID;
  CObRecordVirtualListCtrl	m_RecordList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObCntoEditDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObCntoEditDlg)
  afx_msg void OnDeleteButton();
  virtual BOOL OnInitDialog();
  afx_msg void OnChangeEditorid();
  afx_msg void OnKillfocusEditorid();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnItemchangedRecordlist(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObCntoEditDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  int ObEditContainerItemDlg (CObCntoSubrecord* pSubrecord, CObRecordHandler* pHandler);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObCntoEditDlg.H
 *=========================================================================*/
