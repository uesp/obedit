/*===========================================================================
 *
 * File:	Obfinddlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 1, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObFindDlg.h"
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

  IMPLEMENT_DYNCREATE(CObFindDlg, CObRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObFindDlg, CObRecordDialog)
	//{{AFX_MSG_MAP(CObFindDlg)
	ON_BN_CLICKED(ID_FIND_BUTTON, OnFindButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Columns
 *
 *=========================================================================*/
static obreclistcolinit_t s_FindListInit[] = {
	{ OB_FIELD_EDITORID,	150,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	85,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ OB_FIELD_RECORDTYPE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
  };
/*===========================================================================
 *		End of List Columns
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Constructor
 *
 *=========================================================================*/
CObFindDlg::CObFindDlg (CWnd* pParent) : CObRecordDialog(CObFindDlg::IDD) {
	//{{AFX_DATA_INIT(CObFindDlg)
	//}}AFX_DATA_INIT

  m_BinarySize  = 0;
  m_pBinaryData = NULL;

  m_FindData.Flags     = OB_FIND_COMPARETEXT | OB_FIND_ADDRECORDS | OB_FIND_NOHEADER;
  m_FindData.pData     = NULL;
  m_FindData.DataSize  = 0;

  m_FindData.pFindRecords = m_FindList.GetRecords();
}
/*===========================================================================
 *		End of Class CObFindDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Destructor
 *
 *=========================================================================*/
CObFindDlg::~CObFindDlg () {

  if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);

  if (m_pBinaryData != NULL) {
    delete[] m_pBinaryData;
    m_pBinaryData = NULL;
  }

}
/*===========================================================================
 *		End of Class CObFindDlg Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObFindDlg::DoDataExchange (CDataExchange* pDX) {
	CObRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObFindDlg)
	DDX_Control(pDX, IDC_FIND_LABEL, m_FindLabel);
	DDX_Control(pDX, IDC_CASESENSITIVE_CHECK, m_CaseSensitiveCheck);
	DDX_Control(pDX, IDC_BINARY_CHECK, m_BinaryCheck);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_SearchCombo);
	DDX_Control(pDX, IDC_FIND_LIST, m_FindList);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObFindDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Method - void ClearControlData (void);
 *
 *=========================================================================*/
void CObFindDlg::ClearControlData (void) {

}
/*===========================================================================
 *		End of Class Method CObFindDlg::ClearControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Method - void ConvertBinaryData (void);
 *
 *=========================================================================*/
bool CObFindDlg::ConvertBinaryData (void) {
  CSString Buffer(m_TextData);
  int      Index;

  Buffer.RemoveCharsToMatch(isxdigit);
  m_TextData = Buffer;
  if (Buffer.IsEmpty()) return (false);

  if (m_pBinaryData != NULL) delete[] m_pBinaryData;
  m_BinarySize  = (Buffer.GetLength() + 1)/2;
  m_pBinaryData = new byte[m_BinarySize + 4];

  for (Index = 0; Index < Buffer.GetLength(); Index += 2) {
    m_pBinaryData[Index/2] = ConvertFromHexChar(Buffer[Index]) << 4;
    if (Index + 1 < Buffer.GetLength()) m_pBinaryData[Index/2] |= ConvertFromHexChar(Buffer[Index + 1]);
  }

  Buffer.Empty();

  for (Index = 0; Index < (int)m_BinarySize; ++Index) {
    Buffer += ConvertByteToHexChar(m_pBinaryData[Index]);
  }

  m_TextData = Buffer; 
  //SystemLog.Printf("Searching for binary data '%s' (%.*s)...", Buffer, m_BinarySize, m_pBinaryData);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObFindDlg::ConvertBinaryData()
 *=========================================================================*/

  
/*===========================================================================
 *
 * Class CObFindDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CObFindDlg::GetControlData (void) {
  CString Buffer;
  bool    Result;

	/* Set the find flags */
  m_FindData.Flags = OB_FIND_ADDRECORDS | OB_FIND_NOHEADER;
  if (!m_BinaryCheck.GetCheck())       m_FindData.Flags |= OB_FIND_COMPARETEXT;
  if (m_CaseSensitiveCheck.GetCheck()) m_FindData.Flags |= OB_FIND_CASESENSITIVE;

	/* Update the search text */
  m_SearchCombo.GetWindowText(m_TextData);

	/* Set the binary data as required */
  if (m_BinaryCheck.GetCheck()) {
    Result = ConvertBinaryData();

    if (!Result) {
      m_FindLabel.SetWindowText("Invalid hexadecimal binary data specified!");
      m_FindData.DataSize = 0;
      m_FindData.pData    = NULL;
      return;
    }

    m_FindData.DataSize = m_BinarySize;
    m_FindData.pData    = m_pBinaryData;
    m_SearchCombo.SetWindowText(m_TextData);
  }
  else {
    m_FindData.DataSize = m_TextData.GetLength();
    m_FindData.pData    = (const byte *) (const TCHAR *) m_TextData;
    if (m_FindData.DataSize == 0) m_FindLabel.SetWindowText("Nothing to find!");
  }
  
}
/*===========================================================================
 *		End of Class Method CObFindDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Method - bool IsEditRecord (pRecord);
 *
 *=========================================================================*/
bool CObFindDlg::IsEditRecord (CObRecord* pRecord) {

  return (false);
}
/*===========================================================================
 *		End of Class Method CObFindDlg::IsEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CObFindDlg::OnInitialUpdate (void) {
  CObRecordDialog::OnInitialUpdate();
  
  m_FindList.SetListName("FindList");
  m_FindList.DefaultSettings();
  m_FindList.SetupList(OB_NAME_NULL, s_FindListInit, NULL);

  m_FindList.SortList(OB_FIELD_EDITORID);

  m_pRecordHandler->GetEventHandler().AddListener(this);

  SetTitle("");
  SetControlData();
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - void OnSave (void);
 *
 *=========================================================================*/
void CObFindDlg::OnSave (void) {
  Close();
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - void OnCancel (void);
 *
 *=========================================================================*/
void CObFindDlg::OnCancel (void) {
  Close();
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - void OnApply ();
 *
 *=========================================================================*/
void CObFindDlg::OnApply() {
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnApply()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - void OnFindButton ();
 *
 *=========================================================================*/
void CObFindDlg::OnFindButton() {
  CObProgressDlg* pProgressDlg = NULL;
  CObCallback*    pCallback    = NULL;
  CString	  Buffer;
  dword		  ResultCount;
  obtimer_t	  Timer;
  double	  DeltaTime;
  int		  ListIndex;

  GetControlData();
  m_FindList.DeleteAllItems();

  if (m_FindData.DataSize == 0) return;
  
	/* TODO: Proper history */
  ListIndex = m_SearchCombo.FindStringExact(-1, m_TextData);

  if (ListIndex < 0) {
    m_SearchCombo.InsertString(0, m_TextData);
  }
  else if (ListIndex > 0) {
    m_SearchCombo.DeleteString(ListIndex);   
    m_SearchCombo.InsertString(0, m_TextData);
  }

	/* Clear the current find data */
  m_FindData.FileCount       = 0;
  m_FindData.FoundRecords    = 0;
  m_FindData.FoundSubrecords = 0;
  m_FindData.GroupCount      = 0;
  m_FindData.RecordCount     = 0;
  m_FindData.SubrecordCount  = 0;
  m_FindData.pExcludeRecords = NULL;
  

	/* Create a progress dialog */
  if (m_pRecordHandler->GetNumRecords() > 1000) {
    pProgressDlg = ShowObProgressDlg(_T("Finding..."), _T("Finding data..."));

    m_Callback.SetEnable(true);
    m_Callback.SetFunction(ObEditDefaultProgressCallback);
    m_Callback.SetUserPtr(pProgressDlg);
    m_Callback.Reset();

    pCallback = &m_Callback;
  }
 
	/* Perform the find */
  ObStartTimer(Timer);
  ResultCount = m_pRecordHandler->Find(m_FindData, pCallback);
  DeltaTime = ObEndTimer(Timer);
  
  DestroyObProgressDlg(pProgressDlg);

	/* Update the list */
  m_FindList.SetItemCountEx(m_FindData.pFindRecords->GetSize());
  m_FindList.RedrawWindow();

	/* Update the find label */
  Buffer.Format("Found %u matches in %u records (%.3f seconds).", ResultCount, m_FindData.RecordCount, DeltaTime);
  m_FindLabel.SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnFindButton()
 *=========================================================================*/


/*======================================= ====================================
 *
 * Class CObFindDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CObFindDlg::SetControlData (void) { 
  m_FindList.RedrawWindow();
}
/*===========================================================================
 *		End of Class Method CObFindDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Method - void SetTitle (pEditorID);
 *
 *=========================================================================*/
void CObFindDlg::SetTitle (const SSCHAR* pEditorID) {
  CString Buffer;

  Buffer.Format("%s -- Find", m_pDlgHandler->GetTitle());
  SetWindowText(Buffer);
  SetInternalWindowText(GetParentFrame()->m_hWnd, Buffer);
}
/*===========================================================================
 *		End of Class Method CObFindDlg::SetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - int OnListenAddRecord (pEvent);
 *
 *=========================================================================*/
int CObFindDlg::OnListenAddRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_FindList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_FindList.UpdateRecord(NULL, pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnListenAddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CObFindDlg::OnListenCleanRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_FindList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_FindList.UpdateRecord(NULL, pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindDlg Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CObFindDlg::OnListenUpdateRecord (CObListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_FindList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_FindList.UpdateRecord(NULL, pEvent->GetOldRecord());

  return (OB_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObFindDlg::OnListenUpdateRecord()
 *=========================================================================*/


