/*===========================================================================
 *
 * File:	ObAppaview.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "oblighview.h"
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

  IMPLEMENT_DYNCREATE(CObLighView, CObRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLighView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObLighView, CObRecordDialog)
  //{{AFX_MSG_MAP(CObLighView)
	ON_BN_CLICKED(IDC_CARRIED, OnCarried)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_EN_CHANGE(IDC_RED, OnChangeRed)
	ON_EN_CHANGE(IDC_GREEN, OnChangeRed)
	ON_EN_CHANGE(IDC_BLUE, OnChangeRed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObLighView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_OBRECUIFIELDS(CObLighView)
	ADD_OBRECUIFIELDS( OB_FIELD_EDITORID,	   IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_OBRECUIFIELDS( OB_FIELD_FORMID,	   IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_OBRECUIFIELDS( OB_FIELD_ITEMNAME,	   IDC_NAME,		128,	IDS_TT_FULLNAME)
	ADD_OBRECUIFIELDS( OB_FIELD_VALUE,	   IDC_VALUE,		16,	IDS_TT_VALUE)
	ADD_OBRECUIFIELDS( OB_FIELD_WEIGHT,	   IDC_WEIGHT,		16,	IDS_TT_WEIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_SCRIPT,	   IDC_SCRIPT,		128,	IDS_TT_SCRIPT)
	ADD_OBRECUIFIELDS( OB_FIELD_MODEL,         IDC_MODEL,		256,	IDS_TT_MODEL)
	ADD_OBRECUIFIELDS( OB_FIELD_ICON,          IDC_INVENTORYICON,	256,	IDS_TT_ICON)
	ADD_OBRECUIFIELDS( OB_FIELD_SOUND,	   IDC_SOUND,	        128,	IDS_TT_SOUND)
	ADD_OBRECUIFIELDS( OB_FIELD_TIME,	   IDC_TIME,	        8,	IDS_TT_TIME)
	ADD_OBRECUIFIELDS( OB_FIELD_FADE,	   IDC_FADE,	        8,	IDS_TT_FADE)
	ADD_OBRECUIFIELDS( OB_FIELD_FOV,	   IDC_FOV,	        8,	IDS_TT_FOV)
	ADD_OBRECUIFIELDS( OB_FIELD_FALLOFF,	   IDC_FALLOFF,	        8,	IDS_TT_FALLOFF)
	ADD_OBRECUIFIELDS( OB_FIELD_RADIUS,	   IDC_RADIUS,	        8,	IDS_TT_RADIUS)
	ADD_OBRECUIFIELDS( OB_FIELD_REDCOLOR,	   IDC_RED,	        4,	IDS_TT_REDCOLOR)
	ADD_OBRECUIFIELDS( OB_FIELD_GREENCOLOR,	   IDC_GREEN,	        4,	IDS_TT_GREENCOLOR)
	ADD_OBRECUIFIELDS( OB_FIELD_BLUECOLOR,	   IDC_BLUE,	        4,	IDS_TT_BLUECOLOR)
	ADD_OBRECUIFIELDS( OB_FIELD_QUESTITEM,     IDC_QUESTITEM,	0,	IDS_TT_QUESTITEM)
	ADD_OBRECUIFIELDS( OB_FIELD_DEFAULTOFF,	   IDC_OFFBYDEFAULT,	0,	IDS_TT_OFFBYDEFAULT)
	ADD_OBRECUIFIELDS( OB_FIELD_SPOTLIGHT,	   IDC_SPOTLIGHT,	0,	IDS_TT_SPOTLIGHT)
	ADD_OBRECUIFIELDS( OB_FIELD_SPOTSHADOW,	   IDC_SPOTSHADOW,	0,	IDS_TT_SPOTSHADOW)
	ADD_OBRECUIFIELDS( OB_FIELD_NEGATIVE,	   IDC_NEGATIVE,	0,	IDS_TT_NEGATIVE)
	ADD_OBRECUIFIELDS( OB_FIELD_DYNAMIC,	   IDC_DYNAMIC,	        0,	IDS_TT_DYNAMIC)
	ADD_OBRECUIFIELDS( OB_FIELD_CARRIED,	   IDC_CARRIED,	        0,	IDS_TT_CARRIED)
	ADD_OBRECUIFIELDS( OB_FIELD_TYPE,	   IDC_FLICKERTYPE,	0,	IDS_TT_FLICKERTYPE)
END_OBRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Constructor
 *
 *=========================================================================*/
CObLighView::CObLighView() : CObRecordDialog(CObLighView::IDD) {
  //{{AFX_DATA_INIT(CObLighView)
  //}}AFX_DATA_INIT

  m_ScriptType  = OB_SCRIPTTYPE_OBJECT;
  m_EnchantType = 0;

  m_InitialSetData = false;
  m_Initialized    = false;
}
/*===========================================================================
 *		End of Class CObLighView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Destructor
 *
 *=========================================================================*/
CObLighView::~CObLighView() {

}
/*===========================================================================
 *		End of Class CObLighView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObLighView::DoDataExchange (CDataExchange* pDX) {
  CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObLighView)
	DDX_Control(pDX, IDC_FALLOFF, m_Falloff);
	DDX_Control(pDX, IDC_RADIUS, m_Radius);
	DDX_Control(pDX, IDC_FOV, m_FOV);
	DDX_Control(pDX, IDC_BLUESPIN, m_BlueSpin);
	DDX_Control(pDX, IDC_GREENSPIN, m_GreenSpin);
	DDX_Control(pDX, IDC_REDSPIN, m_RedSpin);
	DDX_Control(pDX, IDC_FLICKERTYPE, m_FlickerType);
	DDX_Control(pDX, IDC_COLOR, m_ColorBox);
	DDX_Control(pDX, IDC_FADE, m_Fade);
	DDX_Control(pDX, IDC_BLUE, m_BlueColor);
	DDX_Control(pDX, IDC_GREEN, m_GreenColor);
	DDX_Control(pDX, IDC_RED, m_RedColor);
	DDX_Control(pDX, IDC_SPOTSHADOW, m_SpotShadow);
	DDX_Control(pDX, IDC_SPOTLIGHT, m_SpotLight);
	DDX_Control(pDX, IDC_DYNAMIC, m_Dynamic);
	DDX_Control(pDX, IDC_NEGATIVE, m_Negative);
	DDX_Control(pDX, IDC_OFFBYDEFAULT, m_OffByDefault);
	DDX_Control(pDX, IDC_SOUND, m_Sound);
	DDX_Control(pDX, IDC_TIME, m_Time);
	DDX_Control(pDX, IDC_CARRIED, m_CanCarry);
	DDX_Control(pDX, IDC_INVENTORYICON, m_Icon);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_SCRIPT, m_Script);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObLighView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Method - void EnableCarried (Enable);
 *
 *=========================================================================*/
void CObLighView::EnableCarried (const bool Enable) {

  m_Name.EnableWindow(Enable);
  m_Icon.EnableWindow(Enable);
  m_OffByDefault.EnableWindow(Enable);
  m_Weight.EnableWindow(Enable);
  m_Value.EnableWindow(Enable);
  m_Time.EnableWindow(Enable);
}
/*===========================================================================
 *		End of Class Method CObLighView::EnableCarried()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLighView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CObLighView::AssertValid() const {
  CObRecordDialog::AssertValid();
}


void CObLighView::Dump(CDumpContext& dc) const {
  CObRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CObLighView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObLighView::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();

  ObFillComboList(m_FlickerType, s_ObLightTypes, OBE_FILLCOMBO_NODUPLICATES);

  m_RedSpin.SetRange(0, 255);
  m_GreenSpin.SetRange(0, 255);
  m_BlueSpin.SetRange(0, 255);

  SetControlData();

  m_ColorBox.SetColor(RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos()));
  m_ColorBox.RedrawWindow();

  OnCarried();

  m_Initialized = true;
}
/*===========================================================================
 *		End of Class Event CObLighView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Event - void OnCarried ();
 *
 *=========================================================================*/
void CObLighView::OnCarried() {
  bool Carried = m_CanCarry.GetCheck() != 0;

  EnableCarried(Carried);
}
/*===========================================================================
 *		End of Class Event CObLighView::OnCarried()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Event - void OnColor ();
 *
 *=========================================================================*/
void CObLighView::OnColor() {
  COLORREF     Color = RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos());
  CColorDialog Dlg(Color, CC_RGBINIT | CC_FULLOPEN, this);
  int          Result;

  Result = Dlg.DoModal();
  if (Result != IDOK) return;

  Color = Dlg.GetColor();

  m_RedSpin.SetPos(GetRValue(Color));
  m_GreenSpin.SetPos(GetGValue(Color));
  m_BlueSpin.SetPos(GetBValue(Color));

  m_ColorBox.SetColor(Color);
  m_ColorBox.RedrawWindow();
	
}
/*===========================================================================
 *		End of Class Event CObLighView::OnColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighView Event - void OnChangeRed ();
 *
 *=========================================================================*/
void CObLighView::OnChangeRed() {
  if (!m_Initialized) return;

  COLORREF Color = RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos());

  m_ColorBox.SetColor(Color);
  m_ColorBox.RedrawWindow();
}
/*===========================================================================
 *		End of Class Event CObLighView::OnChangeRed()
 *=========================================================================*/
