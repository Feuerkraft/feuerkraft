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

SOURCE=.\src\Ammotent.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Background.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Basis.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Controller.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Energie.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Explosion.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Feuerkraft.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Flag.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Fuelstation.cxx
# End Source File
# Begin Source File

SOURCE=.\src\GameWorld.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Headquarter.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Helicopter.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Jeep.cxx
# End Source File
# Begin Source File

SOURCE=.\src\JoystickController.cxx
# End Source File
# Begin Source File

SOURCE=.\src\KeyboardController.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Mine.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Pathfinder.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Playfield.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Projectile.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Radar.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Screen.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Shockwave.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Soldier.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Stone.cxx
# End Source File
# Begin Source File

SOURCE=.\src\StringConverter.cxx
# End Source File
# Begin Source File

SOURCE=.\src\System.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Tank.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Tower.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Tree.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Turret.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Vehicle.cxx
# End Source File
# Begin Source File

SOURCE=.\src\VehicleStatus.cxx
# End Source File
# Begin Source File

SOURCE=.\src\VehicleView.cxx
# End Source File
# Begin Source File

SOURCE=.\src\View.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hh;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\Basis.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Collideable.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Controllable.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Controller.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Energie.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Explosion.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Feuerkraft.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Flag.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Fuelstation.hxx
# End Source File
# Begin Source File

SOURCE=.\src\GameObj.hxx
# End Source File
# Begin Source File

SOURCE=.\src\GameWorld.hxx
# End Source File
# Begin Source File

SOURCE=.\src\GuiObj.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Headquarter.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Helicopter.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Jeep.hxx
# End Source File
# Begin Source File

SOURCE=.\src\JoystickController.hxx
# End Source File
# Begin Source File

SOURCE=.\src\KeyboardController.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Mine.hxx
# End Source File
# Begin Source File

SOURCE=.\src\my_gettext.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Pathfinder.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Playfield.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Projectile.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Radar.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Screen.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Shockwave.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Soldier.hxx
# End Source File
# Begin Source File

SOURCE=.\src\StringConverter.hxx
# End Source File
# Begin Source File

SOURCE=.\src\System.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Tank.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Tower.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Tree.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Turret.hxx
# End Source File
# Begin Source File

SOURCE=.\src\Vehicle.hxx
# End Source File
# Begin Source File

SOURCE=.\src\VehicleStatus.hxx
# End Source File
# Begin Source File

SOURCE=.\src\VehicleView.hxx
# End Source File
# Begin Source File

SOURCE=.\src\View.hxx
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
