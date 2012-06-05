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
// TransferMode.h

#ifndef _TRANSFERMODE_H
#define _TRANSFERMODE_H

using namespace std;

namespace BaRobotLibrary
{
	public __gc class TransferMode {

	public:
		static const int USB = 0;
		static const int COM = 1;
	};
}

#endif
