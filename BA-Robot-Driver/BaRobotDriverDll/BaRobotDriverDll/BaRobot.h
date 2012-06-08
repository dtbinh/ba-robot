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
		void AskSpeed();
		int GetSpeed();
	private:
		bool isValidTransferMode;
		bool isConnected;
		char* communicateRS232(char* message);
		int comPort;
		int transferMode;
		int servoCount;
		int baud;
		int speed;
	};
}
#endif // _BAROBOT_H
