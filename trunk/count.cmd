@echo off 
setlocal enabledelayedexpansion

set "cntr=0" 
set "linecounter=0"
set "cppCounter=0"
set "hCounter=0"
set "inoCounter=0"
set "csCounter=0"
set "vbCounter=0"
set "otherCounter=0"
:: set "filepath=Arduino-Board-Firmware\Firmware_BA_Robot\"
:: set "fileexts=*.cpp *.h *.ino"
set "filepath=%1"
set "fileexts=%2"
set "current="
set "ext="

:: remove the quotes
SET filepath=###%filepath%###
SET filepath=%filepath:"###=%
SET filepath=%filepath:###"=%
SET filepath=%filepath:###=%
SET fileexts=###%fileexts%###
SET fileexts=%fileexts:"###=%
SET fileexts=%fileexts:###"=%
SET fileexts=%fileexts:###=%

echo Dateipfad: %filepath%
for /r %filepath% %%i in (%fileexts%) do ( 
  set /a "cntr+=1" 
  FOR /F "delims=:" %%A IN ('findstr /N .* "%%i"') DO (
    set /a "linecounter+=1"
  )
  set "current=%%i"
  set "ext1=!current:~-1!" :: h
  set "ext2=!current:~-2!" :: cs, vb
  set "ext3=!current:~-3!" :: cpp, ino
  
  if "!ext1!" == "h" (
    set /a "hCounter+=1" 
  ) else (
    if "!ext2!" == "cs" (
      set /a "csCounter+=1" 
    ) else (
      if "!ext2!" == "vb" (
        set /a "vbCounter+=1"
      ) else ( 
        if "!ext3!" == "cpp" (
          set /a "cppCounter+=1" 
        ) else (
          if "!ext3!" == "ino" (
            set /a "inoCounter+=1" 
          ) else (
            set /a "otherCounter+=1" 
          )
        )
      )
    )
  )
)  

echo Anzahl Dateien:    %cntr%
echo Anzahl INO:        %inoCounter%
echo Anzahl CPP:        %cppCounter%
echo Anzahl cs:         %csCounter%
echo Anzahl H:          %hCounter%
echo Anzahl VB:         %vbCounter%
echo Anzahl Other:      %otherCounter%
echo Anzahl Codezeilen: %linecounter%

:: pause
@echo on