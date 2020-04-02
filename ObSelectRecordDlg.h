/*===========================================================================
 *
 * File:	Obselectrecorddlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 26, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSELECTRECORDDLG_H
#define __OBSELECTRECORDDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obespfile.h"
  #include "windows/obrecordlistctrl.h"
  #include "modfile/obmultirecordhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Optional callback function type */
  typedef bool (*OBRECSELDLGCALLBACK) (CObRecord* pRecord, long UserData);

	/* Used to define a selection record dialog */
  struct obselrecdlginfo_t {
	const obrectype_t*	pRecordType;		/* Type of record to display */
	const obrectype_t**	ppRecordArray;
	const TCHAR*		pTitle;

	obreclistcolinit_t*	pListColumns;
	const obrecfieldmap_t*  pFieldMap;

	obrecfieldid_t		SortField;

	OBRECSELDLGCALLBACK	pCheckFunc;
	long			UserData;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSelectRecordDlg Definition
 *
 *=========================================================================*/
class CObSelectRecordDlg : public CDialog {

  /*---------- Begin Protected Class Members ---------------------------*/
protected:
  obselrecdlginfo_t	m_DlgInfo;

  obformid_t		m_InitialFormID;
  CString		m_InitialEditorID;
  obformid_t		m_CurrentFormID;
  CString		m_CurrentEditorID;

  CObRecord*		m_pPrevRecord;
  CObRecord*		m_pCurrentRecord;

  bool			m_AllowNullRecord;		/* Allow a null record to be selected */
  bool			m_IsInitialized;

  CObRecordHandler*	m_pRecordHandler;

  int			m_EditorIDCheck;
  bool			m_UpdateListOnChange;


  /*---------- Begin Protected Class Methods ---------------------------*/
protected:

	/* Get/set control data */
  void GetControlData      (void);
  void SetControlData      (void);
  void FillRecordList      (void);
  void FillRecordList      (const obrectype_t RecordType);
  void AddListColumns      (void);
  void UpdateCurrentRecord (void);
  int  UpdateEditorID      (void);


  /*---------- Begin Public Class Methods ------------------------------*/
public:
	/* Construction */
  CObSelectRecordDlg(CWnd* pParent = NULL);

	/* Get class members */
  CObRecord*   GetCurrentRecord   (void) { return (m_pCurrentRecord); }
  CObRecord*   GetPrevRecord      (void) { return (m_pPrevRecord); }
  obformid_t   GetCurrentFormID   (void) { return (m_CurrentFormID); }
  const TCHAR* GetCurrentEditorID (void) { return (m_CurrentEditorID); }
  
	/* Set class members */
  void SetInitialFormID   (const obformid_t   FormID)   { m_InitialFormID   = FormID; }
  void SetInitialEditorID (const TCHAR*      pString)   { m_InitialEditorID = pString; }
  void SetPrevRecord      (CObRecord*         pRecord)  { m_pPrevRecord     = pRecord; }
  void SetCurrentRecord   (CObRecord*         pRecord)  { m_pCurrentRecord  = pRecord; }
  void SetRecordHandler   (CObRecordHandler*  pHandler) { m_pRecordHandler  = pHandler; }
  void SetDlgInfo         (obselrecdlginfo_t& DlgInfo)  { m_DlgInfo         = DlgInfo; }
  void SetAllowNull       (const bool         Value)    { m_AllowNullRecord = Value; }


  //{{AFX_DATA(CObSelectRecordDlg)
  enum { IDD = IDD_SELECTRECORD_DLG };
  CEdit			m_CurrentFormIDText;
  CEdit			m_PreviousFormIDText;
  CButton		m_ClearButton;
  CEdit			m_CurrentText;
  CEdit			m_PreviousText;
  CObRecordListCtrl	m_RecordList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObSelectRecordDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObSelectRecordDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnClearButton();
  virtual void OnOK();
  afx_msg void OnItemchangedRecordlist(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnEditRecord (WPARAM lParam, LPARAM wParam);
  afx_msg void OnChangeCurrentText();
  afx_msg HBRUSH OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObSelectRecordDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  bool ObSelectItemScript     (CString& EditorID, CObRecordHandler* pRecordHandler);
  bool ObSelectActor          (CString& EditorID, CObRecordHandler* pRecordHandler);
  bool ObSelectApparelEnchant (CString& EditorID, CObRecordHandler* pRecordHandler);
  bool ObSelectIngrediant     (CString& EditorID, CObRecordHandler* pRecordHandler);
  bool ObSelectScrollEnchant  (CString& EditorID, CObRecordHandler* pRecordHandler);
  bool ObSelectSound          (CString& EditorID, CObRecordHandler* pRecordHandler);
  bool ObSelectStaffEnchant   (CString& EditorID, CObRecordHandler* pRecordHandler);
  bool ObSelectWeaponEnchant  (CString& EditorID, CObRecordHandler* pRecordHandler);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obselectrecorddlg.H
 *=========================================================================*/
