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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#include "rgbled.h"

int rgbled_connect(rgb_led_t* led, const char* port) {
    // Open serial port
	int fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
		return -1;
	}

    // Get current settings
    struct termios tty;
    memset (&tty, 0, sizeof(tty));
    if (tcgetattr (fd, &tty) != 0) {
        return -1;
    }
    
    // Set speed
    cfsetospeed (&tty, B4800);
    
    // Change settings
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars

    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // ignore break signal
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL); // ignore modem controls,
    
    tty.c_cflag &= ~(PARENB | PARODD | CSTOPB | CRTSCTS);      // shut off parity and other unneeded crust

    // Set new settings
    if (tcsetattr (fd, TCSANOW, &tty) != 0) {
        return -1;
    }
    
    led->fd = fd;
    return 0;
} 

void rgbled_set(rgb_led_t* led, unsigned char r, unsigned char g, unsigned char b) {
    unsigned char  data[] = { r, g, b };
    write (led->fd, data, 3); 
}

int rgbled_disconnect(rgb_led_t* led) {
    return close(led->fd);
}