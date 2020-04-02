/*===========================================================================
 *
 * File:	Obarmorview.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 25, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBARMORVIEW_H
#define __OBARMORVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecorddialog.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObArmorView Definition
 *
 *=========================================================================*/
class CObArmorView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObArmorView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
  //CObArmoRecord*	m_pInputRecord;
  //CObArmoRecord*	m_pOutputRecord;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObArmorView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObArmorView)
  enum { IDD = IDD_ARMOR_VIEW };
  CButton	m_QuestItem;
  CComboBox	m_TypeList;
  CButton	m_BipedButton;
  CEdit		m_FemaleIcon;
  CEdit		m_FemaleWorld;
  CEdit		m_MaleIcon;
  CEdit		m_MaleWorld;
  CEdit		m_MaleBiped;
  CButton	m_Playable;
  CButton	m_HideRings;
  CButton	m_HideAmulet;
  CEdit		m_Health;
  CEdit		m_Armor;
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
  //{{AFX_VIRTUAL(CObArmorView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObArmorView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObArmorView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObArmorView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obarmorview.H
 *=========================================================================*/
