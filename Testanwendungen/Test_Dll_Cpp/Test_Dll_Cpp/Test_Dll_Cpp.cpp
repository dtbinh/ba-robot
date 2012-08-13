// Includes
#include "stdafx.h"
#include <iostream>
#include <string> 

// Usings
#using <mscorlib.dll>
using namespace System::Runtime::InteropServices;
using namespace std;
using namespace System;
using namespace BaRobotLibrary;

// Function declarations
void handleCommmands(char input);
void MarshalString ( String ^ s, string& os );
void turnRobotOn();
void turnRobotOff();
void sendString();
void sendStorage();
void getStorage();
void eraseStorage();
void demoMode();
void getComport();

// Managed Class Wrapper for Global Use of BaRobotWrapper
ref class ManagedWrapper
{
public:
    static BaRobotWrapper^ BaRobot;
};

int usedCom = 1;

// Main
int _tmain(int argc, _TCHAR* argv[])
{
	ManagedWrapper::BaRobot = gcnew BaRobotWrapper();
	ManagedWrapper::BaRobot->SetMode(TransferMode::COM);
	ManagedWrapper::BaRobot->SetComPort(usedCom);

	// System::String^ str[] = gcnew System::String[];
	// String^ STORE[] = gcnew String^[] { "00;01;02;03;04;05", "16;17;18;19;20;21"};

	char input = 'e';
	do
	{
		system("cls");
		cout << "Eingabe: " << endl;
		cout << "1: Turn Robot on " << endl;
		cout << "2: Turn Robot off" << endl;
		cout << "3: Send String " << endl;
		cout << "4: STORE " << endl;
		cout << "5: GET " << endl;
		cout << "6: ERASE " << endl;
		cout << "7: Demo Mode" << endl;
		cout << "8: Change Comport. Current Used: " << usedCom << endl;
		cout << "e: Exit " << endl;
		cout << "Your choice: "; 
		input = cin.get(); 
		handleCommmands(input);
		
		cin.clear(); 
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin.get(); 

	}while (input != 'e');

	// delete[] CLROfOldCPPClass::Globals::Example;

	return 0;
}

// handle Of User input
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
	case '4':
		sendStorage();
		break;
	case '5':
		getStorage();
		break;
	case '6': 
		eraseStorage();
		break;
	case '7':
		demoMode();
		break;
	case '8':
		getComport();
		ManagedWrapper::BaRobot ->SetComPort(usedCom);
		break;
	default:
		break;
	}
}

// Turn Communication with Robot on
void turnRobotOn()
{
	if (ManagedWrapper::BaRobot->StartCommunication())
	{
		cout << "Device successfully connected..." << endl;
	}
	else
	{
		cout << "Error: Device could not connect..." << endl;
	}
}

// Turn Communication with Robot off
void turnRobotOff()
{
	if (ManagedWrapper::BaRobot->StopCommunication())
	{
		cout << "Device successfully disconnected..." << endl;
	}
	else
	{
		cout << "Error: Device could not disconnect (was it connected?)..." << endl;
	}
}

// Send a String to Robot
void sendString()
{
	cin.clear(); 
    cin.ignore(cin.rdbuf()->in_avail());
	cout << endl << "What to send: ";
	char* sendString = new char[100];
	cin.getline(sendString, 100);
	System::String^ str = gcnew System::String(sendString);
	System::String^ outString = ManagedWrapper::BaRobot->SendString(str);
	std::string outArray;
	MarshalString(outString, outArray);
	cout << "Message received: " << outArray << endl;
	// system("pause");
}

// Store Commands
void sendStorage()
{
	array<System::String ^>^ STORE = gcnew array<System::String ^>(3);
	STORE[0]="00;15;120;140;120;90";
    STORE[1]="00;165;25;90;150;130";
    STORE[2]="00;165;90;160;180;30";
	String^ outString = ManagedWrapper::BaRobot->StoreCommandList(STORE,3);
	std::string outArray;
	MarshalString(outString, outArray);
	cout << "Message received: " << outArray << endl;
}

// Receive Stored Commands
void getStorage()
{
	String^ outString = ManagedWrapper::BaRobot->GetCommandList();
	std::string outArray;
	MarshalString(outString, outArray);
	cout << "Message received: " << outArray << endl;
}

// Delete Stored Commands
void eraseStorage()
{
	String^ outString = ManagedWrapper::BaRobot->EraseCommandList();
	std::string outArray;
	MarshalString(outString, outArray);
	cout << "Message received: " << outArray << endl;
}

void demoMode()
{
	turnRobotOn();
	System::Threading::Thread::Sleep(19400);
	
	char* sendString = new char[100];
	sendString = "LISTPOS;0;1;2";
	System::String^ str = gcnew System::String(sendString);
	System::String^ outString = ManagedWrapper::BaRobot->SendString(str);
	std::string outArray;
	MarshalString(outString, outArray);
	cout << "Message received: " << outArray << endl;

	System::Threading::Thread::Sleep(19400);
	turnRobotOff();
}

// Converting from System::String^ to std::string
void MarshalString ( String ^ s, string& os ) 
{
   using namespace Runtime::InteropServices;
   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void getComport()
{
	char line[3];
	cout << "Comport Number: ";
	cin.clear(); 
	cin.ignore(cin.rdbuf()->in_avail()); 
	cin.getline(line, 2);
	if ( atoi(line) != 0 )
		usedCom = atoi(line);
}
