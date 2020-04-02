/*===========================================================================
 *
 * File:	Obeditdlghandler.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 25, 2006
 *
 * Defines the CObEditDlgHandler class used for handling all child windows
 * to the main view.
 *
 *=========================================================================*/
#ifndef __OBEDITDLGHANDLER_H
#define __OBEDITDLGHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obmultirecordhandler.h"
  #include "obrecorddialog.h"
  #include "../childfrm.h"
  #include "resource.h"
  #include "../obresourceview.h"

  #include "obpromptdlg.h"
  #include "obinputdialog.h"

  #include "obselectrecorddlg.h"
  #include "obcntoeditdlg.h"
  #include "oblvleditdlg.h"
  #include "obeffecteditdlg.h"

  #include "obbatcheditdlg.h"
  #include "obfinddlg.h"

  #include "obactiview.h"
  #include "obalchview.h"
  #include "obammoview.h"
  #include "obappaview.h"
  #include "obarmorview.h"
  #include "obbookview.h"
  #include "obclotview.h"
  #include "obcontview.h"
  #include "obenchview.h"
  #include "obflorview.h"
  #include "obfurnview.h"
  #include "obingrview.h"
  #include "obkeymview.h"
  #include "oblighview.h"
  #include "oblvspview.h"
  #include "oblvlcview.h"
  #include "oblvliview.h"
  #include "obmiscview.h"
  #include "obscptview.h"
  #include "obsgstview.h"
  #include "obslgmview.h"
  #include "obspelview.h"
  #include "obsounview.h"
  #include "obstatview.h"
  #include "obweapview.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Record rename/copy results */
  #define OBEDIT_RECORDPROMPT_CANCEL	0
  #define OBEDIT_RECORDPROMPT_COPY	1
  #define OBEDIT_RECORDPROMPT_RENAME	2

	/* Flags for the ObFillComboList function */
  #define OBE_FILLCOMBO_NODUPLICATES	1
  #define OBE_FILLCOMBO_INCLUDENULL	2
  #define OBE_FILLCOMBO_FORCEEMPTY	4

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Used to create a dialog */
  struct obdlgcreateinfo_t {
	const obrectype_t*	pRecordType;
	const TCHAR*		pTitlePrefix;
	int			ResourceID;
	CRuntimeClass*		pViewClass;
	CRuntimeClass*		pFrameClass;
	const TCHAR*		pUESPPage;
	const TCHAR*		pCSPage;
  };

	/* Holds information about a currently open dialog */
  struct obdlginfo_t {
	CFrameWnd*		pFrameWnd;		/* The frame window object for the dialog */
	obdlgcreateinfo_t*	pCreateInfo;		/* The creation informatio used to create the dialog */
	CObRecordDialog*	pRecordDlg;		/* The object for a record dialog */

  };

  typedef CObPtrArray<obdlginfo_t> CObDlgInfoArray;

	/* Forward class definitions */
  class CObEditDoc;

	/* Options */
  struct obdlghandleroptions_t {
	bool		EnableWebHelp;
	bool		UseUESPWikiHelp;
	CSString	CSWikiPrefix;
	CSString	UESPWikiPrefix;
	CSString	DefaultCSPage;
	CSString	DefaultUESPPage;

	obdlghandleroptions_t() {
		EnableWebHelp   = true;
		UseUESPWikiHelp = true;
		CSWikiPrefix    = "http://cs.elderscrolls.com/constwiki/index.php/";
		UESPWikiPrefix  = "http://www.uesp.net/wiki/";
		DefaultCSPage   = "";
		DefaultUESPPage = "Tes4Mod:ObEdit";
	}
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEditDlgHandler Definition
 *
 * Handles all child windows of the main view (record dialogs, find, etc...).
 *
 *=========================================================================*/
class CObEditDlgHandler : public IObListener {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObDlgInfoArray	m_OpenDialogs;		/* List of currently open dialogs */

  CObEditDoc*		m_pDocument;		/* Current document */

	/* Dialog handler options */
  static obdlghandleroptions_t m_Options;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper close method */
  void Close (obdlginfo_t* pDlgInfo);

	/* Creates a new dialog according to the given creation info */
  obdlginfo_t* CreateDlg (obdlgcreateinfo_t& CreateInfo);
  obdlginfo_t* CreateDlg (const obrectype_t  RecordType);
  obdlginfo_t* CreateDlg (obeditrecinfo_t&   EditInfo);

  	/* Find an open dialog */
  obdlginfo_t* FindOpenDlg (CFrameWnd*       pFrameWnd);
  obdlginfo_t* FindOpenDlg (CObRecord*       pRecord);
  obdlginfo_t* FindOpenDlg (CRuntimeClass*   pRuntimeClass);
  obdlginfo_t* FindOpenDlg (CObRecordDialog* pRecordDlg);

	/* Finds a creation object for the given record type */
  static obdlgcreateinfo_t* FindCreateInfo (const obrectype_t RecordType);



  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEditDlgHandler();
  virtual ~CObEditDlgHandler() { Destroy(); }
  virtual void Destroy (void);

	/* Batch edit a group of similar records */
  bool BatchEdit (CObRefRecordArray& Records);

	/* Force all open dialogs to close */
  void  CloseAll (void);
  dword CloseAll (CObRecord* pRecord, const long Source = 0);

	/* Edits a record */
  bool EditRecord    (obeditrecinfo_t&  EditInfo);
  bool EditRecord    (CObRecord*        pRecord);
  bool EditRecord    (const obformid_t  FormID);
  bool EditNewRecord (const obrectype_t RecordType);

	/* Get class members */
  CObEditDoc*  GetDocument (void) { return (m_pDocument); }
  const TCHAR* GetTitle    (void); 

	/* Access the static options member */
  static obdlghandleroptions_t& GetOptions (void) { return (m_Options); }

	/* Record edit events */
  virtual int OnPreSaveRecord    (obeditrecinfo_t& EditInfo);
  virtual int OnPostSaveRecord   (obeditrecinfo_t& EditInfo);
  virtual int OnCancelEditRecord (obeditrecinfo_t& EditInfo);

	/* Other events */
  virtual bool OnHelp (CObRecordDialog* pDialog, HELPINFO* pHelpInfo);

  	/* Listener events */
  virtual int OnListenAddRecord       (CObListenEvent* pEvent);
  virtual int OnListenCleanRecord     (CObListenEvent* pEvent);
  virtual int OnListenUpdateRecord    (CObListenEvent* pEvent);
  virtual int OnListenPreUpdateRecord (CObListenEvent* pEvent);
  virtual int GetListenEvents         (void) { return (OB_EVENTMASK_ALL); }

	/* Prompt user to rename or copy a changed record */
  int PromptRenameCopy (obeditrecinfo_t& EditInfo);

	/* Remove a frame from the list of currently opened frames */
  void RemoveFrame (CFrameWnd* pFrameWnd);

	/* Open a find dialog */
  bool OpenFind (void);

  	/* Set class members */
  void SetDocument (CObEditDoc* pDoc) { m_pDocument = pDoc; }

	/* Item selection dialogs */
  bool SelectItemScript     (CString& EditorID);
  bool SelectActor          (CString& EditorID);
  bool SelectApparelEnchant (CString& EditorID);
  bool SelectIngrediant     (CString& EditorID);
  bool SelectScrollEnchant  (CString& EditorID);
  bool SelectSound          (CString& EditorID);
  bool SelectStaffEnchant   (CString& EditorID);
  bool SelectWeaponEnchant  (CString& EditorID);

	/* Resource selection */
  bool SelectModel     (const char* pString);
  bool SelectIcon      (const char* pString);
  bool SelectSoundFile (const char* pString);

};
/*===========================================================================
 *		End of Class CObEditDlgHandler Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

	/* Find items in a list */
  int FindListBoxItemData  (CListBox&  ListBox,  const dword ItemData, const bool SelectItem = false);
  int FindComboBoxItemData (CComboBox& ComboBox, const dword ItemData, const bool SelectItem = false);
  int FindComboBoxEffect   (CComboBox& ComboBox, const obrectype_t EffectType, const bool SelectItem = false);
  int FindComboBoxString   (CComboBox& ComboBox, const TCHAR* pString, const bool SelectItem = false);
  int ObAddComboBoxItem    (CComboBox& ComboBox, const TCHAR* pString, const dword ItemData);
  int ObAddListBoxItem     (CListBox&  ListBox,  const TCHAR* pString, const dword ItemData);

  dword GetComboBoxSelItemData (CComboBox& ComboBox, const dword Default = 0);
  dword GetListBoxSelItemData  (CListBox&  ListBox,  const dword Default = 0);

	/* Create list contents */
  bool ObFillComboList       (CComboBox& ComboBox, const stringvalue_t* pStringValues, const dword Flags);
  bool ObFillEffectComboList (CComboBox& ComboBox, const dword Flags, const dword EffectFlagMask, const dword InvalidEffectFlagMask);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obeditdlghandler.H
 *=========================================================================*/
