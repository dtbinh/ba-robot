#ifndef _BAROBOTWRAPPER_H
#define _BAROBOTWRAPPER_H

#include "BaRobot.h"

using namespace System;

namespace BaRobotLibrary
{
	public __gc class BaRobotWrapper : public IDisposable
	{
	private:
		BaRobot __nogc* _pBaRobot;
		String* GetAndSendMessageWrapper(String* message);
	public:
		BaRobotWrapper();
		BaRobotWrapper(const BaRobotWrapper& obj);
		BaRobotWrapper& BaRobotWrapper::operator=(const BaRobotWrapper& rhs) ;
		~BaRobotWrapper();
		void Dispose(bool disposing);
		void Dispose();
		void SetMode(int tm);
		void SetComPort(int cp);
		bool StartCommunication();
		bool StopCommunication();
		String* SendString(String* message);
		String* StoreCommandList(String* commandList[], int count);
		String* GetCommandList();
		String* EraseCommandList();
		String* OpenGripper();
		String* CloseGripper();
		String* ToString();
	};
}

#endif // _BAROBOTWRAPPER_H
