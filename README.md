rgb_led
=======

A collection of scripts used to interface a serial controllable RGB LED based on a PICaxe microcontroller. 


PICaxe pinout
-------------

I used a PICaxe 08M since I found a nice presoldered SMD version online. Since I use it as a controller for my power on LED in my NAS computer case, size mattered.

pin 0 = red led
pin 1 = green led
pin 2 = blue led

pin 4 = dummy pin 
Note: Not needed with M2 model, since they support microsecond sleep.

pin 3 = serial input


How to compile
--------------

Upload the .bas to your PICaxe.

To compile the C library and the command line tool download the code, cd into its folder and run:

    mkdir build
    cd build
    cmake ..
    make


To install them into the default prefix run:

    make install
