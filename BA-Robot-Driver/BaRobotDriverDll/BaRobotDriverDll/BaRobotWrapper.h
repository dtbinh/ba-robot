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
		void StoreCommandList(String* commandList[], int count);
	};
}

#endif // _BAROBOTWRAPPER_H
