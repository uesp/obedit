/*===========================================================================
 *
 * File:	ObSpelView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSPELVIEW_H
#define __OBSPELVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "windows/obrecordlistctrl.h"
  #include "dialogs/obrecorddialog.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSpelView Definition
 *
 *=========================================================================*/
class CObSpelView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObSpelView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CObSpelRecord		m_CopyRecord;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:
	/* Constructor/Destructor */
  CObSpelView();
  virtual ~CObSpelView();

	/* Helper get/set methods */
  void SetEffectList     (void);
  int  AddEffectList     (CObEfidSubrecord* pEffect);
  void UpdateSpellType   (void);
  void UpdateEffectList  (const int ListIndex, const bool Update = true);

  int OnDropCustomData (obrldroprecords_t& DropItems);


  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Get and set data */
  virtual void ClearControlData (void);
  virtual void GetControlData   (void);
  virtual void SetControlData   (void);

  //{{AFX_DATA(CObSpelView)
	enum { IDD = IDD_SPEL_VIEW };
	CEdit	m_FullName;
  CButton		m_AreaIngoresLOS;
  CButton		m_ScriptAlwaysApplies;
  CButton		m_NoAbsorbReflect;
  CButton		m_SilenceImmune;
  CButton		m_PlayerStartSpell;
  CComboBox		m_SpellLevel;
  CComboBox		m_SpellType;
  CObRecordListCtrl	m_EffectList;
  CEdit			m_Cost;
  CButton		m_AutoCalculate;
  CEdit			m_EditorID;
  CEdit			m_FormID;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CObSpelView)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  //}}AFX_VIRTUAL


protected:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObSpelView)
  afx_msg void OnEffectlistEdit();
  afx_msg void OnUpdateEffectlistEdit(CCmdUI* pCmdUI);
  afx_msg void OnEffectlistAdd();
  afx_msg void OnEffectlistDelete();
  afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnAltEditRecordMsg (WPARAM wParam, LPARAM lParam);
  afx_msg void OnEffectlistEditscript();
  afx_msg void OnUpdateEffectlistEditscript(CCmdUI* pCmdUI);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnKeydownEffectList (NMHDR* pHdr, LRESULT* lResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObSpelView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObSpelView.H
 *=========================================================================*/
