# Microsoft Developer Studio Project File - Name="Feuerkraft" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Feuerkraft - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Feuerkraft.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Feuerkraft.mak" CFG="Feuerkraft - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Feuerkraft - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Feuerkraft - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Feuerkraft - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /TP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 clanCore.lib clanApp.lib clanPNG.lib clanJPEG.lib clanDisplay.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Feuerkraft - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FD /GZ /TP /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 clanCored.lib clanAppd.lib clanPNGd.lib clanJPEGd.lib clanDisplayd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Feuerkraft - Win32 Release"
# Name "Feuerkraft - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;cc;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\Ammotent.cc
# End Source File
# Begin Source File

SOURCE=.\src\Background.cc
# End Source File
# Begin Source File

SOURCE=.\src\Basis.cc
# End Source File
# Begin Source File

SOURCE=.\src\Controller.cc
# End Source File
# Begin Source File

SOURCE=.\src\Energie.cc
# End Source File
# Begin Source File

SOURCE=.\src\Explosion.cc
# End Source File
# Begin Source File

SOURCE=.\src\Feuerkraft.cc
# End Source File
# Begin Source File

SOURCE=.\src\Flag.cc
# End Source File
# Begin Source File

SOURCE=.\src\Fuelstation.cc
# End Source File
# Begin Source File

SOURCE=.\src\GameWorld.cc
# End Source File
# Begin Source File

SOURCE=.\src\Headquarter.cc
# End Source File
# Begin Source File

SOURCE=.\src\Helicopter.cc
# End Source File
# Begin Source File

SOURCE=.\src\Jeep.cc
# End Source File
# Begin Source File

SOURCE=.\src\JoystickController.cc
# End Source File
# Begin Source File

SOURCE=.\src\KeyboardController.cc
# End Source File
# Begin Source File

SOURCE=.\src\Mine.cc
# End Source File
# Begin Source File

SOURCE=.\src\Pathfinder.cc
# End Source File
# Begin Source File

SOURCE=.\src\Playfield.cc
# End Source File
# Begin Source File

SOURCE=.\src\Projectile.cc
# End Source File
# Begin Source File

SOURCE=.\src\Radar.cc
# End Source File
# Begin Source File

SOURCE=.\src\Screen.cc
# End Source File
# Begin Source File

SOURCE=.\src\Shockwave.cc
# End Source File
# Begin Source File

SOURCE=.\src\Soldier.cc
# End Source File
# Begin Source File

SOURCE=.\src\Stone.cc
# End Source File
# Begin Source File

SOURCE=.\src\StringConverter.cc
# End Source File
# Begin Source File

SOURCE=.\src\System.cc
# End Source File
# Begin Source File

SOURCE=.\src\Tank.cc
# End Source File
# Begin Source File

SOURCE=.\src\Tower.cc
# End Source File
# Begin Source File

SOURCE=.\src\Tree.cc
# End Source File
# Begin Source File

SOURCE=.\src\Turret.cc
# End Source File
# Begin Source File

SOURCE=.\src\Vehicle.cc
# End Source File
# Begin Source File

SOURCE=.\src\VehicleStatus.cc
# End Source File
# Begin Source File

SOURCE=.\src\VehicleView.cc
# End Source File
# Begin Source File

SOURCE=.\src\View.cc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hh;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\Basis.hh
# End Source File
# Begin Source File

SOURCE=.\src\Collideable.hh
# End Source File
# Begin Source File

SOURCE=.\src\Controllable.hh
# End Source File
# Begin Source File

SOURCE=.\src\Controller.hh
# End Source File
# Begin Source File

SOURCE=.\src\Energie.hh
# End Source File
# Begin Source File

SOURCE=.\src\Explosion.hh
# End Source File
# Begin Source File

SOURCE=.\src\Feuerkraft.hh
# End Source File
# Begin Source File

SOURCE=.\src\Flag.hh
# End Source File
# Begin Source File

SOURCE=.\src\Fuelstation.hh
# End Source File
# Begin Source File

SOURCE=.\src\GameObj.hh
# End Source File
# Begin Source File

SOURCE=.\src\GameWorld.hh
# End Source File
# Begin Source File

SOURCE=.\src\GuiObj.hh
# End Source File
# Begin Source File

SOURCE=.\src\Headquarter.hh
# End Source File
# Begin Source File

SOURCE=.\src\Helicopter.hh
# End Source File
# Begin Source File

SOURCE=.\src\Jeep.hh
# End Source File
# Begin Source File

SOURCE=.\src\JoystickController.hh
# End Source File
# Begin Source File

SOURCE=.\src\KeyboardController.hh
# End Source File
# Begin Source File

SOURCE=.\src\Mine.hh
# End Source File
# Begin Source File

SOURCE=.\src\my_gettext.hh
# End Source File
# Begin Source File

SOURCE=.\src\Pathfinder.hh
# End Source File
# Begin Source File

SOURCE=.\src\Playfield.hh
# End Source File
# Begin Source File

SOURCE=.\src\Projectile.hh
# End Source File
# Begin Source File

SOURCE=.\src\Radar.hh
# End Source File
# Begin Source File

SOURCE=.\src\Screen.hh
# End Source File
# Begin Source File

SOURCE=.\src\Shockwave.hh
# End Source File
# Begin Source File

SOURCE=.\src\Soldier.hh
# End Source File
# Begin Source File

SOURCE=.\src\StringConverter.hh
# End Source File
# Begin Source File

SOURCE=.\src\System.hh
# End Source File
# Begin Source File

SOURCE=.\src\Tank.hh
# End Source File
# Begin Source File

SOURCE=.\src\Tower.hh
# End Source File
# Begin Source File

SOURCE=.\src\Tree.hh
# End Source File
# Begin Source File

SOURCE=.\src\Turret.hh
# End Source File
# Begin Source File

SOURCE=.\src\Vehicle.hh
# End Source File
# Begin Source File

SOURCE=.\src\VehicleStatus.hh
# End Source File
# Begin Source File

SOURCE=.\src\VehicleView.hh
# End Source File
# Begin Source File

SOURCE=.\src\View.hh
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\data\feuerkraft.scr
# End Source File
# End Target
# End Project
