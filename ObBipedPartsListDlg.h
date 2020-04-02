/*===========================================================================
 *
 * File:	Obbipedpartslistdlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 26, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBIPEDPARTSLISTDLG_H
#define __OBBIPEDPARTSLISTDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obespfile.h"
  #include "resource.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBipedPartsListDlg Definition
 *
 *=========================================================================*/
class CObBipedPartsListDlg : public CDialog {

  /*---------- Begin Protected Class Members ----------------*/
protected:
  dword		m_BipedParts;
  CButton	m_BipedButtons[16];


  /*---------- Begin Public Class Methods ------------------*/
public:

	/* Constructor */
  CObBipedPartsListDlg(CWnd* pParent = NULL);
  
	/* Get class members */
  dword GetBipedParts (void) { return (m_BipedParts); }

	/* Set class members */
  void SetBipedParts (const dword Flags) { m_BipedParts = Flags; }

	/* Get/Set control data */
  void GetControlData (void);
  void SetControlData (void);


  //{{AFX_DATA(CObBipedPartsListDlg)
  enum { IDD = IDD_BIPEDPARTSLIST_DLG };
  CListBox	m_BipedList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObBipedPartsListDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObBipedPartsListDlg)
  virtual void OnOK();
  virtual BOOL OnInitDialog();
	afx_msg void OnDblclkBipedList();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObBipedPartsListDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* Show a model biped parts dialog */
  bool ObEditBipedPartsList (dword& BipedParts);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obbipedpartslistdlg.H
 *=========================================================================*/
