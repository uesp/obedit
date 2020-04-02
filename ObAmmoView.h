/*===========================================================================
 *
 * File:	ObAmmoview.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBAMMOVIEW_H
#define __OBAMMOVIEW_H


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
 * Begin Class CObAmmoView Definition
 *
 *=========================================================================*/
class CObAmmoView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObAmmoView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObAmmoView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObAmmoView)
  enum { IDD = IDD_AMMO_VIEW };
  CEdit		m_Icon;
  CEdit		m_Model;
  CButton	m_IgnoreResist;
  CEdit		m_Speed;
  CEdit		m_Damage;
  CEdit		m_EnchantCharge;
  CButton	m_QuestItem;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Enchantment;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
	//}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObAmmoView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObAmmoView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObAmmoView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObAmmoView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obarmorview.H
 *=========================================================================*/
