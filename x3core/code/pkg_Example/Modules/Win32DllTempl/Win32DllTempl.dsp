# Microsoft Developer Studio Project File - Name="Win32DllTempl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Win32DllTempl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Win32DllTempl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Win32DllTempl.mak" CFG="Win32DllTempl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32DllTempl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32DllTempl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32DllTempl - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\bin\vc60\Release\Plugins"
# PROP Intermediate_Dir "..\..\..\..\obj\vc60\Release\Win32DllTempl"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W4 /GR /GX /O2 /I "..\..\Interface" /I "..\..\..\pkg_Core\Interface" /I "..\..\..\pkg_Core\Interface\Module" /I "..\..\..\pkg_Core\Interface\UtilFunc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 /nologo /dll /pdb:"..\..\..\..\obj\vc60\Release\Symbols/Win32DllTempl.pdb" /map:"..\..\..\..\obj\vc60\Release\Symbols/Win32DllTempl.map" /machine:I386 /out:"..\..\..\bin\vc60\Release\Plugins/Win32DllTempl.plugin.dll" /implib:"..\..\..\..\obj\vc60\Release\Lib/Win32DllTempl.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Win32DllTempl - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\bin\vc60\Debug\Plugins"
# PROP Intermediate_Dir "..\..\..\..\obj\vc60\Debug\Win32DllTempl"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /I "..\..\Interface" /I "..\..\..\pkg_Core\Interface" /I "..\..\..\pkg_Core\Interface\Module" /I "..\..\..\pkg_Core\Interface\UtilFunc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 /nologo /dll /pdb:"..\..\..\..\obj\vc60\Debug\Symbols/Win32DllTempl.pdb" /debug /machine:I386 /out:"..\..\..\bin\vc60\Debug\Plugins/Win32DllTempl.plugin.dll" /implib:"..\..\..\..\obj\vc60\Debug\Lib/Win32DllTempl.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map

!ENDIF 

# Begin Target

# Name "Win32DllTempl - Win32 Release"
# Name "Win32DllTempl - Win32 Debug"
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Interface\ClsID_Example.h
# End Source File
# Begin Source File

SOURCE=..\..\Interface\Ix_Example.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Cx_Example.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Cx_Example.cpp
# End Source File
# Begin Source File

SOURCE=.\Module.cpp
# End Source File
# Begin Source File

SOURCE=.\Plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Version.rc2
# End Source File
# Begin Source File

SOURCE=.\Win32DllTempl.rc
# End Source File
# End Group
# End Target
# End Project
