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
// BaRobotWrapper.h

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
