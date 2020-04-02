/*===========================================================================
 *
 * File:	ObSgstView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSGSTVIEW_H
#define __OBSGSTVIEW_H


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
 * Begin Class CObSgstView Definition
 *
 *=========================================================================*/
class CObSgstView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObSgstView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CObSgstRecord		m_CopyRecord;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:
	/* Constructor/Destructor */
  CObSgstView();
  virtual ~CObSgstView();

	/* Helper get/set methods */
  void SetEffectList     (void);
  int  AddEffectList     (CObEfidSubrecord* pEffect);
  void UpdateEffectList  (const int ListIndex, const bool Update = true);

  int OnDropCustomData (obrldroprecords_t& DropItems);


  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Get and set data */
  virtual void ClearControlData (void);
  virtual void GetControlData   (void);
  virtual void SetControlData   (void);
          

  //{{AFX_DATA(CObSgstView)
  enum { IDD = IDD_SGST_VIEW };
  CEdit			m_Icon;
  CEdit			m_Model;
  CEdit			m_Uses;
  CButton		m_QuestItem;
  CEdit			m_Value;
  CEdit			m_Weight;
  CEdit			m_Script;
  CEdit			m_FullName;
  CObRecordListCtrl	m_EffectList;
  CEdit			m_EditorID;
  CEdit			m_FormID;
  //}}AFX_DATA


	// ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CObSgstView)
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
  //{{AFX_MSG(CObSgstView)
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
  afx_msg void OnEditScript();
  afx_msg void OnSelectscriptButton();
  afx_msg void OnKeydownEffectList (NMHDR* pHdr, LRESULT* lResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObSgstView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObSgstView.H
 *=========================================================================*/
