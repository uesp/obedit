/*===========================================================================
 *
 * File:	Obfiletreedlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 4, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBFILETREEDLG_H
#define __OBFILETREEDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObFileTreeDlg
 *
 *=========================================================================*/
class CObFileTreeDlg : public CDialog {

  /*---------- Begin Protected Class Members ----------------------*/
protected:
  //CObEspFile*	m_pEspFile;
  CObGroup*	m_pTopGroup;


  /*---------- Begin Protected Class Methods ----------------------*/
protected:  

	/* Create the tree contents */
  void CreateTree (void);
  void CreateTree (CObGroup* pTopGroup, HTREEITEM hParent);

  void AddTreeRecord        (CObBaseRecord* pBaseRecord, HTREEITEM hParent);
  void AddTreeGroupChildren (CObGroup* pGroup, HTREEITEM hParent);

  void AddTreeGroup       (CObGroup*       pGroup, HTREEITEM hParent);
  void AddTreeTypeGroup   (CObTypeGroup*   pGroup, HTREEITEM hParent);
  void AddTreeFormIDGroup (CObFormIDGroup* pGroup, HTREEITEM hParent);
  void AddTreeBlockGroup  (CObBlockGroup*  pGroup, HTREEITEM hParent);
  void AddTreeGridGroup   (CObGridGroup*   pGroup, HTREEITEM hParent);



  /*---------- Begin Public Class Methods -------------------------*/
public:

	/* Constructor */
  CObFileTreeDlg(CWnd* pParent = NULL);

	/* Set class members */
  //void SetEspFile (CObEspFile* pFile) { m_pEspFile = pFile; }
  void SetTopGroup (CObGroup* pGroup) { m_pTopGroup = pGroup; }


	/* Dialog Data */
  //{{AFX_DATA(CObFileTreeDlg)
  enum { IDD = IDD_FILETREE_DLG };
  CTreeCtrl	m_FileTree;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObFileTreeDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObFileTreeDlg)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObFileTreeDlg
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obfiletreedlg.H
 *=========================================================================*/
