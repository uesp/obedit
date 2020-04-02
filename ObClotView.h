/*===========================================================================
 *
 * File:	ObClotView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCLOTVIEW_H
#define __OBCLOTVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/obrecorddialog.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObClotView Definition
 *
 *=========================================================================*/
class CObClotView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObClotView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObClotView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObClotView)
  enum { IDD = IDD_CLOT_VIEW };
  CButton	m_QuestItem;
  CButton	m_BipedButton;
  CEdit		m_FemaleIcon;
  CEdit		m_FemaleWorld;
  CEdit		m_MaleIcon;
  CEdit		m_MaleWorld;
  CEdit		m_MaleBiped;
  CButton	m_Playable;
  CButton	m_HideRings;
  CButton	m_HideAmulet;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Script;
  CEdit		m_Enchantment;
  CEdit		m_BipedParts;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_FemaleBiped;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObClotView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObClotView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObClotView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObClotView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObClotView.H
 *=========================================================================*/
