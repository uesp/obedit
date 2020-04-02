/*===========================================================================
 *
 * File:	ObLighview.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBLIGHVIEW_H
#define __OBLIGHVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/obrecorddialog.h"
  #include "colorstatic.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLighView Definition
 *
 *=========================================================================*/
class CObLighView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObLighView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
  bool	m_Initialized;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObLighView();

  void EnableCarried (const bool Enable);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObLighView)
	enum { IDD = IDD_LIGH_VIEW };
	CEdit	m_Falloff;
	CEdit	m_Radius;
	CEdit	m_FOV;
  CSpinButtonCtrl	m_BlueSpin;
  CSpinButtonCtrl	m_GreenSpin;
  CSpinButtonCtrl	m_RedSpin;
  CComboBox	m_FlickerType;
  CColorStatic	m_ColorBox;
  CEdit		m_Fade;
  CEdit		m_BlueColor;
  CEdit		m_GreenColor;
  CEdit		m_RedColor;
  CButton	m_SpotShadow;
  CButton	m_SpotLight;
  CButton	m_Dynamic;
  CButton	m_Negative;
  CButton	m_OffByDefault;
  CEdit		m_Sound;
  CEdit		m_Time;
  CButton	m_CanCarry;
  CEdit		m_Icon;
  CEdit		m_Model;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Script;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CButton	m_QuestItem;
	//}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObLighView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObLighView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObLighView)
	afx_msg void OnCarried();
	afx_msg void OnColor();
	afx_msg void OnChangeRed();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObLighView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObLighview.H
 *=========================================================================*/
