/*===========================================================================
 *
 * File:	obeditDoc.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	Thursday, 27 July, 2006
 *
 * Definition of the CObEditDoc document class.
 *
 *=========================================================================*/
#ifndef __obeditDoc_H
#define __obeditDoc_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "common/csvfile.h"
  #include "modfile/obsimplerecordhandler.h"
  #include "modfile/obmultirecordhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* View update hints */
   #define OBEDIT_DOC_HINT_UPDATEALL	 8001
   #define OBEDIT_DOC_HINT_GETDATA	 8002
   #define OBEDIT_DOC_HINT_CLEARFILTERS  8003
   #define OBEDIT_DOC_HINT_UPDATEFILTERS 8004
   #define OBEDIT_DOC_HINT_UPDATERECORD  8005
   #define OBEDIT_DOC_HINT_ADDRECORD     8006

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Used for view updates */
  class obrecupdateinfo_t : public CObject {
	public:
	CObRecord*	pOldRecord;
	CObRecord*	pNewRecord;
  };
  
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditDoc Definition
 * 
 *=========================================================================*/
class CObEditDoc : public CDocument {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CObMultiRecordHandler	m_RecordHandler;

  bool			m_HasActiveContent;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:
	
	/* Create from serialization only */
  CObEditDoc();
  DECLARE_DYNCREATE(CObEditDoc)


  /*---------- Begin Public Class Methods -----------------------------*/
public:

	/* Destructor */
  virtual ~CObEditDoc();

	/* Find operations */
  dword Find (obfinddata_t& FindData, CObCallback* pCallback) { return m_RecordHandler.Find(FindData, pCallback); }

	/* Get class members */
  CObEspFile&             GetActiveFile    (void) { return (m_RecordHandler.GetActiveFile()); }
  CObGroup*		  GetTopGroup      (void) { return m_RecordHandler.GetTopGroup(); }
  CObMultiRecordHandler&  GetRecordHandler (void) { return (m_RecordHandler); }

	/* Backup methods */
  bool DoSaveBackup     (const char* pFilename);
  bool DoBackup         (const char* pFilename);
  bool MakeBackupFile   (CString& OutputFile, CString& InputFile);
  bool CreateBackupPath (void);
  bool CheckBackups     (const char* OldestFile, const dword BackupCount, const int64 BackupSize);


	/* Diagnostics */
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObEditDoc)
public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);
  virtual void DeleteContents();
  virtual BOOL OnOpenDocument (LPCTSTR lpszPathName);
  virtual BOOL OnSaveDocument (LPCTSTR lpszPathName);
  virtual BOOL DoFileSave();
  //}}AFX_VIRTUAL


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CObEditDoc)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

 };
/*===========================================================================
 *		End of Class CObEditDoc Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File obeditDoc.H
 *=========================================================================*/
