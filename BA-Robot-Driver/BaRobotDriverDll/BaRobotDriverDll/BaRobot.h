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
		BaRobot(const BaRobot& obj);
		BaRobot& operator=(const BaRobot& rhs) ;
		void SetMode(int tm);
		void SetComPort(int cp);
		bool StartCommunication();
		bool StopCommunication();
		char* SendString(char* message);
		void AddCommand(unsigned char command,unsigned char servoFields[]);
		unsigned char* GetCommand(int index);
	private:
		bool isValidTransferMode;
		bool isConnected;
		char* communicateRS232(char* message);
		int comPort;
		int transferMode;
		int servoCount;
		string toString();
	};
}
#endif // _BAROBOT_H
