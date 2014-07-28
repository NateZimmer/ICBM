/*
 * Read_Digital.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Nate
 */

/*
  	This file is part of MSP430 DAC.
    MSP430 DAC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MSP430 DAC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MSP430 DAC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Read_Digital.h"

bool Read_Digital(char * Input_Text)
{
	uint16_t Port_1_Data = Read_Digital_Port(GPIO_PORT1);
	uint16_t Port_2_Data = Read_Digital_Port(GPIO_PORT2);
	sprintf(outputTextBuffer,"\r\n%d,%d\r\n",Port_1_Data,Port_2_Data);
	writeUartString(outputTextBuffer);
	return true;
}
