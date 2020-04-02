/*===========================================================================
 *
 * File:	Obfindbinarydlg.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 29, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obedit.h"
#include "ObFindBinaryDlg.h"



/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFindBinaryDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObFindBinaryDlg, CDialog)
	//{{AFX_MSG_MAP(CObFindBinaryDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObFindBinaryDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindBinaryDlg Constructor
 *
 *=========================================================================*/
CObFindBinaryDlg::CObFindBinaryDlg(CWnd* pParent) : CDialog(CObFindBinaryDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CObFindBinaryDlg)
	//}}AFX_DATA_INIT
}
/*===========================================================================
 *		End of Class CObFindBinaryDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindBinaryDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CObFindBinaryDlg::DoDataExchange (CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CObFindBinaryDlg)
	DDX_Control(pDX, IDC_BINARYDATA_TEXT, m_BinaryDataText);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CObFindBinaryDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindBinaryDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CObFindBinaryDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	return (TRUE);
}
/*===========================================================================
 *		End of Class Event CObFindBinaryDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFindBinaryDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CObFindBinaryDlg::OnOK() {

  m_BinaryDataText.GetWindowText(m_BinaryData);
  m_BinaryData.TrimLeft(" \t");
  m_BinaryData.TrimRight(" \t");

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CObFindBinaryDlg::OnOK()
 *=========================================================================*/
