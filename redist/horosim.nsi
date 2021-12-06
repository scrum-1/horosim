# set the name of the installer
Outfile "HoRoSim_Installer.exe"
 
# define the directory to install to
InstallDir $DOCUMENTS\Arduino\horosim_installer_test

!include MUI2.nsh
!define MUI_PAGE_HEADER_TEXT "HoRoSim Install Directory"
!define MUI_PAGE_HEADER_SUBTEXT "Select Arduino Sketchbook Folder"
!define MUI_DIRECTORYPAGE_TEXT_TOP "HoRoSim needs an Arduino IDE (>1.5.0 and <2.0) installed in your system. If it is not installed, please, close this installer, install an Arduino IDE and run again this installer. $\r$\n$\r$\nYou need to point to the Arduino's sketchbook location. You can check it in Arduino's menu (File->Preferences). Usually, it is something like C:\Users\xxxx\Documents\Arduino"
!define MUI_DIRECTORYPAGE_TEXT_DESTINATION "Arduino's sketchbook location"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_LANGUAGE English


Section -CheckArduinoSketchbook
StrCpy $InstDir $InstDir\hardware\HoRoSim
SectionEnd

# These are the programs that are needed by HoRoSim.
Section -Prerequisites
  SetOutPath $INSTDIR\redist
  
  #Arduino removed, users need to install it before installing HoRoSim
  #MessageBox MB_OK "HoRoSim needs an Arduino IDE >1.5.0 and <2.0. Skip Arduino installation in next dialog if you already have it installed!"
  #MessageBox MB_YESNO "Install Arduino IDE?" /SD IDYES IDNO endArduino
  #  File "arduino-1.8.16-windows.exe"
  #  ExecWait "$INSTDIR\redist\arduino-1.8.16-windows.exe"
  #  Goto endArduino
  #endArduino:
  
  MessageBox MB_OK "HoRoSim needs the Mingw-w64 g++ compiler. Use the default settings, do not change the architecture field!"
  MessageBox MB_YESNO "Install the Mingw-w64 (g++)?" /SD IDYES IDNO endG++
    File "mingw-w64-install.exe"
    ExecWait "$INSTDIR\redist\mingw-w64-install.exe"
    Goto endG++
  endG++:
SectionEnd


Section -AddEnvVar
  IfFileExists "C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe" g++Found
    MessageBox MB_ICONEXCLAMATION|MB_OK "We have not found the g++ compiler at the defalt location. You need to install the g++ compiler and/or add the path to the g++ compiler to the PATH environmental variable. Anotjer option would be to reinstall HoRoSim without modifying the settings of mingw. HoRoSim will not work until this is fixed."
    GoTo endAddEnvVar
    g++Found:
      EnVar::AddValue "PATH" "C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin"
    endAddEnvVar:

SectionEnd



# create a default section.
Section -HoRoSimFiles
  SetOutPath $INSTDIR
  File /nonfatal "..\LICENSE.txt"
  File /nonfatal "..\README.md"
  SetOutPath $INSTDIR\horosim
  File /nonfatal /r "..\horosim\"
  SetOutPath $INSTDIR\redist\freeglut
  File /nonfatal /r "freeglut\"
  SetOutPath $INSTDIR\docs
  File /nonfatal /r "..\docs\"
  SetOutPath $INSTDIR\examples
  File /nonfatal /r "..\examples\"


 
SectionEnd