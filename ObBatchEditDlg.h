/*===========================================================================
 *
 * File:	Obbatcheditdlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 30, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBATCHEDITDLG_H
#define __OBBATCHEDITDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/obrecorddialog.h"
  #include "obbatchlistctrl.h"
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

  typedef CObPtrArray<obbatchfieldinfo_t> CObBatchFieldInfoArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBatchEditDlg Definition
 *
 *=========================================================================*/
class CObBatchEditDlg : public CObRecordDialog {
  DECLARE_DYNCREATE(CObBatchEditDlg);

  /*---------- Begin Protected Class Members -----------------------*/
protected:
  CObRefRecordArray		m_Records;

  int				m_CurrentEditItem;

  bool				m_Initialized;
  bool				m_IsChanging;
  
  CObBatchFieldInfoArray	m_Fields;
  dword				m_SavedFieldCount;


  /*---------- Begin Protected Class Methods -----------------------*/
protected:

	/* Creates the field array */
  void AddFields           (CObRecord* pRecord);
  void RemoveMissingFields (CObRecord* pRecord);
  void CreateFieldArray    (void);
  void FillFieldList       (void);

	/* Helper update methods */
  CObRecord* PrepareRecord (CObRecord* pRecord);
  bool       UpdateFields  (CObRecord* pRecord);

	/* Update the edit control */
  void UpdateEditCtrl (const int NewIndex);


  /*---------- Begin Public Class Methods --------------------------*/
public:

	/* Construction */
  CObBatchEditDlg(CWnd* pParent = NULL);

  	/* Set records to the edited */
  void AddEditRecords (CObRefRecordArray& Records);
  void AddEditRecords (CObRecordArray&    Records);

	/* Get class members */
  CObRefRecordArray& GetRecords    (void) { return (m_Records); }
  dword              GetNumRecords (void) { return (m_Records.GetSize()); }

	/* Check if the dialog is editing the given record */
  virtual bool IsEditRecord (CObRecord* pRecord);

	/* Set and get control data */
  virtual void  ClearControlData (void);
  virtual void  GetControlData   (void);
  virtual void  SetControlData   (void);
  virtual void  SetTitle         (const SSCHAR* pEditorID);
  virtual void  UpdateSaveFields (void);

	/* Events */
  virtual void OnApply  (void);
  virtual void OnSave	(void);
  virtual void OnCancel	(void);



  //{{AFX_DATA(CObBatchEditDlg)
  enum { IDD = IDD_BATCHEDIT_DLG };
  CObBatchListCtrl	m_FieldList;
  CEdit			m_EditCtrl;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObBatchEditDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObBatchEditDlg)
	afx_msg void OnItemchangedFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusBatchEdit(void);
	afx_msg void OnSetfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditCtrl (void);
	afx_msg void OnUncheckAll (void);
	afx_msg void OnCheckAll (void);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnEditUpdate (WPARAM mParam, LPARAM lParam);
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP()

};
/*===========================================================================
 *		End of Class CObBatchEditDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obbatcheditdlg.H
 *=========================================================================*/
