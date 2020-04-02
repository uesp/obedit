/*===========================================================================
 *
 * File:	Obenchview.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBENCHVIEW_H
#define __OBENCHVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "windows/obrecordlistctrl.h"
  #include "obrecorddialog.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEnchView Definition
 *
 *=========================================================================*/
class CObEnchView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObEnchView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CObEnchRecord		m_CopyRecord;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:
	/* Constructor/Destructor */
  CObEnchView();
  virtual ~CObEnchView();

	/* Helper get/set methods */
  void SetEffectList     (void);
  int  AddEffectList     (CObEfidSubrecord* pEffect);
  void UpdateEnchantType (void);
  void UpdateEffectList  (const int ListIndex, const bool Update = true);

  int OnDropCustomData (obrldroprecords_t& DropItems);


  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Get and set data */
  virtual void ClearControlData (void);
  virtual void GetControlData   (void);
  virtual void SetControlData   (void);
          

	//{{AFX_DATA(CObEnchView)
  enum { IDD = IDD_ENCH_VIEW };
  CObRecordListCtrl	m_EffectList;
  CEdit			m_Charge;
  CEdit			m_Cost;
  CButton		m_AutoCalculate;
  CComboBox		m_EnchantType;
  CEdit			m_EditorID;
  CEdit			m_FormID;
  //}}AFX_DATA


	// ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CObEnchView)
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
  //{{AFX_MSG(CObEnchView)
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
  afx_msg void OnCharEffectList (NMHDR* pHdr, LRESULT* lResult);
  afx_msg void OnKeydownEffectList (NMHDR* pHdr, LRESULT* lResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObEnchView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obenchview.H
 *=========================================================================*/
