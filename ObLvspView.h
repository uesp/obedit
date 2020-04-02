/*===========================================================================
 *
 * File:	Oblvspview.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 7, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBLVSPVIEW_H
#define __OBLVSPVIEW_H


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
 * Begin Class CObLvspView Definition
 *
 *=========================================================================*/
class CObLvspView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObLvspView)
  DECLARE_OBRECUIFIELDS()

  /*---------- Begin Protected Class Members ----------------------------*/
protected:
  CObLvspRecord		m_CopyRecord;


  /*---------- Begin Protected Class Methods ----------------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObLvspView();         
  virtual ~CObLvspView();

	/* Helper update methods */
  void FillItemList   (void);
  void SaveSubrecords (void);
  int  AddItemList    (CObLvloSubrecord* pItem);
  void UpdateItem     (const int ListIndex, CObLvloSubrecord* pSubrecord);

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

  //{{AFX_DATA(CObLvspView)
  enum { IDD = IDD_LVSP_VIEW };
  CButton		m_UseAllSpells;
  CButton		m_CalculateEach;
  CButton		m_CalculateAll;
  CEdit			m_ChanceNone;
  CEdit			m_EditorID;
  CEdit			m_FormID;
  CObRecordListCtrl	m_ItemList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObLvspView)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL


#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObLvspView)
  virtual void OnInitialUpdate (void);
  afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
  afx_msg void OnLvllistEdit();
  afx_msg void OnUpdateLvllistEdit(CCmdUI* pCmdUI);
  afx_msg void OnLvllistAdd();
  afx_msg void OnLvllistDelete();
  afx_msg void OnUpdateLvllistDelete(CCmdUI* pCmdUI);
  afx_msg void OnMinusCount();
  afx_msg void OnAddCount();
  afx_msg void OnMinusLevel();
  afx_msg void OnAddLevel();
  afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam);
  afx_msg void OnLvlEditrecord();
  afx_msg void OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult);
  afx_msg void OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObLvspView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Oblvspview.H
 *=========================================================================*/
