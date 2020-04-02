/*===========================================================================
 *
 * File:	ObContView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCONTVIEW_H
#define __OBCONTVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/obrecorddialog.h"
  #include "windows/obrecordlistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObContView Definition
 *
 *=========================================================================*/
class CObContView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObContView)
  DECLARE_OBRECUIFIELDS()

  /*---------- Begin Protected Class Members ----------------------------*/
protected:
  CObContRecord		m_CopyRecord;


  /*---------- Begin Protected Class Methods ----------------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObContView();         
  virtual ~CObContView();

	/* Helper update methods */
  void FillItemList   (void);
  void SaveSubrecords (void);
  int  AddItemList    (CObCntoSubrecord* pItem);
  void UpdateItem     (const int ListIndex, CObCntoSubrecord* pSubrecord);

	/* Drag/drop helpers */
  int OnDropCustomData (obrldroprecords_t& DropItems);
  int OnDropRecords    (obrldroprecords_t& DropItems);


  /*---------- Begin Public Class Methods -------------------------------*/
public:

	/* Get and set data */
  virtual void  GetControlData   (void);
  virtual void  SetControlData   (void);

  	/* Listener events */
  virtual int OnListenCleanRecord     (CObListenEvent* pEvent);
  virtual int OnListenUpdateRecord    (CObListenEvent* pEvent);
  virtual int GetListenEvents         (void) { return (OB_EVENT_CLEANRECORD | OB_EVENT_UPDATERECORD); }

  //{{AFX_DATA(CObContView)
  enum { IDD = IDD_CONT_VIEW };
  CButton		m_Respawns;
  CButton		m_QuestItem;
  CEdit			m_Weight;
  CEdit			m_FullName;
  CEdit			m_Script;
  CEdit			m_OpenSound;
  CEdit			m_ClosingSound;
  CEdit			m_Model;
  CEdit			m_EditorID;
  CEdit			m_FormID;
  CObRecordListCtrl	m_ItemList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObContView)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL


#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObContView)
  virtual void OnInitialUpdate (void);
  afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
  afx_msg void OnLvllistEdit();
  afx_msg void OnUpdateLvllistEdit(CCmdUI* pCmdUI);
  afx_msg void OnLvllistAdd();
  afx_msg void OnLvllistDelete();
  afx_msg void OnUpdateLvllistDelete(CCmdUI* pCmdUI);
  afx_msg void OnMinusCount();
  afx_msg void OnAddCount();
  afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam);
  afx_msg void OnLvlEditrecord();
  afx_msg void OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult);
  afx_msg void OnSelectClosesoundButton();
  afx_msg void OnEditCloseSound();
  afx_msg void OnDropCloseSound (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnSelectOpensoundButton();
  afx_msg void OnEditOpenSound();
  afx_msg void OnDropOpenSound (NMHDR* pNotifyStruct, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObContView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObContView.H
 *=========================================================================*/
