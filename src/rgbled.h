/*
 * rgbled.h - Serial RGB LED control API
 * Copyright (C) 2013 Florian Franzen
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef RGBLED_H
#define RGBLED_H

#ifdef __cplusplus 
	extern "C" {
#endif

typedef struct {	
    int fd;
} rgb_led_t;

/*
	Opens the connection to a RGB LED.

	@param led is the led you want to connect.
	@param port is the serial port to use e.g. /dev/ttyS0.
*/
int rgbled_connect(rgb_led_t* led, const char* port);

/*
	Change the color of a RGB LED

	@param led is the led whos color you want to change.
	@param red_value is the value of the red led.
	@param green_value is the value of the green led.
	@param blue_value is the value of the blue led.
*/
void rgbled_set(rgb_led_t* led, unsigned char red_value, unsigned char green_value, unsigned char blue_value);

/*
	Closes the connection to a RGB LED.

	@param led is the led you want to disconnect.
*/
int rgbled_disconnect(rgb_led_t* led);

#ifdef __cplusplus
	}
# endif

#endif