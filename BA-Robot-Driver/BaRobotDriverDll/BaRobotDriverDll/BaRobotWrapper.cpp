#include "stdafx.h" 
#include <stdio.h> 
#include <string>
#include <windows.h>
#include "BaRobot.h" 
#include "BaRobotWrapper.h" 

using namespace System::Runtime::InteropServices; 
using namespace BaRobotLibrary;

BaRobotWrapper::BaRobotWrapper()
{
	_pBaRobot = new BaRobot();
}

BaRobotWrapper::~BaRobotWrapper() 
{ 
   Dispose(false); 
} 

void BaRobotWrapper::Dispose(bool disposing) 
{ 
    if (_pBaRobot) 
    { 
	    _pBaRobot->StopCommunication();
	    delete _pBaRobot; 
		_pBaRobot = NULL; 
    } 
    if (disposing) 
    { 
		GC::SuppressFinalize(this); 
    } 
} 

void BaRobotWrapper::Dispose() 
{ 
   Dispose(true); 
}

void BaRobotWrapper::SetMode(int tm)
{
	_pBaRobot->SetMode(tm);
}

void BaRobotWrapper::SetComPort(int cp)
{
	_pBaRobot->SetComPort(cp);
}

bool BaRobotWrapper::StartCommunication()
{
	return _pBaRobot->StartCommunication();
}

bool BaRobotWrapper::StopCommunication()
{
	return _pBaRobot->StopCommunication();
}

String* BaRobotWrapper::SendString(String* message)
{
	return GetAndSendMessageWrapper(message);
}

BaRobotWrapper::BaRobotWrapper(const BaRobotWrapper& obj)
{
	this->_pBaRobot = obj._pBaRobot;
	*this = obj;
}

BaRobotWrapper& BaRobotWrapper::operator=(const BaRobotWrapper& rhs) 
{
    *this = rhs;
    return *this;
}

String* BaRobotWrapper::StoreCommandList(String* commandList[], int count)
{
	String* message = "STORE";
	String* decodedString = GetAndSendMessageWrapper(message);

	if (! decodedString->Equals("ACK") )
	{
		return decodedString;
	}

	message = count.ToString();
	decodedString = GetAndSendMessageWrapper(message);

	if (! decodedString->Equals("ACK") )
	{
		return decodedString;
	}

	for (int i = 0; i < count; i++)
	{
		decodedString = GetAndSendMessageWrapper(commandList[i]);
	}
	return "Finished Saving...";
}

#pragma warning( disable : 4101 )
String* BaRobotWrapper::GetCommandList()
{
	String* message = "GET";
	String* decodedString = GetAndSendMessageWrapper(message);
	// String** retVal = new String*[numberCommands];

	/*
	IntPtr messageBuffer = Marshal::StringToHGlobalAnsi(message);
	char* pMessage = (char*) messageBuffer.ToPointer();
	char* pDecoded = _pBaRobot->SendString(pMessage);
	String* decodedString =	Marshal::PtrToStringAnsi(pDecoded);
	*/
	
	String* retVal = "";

	int numberCommands = 0;
	int numberServos = 0;
	int speed = 0;

	try
	{
		numberCommands = System::Int32::Parse(decodedString);	
	}
	/*
	catch (FormatException *e)
	{
		return decodedString;
	}
	*/
	catch (Exception *e)
	{
		return decodedString;
	}
	if (numberCommands <= 0)
	{
		return "Nothing Stored";
	}

	// Numbercommands@
	retVal = String::Concat(retVal, decodedString );
	retVal = String::Concat(retVal, "@" );
	// retVal += decodedString + "@";

	// Send ACK
	message = "ACK";

	decodedString = GetAndSendMessageWrapper(message);
	// Numbercommands@Anzahl Servos@
	retVal = String::Concat(retVal, decodedString );
	retVal = String::Concat(retVal, "@" );

	decodedString = GetAndSendMessageWrapper(message);
	// Numbercommands@Anzahl Servos@Speed@
	retVal = String::Concat(retVal, decodedString );
	retVal = String::Concat(retVal, "@" );

	for (int i = 0; i < numberCommands; i++)
	{
		decodedString = GetAndSendMessageWrapper(message);
		// Numbercommands@Anzahl Servos@Speed@command1@command2...
		retVal = String::Concat(retVal, decodedString );
		retVal = String::Concat(retVal, "@" );
	}

	// Numbercommands@Anzahl Servos@Speed@command1@command2...@FINISHED
	decodedString = GetAndSendMessageWrapper(message);
	retVal = String::Concat(retVal, decodedString );
	retVal = String::Concat(retVal, "@" );
	return retVal;
}

String* BaRobotWrapper::GetAndSendMessageWrapper(String* message)
{
	IntPtr messageBuffer = Marshal::StringToHGlobalAnsi(message);
	char* pMessage = (char*) messageBuffer.ToPointer();
	char* pDecoded = _pBaRobot->SendString(pMessage);
	String* decodedString =	Marshal::PtrToStringAnsi(pDecoded);
    // deletion 
	pDecoded = new char[1];
	pDecoded[0] = '\0';
	delete[] pDecoded;
	Marshal::FreeHGlobal(pMessage);

	return decodedString;
}

String* BaRobotWrapper::EraseCommandList()
{
	String* message = "ERASE";
	String* retVal = "";
	String* decodedString = GetAndSendMessageWrapper(message);
	retVal = String::Concat(retVal, decodedString );
	// retVal = String::Concat(retVal, "\n" );
	// nicht mehr genutzt, da nur noch der CommandCount auf 0 gesetzt wird
	// hier Sleep, da EEPROM Erasing etwas dauert... (3.3 ms pro byte * 4096 byte)
	// ungefähr 13,52 Sekunden -> 15s
	// Sleep(15000);
	Sleep(300);
	message = "ACK";
	decodedString = GetAndSendMessageWrapper(message);	
	retVal = String::Concat(retVal, decodedString );
	return retVal;
}

String* BaRobotWrapper::ToString()
{
	std::string tempString = _pBaRobot->ToString();
	String* retVal = new System::String(tempString.c_str());
	return retVal;
}

String* BaRobotWrapper::OpenGripper()
{
	String* message = "OPEN_GRIPPER";
	String* decodedString = GetAndSendMessageWrapper(message);
	return decodedString;
}

String* BaRobotWrapper::CloseGripper()
{
	String* message = "CLOSE_GRIPPER";
	String* decodedString = GetAndSendMessageWrapper(message);
	return decodedString;
}
