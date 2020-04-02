/*===========================================================================
 *
 * File:	Obeffecteditdlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObEffectEditDlg.h"
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

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObEffectEditDlg, CDialog)
	//{{AFX_MSG_MAP(CObEffectEditDlg)
	ON_BN_CLICKED(ID_DELETE_BUTTON, OnDeleteButton)
	ON_CBN_SELCHANGE(IDC_EFFECT_LIST, OnSelchangeEffectList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Constructor
 *
 *=========================================================================*/
CObEffectEditDlg::CObEffectEditDlg(CWnd* pParent) : CDialog(CObEffectEditDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CObEffectEditDlg)
	//}}AFX_DATA_INIT

  m_TitleValue        = _T("Edit Effect");
  m_pEffectRecord     = NULL;
  m_pEffect           = NULL;
  m_pRecordHandler    = NULL;
  m_Flags             = 0;
  m_ValidEffectMask   = 0;
  m_InvalidEffectMask = 0;
}
/*===========================================================================
 *		End of Class CObEffectEditDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObEffectEditDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObEffectEditDlg)
	DDX_Control(pDX, IDC_MAGPRECENT, m_MagPercentLabel);
	DDX_Control(pDX, IDC_HOSTILE, m_Hostile);
	DDX_Control(pDX, IDC_SCHOOL_LIST, m_SchoolList);
	DDX_Control(pDX, IDC_VISUALEFFECT_LIST, m_VisualEffectList);
	DDX_Control(pDX, IDC_EFFECTNAME, m_EffectName);
	DDX_Control(pDX, IDC_SCRIPT_LIST, m_ScriptList);
	DDX_Control(pDX, IDC_ACTORVALUE_LIST, m_ActorValueList);
	DDX_Control(pDX, IDC_MAGNITUDE, m_Magnitude);
	DDX_Control(pDX, IDC_DURATION, m_Duration);
	DDX_Control(pDX, IDC_AREA, m_Area);
	DDX_Control(pDX, IDC_RANGE_LIST, m_RangeList);
	DDX_Control(pDX, IDC_EFFECT_LIST, m_EffectList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObEffectEditDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObEffectEditDlg::GetControlData (void) {
  CObEfitSubrecord*     pEfit;
  CObScitSubrecord*     pScit;
  CObFullSubrecord*     pFull;
  CString		Buffer;
  obeffectdata_t*       pEffectData = NULL;
  obeffectdata_t*       pVisualEffectData = NULL;
  dword			Value;
  bool		        Result;

  	/* Ignore invalid input */
  if (m_pEffectRecord == NULL || m_pEffect == NULL) return;

  pEfit = m_pEffectRecord->GetEffectData(m_pEffect);
  pScit = m_pEffectRecord->GetScriptEffectData(m_pEffect);
  pFull = m_pEffectRecord->GetScriptEffectNameData(m_pEffect);
  if (pEfit == NULL) return;

	/* Effect type code */
  pEffectData = (obeffectdata_t *) GetComboBoxSelItemData(m_EffectList, 0);

  if (pEffectData != NULL) {
    m_pEffect->SetDataName(*pEffectData->pName);
    pEfit->SetEffectName(*pEffectData->pName);
  }

	/* Effect range */
  Value = GetComboBoxSelItemData(m_RangeList, pEfit->GetEffectType());
  pEfit->SetEffectType(Value);

	/* Area */
  m_Area.GetWindowText(Buffer);
  Result = ObFieldConvertDword(Buffer, Value);
  pEfit->SetArea(Value);

	/* Duration */
  m_Duration.GetWindowText(Buffer);
  Result = ObFieldConvertDword(Buffer, Value);
  pEfit->SetDuration(Value);

	/* Magnitude */
  m_Magnitude.GetWindowText(Buffer);
  Result = ObFieldConvertDword(Buffer, Value);
  pEfit->SetMagnitude(Value);

	/* Actor value */
  Value = GetComboBoxSelItemData(m_ActorValueList, OB_SKILL_NONE);
  pEfit->SetActorValue(Value);

	/* Set the script effect if needed */
  if (pEfit->GetEffectName() != OB_MGEF_SEFF) return;

  obformid_t  ScriptFormID = 0;
  dword       School       = 0;
  obrectype_t VisualEffect = OB_NAME_NULL;
  bool        Hostile      = true;

  if (pScit != NULL) {
    VisualEffect = pScit->GetVisualEffect();
    School       = pScit->GetSchool();
    ScriptFormID = pScit->GetScriptFormID();
    Hostile      = pScit->IsHostile();
  }

  Hostile = m_Hostile.GetCheck() != 0;
  School  = GetComboBoxSelItemData(m_SchoolList, School);
  ScriptFormID = GetComboBoxSelItemData(m_ScriptList, ScriptFormID);

  pVisualEffectData = (obeffectdata_t *) GetComboBoxSelItemData(m_VisualEffectList, 0);
  if (pVisualEffectData != NULL) VisualEffect = *pVisualEffectData->pName;
  
  m_pEffectRecord->SetScriptEffectData(m_pEffect, ScriptFormID, School, VisualEffect, Hostile);

  m_EffectName.GetWindowText(Buffer);
  m_pEffectRecord->SetScriptEffectName(m_pEffect, Buffer);
}
/*===========================================================================
 *		End of Class Method CObEffectEditDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Method - void FillScriptList (void);
 *
 *=========================================================================*/
void CObEffectEditDlg::FillScriptList (void) {
  CObTypeGroup*  pScriptGroup;
  CObBaseRecord* pBaseRecord;
  CObScptRecord* pScript;
  dword          Index;

  m_ScriptList.ResetContent();

  ObAddComboBoxItem(m_ScriptList, "", 0);

  pScriptGroup = m_pRecordHandler->GetTopGroup()->GetTypeGroup(OB_NAME_SCPT);
  if (pScriptGroup == NULL) return;

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pScriptGroup->GetRecord(Index);
    pScript = ObCastClass(CObScptRecord, pBaseRecord);
    if (pScript == NULL) continue;
    if (pScript->GetType() != OB_SCRIPTTYPE_MAGICEFFECT) continue;

    ObAddComboBoxItem(m_ScriptList, pScript->GetEditorID(), pScript->GetFormID());
  }

  m_ScriptList.SetCurSel(0);
}
/*===========================================================================
 *		End of Class Method CObEffectEditDlg::FillScriptList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObEffectEditDlg::OnInitDialog() {
  int ListIndex;

  CDialog::OnInitDialog();

  SetWindowText(m_TitleValue);

  ObFillComboList(m_SchoolList, s_ObSpellSchoolValues, 0);
  ObFillEffectComboList(m_EffectList, 0, m_ValidEffectMask, m_InvalidEffectMask);
  m_SchoolList.SetCurSel(0);
  m_EffectList.SetCurSel(0);

  ObFillEffectComboList(m_VisualEffectList, OBE_FILLCOMBO_INCLUDENULL, 0, 0);
  ListIndex = FindComboBoxEffect(m_VisualEffectList, OB_MGEF_SEFF, false);
  if (ListIndex >= 0) m_VisualEffectList.DeleteString(ListIndex);
  m_VisualEffectList.SetCurSel(0);

  FillScriptList();

  m_EffectName.SetLimitText(64);
  m_Duration.SetLimitText(8);
  m_Magnitude.SetLimitText(8);
  m_Area.SetLimitText(8);

	/* Fill the range list with allowed types */
  if ((m_Flags & OB_EFFECTEDITDLG_FLAG_SELF)   != 0) ObAddComboBoxItem(m_RangeList, "Self",   OB_EFFECTTYPE_SELF);
  if ((m_Flags & OB_EFFECTEDITDLG_FLAG_TOUCH)  != 0) ObAddComboBoxItem(m_RangeList, "Touch",  OB_EFFECTTYPE_TOUCH);
  if ((m_Flags & OB_EFFECTEDITDLG_FLAG_TARGET) != 0) ObAddComboBoxItem(m_RangeList, "Target", OB_EFFECTTYPE_TARGET);
  m_RangeList.SetCurSel(0);
  	
  SetControlData();
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObEffectEditDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CObEffectEditDlg::OnOK() {
  GetControlData();
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObEffectEditDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Event - void OnDeleteButton ();
 *
 *=========================================================================*/
void CObEffectEditDlg::OnDeleteButton() {
  EndDialog(OB_EFFECTEDITDLG_RESULT_DELETE);
}
/*===========================================================================
 *		End of Class Event CObEffectEditDlg::OnDeleteButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObEffectEditDlg::SetControlData (void) {
  CObEfitSubrecord*     pEfit;
  CObScitSubrecord*     pScit;
  CObFullSubrecord*     pFull;
  CSString		Buffer;
  int			ListIndex;

	/* Ignore invalid input */
  if (m_pEffectRecord == NULL || m_pEffect == NULL) return;

  pEfit = m_pEffectRecord->GetEffectData(m_pEffect);
  pScit = m_pEffectRecord->GetScriptEffectData(m_pEffect);
  pFull = m_pEffectRecord->GetScriptEffectNameData(m_pEffect);
  if (pEfit == NULL) return;

  ListIndex = FindComboBoxEffect(m_EffectList, m_pEffect->GetDataName(), true);
  if (ListIndex < 0) m_EffectList.SetCurSel(0);

  ListIndex = FindComboBoxItemData(m_RangeList, pEfit->GetEffectType(), true);
  if (ListIndex < 0) m_RangeList.SetCurSel(0);

  pEfit->GetField(Buffer, OB_FIELD_AREA);
  m_Area.SetWindowText(Buffer);

  pEfit->GetField(Buffer, OB_FIELD_DURATION);
  m_Duration.SetWindowText(Buffer);

  pEfit->GetField(Buffer, OB_FIELD_MAGNITUDE);
  m_Magnitude.SetWindowText(Buffer);

  UpdateControlState();

  ListIndex = FindComboBoxItemData(m_ActorValueList, pEfit->GetActorValue(), true);
  if (ListIndex < 0) m_RangeList.SetCurSel(0);

	/* Set the script effect if needed */
  if (pScit == NULL) return;
  if (pFull != NULL) m_EffectName.SetWindowText(pFull->GetString().c_str());

  m_Hostile.SetCheck(pScit->IsHostile());

  ListIndex = FindComboBoxItemData(m_SchoolList, pScit->GetSchool(), true);
  if (ListIndex < 0) m_SchoolList.SetCurSel(0);

  ListIndex = FindComboBoxEffect(m_VisualEffectList, pScit->GetVisualEffect(), true);
  if (ListIndex < 0) m_VisualEffectList.SetCurSel(0);

  ListIndex = FindComboBoxItemData(m_ScriptList, pScit->GetScriptFormID(), true);
  if (ListIndex < 0) m_ScriptList.SetCurSel(0);

}
/*===========================================================================
 *		End of Class Method CObEffectEditDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Method - void UpdateControlState (void);
 *
 *=========================================================================*/
void CObEffectEditDlg::UpdateControlState (void) {
  obeffectdata_t* pEffectData;
  CString         Buffer;
  bool		  NoArea;
  int		  ListIndex;
  int		  RangeType;

	/* Get control data */
  ListIndex = m_EffectList.GetCurSel();
  if (ListIndex < 0) return;

  pEffectData = (obeffectdata_t *) m_EffectList.GetItemData(ListIndex);
  if (pEffectData == NULL) return;

  ListIndex = m_RangeList.GetCurSel();
  if (ListIndex < 0) return;
  RangeType = m_RangeList.GetItemData(ListIndex);

	/* Enable/disable the area, duration, and magnitude edit boxes */
  NoArea = (RangeType != OB_EFFECTTYPE_SELF) && ((pEffectData->DefaultFlags & OB_EFFECTFLAG_NODURATION) == 0);
  m_Area.EnableWindow(NoArea);
  m_Duration.EnableWindow((pEffectData->DefaultFlags & OB_EFFECTFLAG_NODURATION) == 0);
  m_Magnitude.EnableWindow((pEffectData->DefaultFlags & OB_EFFECTFLAG_NOMAGNITUDE) == 0);

  if ((pEffectData->DefaultFlags & OB_EFFECTFLAG_MAGNITUDEPERCENT) != 0)
    m_MagPercentLabel.ShowWindow(SW_HIDE);
  else
    m_MagPercentLabel.ShowWindow(SW_SHOW);

	/* Update the actor list as needed */
  if ((pEffectData->DefaultFlags & OB_EFFECTFLAG_USESKILL) != 0) {
    m_ActorValueList.GetWindowText(Buffer);
    m_ActorValueList.ResetContent();

    ObFillComboList(m_ActorValueList, s_ObActorValueSkills, OBE_FILLCOMBO_NODUPLICATES);
    m_ActorValueList.SelectString(-1, Buffer);

    if (m_ActorValueList.GetCurSel() < 0) m_ActorValueList.SetCurSel(0);
    m_ActorValueList.EnableWindow(TRUE);
  }
  else if ((pEffectData->DefaultFlags & OB_EFFECTFLAG_USEATTRIBUTE) != 0) {
    m_ActorValueList.GetWindowText(Buffer);
    m_ActorValueList.ResetContent();

    ObFillComboList(m_ActorValueList, s_ObActorValueAttributes, OBE_FILLCOMBO_NODUPLICATES);
    m_ActorValueList.SelectString(-1, Buffer);

    if (m_ActorValueList.GetCurSel() < 0) m_ActorValueList.SetCurSel(0);
    m_ActorValueList.EnableWindow(TRUE);
  }
  else {
    m_ActorValueList.ResetContent();
    m_ActorValueList.EnableWindow(FALSE);
    m_ActorValueList.SetWindowText("");
  }

	/* Update script effect */
  SetScriptState (*pEffectData->pName == OB_MGEF_SEFF);

}
/*===========================================================================
 *		End of Class Method CObEffectEditDlg::UpdateControlState()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Method - void SetScriptState (Enable);
 *
 *=========================================================================*/
void CObEffectEditDlg::SetScriptState (const bool Enable) {
  m_ScriptList.EnableWindow(Enable);
  m_EffectName.EnableWindow(Enable);
  m_VisualEffectList.EnableWindow(Enable);
  m_SchoolList.EnableWindow(Enable);
  m_Hostile.EnableWindow(Enable);
}
/*===========================================================================
 *		End of Class Method CObEffectEditDlg::SetScriptState()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectEditDlg Event - void OnSelchangeEffectList ();
 *
 *=========================================================================*/
void CObEffectEditDlg::OnSelchangeEffectList() {
  UpdateControlState();
}
/*===========================================================================
 *		End of Class Event CObEffectEditDlg::OnSelchangeEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditEnchantEffectDlg (pRecord, pEffect, pRecordHandler);
 *
 *=========================================================================*/
int ObEditEnchantEffectDlg (CObEnchRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler) {
  CObEffectEditDlg  Dlg;
  int               Result;

  if (pRecord == NULL || pEffect == NULL || pRecordHandler == NULL) return (OB_EFFECTEDITDLG_RESULT_CANCEL);

	/* Determine which range types are allowed */
  switch (pRecord->GetType()) {
    case OB_ENCHTYPE_APPAREL:
	Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_SELF);
	break;
    case OB_ENCHTYPE_SCROLL:
	Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_SELF | OB_EFFECTEDITDLG_FLAG_TOUCH | OB_EFFECTEDITDLG_FLAG_TARGET);
	break;
    case OB_ENCHTYPE_STAFF:
	Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_TARGET);
	break;
    case OB_ENCHTYPE_WEAPON:
	Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_TOUCH);
	break;
  }

  Dlg.SetTitleValue(_T("Edit Enchantment Effect"));
  Dlg.SetEffectRecord(pRecord);
  Dlg.SetEffect(pEffect);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetValidEffectMask(OB_EFFECTFLAG_ENCHANTING);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditEnchantEffectDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditIngredientEffectDlg (pRecord, pEffect, pRecordHandler);
 *
 *=========================================================================*/
int ObEditIngredientEffectDlg (CObIngrRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler) {
  CObEffectEditDlg  Dlg;
  int               Result;

  if (pRecord == NULL || pEffect == NULL || pRecordHandler == NULL) return (OB_EFFECTEDITDLG_RESULT_CANCEL);

  Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_SELF);
  Dlg.SetTitleValue(_T("Edit Ingredient Effect"));
  Dlg.SetEffectRecord(pRecord);
  Dlg.SetEffect(pEffect);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetValidEffectMask(OB_EFFECTFLAG_SELF);
  //Dlg.SetInvalidEffectMask(OB_EFFECTFLAG_NOINGREDIANT);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditIngredientEffectDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditPotionEffectDlg (pRecord, pEffect, pRecordHandler);
 *
 *=========================================================================*/
int ObEditPotionEffectDlg (CObAlchRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler) {
  CObEffectEditDlg  Dlg;
  int               Result;

  if (pRecord == NULL || pEffect == NULL || pRecordHandler == NULL) return (OB_EFFECTEDITDLG_RESULT_CANCEL);

  Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_SELF);
  Dlg.SetTitleValue(_T("Edit Potion Effect"));
  Dlg.SetEffectRecord(pRecord);
  Dlg.SetEffect(pEffect);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetValidEffectMask(OB_EFFECTFLAG_SELF);
  //Dlg.SetInvalidEffectMask(OB_EFFECTFLAG_NOINGREDIANT);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditPotionEffectDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditSigilStoneEffectDlg (pRecord, pEffect, pRecordHandler);
 *
 *=========================================================================*/
int ObEditSigilStoneEffectDlg (CObSgstRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler) {
  CObEffectEditDlg  Dlg;
  int               Result;

  if (pRecord == NULL || pEffect == NULL || pRecordHandler == NULL) return (OB_EFFECTEDITDLG_RESULT_CANCEL);

  Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_SELF | OB_EFFECTEDITDLG_FLAG_TOUCH);
  Dlg.SetTitleValue(_T("Edit Sigil Stone Effect"));
  Dlg.SetEffectRecord(pRecord);
  Dlg.SetEffect(pEffect);
  Dlg.SetRecordHandler(pRecordHandler);
  //Dlg.SetValidEffectMask(OB_EFFECTFLAG_SELF | OB_EFFECTFLAG_TOUCH);
  //Dlg.SetInvalidEffectMask(OB_EFFECTFLAG_NOINGREDIANT);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditSigilStoneEffectDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObEditSpellEffectDlg (pRecord, pEffect, pRecordHandler);
 *
 *=========================================================================*/
int ObEditSpellEffectDlg (CObSpelRecord* pRecord, CObEfidSubrecord* pEffect, CObRecordHandler* pRecordHandler) {
  CObEffectEditDlg  Dlg;
  int               Result;

  if (pRecord == NULL || pEffect == NULL || pRecordHandler == NULL) return (OB_EFFECTEDITDLG_RESULT_CANCEL);

	/* Determine which range types are allowed */
  switch (pRecord->GetType()) {
    case OB_SPELLTYPE_ABILITY:
    case OB_SPELLTYPE_DISEASE:
        Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_SELF);
	break;
    case OB_SPELLTYPE_SPELL:
    case OB_SPELLTYPE_POISON:
    case OB_SPELLTYPE_POWER:
    case OB_SPELLTYPE_LESSERPOWER:
	Dlg.SetFlags(OB_EFFECTEDITDLG_FLAG_SELF | OB_EFFECTEDITDLG_FLAG_TOUCH | OB_EFFECTEDITDLG_FLAG_TARGET);
	break;
  }

  Dlg.SetTitleValue(_T("Edit Spell Effect"));
  Dlg.SetEffectRecord(pRecord);
  Dlg.SetEffect(pEffect);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetValidEffectMask(OB_EFFECTFLAG_SPELLMAKING);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function ObEditSpellEffectDlg()
 *=========================================================================*/

