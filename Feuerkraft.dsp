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
# ADD LINK32 libguile.lib SphriteLibGLd.lib clanCored.lib clanAppd.lib clanPNGd.lib clanJPEGd.lib clanDisplayd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Feuerkraft - Win32 Release"
# Name "Feuerkraft - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;cc;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\Ambulance.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\Ammotent.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\AmmotentData.cxx
# End Source File
# Begin Source File

SOURCE=.\src\Background.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\Base.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\BaseData.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\BuildingMap.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\BuildingMapData.cxx
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

SOURCE=.\src\vehicles\FoxTank.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\Fuelstation.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\FuelstationData.cxx
# End Source File
# Begin Source File

SOURCE=.\src\GameWorld.cxx
# End Source File
# Begin Source File

SOURCE=.\src\groundmap\GroundMapData.cxx
# End Source File
# Begin Source File

SOURCE=.\src\groundmap\GroundMapDataFactory.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\Headquarter.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\HeadquarterData.cxx
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

SOURCE=.\src\generic\Random.cxx
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

SOURCE=.\src\groundmap\SpriteTile.cxx
# End Source File
# Begin Source File

SOURCE=.\src\groundmap\SpriteTileData.cxx
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

SOURCE=.\src\groundmap\TileDataFactory.cxx
# End Source File
# Begin Source File

SOURCE=.\src\groundmap\TileMap.cxx
# End Source File
# Begin Source File

SOURCE=.\src\groundmap\TileMapData.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\Tower.cxx
# End Source File
# Begin Source File

SOURCE=.\src\buildings\TowerData.cxx
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
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\data\feuerkraft.scr
# End Source File
# End Target
# End Project
