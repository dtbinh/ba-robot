cls

@echo off
call count.cmd "Arduino-Board-Firmware\Firmware_BA_Robot\" "*.cpp *.h *.ino" 
@echo off
echo.
call count.cmd "BA-Robot-Driver\BaRobotDriverDll\BaRobotDriverDll\" "*.cpp *.h"
@echo off
echo.
call count.cmd "Testanwendungen\Test_Dll_C#\TestDLL\TestDLL\" "*.cs"
@echo off
echo.
call count.cmd "Testanwendungen\Test_Dll_Cpp\Test_Dll_Cpp\" "*.cpp *.h"
@echo off
pause
@echo on