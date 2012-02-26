// for communication with Com
#include "rs232.h"
// needed for managed dll
#include "stdafx.h"
// includes Basic BaRobot
#include "BaRobot.h"
// Wrapper of BaRobot for managed Code
#include "BaRobotWrapper.h"
// for sleep
#include <windows.h>
// for toString()
#include <sstream>

using namespace std;
using namespace BaRobotLibrary;

BaRobot::BaRobot()
{
	comPort = 0;
	transferMode = TransferMode::COM;
	isValidTransferMode = false;
}

void BaRobot::SetMode(int tm)
{
	transferMode = tm;
	
	if (tm == TransferMode::USB)
		isValidTransferMode = true;
	else
	{
		comPort = 0;
		isValidTransferMode = false;
	}
}

void BaRobot::SetComPort(int port)
{
	if (transferMode == TransferMode::COM)
	{
		if ( (port > 0) && (port < 21) )
		{
		    comPort = port;
		    isValidTransferMode = true;
		}
		else
		{
			comPort = 0;
		}

	}
	else
		comPort = 0;
}

char* BaRobot::SendString(char* message)
{
	// transfermode == Usb || (transfermode == com and port > 1 && port < 21 )
	if (isValidTransferMode && strlen(message) < 90)
	{
		if (transferMode == TransferMode::COM)
			return communicateRS232(message);
		else
			return communicateRS232(message);
	}
	else
	{
		return "No valid transfer mode...";
	}
}

#pragma warning( disable : 4996 )
char* BaRobot::communicateRS232(char* message)
{
	int notOkay = OpenComport(comPort - 1,9600);						// gives 1 if error and 0 if okay
	char* newMessage = new char[strlen(message) + 2];
	int counterBytes = 0;
    
	strcpy(newMessage, message);
	strcat(newMessage, "\n\0");

	if (!notOkay)														// ugly to say if not not okay but the rs232 library give the returncodes that way
	{
		cprintf(comPort - 1, newMessage);   							// writes to the serial line (comPort -1) because Com counts from 1
		char* retBuffer = new char[4096];								// return buffer for reading serial line (what has the device to say?)
		// memset (retBuffer, '0', 4096);
		Sleep(250);														// wait for the device to send (from rs232 library where is said minimum 100 ms)
																		// + 100 seems to small for signs up 80
		counterBytes = PollComport(comPort - 1,(unsigned char*) retBuffer, 4096);   	// read the serial line

		CloseComport(comPort - 1);										// very important to close the serial connection

		// hier umkopieren, weil bei manchen Übertragungen zuviele Zeichen von PollComport gelesen oder gesetzt werden.
		char* buffer = new char[counterBytes + 1];
		for (int i = 0; i < counterBytes; i++)
		{
			buffer[i] = retBuffer[i];
		}
		buffer[counterBytes] = '\0';
		return buffer;												// returns what the device said
	}
	CloseComport(comPort - 1);
	return "Error opening the serial line...";
}

string BaRobot::toString()
{
	stringstream stream;
	stream << "BaRobot: Communication: ";
	if (transferMode == TransferMode::COM)
		stream << "COM\n";
	else
		stream << "USB\n";

	return stream.str();
}
