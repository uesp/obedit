/*===========================================================================
 *
 * File:	obeditView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Interface of the CObEditView class.
 *
 *=========================================================================*/
#ifndef __OBEDITVIEW_H
#define __OBEDITVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "windows/obrecordlistctrl.h"
  #include "windows/obrecordvirtuallistctrl.h"
  #include "windows/obrecordtreectrl.h"
  #include "modfile/obexport.h"
  #include "dialogs/obeditdlghandler.h"
  #include "obresourceview.h"
  #include "il/il.h"
  #include "il/ilu.h"
  #include "il/ilut.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* File filters for the open/save dialog */
  #define OBEDIT_CSV_FILTER _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||")

	/* Default file extensions */
  #define OBEDIT_CSV_EXT _T("csv")

	/* Number of operations required for a progress dlg to be shown */
  #define OBEDIT_MINIMUM_PROGRESS_COUNT 100

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEditView Definition
 *
 *=========================================================================*/
class CObEditView : public CFormView, public IObListener {

  /*---------- Begin Protected Class Members ----------------------*/
protected:
  CObEditDlgHandler	m_DlgHandler;		/* Handles all child windows */

  bool			m_IsInitialized;	/* Has the view been initialized yet? */

  CObRecordFilter*	m_pCurrentFilter;	/* Currently displayed record filter */
  CSString		m_LastFilterID; 


  /*---------- Begin Protected Class Methods ----------------------*/
protected: 

	/* Create from serialization only */
  CObEditView();
  DECLARE_DYNCREATE(CObEditView)


public:
  //{{AFX_DATA(CObEditView)
  enum { IDD = IDD_OBEDIT_FORM };
  CStatic			m_VertEdge;
  CObRecordVirtualListCtrl	m_RecordList;
  CObRecordTreeCtrl		m_RecordTree;
  //}}AFX_DATA


  /*---------- Begin Public Class Methods --------------------------*/
public:

	/* Class destructor */
  virtual ~CObEditView();

	/* Get the parent document */
  CObEditDoc*        GetDocument();
  CObEditDlgHandler& GetDlgHandler (void) { return m_DlgHandler; }

	/* Helper export methods */
  bool OnCsvExport (obexportinfo_t& ExportInfo, const TCHAR* pDialogTitle);

	/* Update events */
  void OnEditRecord (CObRecord* pRecord);

	/* Listener events */
  virtual int OnListenAddRecord       (CObListenEvent* pEvent);
  virtual int OnListenCleanRecord     (CObListenEvent* pEvent);
  virtual int OnListenUpdateRecord    (CObListenEvent* pEvent);
  virtual int OnListenPreUpdateRecord (CObListenEvent* pEvent);
  virtual int GetListenEvents         (void) { return (OB_EVENTMASK_ALL); }

  bool OnToggleDeleteRecord (CObRecord* pRecord);
  bool OnToggleIgnoreRecord (CObRecord* pRecord);
  bool OnToggleQuestRecord  (CObRecord* pRecord);

	/* Updates the main view content display */
  void UpdateContents (void);


	/* Diagnostics */
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  
	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObEditView)
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
  virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
  //}}AFX_VIRTUAL


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CObEditView)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnSelchangedRecordtree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnFileImportCsv();
  afx_msg void OnFileExportcsvSelecteditems();
	afx_msg void OnRecordtreeReload();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRecordtreeExporttocsv();
	afx_msg void OnViewFilestructure();
	afx_msg void OnFileExportCsvexteriorlocations();
	afx_msg void OnFileExportCsvExtMapMarkers();
	afx_msg void OnHelpTestfieldlookup();
	afx_msg void OnFileExportCsvexportexteriorplants();
	afx_msg void OnEditFindbinarydata();
	afx_msg void OnHelpTestfindformid();
	afx_msg void OnTestMemoryspeed();
	afx_msg void OnTestTokenscripts();
	afx_msg void OnRecordClean();
	afx_msg void OnUpdateHasSelectedRecords(CCmdUI* pCmdUI);
	afx_msg void OnRecordMoveactive();
	afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy (void);
	afx_msg void OnMenuEditrecord();
	afx_msg void OnEditNewrecord();
	afx_msg void OnRecordTogglequest();
	afx_msg void OnRecordToggleignore();
	afx_msg void OnRecordToggledelete();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnRecordRename();
	afx_msg void OnRecordCreatecopy();
	afx_msg void OnRecordBatchedit();
	afx_msg void OnEditFind();
	afx_msg void OnHelpTestoutputeffects();
	afx_msg void OnHelpTestrecordsize();
	afx_msg void OnTestCleanrecompileall();
	afx_msg void OnTestRecompileall();
	afx_msg void OnHelpTestcomparescripts();
	afx_msg void OnEditSelectall();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

 };
/*===========================================================================
 *		End of Class CObEditView Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Inline Class Methods
 *
 *=========================================================================*/
#ifndef _DEBUG
  inline CObEditDoc* CObEditView::GetDocument() {
    return (CObEditDoc*)m_pDocument; }
#endif
/*===========================================================================
 *		End of Inline Class Methods
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File View.H
 *=========================================================================*/
