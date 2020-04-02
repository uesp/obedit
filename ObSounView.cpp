/*===========================================================================
 *
 * File:	ObSounView.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "obsounview.h"
#include "dialogs/obeditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif

  IMPLEMENT_DYNCREATE(CObSounView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSounView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObSounView, CObRecordDialog)
	//{{AFX_MSG_MAP(CObSounView)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObSounView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObSounView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	       IDC_EDITORID,	      128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	       IDC_FORMID,	      128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_SOUNDFILE,	       IDC_SOUNDFILE,	      256,	IDS_TT_SOUNDFILE)
	ADD_OBRECUIFIELDS( OB_FIELD_MINATTENUATION,    IDC_MINATTENUATION,    8,	IDS_TT_MINATTENUATION)
	ADD_OBRECUIFIELDS( OB_FIELD_MAXATTENUATION,    IDC_MAXATTENUATION,    8,	IDS_TT_MAXATTENUATION)
	ADD_OBRECUIFIELDS( OB_FIELD_STATICATTENUATION, IDC_STATICATTENUATION, 8,	IDS_TT_STATICATTENUATION)
	ADD_OBRECUIFIELDS( OB_FIELD_FREQADJUSTMENT,    IDC_FREQADJUSTMENT,    8,	IDS_TT_FREQADJUSTMENT)
	ADD_OBRECUIFIELDS( OB_FIELD_STARTTIME,         IDC_STARTTIME,         8,	IDS_TT_STARTTIME)
	ADD_OBRECUIFIELDS( OB_FIELD_STOPTIME ,         IDC_STOPTIME,          8,	IDS_TT_STOPTIME)
	ADD_OBRECUIFIELDS( OB_FIELD_RANDOMFREQSHIFT,   IDC_RANDOMFREQSHIFT,   0,	IDS_TT_RANDOMFREQSHIFT)
	ADD_OBRECUIFIELDS( OB_FIELD_RANDOMPLAY,        IDC_RANDOMPLAY,        0,	IDS_TT_RANDOMPLAY)
	ADD_OBRECUIFIELDS( OB_FIELD_RANDOMLOCATION,    IDC_RANDOMLOCATION,    0,	IDS_TT_RANDOMLOCATION)
	ADD_OBRECUIFIELDS( OB_FIELD_LOOP,              IDC_LOOP,              0,	IDS_TT_LOOP)
	ADD_OBRECUIFIELDS( OB_FIELD_MENUSOUND,	       IDC_MENUSOUND,	      0,	IDS_TT_MENUSOUND)
	ADD_OBRECUIFIELDS( OB_FIELD_IGNOREENVIRONMENT, IDC_IGNOREENVIRONMENT, 0,	IDS_TT_IGNOREENVIRONMENT)
	ADD_OBRECUIFIELDS( OB_FIELD_2DSOUND,           IDC_2DSOUND,	      0,	IDS_TT_2DSOUND)
	ADD_OBRECUIFIELDS( OB_FIELD_360LFE,            IDC_360LFE,	      0,	IDS_TT_360LFE)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounView Constructor
 *
 *=========================================================================*/
CObSounView::CObSounView() : CObRecordDialog(CObSounView::IDD) {
  //{{AFX_DATA_INIT(CObSounView)
  //}}AFX_DATA_INIT

  m_ScriptType  = 0;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CObSounView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounView Destructor
 *
 *=========================================================================*/
CObSounView::~CObSounView() {

}
/*===========================================================================
 *		End of Class CObSounView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObSounView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObSounView)
	DDX_Control(pDX, IDC_STOPTIME_SLIDER, m_StopTimeSlider);
	DDX_Control(pDX, IDC_STARTTIME_SLIDER, m_StartTimeSlider);
	DDX_Control(pDX, IDC_STATATT_SLIDER, m_StaticAttSlider);
	DDX_Control(pDX, IDC_MAXATT_SLIDER, m_MaxAttSlider);
	DDX_Control(pDX, IDC_MINATT_SLIDER, m_MinAttSlider);
	DDX_Control(pDX, IDC_360LFE, m_360LFE);
	DDX_Control(pDX, IDC_2DSOUND, m_2DSound);
	DDX_Control(pDX, IDC_IGNOREENVIRONMENT, m_IgnoreEnvironment);
	DDX_Control(pDX, IDC_MENUSOUND, m_MenuSound);
	DDX_Control(pDX, IDC_LOOP, m_Loop);
	DDX_Control(pDX, IDC_RANDOMLOCATION, m_RandomLocation);
	DDX_Control(pDX, IDC_RANDOMPLAY, m_RandomPlay);
	DDX_Control(pDX, IDC_RANDOMFREQSHIFT, m_RandomFreqShift);
	DDX_Control(pDX, IDC_STOPTIME, m_StopTime);
	DDX_Control(pDX, IDC_STARTTIME, m_StartTime);
	DDX_Control(pDX, IDC_STATICATTENUATION, m_StaticAttenuation);
	DDX_Control(pDX, IDC_FREQADJUSTMENT, m_FreqAdjustment);
	DDX_Control(pDX, IDC_MAXATTENUATION, m_MaxAttenuation);
	DDX_Control(pDX, IDC_MINATTENUATION, m_MinAttenuation);
	DDX_Control(pDX, IDC_SOUNDFILE, m_SoundFile);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObSounView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSounView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObSounView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObSounView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObSounView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObSounView::OnInitialUpdate (void) {
  CObSounRecord* pRecord;

  CObRecordDialog::OnInitialUpdate();

  m_MinAttSlider.SetRange(0, 255, FALSE);
  m_MaxAttSlider.SetRange(0, 255, FALSE);
  m_StaticAttSlider.SetRange(0, 10000, FALSE);
  m_StartTimeSlider.SetRange(0, 255, FALSE);
  m_StopTimeSlider.SetRange(0, 255, FALSE);

  m_MinAttSlider.SetLineSize(1);
  m_MaxAttSlider.SetLineSize(10);
  m_StaticAttSlider.SetLineSize(10);
  m_StartTimeSlider.SetLineSize(1);
  m_StopTimeSlider.SetLineSize(1);
  
  m_MinAttSlider.SetPageSize(10);
  m_MaxAttSlider.SetPageSize(100);
  m_StaticAttSlider.SetPageSize(100);
  m_StartTimeSlider.SetPageSize(6);
  m_StopTimeSlider.SetPageSize(6);

  pRecord = ObCastClass(CObSounRecord, m_EditInfo.pOldRecord);

  if (pRecord != NULL) {
    m_MinAttSlider.SetPos(pRecord->GetMinAttenuation());
    m_MaxAttSlider.SetPos(pRecord->GetMaxAttenuation());
    m_StaticAttSlider.SetPos(pRecord->GetStaticAttenuation());
    m_StartTimeSlider.SetPos(pRecord->GetStartTime());
    m_StopTimeSlider.SetPos(pRecord->GetStopTime());
  }

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObSounView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounView Event - void OnHScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CObSounView::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  CString      Buffer;
  CSliderCtrl* pSlider = NULL;
  bool         Update = false;
  int          Position = nPos;

  if (pScrollBar->IsKindOf(RUNTIME_CLASS(CSliderCtrl))) {
    pSlider = (CSliderCtrl *) pScrollBar;
    Position = pSlider->GetPos();
  }

  switch (nSBCode) {
    case TB_ENDTRACK:
	break;
    case TB_BOTTOM:
    case TB_TOP:
    case TB_LINEDOWN:
    case TB_LINEUP:
    case TB_PAGEDOWN:
    case TB_PAGEUP:
    case TB_THUMBTRACK:
    case TB_THUMBPOSITION:
        Update = true;
	break;
  }

  if (!Update) {
    CObRecordDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  }
  else if (pScrollBar == (CScrollBar *) &m_MinAttSlider) {
    Buffer.Format(_T("%u"), Position * OB_SOUN_MINATTENUATION_FACTOR);
    m_MinAttenuation.SetWindowText(Buffer);
  }
  else if (pScrollBar == (CScrollBar *) &m_MaxAttSlider) {
    Buffer.Format(_T("%u"), Position * OB_SOUN_MAXATTENUATION_FACTOR);
    m_MaxAttenuation.SetWindowText(Buffer);
  }
  else if (pScrollBar == (CScrollBar *) &m_StaticAttSlider) {
    Buffer.Format(_T("%.2f"), (float) Position / -100.0f);
    m_StaticAttenuation.SetWindowText(Buffer);
  }
  else if (pScrollBar == (CScrollBar *) &m_StartTimeSlider) {
    Position = (int) (Position * OB_SOUN_TIME_FACTOR);
    Buffer.Format(_T("%u:%02u"), Position / 60, Position % 60);
    m_StartTime.SetWindowText(Buffer);
  }
  else if (pScrollBar == (CScrollBar *) &m_StopTimeSlider) {
    Position = (int) (Position * OB_SOUN_TIME_FACTOR);
    Buffer.Format(_T("%u:%02u"), Position / 60, Position % 60);
    m_StopTime.SetWindowText(Buffer);
  }
  else {
    CObRecordDialog::OnHScroll(nSBCode, nPos, pScrollBar);
  }

}
/*===========================================================================
 *		End of Class Event CObSounView::OnHScroll()
 *=========================================================================*/
