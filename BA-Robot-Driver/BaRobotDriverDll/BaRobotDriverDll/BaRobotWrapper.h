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
		~BaRobotWrapper();
		void Dispose(bool disposing);
		void Dispose();
		void SetMode(int tm);
		void SetComPort(int cp);
		String* SendString(String* message);
	};
}

#endif // _BAROBOTWRAPPER_H
