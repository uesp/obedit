/*===========================================================================
 *
 * File:	Obrecorddialog.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 11, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBRECORDDIALOG_H
#define __OBRECORDDIALOG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obespfile.h"
  #include "modfile/obmultirecordhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Macros to help define a UI field map */
  #define DECLARE_OBRECUIFIELDS()	static obuirecfields_t s_UIRecFields[]; \
	 virtual obuirecfields_t* GetUIFields (void);

  #define BEGIN_OBRECUIFIELDS(Class) obuirecfields_t* Class::GetUIFields (void) { return Class::s_UIRecFields; } \
		obuirecfields_t Class::s_UIRecFields[] = { 

  #define ADD_OBRECUIFIELDS(Field, ID, MaxLength, ToolID)  { Field, ID, MaxLength, ToolID },
  #define END_OBRECUIFIELDS()  { OB_FIELD_NONE, 0, 0, 0 } }; 

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Holds the UI field information */
  struct obuirecfields_t {
	obfieldid_t	FieldID;
	int		ControlID;
	int		MaxLength;
	int		ToolTipID;

  };

	/* Forward class definitions */
  class CObEditDlgHandler;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRecordDialog Definition
 *
 * Description
 *
 *=========================================================================*/
class CObRecordDialog : public CFormView, public IObListener {
  DECLARE_DYNCREATE(CObRecordDialog);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obeditrecinfo_t	 m_EditInfo;		/* Holds information on the record being edited */
  CObMultiRecordHandler* m_pRecordHandler;	/* Main record handler object */

  HACCEL		m_hAccelerator;		/* Optional custom accelerator table for the dialog */
  int			m_AcceleratorID;

  CObEditDlgHandler*	m_pDlgHandler;

  CString		m_TitlePrefix;		/* Used to output the record type to the window title */

  CWnd*			m_pEditorIDField;
  CWnd*			m_pBipedPartsField;
  CWnd*			m_pScriptField;
  dword			m_ScriptType;
  CWnd*			m_pEnchantField;
  dword			m_EnchantType;
  CWnd*			m_pSoundField;

  CWnd*			m_pModelField;
  CWnd*			m_pIconField;
  CWnd*			m_pSoundFileField;  
  CWnd*			m_pMaleWorldModelField;
  CWnd*			m_pMaleBipedModelField;
  CWnd*			m_pFemaleWorldModelField;
  CWnd*			m_pFemaleBipedModelField;
  CWnd*			m_pMaleIconField;
  CWnd*			m_pFemaleIconField;

  bool			m_InitialSetData;
  bool			m_NoActivateRecord;

  CToolTipCtrl		m_ToolTip;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Output/input defined fields */
  void GetUIFieldData (void);
  void SetUIFieldData (void);

	/* Update the editor ID in the edit info structure */
  virtual int UpdateEditorID (void);

	/* Initialize the dialog tooltips */
  virtual void InitToolTips (void);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRecordDialog (const int ID = 0);
  //virtual ~CObRecordDialog() { Destroy(); }
  //virtual void Destroy (void);

	/* Close the window */
  virtual void Close (void);

	/* Access the UI field array */
  //virtual obuirecfields_t* GetUIFields (void) { return (NULL); }

	/* Access the dialog record object */
  virtual CObRecord*       GetInputRecord  (void) { return (m_EditInfo.pOldRecord); }
  virtual CObRecord*       GetOutputRecord (void) { return (m_EditInfo.pNewRecord); }
  virtual obeditrecinfo_t& GetEditInfo     (void) { return (m_EditInfo); }

	/* Return a prefix describing the record type */
  virtual const SSCHAR* GetTitlePrefix (void) { return (m_TitlePrefix); }

	/* Check if the dialog is editing the given record */
  virtual bool IsEditRecord (CObRecord* pRecord) { return (m_EditInfo.pOldRecord == pRecord); }

  	/* Set and get control data */
  virtual void  ClearControlData (void);
  virtual void  GetControlData   (void);
  virtual void  SetControlData   (void);
  virtual void  SetTitle         (const SSCHAR* pEditorID);

	/* Main Events */
  virtual int  OnPreSaveRecord    (void);
  virtual int  OnPostSaveRecord   (void);
  virtual int  OnCancelEditRecord (void);
  virtual void OnApply            (void);
  virtual void OnSave		  (void);
  virtual void OnCancel		  (void);

	/* Listener events */
  virtual int OnListenAddRecord       (CObListenEvent* pEvent) { return (0); }
  virtual int OnListenCleanRecord     (CObListenEvent* pEvent) { return (0); }
  virtual int OnListenUpdateRecord    (CObListenEvent* pEvent) { return (0); }
  virtual int OnListenPreUpdateRecord (CObListenEvent* pEvent) { return (0); }
  virtual int GetListenEvents         (void)                   { return (0); }

  	/* Set class members */
  virtual void SetEditInfo      (obeditrecinfo_t&       InputInfo);
  virtual void SetRecordHandler (CObMultiRecordHandler* pHandler) { m_pRecordHandler = pHandler; }
  virtual void SetDlgHandler    (CObEditDlgHandler*     pHandler) { m_pDlgHandler    = pHandler; }
  virtual void SetTitlePrefix   (const TCHAR*           pString)  { m_TitlePrefix    = pString; }


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObRecordDialog)
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
  virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObRecordDialog)
  afx_msg void OnDestroy();
  afx_msg void OnKillfocusEditorid();
  afx_msg void OnBipedpartsButton();
  afx_msg void OnEditScript();
  afx_msg void OnEditEnchantment();
  afx_msg void OnSelectScript();
  afx_msg void OnSelectEnchantment();
  afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
  afx_msg void OnDropScript (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropEnchant (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnEditCut (void);
  afx_msg void OnEditUndo (void);
  afx_msg void OnEditCopy (void);
  afx_msg void OnEditPaste (void);
  afx_msg void OnEditSelectAll (void);
  afx_msg void OnUpdateEditSelectAll (CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditCopy (CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditPaste (CCmdUI* pCmdUI);
  afx_msg BOOL OnHelpInfo (HELPINFO* pHeplInfo);
  afx_msg void OnHelp (void);
  afx_msg void OnDropModel (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropMaleWorldModel (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropMaleBipedModel (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropFemaleWorldModel (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropFemaleBipedModel (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropIcon (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropMaleIcon (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropFemaleIcon (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnDropSoundFile (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnSelectModel (void);
  afx_msg void OnSelectIcon (void);
  afx_msg void OnSelectSoundFile (void);
  afx_msg void OnSelectMaleWorldModel (void);
  afx_msg void OnSelectMaleBipedModel (void);
  afx_msg void OnSelectMaleIcon (void);
  afx_msg void OnSelectFemaleWorldModel (void);
  afx_msg void OnSelectFemaleBipedModel (void);
  afx_msg void OnSelectFemaleIcon (void);
  afx_msg void OnSelectsoundButton();
  afx_msg void OnEditSound();
  afx_msg void OnDropSound (NMHDR* pNotifyStruct, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

 };
/*===========================================================================
 *		End of Class CObRecordDialog Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRecordDialog.H
 *=========================================================================*/
