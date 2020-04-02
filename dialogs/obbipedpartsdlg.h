/*===========================================================================
 *
 * File:	Obbipedpartsdlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 25, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBIPEDPARTSDLG_H
#define __OBBIPEDPARTSDLG_H


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
 * Begin Class CObBipedPartsDlg
 *
 *=========================================================================*/
class CObBipedPartsDlg : public CDialog {

  /*---------- Begin Protected Class Members ----------------*/
protected:
  dword		m_BipedParts;
  CButton	m_BipedButtons[16];


  /*---------- Begin Public Class Methods ------------------*/
public:

	/* Constructor */
  CObBipedPartsDlg(CWnd* pParent = NULL);

	/* Get class members */
  dword GetBipedParts (void) { return (m_BipedParts); }

	/* Set class members */
  void SetBipedParts (const dword Flags) { m_BipedParts = Flags; }

	/* Get/Set control data */
  void GetControlData (void);
  void SetControlData (void);


  //{{AFX_DATA(CObBipedPartsDlg)
  enum { IDD = IDD_BIPEDPARTS_DLG };
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObBipedPartsDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObBipedPartsDlg)
  virtual void OnOK();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObBipedPartsDlg
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* Show a model biped parts dialog */
  bool ObEditBipedParts (dword& BipedParts);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obbipedpartsdlg.H
 *=========================================================================*/
