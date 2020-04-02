/*===========================================================================
 *
 * File:	ObSounView.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSOUNVIEW_H
#define __OBSOUNVIEW_H


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
 * Begin Class CObSounView Definition
 *
 *=========================================================================*/
class CObSounView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObSounView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObSounView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CObSounView)
  enum { IDD = IDD_SOUN_VIEW };
  CSliderCtrl	m_StopTimeSlider;
  CSliderCtrl	m_StartTimeSlider;
  CSliderCtrl	m_StaticAttSlider;
  CSliderCtrl	m_MaxAttSlider;
  CSliderCtrl	m_MinAttSlider;
  CButton	m_360LFE;
  CButton	m_2DSound;
  CButton	m_IgnoreEnvironment;
  CButton	m_MenuSound;
  CButton	m_Loop;
  CButton	m_RandomLocation;
  CButton	m_RandomPlay;
  CButton	m_RandomFreqShift;
  CEdit		m_StopTime;
  CEdit		m_StartTime;
  CEdit		m_StaticAttenuation;
  CEdit		m_FreqAdjustment;
  CEdit		m_MaxAttenuation;
  CEdit		m_MinAttenuation;
  CEdit		m_SoundFile;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObSounView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObSounView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObSounView)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObSounView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ObSounView.H
 *=========================================================================*/
