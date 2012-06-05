 /**************************************************************************
 *									   									   *
 *      Created: 05.06.2012			     								   *
 *      Author:  Michael Berth / Christian Güthling		   				   *
 *      mail:	 berdsen.home@gmail.com					   				   *
 *      mail:	 guedy87@gmx.de     					   				   *
 *									   									   *
 ***************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ***************************************************************************
 *									   									   *
 * This version of GPL is at http://www.gnu.org/licenses/gpl.html	       *
 *									   									   *
 ***************************************************************************
 */
// BaRobotWrapper.cpp

#include "stdafx.h" 
#include <stdio.h> 
#include <string>
#include <windows.h>
#include "BaRobot.h" 
#include "BaRobotWrapper.h" 

using namespace System::Runtime::InteropServices; 
using namespace BaRobotLibrary;

// Standardkonstruktor
BaRobotWrapper::BaRobotWrapper()
{
	_pBaRobot = new BaRobot();
}

// Standarddestruktor
BaRobotWrapper::~BaRobotWrapper() 
{ 
   Dispose(false); 
} 

// Zum verwerfen des Objectes (GC)
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

// Zum verwerfen des Objectes (GC)
void BaRobotWrapper::Dispose() 
{ 
   Dispose(true); 
}

// Setzen des Modes (COM oder USB)
void BaRobotWrapper::SetMode(int tm)
{
	_pBaRobot->SetMode(tm);
}

// Setzen des Comports
void BaRobotWrapper::SetComPort(int cp)
{
	_pBaRobot->SetComPort(cp);
}

// Starten der Kommunikation
bool BaRobotWrapper::StartCommunication()
{
	return _pBaRobot->StartCommunication();
}

// Stoppen der Kommunikation
bool BaRobotWrapper::StopCommunication()
{
	return _pBaRobot->StopCommunication();
}

// Nachricht an BA-Robot senden
String* BaRobotWrapper::SendString(String* message)
{
	return GetAndSendMessageWrapper(message);
}

// Kopierkonstruktor
BaRobotWrapper::BaRobotWrapper(const BaRobotWrapper& obj)
{
	this->_pBaRobot = obj._pBaRobot;
	*this = obj;
}

// Kopierkonstruktor
BaRobotWrapper& BaRobotWrapper::operator=(const BaRobotWrapper& rhs) 
{
    *this = rhs;
    return *this;
}

// Speichern einer Commandoliste (Format: a0,a1,a2,a3,a4 für jeden Servo einen Wert)
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

// Auslesen der Commandoliste
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

// Zum Ausgeben der Texte
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

// Löschen der Commandoliste die auf dem EEPROM des BA-Robot gespeichert ist
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

// Ausgabe des Kommunikationsprotokolls
String* BaRobotWrapper::ToString()
{
	std::string tempString = _pBaRobot->ToString();
	String* retVal = new System::String(tempString.c_str());
	return retVal;
}

// Kommando zum öffnen des Greifarms
String* BaRobotWrapper::OpenGripper()
{
	String* message = "OPEN_GRIPPER";
	String* decodedString = GetAndSendMessageWrapper(message);
	return decodedString;
}

// Kommando zum schließen des Greifarms
String* BaRobotWrapper::CloseGripper()
{
	String* message = "CLOSE_GRIPPER";
	String* decodedString = GetAndSendMessageWrapper(message);
	return decodedString;
}
