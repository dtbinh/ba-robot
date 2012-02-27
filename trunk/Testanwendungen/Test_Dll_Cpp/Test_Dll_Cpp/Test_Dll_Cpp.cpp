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

void handleCommmands(char input);
void MarshalString ( String ^ s, string& os );
void turnRobotOn();
void turnRobotOff();
void sendString();

ref class ManagedWrapper
{
public:
    static BaRobotWrapper^ BaRobot;
};

int _tmain(int argc, _TCHAR* argv[])
{
	ManagedWrapper::BaRobot = gcnew BaRobotWrapper();
	ManagedWrapper::BaRobot ->SetMode(TransferMode::COM);
	ManagedWrapper::BaRobot ->SetComPort(4);

	char input = 'e';
	do
	{
		system("cls");
		cout << "Eingabe: " << endl;
		cout << "1: Turn Robot on " << endl;
		cout << "2: Turn Robot off" << endl;
		cout << "3: Send String " << endl;
		cout << "e: Exit " << endl;
		cout << "Your choice: "; 
		input = cin.get(); 
		handleCommmands(input);
	}while (input != 'e');

	// delete[] CLROfOldCPPClass::Globals::Example;

	return 0;
}

void handleCommmands(char input)
{
	switch(input)
	{
	case '1':
		turnRobotOn();
		break;
	case '2':
		turnRobotOff();
		break;
	case '3':
		sendString();
		break;
	default:
		break;
	}
}

void turnRobotOn()
{
	if (ManagedWrapper::BaRobot->StartCommunication())
	{
		cout << "Device successfully connected..." << endl;
		cin.clear(); 
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin.get(); 
	}
	else
	{
		cout << "Error: Device could not connect..." << endl;
		cin.clear(); 
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin.get(); 
	}
}

void turnRobotOff()
{
	if (ManagedWrapper::BaRobot->StopCommunication())
	{
		cout << "Device successfully disconnected..." << endl;
		cin.clear(); 
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin.get(); 
	}
	else
	{
		cout << "Error: Device could not disconnect (was it connected?)..." << endl;
		cin.clear(); 
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin.get(); 
	}
}

void sendString()
{
	cin.clear(); 
    cin.ignore(cin.rdbuf()->in_avail());
	cout << endl << "What to send: ";
	char* sendString = new char[];
	cin >> sendString;
	System::String^ str = gcnew System::String(sendString);
	System::String^ outString = ManagedWrapper::BaRobot->SendString(str);
	std::string outArray;
	MarshalString(outString, outArray);
	cout << "Message received: " << outArray << endl;
	cin.clear(); 
    cin.ignore(cin.rdbuf()->in_avail()); 
    cin.get(); 
	// system("pause");
}

void MarshalString ( String ^ s, string& os ) 
{
   using namespace Runtime::InteropServices;
   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}
