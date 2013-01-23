; Serial RGB LED firmware
; (c) by Florian Franzen, 2013

#PICAXE 08M

; Define variables
symbol red_value = b0 
symbol red_timeout = b1

symbol green_value = b2
symbol green_timeout = b3

symbol blue_value = b4
symbol blue_timeout = b5

symbol delay = b6

; Define output
symbol red_led     = 0
symbol green_led = 1
symbol blue_led   = 2

symbol dummy = 4

symbol serial_in = 3

output 1, 2, 4

; Choose higher frequency
setfreq m8

; Enable interrupt
setint %00001000, %00001000

	; Initialisation
	green_value = 0
	green_timeout = 255
	blue_value = 255
	blue_timeout = 0
	; hue circle 5/6: red rising
	for red_value = 0 to 252 step 4
		let red_timeout = 255 - red_value
		gosub pulses
	next 
	red_value = 255
	red_timeout = 0
	; hue circle 6/6 blue falling
	for blue_value = 252 to 0 step -4
		let blue_timeout = 255 - blue_value
		gosub pulses
	next blue_value
	blue_value = 0
	blue_timeout = 255
	; hue circle 1/6 : green rising
	for green_value = 0 to 252 step 4
		let green_timeout = 255 - green_value
		gosub pulses
	next green_value
	green_value = 255
	green_timeout = 0
	; hue circle 2/6: red falling
	for red_value = 252 to 0 step -4
		let red_timeout = 255 - red_value
		gosub pulses
	next red_value
	red_value = 0
	red_timeout = 255
	gosub timeout
	; hue circle 3/6: blue rising
	for blue_value = 0 to 252 step 4
		let blue_timeout = 255 - blue_value
		gosub pulses
	next 
	blue_value = 255
	blue_timeout = 0
	gosub timeout
	; hue circle 4/6: green falling
	for green_value = 252 to 0 step -4
		let green_timeout = 255 - green_value
		gosub pulses
	next green_value
	green_value = 0
	green_timeout = 255
	
	; Run main loop
	do
		gosub pulse
	loop

pulses:
	for delay = 1 to 5
		gosub pulse
	next delay
	return
	
; pulse led
pulse:
	pulsout red_led, red_value
	pulsout dummy, red_timeout
	pulsout green_led, green_value
	pulsout dummy, green_timeout
	pulsout blue_led, blue_value
	pulsout dummy, blue_timeout
	return

timeout:
	let red_timeout = 255 - red_value
	let green_timeout = 255 - green_value
	let blue_timeout = 255 - blue_value
	return

; Interrupt function to read serial data
interrupt:
	; Debugging output:
	;sertxd ("Int", cr,lf)

	; Read serial data
	serin serial_in,N4800_8, red_value, green_value, blue_value
	gosub timeout
	
	; Debugging output:
	;sertxd ("Rec ", #red_value, ", ", #green_value, " and ", #blue_value, cr,lf)
		
	; re-activate interrupt
	setint %00001000, %00001000
	return