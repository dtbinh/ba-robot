// BaRobot.h

#ifndef _BAROBOT_H
#define _BAROBOT_H

#include "TransferMode.h"
#include <string>

namespace BaRobotLibrary
{
	__nogc

	private class BaRobot
	{
	public:
		BaRobot();
		BaRobot(const BaRobot& obj);
		BaRobot& operator=(const BaRobot& rhs) ;
		void SetMode(int tm);
		void SetComPort(int cp);
		bool StartCommunication();
		bool StopCommunication();
		char* SendString(char* message);
		void AddCommand(unsigned char command,unsigned char servoFields[]);
		unsigned char* GetCommand(int index);
		string ToString();
	private:
		bool isValidTransferMode;
		bool isConnected;
		char* communicateRS232(char* message);
		int comPort;
		int transferMode;
		int servoCount;
		int baud;
	};
}
#endif // _BAROBOT_H
