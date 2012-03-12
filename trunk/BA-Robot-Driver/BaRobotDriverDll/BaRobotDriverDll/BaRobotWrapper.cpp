#include "stdafx.h" 
#include <stdio.h> 
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
	IntPtr messageBuffer = Marshal::StringToHGlobalAnsi(message);

	char* pMessage = (char*) messageBuffer.ToPointer();

	char* pDecoded = _pBaRobot->SendString(pMessage);

	String* decodedString =	Marshal::PtrToStringAnsi(pDecoded);
	
	pDecoded = new char[1];
	pDecoded[0] = '\0';
	delete[] pDecoded;

	Marshal::FreeHGlobal(pMessage);

	return decodedString;
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

void BaRobotWrapper::StoreCommandList(String* commandList[], int count)
{
	String* message = "STORE";
	IntPtr messageBuffer = Marshal::StringToHGlobalAnsi(message);
	char* pMessage = (char*) messageBuffer.ToPointer();
	char* pDecoded = _pBaRobot->SendString(pMessage);
	String* decodedString =	Marshal::PtrToStringAnsi(pDecoded);

	if (! decodedString->Equals("ACK") )
	{
		return;
	}

	message = count.ToString();
	messageBuffer = Marshal::StringToHGlobalAnsi(message);
	pMessage = (char*) messageBuffer.ToPointer();
	pDecoded = _pBaRobot->SendString(pMessage);
	decodedString =	Marshal::PtrToStringAnsi(pDecoded);

	if (! decodedString->Equals("ACK") )
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		messageBuffer = Marshal::StringToHGlobalAnsi(commandList[i]);
		pMessage = (char*) messageBuffer.ToPointer();
		pDecoded = _pBaRobot->SendString(pMessage);
		decodedString =	Marshal::PtrToStringAnsi(pDecoded);

		System::Console::WriteLine(decodedString);		
		// deletion 
		pDecoded = new char[1];
		pDecoded[0] = '\0';
		delete[] pDecoded;
		Marshal::FreeHGlobal(pMessage);
	}
}