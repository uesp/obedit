/*===========================================================================
 *
 * File:	ObscriptErrors.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	December 18, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obscripterrors.h"


/*===========================================================================
 *
 * Begin Script Error and Warning Definitions
 *
 *=========================================================================*/
obscripterrordef_t g_ObScriptErrorDefs[] = {
	DEFOBSCRIPTERROR( NONE,			"No error occurred!")
		
	DEFOBSCRIPTERROR( BADTOKEN,		"Bad or unexpected script token found!")		
	DEFOBSCRIPTERROR( BADSCRIPTSIZE,	"Exceeded the maximum allowable compiled script size!")	
	DEFOBSCRIPTWARNING( LOCALREDEFSAME,	"A local variable was redefined as the same type! The redefinition will be ignored.")	
	DEFOBSCRIPTERROR( LOCALREDEFDIFF,	"A local variable has been redefined as different type!")	
	DEFOBSCRIPTERROR( BADBLOCKFUNCTION,	"Invalid function found in a 'begin' block!")	
	DEFOBSCRIPTERROR( MISSINGPARAMETER,	"Missing a required function parameter!")	
	DEFOBSCRIPTERROR( EXTRAPARAMETER,	"An extra function parameter was found!")	
	DEFOBSCRIPTERROR( BADCRIMETYPE,		"Invalid crime type value found!")
	DEFOBSCRIPTERROR( BADFORMTYPE,		"Unknown or invalid form type value found!")
	DEFOBSCRIPTERROR( BADVARIABLENAME,	"Unknown or invalid variable name found!")
	DEFOBSCRIPTWARNING( NOTPERSISTENT,	"A non-persistent reference was used in a script!")
	DEFOBSCRIPTWARNING( BADQUESTSTAGE,	"Invalid quest stage value was found!")
	DEFOBSCRIPTERROR( BADANIMATIONGROUP,	"Unknown or invalud animation group value was found!")
	DEFOBSCRIPTERROR( BADACTORVALUE,	"Unknown or invalid actor value was found!")
	DEFOBSCRIPTERROR( BADAXIS,		"Unknown or invalid axis value was found!")	
	DEFOBSCRIPTWARNING( FLOATTOINTEGER,	"A floating point value was converted to an integer which may result in lost precision!")
	DEFOBSCRIPTERROR( BADINTEGER,		"Invalid integer value found!")	
	DEFOBSCRIPTERROR( BADFLOAT,		"Invalid float value found!")	
	DEFOBSCRIPTERROR( BADSTRING,		"Invalid string value found!")	
	DEFOBSCRIPTERROR( BADIDENTIFIER,	"Unknown or invalid identifier found!")	
	DEFOBSCRIPTERROR( BADLOCAL,		"Unknown or invalid local variable found!")	
	DEFOBSCRIPTERROR( UNDEFINEDVARIABLE,	"Undefined global or local variable found!")
	DEFOBSCRIPTERROR( BADEXPRESSION,	"Invalid expression found!")	
	DEFOBSCRIPTERROR( BADFUNCTION,		"Unknown or invalid function found!")	
	DEFOBSCRIPTERROR( BADREFERENCE,		"Unknown or invalid reference call found!")	
	DEFOBSCRIPTWARNING( NAMECONFLICT,	"Variable name conflicts with a record editor ID!")	
	DEFOBSCRIPTWARNING( NONREFFUNCTION,	"A non-reference function was called with a reference!")
	DEFOBSCRIPTERROR( MAXMESSAGEPARAMS,	"Exceeded the maximum number of messagebox parameters!")
	DEFOBSCRIPTERROR( MAXMESSAGEBUTTONS,	"Exceeded the maximum number of messagebox buttons!")
	DEFOBSCRIPTWARNING( EXTRASTOPCOMBATPARAM,"Ignoring an extra parameter used with the StopCombat function!")	
	DEFOBSCRIPTERROR( BADGAMESETTING,	"Unknown or invalid game setting value found!")
	DEFOBSCRIPTERROR( BADMESSAGEFORMAT,	"Possibly invalid messagebox format string found!")
	DEFOBSCRIPTERROR( MISSINGMESSAGEVAR,	"Missing a required messagebox output variable!")
	DEFOBSCRIPTERROR( EXTRAMESSAGEVAR,	"An extra output variable was used in a messagebox function call!")
	DEFOBSCRIPTERROR( INTERNAL,		"An internal compiler error has occurred!")
	DEFOBSCRIPTWARNING( UNKNOWNCRIMETYPE,	"Unknown crime type value found!")
	DEFOBSCRIPTWARNING( UNKNOWNQUESTSTAGE,	"Unknown quest stage value found!")
	DEFOBSCRIPTERROR( BADGENDER,		"Invalid gender value found!")
	DEFOBSCRIPTERROR( UNKNOWNRECORD,	"Unknown record identifier found!")
	DEFOBSCRIPTERROR( MAXLOCALS,		"Exceeded the maximum number of allowed local variable definitions!")
	DEFOBSCRIPTERROR( BADPARAMETER,		"Invalid function parameter found!")
	DEFOBSCRIPTERROR( BADCHARACTER,         "Unknown or invalid character found!")
		
	{ 0, NULL, 0, NULL }
};

	/* Error definition maps */
  CObScriptErrorIdMap    g_ObScriptErrorIDMap;
  CObScriptErrorNameMap  g_ObScriptErrorNameMap;
  bool                   g_InitScriptErrorMaps = false;

/*===========================================================================
 *		End of Script Error and Warning Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptError Constructor
 *
 *=========================================================================*/
CObScriptError::CObScriptError() {
  m_ID        = 0;
  m_UserData  = 0;
  m_pToken    = NULL;
  m_pErrorDef = NULL;
  m_Position.CharPos = 0;
  m_Position.LinePos = 0;
}
/*===========================================================================
 *		End of Class CObScriptError Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptError Method - void FormatMessage (pString, ...);
 *
 *=========================================================================*/
void CObScriptError::FormatMessage (const char* pString, ...) {
  va_list Args;

  va_start(Args, pString);
  FormatMessageV(pString, Args);
  va_end(Args);
}
/*===========================================================================
 *		End of Class Method CObScriptError::FormatMessage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptError Method - void FormatMessageV (pString, Args);
 *
 *=========================================================================*/
void CObScriptError::FormatMessageV (const char* pString, va_list Args) {
  m_Message.FormatV(pString, Args);
}
/*===========================================================================
 *		End of Class Method CObScriptError::FormatMessageV()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptError Method - const char* MakeErrorString (void);
 *
 *=========================================================================*/
const char* CObScriptError::MakeErrorString (void) {
  static CSString s_Buffer;
  bool            IsError = ! (GetLevel() <= OB_SCRIPTERROR_LEVEL_WARNING);

  if (GetToken() == NULL) {
    s_Buffer.Format("%d, %d: %s: %s", m_Position.LinePos + 1, m_Position.CharPos + 1, IsError ? "Error" : "Warning", GetMessage());
  }
  else {
    s_Buffer.Format("%d, %d: %s: %s", GetToken()->StartPos.LinePos + 1, GetToken()->StartPos.CharPos + 1,
			 IsError ? "Error" : "Warning", GetMessage());
  }

  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method CObScriptError::MakeErrorString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObInitScriptErrorMaps (void);
 *
 *=========================================================================*/
bool ObInitScriptErrorMaps (void) {
  dword Index;

	/* Clear the current map contents */
  g_ObScriptErrorIDMap.Destroy();
  g_ObScriptErrorNameMap.Destroy();

  for (Index = 0; g_ObScriptErrorDefs[Index].pName != NULL; ++Index) {
    g_ObScriptErrorIDMap.SetAt  (g_ObScriptErrorDefs[Index].ID,    &g_ObScriptErrorDefs[Index]);
    g_ObScriptErrorNameMap.SetAt(g_ObScriptErrorDefs[Index].pName, &g_ObScriptErrorDefs[Index]);
  }
   
  g_InitScriptErrorMaps = true;
  return (true);
}
/*===========================================================================
 *		End of Function ObInitScriptErrorMaps()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obscripterrordef_t* ObGetScriptErrorDef (ID);
 *
 *=========================================================================*/
obscripterrordef_t* ObGetScriptErrorDef (const int ID) {

	/* Ensure the maps have been initialized */
  if (!g_InitScriptErrorMaps) ObInitScriptErrorMaps();

  return g_ObScriptErrorIDMap.Lookup(ID);
}
/*===========================================================================
 *		End of Function ObGetScriptErrorDef()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obscripterrordef_t* ObGetScriptErrorDef (pName);
 *
 *=========================================================================*/
obscripterrordef_t* ObGetScriptErrorDef (const char* pName) {

	/* Ensure the maps have been initialized */
  if (!g_InitScriptErrorMaps) ObInitScriptErrorMaps();

  return g_ObScriptErrorNameMap.Lookup(pName);
}
/*===========================================================================
 *		End of Function ObGetScriptErrorDef()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void* ObGetScriptErrorDef (pName);
 *
 *=========================================================================*/
void ObSetScriptErrorLevel (const char* pName, const int Level) {
  obscripterrordef_t* pErrorDef;

	/* Ensure the maps have been initialized */
  if (!g_InitScriptErrorMaps) ObInitScriptErrorMaps();

  pErrorDef = g_ObScriptErrorNameMap.Lookup(pName);

  if (pErrorDef != NULL) pErrorDef->Level = Level;
}
/*===========================================================================
 *		End of Function ObGetScriptErrorDef()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ObOutputScriptErrorsToLog (Errors);
 *
 *=========================================================================*/
void ObOutputScriptErrorsToLog (CObScriptErrorArray& Errors) {
  dword Index;

  for (Index = 0; Index < Errors.GetSize(); ++Index) {
    SystemLog.Printf("%s", Errors.GetAt(Index)->MakeErrorString());
  }

}
/*===========================================================================
 *		End of Function ObOutputScriptErrorsToLog()
 *=========================================================================*/

