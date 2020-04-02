/*===========================================================================
 *
 * File:	Obloaddlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 28, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBLOADDLG_H
#define __OBLOADDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obespfile.h"
  #include "common/obutils.h"
  #include "modfile/obmultirecordhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* File list subitems indices */
  #define OBFILELIST_FILENAME     0
  #define OBFILELIST_DATE         1
  #define OBFILELIST_SIZE         2
  #define OBFILELIST_DEFAULTSORT  3

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  struct obloadfilesortinfo_t {
	bool Reverse;
	int  SortType;
  };

	/* Used to hold information of files in the list */
  struct obloaddlgfileinfo_t {
	WIN32_FIND_DATA FindData;
	bool		IsActive;
	bool		IsMaster;
  };

  typedef CObPtrArray<obloaddlgfileinfo_t>    CObLoadDlgFileInfos;
  typedef CObRefPtrArray<obloaddlgfileinfo_t> CObRefLoadDlgFileInfos;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLoadDlg Definition
 *
 *=========================================================================*/
class CObLoadDlg : public CDialog {

  /*---------- Protected Class Members ---------------------------------*/
protected:
  CObLoadDlgFileInfos	m_FileInfos;		/* Holds file information */
  obloaddlgfileinfo_t*  m_pLastActiveFile;

  obfileloadinfo_t	m_LoadInfo;

  CString		m_FilePath;
  bool			m_LastSortReverse;
  int			m_LastSortSubItem;


  /*---------- Protected Class Methods ---------------------------------*/
protected:

	/* Populate the file list with plugins */
  void FillFileList (void);
  int  FillFileList (const char* pFileSpec);
  void AddFile      (WIN32_FIND_DATA& FindData);
  void UpdateFile   (const int ListIndex, obloaddlgfileinfo_t* pFileData);

	/* Create the loadinfo structure from the current list */
  void CreateLoadInfo (void);


  /*---------- Public Class Methods ------------------------------------*/
public:

	/* Construction */
  CObLoadDlg (CWnd* pParent = NULL);

	/* Get class members */
  obfileloadinfo_t& GetLoadInfo (void) { return (m_LoadInfo); }

	/* Dialog Data */
  //{{AFX_DATA(CObLoadDlg)
  enum { IDD = IDD_LOAD_DLG };
  CListCtrl	m_FileList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObLoadDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObLoadDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnColumnclickFileList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDblclkFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetactive();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CObLoadDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obloaddlg.H
 *=========================================================================*/
