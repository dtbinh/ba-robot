// BaRobot.h

#ifndef _BAROBOT_H
#define _BAROBOT_H

#include "TransferMode.h"
#include <string>

namespace BaRobotLibrary
{
	__nogc

	public class BaRobot
	{
	public:
		BaRobot();
		void SetMode(int tm);
		void SetComPort(int cp);
		char* SendString(char* message);
	private:
		int comPort;
		int transferMode;
		bool isValidTransferMode;
		char* communicateRS232(char* message);
		string toString();
	};
}
#endif // _BAROBOT_H
