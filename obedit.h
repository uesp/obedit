/*===========================================================================
 *
 * File:	obedit.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Main header file for the OBEDIT application.
 *
 *=========================================================================*/
#ifndef __OBEDIT_H
#define __OBEDIT_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

  #include "resource.h"
  #include "modfile/obespfile.h"
  #include "obprogressdlg.h"
  #include "windows/obrecordfilter.h"
  #include "oberrordlg.h"
  #include "modfile/obmultirecordhandler.h"
  #include "common/obconfigfile.h"
  #include "bsafile/obresourcehandler.h"
  #include "mainfrm.h"
  #include "obresourceview.h"
  #include "modfile/compiler/customcompiler.h"
/*===========================================================================
 *		End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default options filename */
  #define OBEDIT_OPTIONS_FILE "obedit.ini"

	/* Default colors */
  #define OBEDIT_COLOR_GRAY RGB(212,208,200)

	/* Base registry section */
  #define OBEDIT_REGISTRY_BASE "Software\\UESP\\obedit\\"

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEditApp Definition
 *
 *=========================================================================*/
class CObEditApp : public CWinApp {

  /*---------- Begin Protected Class Members -----------------------*/
protected:
  CMainFrame*		m_pMainFrame;

  obfileloadinfo_t*	m_pCurrentLoadInfo;		/* Used when loading a file */
  CObProgressDlg*	m_pCurrentProgressDlg;
  CObCallback*		m_pCurrentLoadCallback;

  CObConfigFile		m_ConfigFile;

  CSString		m_AppPath;

  dword			m_NewFileIndex;

  CObResourceHandler	m_ResourceHandler;
  CObBsaFileArray	m_BsaFiles;
  bool			m_InitResourceHandler;


  /*--------- Begin Public Class Methods ---------------------------*/
public:

	/* Class Constructor */
  CObEditApp();
  virtual ~CObEditApp();

	/* Get class members */
  obfileloadinfo_t*  GetCurrentLoadInfo     (void) { return (m_pCurrentLoadInfo); }
  CObProgressDlg*    GetCurrentProgressDlg  (void) { return (m_pCurrentProgressDlg); }
  CObCallback*       GetCurrentLoadCallback (void) { return (m_pCurrentLoadCallback); }
  CObConfigFile&     GetConfigFile          (void) { return (m_ConfigFile); }
  const char*        GetAppPath             (void) { return (m_AppPath); }

	/* Load/save/update options */
  bool LoadOptions              (const TCHAR* pFilename);
  bool SaveOptions              (const TCHAR* pFilename);
  void UpdateOptions            (const bool Set);
  void UpdateScriptColorOptions (CCustomCompiler& Compiler, const bool Set);
  void UpdateScriptErrorOptions (const bool Set);
  void ResolveOptionPaths       (void);

  bool OpenWebHelp (const char* pPage);

  void             OpenResourceView    (const char* pResource);
  CFrameWnd*       FindResourceView    (void);
  bool             InitResourceHandler (void);
  CObResourceView* CreateResourceView  (void);
  CObResourceView* OpenResourceView    (void);


  void ResetListState (void);


  bool AddBsaFile      (const char* pFilename);
  //bool AddResourcePath (const char* pFilename);

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObEditApp)
public:
  virtual BOOL InitInstance();
  virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
  virtual int ExitInstance();
  //}}AFX_VIRTUAL

public:
  //{{AFX_MSG(CObEditApp)
  afx_msg void OnAppAbout();
  afx_msg void OnFileOpen();
  //}}AFX_MSG


  DECLARE_MESSAGE_MAP()
 };
/*===========================================================================
 *		End of Class CObEditApp Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin External Definitions
 *
 *=========================================================================*/

  CObEditApp&    GetObEditApp        (void);
  CObConfigFile& GetObEditConfigFile (void);

  bool ObEditShowError     (const dword Flags, const TCHAR* pTitle, const TCHAR* pString, ...);
  bool ObEditShowError     (const TCHAR* pTitle, const TCHAR* pString, ...);
  bool ObEditShowError     (const TCHAR* pString, ...);
  bool ObEditShowLastError (const TCHAR* pString, ...);

  bool OpenWebPage (const char* pAddress);

  void ObLockUndoUpdates (const bool Lock);

  void WINAPI SetInternalWindowText(HWND hwnd, LPCTSTR lpText);

/*===========================================================================
 *		End of External Definitions
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Root.H
 *=========================================================================*/
