/*===========================================================================
 *
 * File:	Obeffecteditdlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBEFFECTEDITDLG_H
#define __OBEFFECTEDITDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/records/obenchrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Return results */
  #define OB_EFFECTEDITDLG_RESULT_OK		IDOK
  #define OB_EFFECTEDITDLG_RESULT_CANCEL	IDCANCEL
  #define OB_EFFECTEDITDLG_RESULT_DELETE	201

	/* Edit dialog flags */
  #define OB_EFFECTEDITDLG_FLAG_SELF	1
  #define OB_EFFECTEDITDLG_FLAG_TOUCH	2
  #define OB_EFFECTEDITDLG_FLAG_TARGET	4

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEffectEditDlg Definition
 *
 *=========================================================================*/
class CObEffectEditDlg : public CDialog {


  /*---------- Begin Protected Class Members -----------------------*/
protected:
  CObRecordHandler*	m_pRecordHandler;

  CString		m_TitleValue;

  CObEffectItemRecord*  m_pEffectRecord;
  CObEfidSubrecord*	m_pEffect;
  dword			m_ValidEffectMask;
  dword			m_InvalidEffectMask;
  dword			m_Flags;


  /*---------- Begin Protected Class Methods -----------------------*/
protected:

  void UpdateControlState (void);
  void SetScriptState     (const bool Enable);
  void FillScriptList     (void);


  /*---------- Begin Public Class Methods --------------------------*/
public:

	/* Constructor */
  CObEffectEditDlg(CWnd* pParent = NULL);

	/* Get/set effect data */
  void GetControlData (void);
  void SetControlData (void);

	/* Set class members */
  void SetTitleValue    (const TCHAR*         pString) { m_TitleValue     = pString; }
  void SetEffectRecord  (CObEffectItemRecord* pRecord) { m_pEffectRecord  = pRecord; }
  void SetEffect        (CObEfidSubrecord* pSubrecord) { m_pEffect        = pSubrecord; }
  void SetFlags         (const dword            Flags) { m_Flags          = Flags; }
  void SetRecordHandler (CObRecordHandler*   pHandler) { m_pRecordHandler = pHandler; }

  void SetValidEffectMask   (const dword Flags) { m_ValidEffectMask   = Flags; }
  void SetInvalidEffectMask (const dword Flags) { m_InvalidEffectMask = Flags; }
  

  //{{AFX_DATA(CObEffectEditDlg)
  enum { IDD = IDD_EFFECT_DLG };
  CStatic	m_MagPercentLabel;
  CButton	m_Hostile;
  CComboBox	m_SchoolList;
  CComboBox	m_VisualEffectList;
  CEdit		m_EffectName;
  CComboBox	m_ScriptList;
  CComboBox	m_ActorValueList;
  CEdit		m_Magnitude;
  CEdit		m_Duration;
  CEdit		m_Area;
  CComboBox	m_RangeList;
  CComboBox	m_EffectList;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObEffectEditDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObEffectEditDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnDeleteButton();
  afx_msg void OnSelchangeEffectList();
  afx_msg void OnOK();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObEffectEditDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  int ObEditEnchantEffectDlg    (CObEnchRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler);
  int ObEditSpellEffectDlg      (CObSpelRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler);
  int ObEditIngredientEffectDlg (CObIngrRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler);
  int ObEditSigilStoneEffectDlg (CObSgstRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler);
  int ObEditPotionEffectDlg     (CObAlchRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obeffecteditdlg.H
 *=========================================================================*/
 