// Test_Dll_Cpp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <string> 

#using <mscorlib.dll>
using namespace System::Runtime::InteropServices;
using namespace std;
using namespace System;
using namespace BaRobotLibrary;

void MarshalString ( String ^ s, string& os ) {
   using namespace Runtime::InteropServices;
   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

int _tmain(int argc, _TCHAR* argv[])
{
	BaRobotWrapper ba;
	ba.SetMode(TransferMode::COM);
	ba.SetComPort(10);
	String^ bla = ba.SendString("ON");
	string temp = "";
	MarshalString(bla,temp);
	cout << temp;
	cin.get();
	bla = ba.SendString("OFF");
	MarshalString(bla,temp);
	cout << temp;
	cin.get();

	return 0;
}

