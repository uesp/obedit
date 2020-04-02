/*===========================================================================
 *
 * File:	ObScriptErrors.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	December 17, 2006
 *
 * 
 *
 *=========================================================================*/
#ifndef __OBSCRIPTERRORS_H
#define __OBSCRIPTERRORS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../tes4lib/modfile/records/obscptrecord.h"
  #include "../tes4lib/modfile/compiler/tokentypearray.h"
  #include "../tes4lib/common/dl_map.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Error and warning levels */
  #define OB_SCRIPTERROR_LEVEL_NONE	0
  #define OB_SCRIPTERROR_LEVEL_INFO	1
  #define OB_SCRIPTERROR_LEVEL_WARNING	3
  #define OB_SCRIPTERROR_LEVEL_ERROR	5

	/* Helper error definition macros */
  #define DEFOBSCRIPTNONE(ID, pString)    { OB_SCRIPT_ERROR_##ID, #ID, OB_SCRIPTERROR_LEVEL_NONE,    pString }, 
  #define DEFOBSCRIPTNOTE(ID, pString)    { OB_SCRIPT_ERROR_##ID, #ID, OB_SCRIPTERROR_LEVEL_INFO,    pString }, 
  #define DEFOBSCRIPTERROR(ID, pString)   { OB_SCRIPT_ERROR_##ID, #ID, OB_SCRIPTERROR_LEVEL_ERROR,   pString }, 
  #define DEFOBSCRIPTWARNING(ID, pString) { OB_SCRIPT_ERROR_##ID, #ID, OB_SCRIPTERROR_LEVEL_WARNING, pString }, 

	/* Error and warning IDs */
  #define OB_SCRIPT_ERROR_NONE			0
  #define OB_SCRIPT_ERROR_BADTOKEN		100
  #define OB_SCRIPT_ERROR_BADSCRIPTSIZE		101
  #define OB_SCRIPT_ERROR_LOCALREDEFSAME	102
  #define OB_SCRIPT_ERROR_LOCALREDEFDIFF	103
  #define OB_SCRIPT_ERROR_BADBLOCKFUNCTION	104
  #define OB_SCRIPT_ERROR_MISSINGPARAMETER	105
  #define OB_SCRIPT_ERROR_EXTRAPARAMETER	106
  #define OB_SCRIPT_ERROR_BADCRIMETYPE		107
  #define OB_SCRIPT_ERROR_BADFORMTYPE		108
  #define OB_SCRIPT_ERROR_BADVARIABLENAME	109
  #define OB_SCRIPT_ERROR_NOTPERSISTENT		110
  #define OB_SCRIPT_ERROR_BADQUESTSTAGE		111
  #define OB_SCRIPT_ERROR_BADANIMATIONGROUP	112
  #define OB_SCRIPT_ERROR_BADACTORVALUE		113
  #define OB_SCRIPT_ERROR_BADAXIS		114
  #define OB_SCRIPT_ERROR_FLOATTOINTEGER	115
  #define OB_SCRIPT_ERROR_BADINTEGER		116
  #define OB_SCRIPT_ERROR_BADFLOAT		117
  #define OB_SCRIPT_ERROR_BADSTRING		118
  #define OB_SCRIPT_ERROR_BADIDENTIFIER		119
  #define OB_SCRIPT_ERROR_BADLOCAL		120
  #define OB_SCRIPT_ERROR_UNDEFINEDVARIABLE	121
  #define OB_SCRIPT_ERROR_BADEXPRESSION		122
  #define OB_SCRIPT_ERROR_BADFUNCTION		123
  #define OB_SCRIPT_ERROR_BADREFERENCE		124
  #define OB_SCRIPT_ERROR_NAMECONFLICT		125
  #define OB_SCRIPT_ERROR_NONREFFUNCTION	126
  #define OB_SCRIPT_ERROR_MAXMESSAGEPARAMS	127
  #define OB_SCRIPT_ERROR_MAXMESSAGEBUTTONS	128
  #define OB_SCRIPT_ERROR_EXTRASTOPCOMBATPARAM 	129
  #define OB_SCRIPT_ERROR_BADGAMESETTING	130
  #define OB_SCRIPT_ERROR_BADMESSAGEFORMAT	131
  #define OB_SCRIPT_ERROR_MISSINGMESSAGEVAR	132
  #define OB_SCRIPT_ERROR_EXTRAMESSAGEVAR	133
  #define OB_SCRIPT_ERROR_INTERNAL		134
  #define OB_SCRIPT_ERROR_UNKNOWNCRIMETYPE	135
  #define OB_SCRIPT_ERROR_UNKNOWNQUESTSTAGE	136
  #define OB_SCRIPT_ERROR_BADGENDER		137
  #define OB_SCRIPT_ERROR_UNKNOWNRECORD		138
  #define OB_SCRIPT_ERROR_MAXLOCALS		139
  #define OB_SCRIPT_ERROR_BADPARAMETER		140
  #define OB_SCRIPT_ERROR_BADCHARACTER		141

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Script error/warning definition */
  struct obscripterrordef_t {
	int         ID;
	const char* pName;
	int         Level;
	const char* pDescription;
  };

	/* Map of error definitions */
  typedef TGenRefPtrMap<int,      obscripterrordef_t, int>         CObScriptErrorIdMap;
  typedef TGenRefPtrMap<CSString, obscripterrordef_t, const char*> CObScriptErrorNameMap;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScriptError Definition
 *
 * Holds information on a single script error or warning.
 *
 *=========================================================================*/
class CObScriptError {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  int			m_ID;			/* Error/warning ID */
  CSString		m_Message;		/* Custom error message */
  tokeninstance_t*	m_pToken;		/* Token where the error occurred */ 
  obscripterrordef_t*   m_pErrorDef;
  sourcepos_t           m_Position;

  int			m_UserData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObScriptError();
  //virtual ~CObScriptError() { Destroy(); }
  //virtual void Destroy (void);

	/* Format a message string */
  void FormatMessage  (const char* pString, ...);
  void FormatMessageV (const char* pString, va_list Args);

	/* Get class members */
  int                 GetID       (void) { return (m_ID); }
  int                 GetUserData (void) { return (m_UserData); }
  const char*         GetMessage  (void) { return (m_Message); }
  tokeninstance_t*    GetToken    (void) { return (m_pToken); }
  obscripterrordef_t* GetErrorDef (void) { return (m_pErrorDef); }
  sourcepos_t         GetPosition (void) { return (m_Position); }
  int                 GetLevel    (void) { return (m_pErrorDef ? m_pErrorDef->Level : OB_SCRIPTERROR_LEVEL_ERROR); }
  int                 GetLinePos  (void) { return (m_pToken ? m_pToken->StartPos.LinePos : m_Position.LinePos); }
  int                 GetCharPos  (void) { return (m_pToken ? m_pToken->StartPos.CharPos : m_Position.CharPos); }

  const char* MakeErrorString (void);

	/* Set class members */
  void SetID       (const int           Value)   { m_ID        = Value; }
  void SetUserData (const int           Value)   { m_UserData  = Value; }
  void SetMessage  (const char*         pString) { m_Message   = pString; }
  void SetToken    (tokeninstance_t*    pToken)  { m_pToken    = pToken; }
  void SetErrorDef (obscripterrordef_t* pError)  { m_pErrorDef = pError; }
  void SetPosition (const sourcepos_t   Pos)     { m_Position  = Pos; }

};

	/* Arrays of errors */
  typedef CObPtrArray<CObScriptError>     CObScriptErrorArray;
  typedef CObRefPtrArray<CObScriptError>  CObRefScriptErrorArray;

  struct obscripterrorinfo_t {
	CObScriptErrorArray	Errors;
	dword			ErrorCount;
	dword			WarningCount;
  };

/*===========================================================================
 *		End of Class CObScriptError Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  extern obscripterrordef_t g_ObScriptErrorDefs[];

	/* Lookup script error definitions */
  obscripterrordef_t* ObGetScriptErrorDef (const int   ID);
  obscripterrordef_t* ObGetScriptErrorDef (const char* pName);

  void ObSetScriptErrorLevel (const char* pName, const int Level);

  void ObOutputScriptErrorsToLog (CObScriptErrorArray& Errors);

/*===========================================================================
 *		End of Class CObScriptError Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObScriptErrors.H
 *=========================================================================*/
