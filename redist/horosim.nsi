#Name of the App
Name HoRoSim

# set the name of the installer
Outfile "HoRoSim_Installer.exe"
 
# define the directory to install to
InstallDir $DOCUMENTS\Arduino


#Function StrContains
; StrContains
; This function does a case sensitive searches for an occurrence of a substring in a string. 
; It returns the substring if it is found. 
; Otherwise it returns null(""). 
; Written by kenglish_hi
; Adapted from StrReplace written by dandaman32
 
 
Var STR_HAYSTACK
Var STR_NEEDLE
Var STR_CONTAINS_VAR_1
Var STR_CONTAINS_VAR_2
Var STR_CONTAINS_VAR_3
Var STR_CONTAINS_VAR_4
Var STR_RETURN_VAR
 
Function StrContains
  Exch $STR_NEEDLE
  Exch 1
  Exch $STR_HAYSTACK
  ; Uncomment to debug
  ;MessageBox MB_OK 'STR_NEEDLE = $STR_NEEDLE STR_HAYSTACK = $STR_HAYSTACK '
    StrCpy $STR_RETURN_VAR ""
    StrCpy $STR_CONTAINS_VAR_1 -1
    StrLen $STR_CONTAINS_VAR_2 $STR_NEEDLE
    StrLen $STR_CONTAINS_VAR_4 $STR_HAYSTACK
    loop:
      IntOp $STR_CONTAINS_VAR_1 $STR_CONTAINS_VAR_1 + 1
      StrCpy $STR_CONTAINS_VAR_3 $STR_HAYSTACK $STR_CONTAINS_VAR_2 $STR_CONTAINS_VAR_1
      StrCmp $STR_CONTAINS_VAR_3 $STR_NEEDLE found
      StrCmp $STR_CONTAINS_VAR_1 $STR_CONTAINS_VAR_4 done
      Goto loop
    found:
      StrCpy $STR_RETURN_VAR $STR_NEEDLE
      Goto done
    done:
   Pop $STR_NEEDLE ;Prevent "invalid opcode" errors and keep the
   Exch $STR_RETURN_VAR  
FunctionEnd
 
!macro _StrContainsConstructor OUT NEEDLE HAYSTACK
  Push `${HAYSTACK}`
  Push `${NEEDLE}`
  Call StrContains
  Pop `${OUT}`
!macroend
 
!define StrContains '!insertmacro "_StrContainsConstructor"'


#Custom page for asking the installation folder
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
  
  #We will install the offline g++ compiler
  #MessageBox MB_OK "HoRoSim needs the Mingw-w64 g++ compiler. Use the default settings, do not change the architecture field!"
  #MessageBox MB_YESNO "Install the Mingw-w64 (g++)?" /SD IDYES IDNO endG++
    #File "mingw-w64-install.exe"
    #ExecWait "$INSTDIR\redist\mingw-w64-install.exe"
    #Goto endG++
  #endG++:

  #Copy the mingw-w64
  SetOutPath $INSTDIR\redist\mingw32
  File /nonfatal "mingw32\build-info.txt"
  File /nonfatal "mingw32\version.txt"
  SetOutPath $INSTDIR\redist\mingw32\bin
  File /nonfatal /r "mingw32\bin\"
  SetOutPath $INSTDIR\redist\mingw32\etc
  File /nonfatal /r "mingw32\etc\"
  SetOutPath $INSTDIR\redist\mingw32\i686-w64-mingw32
  File /nonfatal /r "mingw32\i686-w64-mingw32\"
  SetOutPath $INSTDIR\redist\mingw32\include
  File /nonfatal /r "mingw32\include\"
  SetOutPath $INSTDIR\redist\mingw32\lib
  File /nonfatal /r "mingw32\lib\"
  SetOutPath $INSTDIR\redist\mingw32\libexec
  File /nonfatal /r "mingw32\libexec\"
  SetOutPath $INSTDIR\redist\mingw32\licenses
  File /nonfatal /r "mingw32\licenses\"
  SetOutPath $INSTDIR\redist\mingw32\opt
  File /nonfatal /r "mingw32\opt\"
  SetOutPath $INSTDIR\redist\mingw32\share
  File /nonfatal /r "mingw32\share\"

SectionEnd


Section -AddEnvVar
  IfFileExists "$INSTDIR\redist\mingw32\bin\g++.exe" g++Found
    MessageBox MB_ICONEXCLAMATION|MB_OK "We have not found the g++ compiler at the defalt location. You need to install the g++ compiler and/or add the path to the g++ compiler to the PATH environmental variable. HoRoSim will not work until this is fixed."
    GoTo endAddEnvVar
    g++Found:
      MessageBox MB_YESNO "HoRoSim needs to be able to find g++. To do so, the installer will add Mingw-w64 (g++) to the PATH environmental variable. If it is not added, HoRoSim will not work. Add g++ to the PATH env variable?" /SD IDYES IDNO endAddEnvVar
      EnVar::AddValue "PATH" "$INSTDIR\redist\mingw32\bin"
      nsExec::ExecToStack  'cmd /c "g++ --version"'
      Pop $0
      Pop $0
      ;now we have the version in $0
      #MessageBox MB_OK "g++ version is $0"

      Var /GLOBAL versionTest
      ${StrContains} $versionTest "g++ (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0" $0
      StrCmp $versionTest "" notfound
        MessageBox MB_OK "g++ is working OK!$\r$\n$\r$\ng++ version is:$\r$\n $0"
        Goto done
      notfound:
        MessageBox MB_OK 'g++ version seems incorrect. HoRoSim will probably not work. Check that you do not have other g++ compilers in the PATH environmental variable. Version of g++ found: $0'
      done:
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