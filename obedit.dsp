# Microsoft Developer Studio Project File - Name="obedit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=obedit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "obedit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "obedit.mak" CFG="obedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "obedit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "obedit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "obedit - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../tes4lib" /I "./" /I "devil/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "obedit - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../tes4lib" /I "./" /I "devil/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "obedit - Win32 Release"
# Name "obedit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObActiView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObAlchView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObAmmoView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObAppaView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\dialogs\obarmorview.cpp
# ADD CPP /I ".." /YX
# End Source File
# Begin Source File

SOURCE=.\ObBatchEditDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\dialogs\obbipedpartsdlg.cpp
# ADD CPP /I ".." /YX
# End Source File
# Begin Source File

SOURCE=.\ObBipedPartsListDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObBookView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObClotView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObCntoEditDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObContView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObEffectEditDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\dialogs\obenchview.cpp
# ADD CPP /I ".." /YX
# End Source File
# Begin Source File

SOURCE=.\ObFindDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObFlorView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObFurnView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObIngrView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObKeymView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObLighView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObLvlcView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObLvlEditDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObLvliView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObLvspView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObMiscView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObScptView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObScriptErrorView.cpp

!IF  "$(CFG)" == "obedit - Win32 Release"

!ELSEIF  "$(CFG)" == "obedit - Win32 Debug"

# ADD CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObSgstView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\OBSlgmView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObSounView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObSpelView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObStatView.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObWeapView.cpp
# ADD CPP /YX
# End Source File
# End Group
# Begin Group "Base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dialogs\obeditdlghandler.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\dialogs\obrecorddialog.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObSelectRecordDlg.cpp
# ADD CPP /YX
# End Source File
# End Group
# Begin Group "CommonDlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ColorStatic.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ErrorBar.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\obbatchlistctrl.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObImageCtrl.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObInputDialog.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObPromptDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordlistctrl.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordtreectrl.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordvirtuallistctrl.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\scbarcf.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\scbarg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\sizecbar.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\tabctrlsheet.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UndoBar.cpp
# ADD CPP /YX
# End Source File
# End Group
# Begin Source File

SOURCE=.\aboutdlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ChildFrmFix.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ChildFrmScript.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\obeditView.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ObErrorDlg.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ObFileTreeDlg.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ObFindBinaryDlg.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ObLoadDlg.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\obprogressdlg.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\obresourceview.cpp
# ADD CPP /YX
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\obedit.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Group "Devil"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\devil\lib\DevIL.lib
# End Source File
# Begin Source File

SOURCE=.\devil\lib\ILU.lib
# End Source File
# Begin Source File

SOURCE=.\devil\lib\ILUT.lib
# End Source File
# End Group
# Begin Source File

SOURCE=..\tes4lib\common\csvfile.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\filebuffer.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obcallback.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obconfigentry.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obconfigfile.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\oberror.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\oberrorhandler.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obfile.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\oblogfile.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obmemfile.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obptrarray.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obtime.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obutils.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\sstring.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\textutils.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\zlib\zdll.lib
# End Source File
# End Group
# Begin Group "ESP"

# PROP Default_Filter ""
# Begin Group "Records"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obachrrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obacrerecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obactirecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obalchrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obammorecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obaniorecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obapparecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obarmorecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbasereccont.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbaserecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbaserefrrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbookrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbsgnrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcellrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obclmtrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obclotrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcontrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcrearecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obdialrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obdoorrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obeffitemrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obenchrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obfactrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obflorrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obfurnrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obidlerecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obidrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obinforecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obingrrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obitem1record.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obitem2record.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obkeymrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblandrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblighrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblscrrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obltexrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblvlcrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblvlirecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblvsprecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obmgefrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obmiscrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obnpcrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obpackrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obpgrdrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obqustrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obracerecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obreccont.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obrefrrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obregnrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obscptrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obsgstrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obslgmrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obsounrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obspelrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obstatrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obtes4record.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obwatrrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obweaprecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obwrldrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obwthrrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Subrecords"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obctdasubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obctdtsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obdatasubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obefitsubrecord.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obenitsubrecord.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obformidarraysubrecord.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obhedrsubrecord.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obnamesubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obpgrlsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdgssubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdotsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdsdsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdwtsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obscitsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obspitsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obstring1subrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obstringsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obsubreccont.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obwlstsubrecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Groups"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obfilegroup.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obgroup.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obgrupcont.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obtypegroup.cpp
# ADD CPP /YX
# End Source File
# End Group
# Begin Group "Handler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\obmultirecordhandler.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obsimplerecordhandler.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obundoitem.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Compiler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\charclass.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\charclassarray.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\customcompiler.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obfixedparser.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\obscripterrors.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obscriptfunction.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obscriptfunctions.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obscriptutils.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\scansourcestring.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentable.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentablearray.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentableresult.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentablerow.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentype.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentypearray.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\obeventhandler.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Bsa"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\bsafile\obbsafile.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obbsafilerecord.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obbsafolder.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourcefile.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourcefolder.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourcehandler.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourceinstance.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcheckrecord.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obespfile.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obexport.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obfields.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obimport.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obmoddefs.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obrecordcreate.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordfilter.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obrectype.cpp
# ADD CPP /YX
# End Source File
# End Group
# Begin Source File

SOURCE=.\obedit.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\obeditDoc.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Program Files\MSVS\VC98\Lib\SHLWAPI.LIB"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Forms."

# PROP Default_Filter ""
# Begin Group "Dialogs."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObActiView.h
# End Source File
# Begin Source File

SOURCE=.\ObAlchView.h
# End Source File
# Begin Source File

SOURCE=.\ObAmmoView.h
# End Source File
# Begin Source File

SOURCE=.\ObAppaView.h
# End Source File
# Begin Source File

SOURCE=.\dialogs\obarmorview.h
# End Source File
# Begin Source File

SOURCE=.\ObBatchEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\dialogs\obbipedpartsdlg.h
# End Source File
# Begin Source File

SOURCE=.\ObBipedPartsListDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObBookView.h
# End Source File
# Begin Source File

SOURCE=.\ObClotView.h
# End Source File
# Begin Source File

SOURCE=.\ObContView.h
# End Source File
# Begin Source File

SOURCE=.\ObEffectEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\dialogs\obenchview.h
# End Source File
# Begin Source File

SOURCE=.\ObFindDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObFlorView.h
# End Source File
# Begin Source File

SOURCE=.\ObFurnView.h
# End Source File
# Begin Source File

SOURCE=.\ObIngrView.h
# End Source File
# Begin Source File

SOURCE=.\ObKeymView.h
# End Source File
# Begin Source File

SOURCE=.\ObLighView.h
# End Source File
# Begin Source File

SOURCE=.\ObLvlcView.h
# End Source File
# Begin Source File

SOURCE=.\ObLvliView.h
# End Source File
# Begin Source File

SOURCE=.\ObLvspView.h
# End Source File
# Begin Source File

SOURCE=.\ObMiscView.h
# End Source File
# Begin Source File

SOURCE=.\ObScptView.h
# End Source File
# Begin Source File

SOURCE=.\ObSgstView.h
# End Source File
# Begin Source File

SOURCE=.\OBSlgmView.h
# End Source File
# Begin Source File

SOURCE=.\ObSounView.h
# End Source File
# Begin Source File

SOURCE=.\ObSpelView.h
# End Source File
# Begin Source File

SOURCE=.\ObStatView.h
# End Source File
# Begin Source File

SOURCE=.\ObWeapView.h
# End Source File
# End Group
# Begin Group "Base."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dialogs\obeditdlghandler.h
# End Source File
# Begin Source File

SOURCE=.\ObLvlEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\dialogs\obrecorddialog.h
# End Source File
# Begin Source File

SOURCE=.\ObSelectRecordDlg.h
# End Source File
# End Group
# Begin Group "CommonDlg."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ColorStatic.h
# End Source File
# Begin Source File

SOURCE=.\ErrorBar.h
# End Source File
# Begin Source File

SOURCE=.\obbatchlistctrl.h
# End Source File
# Begin Source File

SOURCE=.\ObCntoEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObImageCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ObInputDialog.h
# End Source File
# Begin Source File

SOURCE=.\ObPromptDlg.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordlistctrl.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordtreectrl.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordvirtuallistctrl.h
# End Source File
# Begin Source File

SOURCE=.\ObScriptErrorView.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\scbarcf.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\scbarg.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\sizecbar.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\tabctrlsheet.h
# End Source File
# Begin Source File

SOURCE=.\UndoBar.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\aboutdlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrmFix.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrmScript.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\obeditView.h
# End Source File
# Begin Source File

SOURCE=.\ObErrorDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObFileTreeDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObFindBinaryDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObLoadDlg.h
# End Source File
# Begin Source File

SOURCE=.\obprogressdlg.h
# End Source File
# Begin Source File

SOURCE=.\obresourceview.h
# End Source File
# End Group
# Begin Group "Misc."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "ESP."

# PROP Default_Filter ""
# Begin Group "Records."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obachrrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obacrerecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obactirecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obalchrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obammorecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obaniorecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obapparecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obarmorecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbasereccont.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbaserecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbaserefrrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbookrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obbsgnrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcellrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obclmtrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obclotrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcontrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcrearecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obdialrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obdoorrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obeffitemrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obenchrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obfactrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obflorrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obfurnrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obidlerecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obidrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obinforecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obingrrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obitem1record.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obitem2record.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obkeymrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblandrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblighrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblscrrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obltexrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblvlcrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblvlirecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\oblvsprecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obmgefrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obmiscrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obnpcrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obpackrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obpgrdrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obqustrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obracerecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obreccont.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obrefrrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obregnrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obscptrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obsgstrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obslgmrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obsounrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obspelrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obstatrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obtes4record.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obwatrrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obweaprecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obwrldrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obwthrrecord.h
# End Source File
# End Group
# Begin Group "Subrecords."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obammodatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obappadatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obarmodatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obatxtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obbookdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obbytesubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obclotdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obcntosubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obcontdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obctdasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obctdtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obdnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obdwordsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obefitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obenamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obenit8subrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obenitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obfloatsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obformidarraysubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obformidsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obhedrsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obidledatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obingrenitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obint64subrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obkeymdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\oblighdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\oblnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\oblongsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\oblvlosubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obmgefdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obmiscdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obnamesubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obpfpcsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obpgrlsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obpldtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obposanglesubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obpositionsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obptdtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obqstasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdgssubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdotsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdsdsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrdwtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obrefrdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obschrsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obscitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obscrosubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obsgstdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obslgmdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obslsdsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obsnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obsndxsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obspitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obstring1subrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obstringsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obsubreccont.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obvnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obvtexsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obweapdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obwlstsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obwordsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obxespsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obxlocsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obxnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\subrecords\obxtelsubrecord.h
# End Source File
# End Group
# Begin Group "Groups."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obblockgroup.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obfilegroup.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obformidgroup.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obgridgroup.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obgroup.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obgrupcont.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\groups\obtypegroup.h
# End Source File
# End Group
# Begin Group "Handler."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\obmultirecordhandler.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obrecordhandler.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obsimplerecordhandler.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obundoitem.h
# End Source File
# End Group
# Begin Group "Compiler."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\charclass.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\charclassarray.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\customcompiler.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obfixedparser.h
# End Source File
# Begin Source File

SOURCE=.\obscripterrors.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obscriptfunction.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obscriptfunctions.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\obscriptutils.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\scansource.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\scansourcestring.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentable.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentablearray.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentableresult.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentablerow.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentype.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\compiler\tokentypearray.h
# End Source File
# End Group
# Begin Group "Events."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\modfile\obeventhandler.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\oblistener.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\oblistenevent.h
# End Source File
# End Group
# Begin Group "Bsa."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\tes4lib\bsafile\obbsafile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obbsafilerecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obbsafolder.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourcebase.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourcefile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourcefolder.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourcehandler.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\bsafile\obresourceinstance.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obcheckrecord.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obespfile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obexport.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obfields.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obimport.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obmoddefs.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obrecordfield.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\windows\obrecordfilter.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\records\obrecordmap.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\modfile\obrectype.h
# End Source File
# End Group
# Begin Group "Common."

# PROP Default_Filter ""
# Begin Group "Devil."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\devil\include\IL\config.h
# End Source File
# Begin Source File

SOURCE=.\devil\include\IL\il.h
# End Source File
# Begin Source File

SOURCE=.\devil\include\IL\ilu.h
# End Source File
# Begin Source File

SOURCE=.\devil\include\IL\ilut.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\tes4lib\common\csvfile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\dl_map.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\filebuffer.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obarray.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obblockallocator.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obcallback.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obconfigentry.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obconfigfile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\oberror.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\oberrorhandler.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obfile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\oblogfile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obmemfile.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obplatform.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obptrarray.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obsimplemap.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obtime.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obtypes.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obutils.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\obversion.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\sstring.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\textutils.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\zlib\zconf.h
# End Source File
# Begin Source File

SOURCE=..\tes4lib\common\zlib\zlib.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\obedit.h
# End Source File
# Begin Source File

SOURCE=.\obeditDoc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\armor.ico
# End Source File
# Begin Source File

SOURCE=.\res\file.bmp
# End Source File
# Begin Source File

SOURCE=.\res\find_dlg.ico
# End Source File
# Begin Source File

SOURCE=.\res\folder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\obedit.ico
# End Source File
# Begin Source File

SOURCE=.\res\obedit.rc2
# End Source File
# Begin Source File

SOURCE=.\res\obeditDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\compiler.txt
# End Source File
# Begin Source File

SOURCE=.\displayfilters.dat
# End Source File
# Begin Source File

SOURCE=.\functions.dat
# End Source File
# Begin Source File

SOURCE=.\obedit.ini
# End Source File
# Begin Source File

SOURCE=.\obedit.log
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\testtable.dat
# End Source File
# Begin Source File

SOURCE=.\testtable1.dat
# End Source File
# Begin Source File

SOURCE=.\todo.txt
# End Source File
# End Target
# End Project
