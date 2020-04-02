/*===========================================================================
 *
 * File:	Obscptview.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 5, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSCPTVIEW_H
#define __OBSCPTVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/obrecorddialog.h"
  #include "modfile/compiler/customcompiler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  struct obscptoptions_t {
	CSString	FontName;
	int             FontSize;

	int		TabSize;

	COLORREF	DefaultForeColor;
	COLORREF	DefaultBackColor;

        obscptoptions_t() {
		FontName = "FixedSys";
		FontSize = 90;
		TabSize  = 5;
		DefaultForeColor = RGB(255, 255, 255);
		DefaultBackColor = RGB(0, 0, 0);
	}
  };

  class CObScriptErrorView;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScptView Definition
 *
 *=========================================================================*/
class CObScptView : public CObRecordDialog {
  DECLARE_DYNCREATE(CObScptView);
  DECLARE_OBRECUIFIELDS();

  /*---------- Begin Protected Class Methods ------------------------*/
protected:
  CFont			m_Font;
  CObScptRecord		m_CopyRecord;

  CCustomCompiler	m_Compiler;

  CObScriptErrorView*   m_pErrorView;

public:
  static obscptoptions_t m_Options;


  /*---------- Begin Protected Class Methods ------------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CObScptView();

	/* Update the editor ID in the edit info structure */
  virtual int UpdateEditorID (void);
  bool FindScriptEditorID (CString& Buffer);

  void GetCurrentWord (CString& Buffer);


  /*---------- Begin Public Class Methods ---------------------------*/
public:

	/* Get and set data */
  virtual void  GetControlData   (void);
  virtual void  GetCompileData   (CObScptRecord* pScript);
  virtual void  SetControlData   (void);

  CCustomCompiler& GetCompiler (void) { return (m_Compiler); }

  void SetErrorView (CObScriptErrorView* pView) { m_pErrorView = pView; }

  void SelectFromError (CObScriptError* pError);

  //{{AFX_DATA(CObScptView)
  enum { IDD = IDD_SCPT_VIEW };
  CEdit		m_StatusText;
  CComboBox	m_TypeList;
  CRichEditCtrl	m_ScriptText;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObScptView)
protected:
  virtual void DoDataExchange (CDataExchange* pDX);
  virtual void OnInitialUpdate (void);
  //}}AFX_VIRTUAL

protected:
  virtual ~CObScptView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CObScptView)
  afx_msg void OnSize (UINT Type, int cx, int cy);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnCompileButton();
  afx_msg void OnSelchangeScriptText(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnChangeScriptText();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObScptView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obscptview.H
 *=========================================================================*/
