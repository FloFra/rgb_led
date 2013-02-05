/*
 * rgbledctl.c - Serial RGB LED control command line interface
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
#include <unistd.h>
#include <errno.h>
#include <iostream>

#include "rgbled.h"

int main(int argc, char* argv[])
{
    // Check if values for all colors where supplied
    if(argc != 4 and argc != 5) {
        std::cerr << "Usage: " << argv[0] << " RED GREEN BLUE [PORT]" << std::endl
                  << std::endl
                  << "        RED, GREEN and BLUE must in the range of 0 to 255" << std::endl
                  << "        PORT is optional and defaults to /dev/ttyS0" << std::endl;
        
        return 1;
    } 

    // Parse input
    int red_value = atoi(argv[1]);
    int green_value = atoi(argv[2]);
    int blue_value = atoi(argv[3]);

    // Check if port was specified
    const char* port = (argc == 5 ? argv[4] : "/dev/ttyS0");

    // Check if input is valid
    if(red_value < 0 or red_value > 255 or green_value < 0 or green_value > 255 or blue_value < 0 or blue_value > 255) {
        std::cerr << "Error: Color values must be in the range of 0 to 255!";
        return 1;
    }

    // Send out serial command
	rgb_led_t led;

	if(rgbled_connect(&led, port) != 0) {
		std::cerr <<  "Error #" << errno << " while connecting to " << port << " : " << strerror (errno) << std::endl;
		return 1;
	}

	rgbled_set(&led, red_value, green_value, blue_value);
	
	if(rgbled_disconnect(&led) != 0) {
		std::cerr <<  "Error #" << errno << " while disconnecting from " << port << " : " << strerror (errno) << std::endl;
		return 1;
	}

    return 0;
}
