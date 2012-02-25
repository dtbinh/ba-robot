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

String* BaRobotWrapper::SendString(String* message)
{
	IntPtr messageBuffer = Marshal::StringToHGlobalAnsi(message);

	char* pMessage = (char*) messageBuffer.ToPointer();

	char* pDecoded = _pBaRobot->SendString(pMessage);

	String* decodedString =	Marshal::PtrToStringAnsi(pDecoded);
	
	delete pDecoded;

	Marshal::FreeHGlobal(pMessage);

	return decodedString;
}
