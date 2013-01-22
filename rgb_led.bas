; Serial RGB LED firmware
; (c) by Florian Franzen, 2013

; Define variables
symbol red_value     = b0 
symbol green_value = b1
symbol blue_value   = b2
symbol delay = b3

symbol timeout = w2 

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
	blue_value = 255
	; hue circle 5/6: red rising
	for red_value = 0 to 252 step 4
		let timeout = 511 - red_value
		gosub pulses
	next 
	red_value = 255
	; hue circle 6/6 blue falling
	for blue_value = 252 to 0 step -4
		let timeout = 511 - blue_value
		gosub pulses
	next blue_value
	blue_value = 0
	; hue circle 1/6 : green rising
	for green_value = 0 to 252 step 4
		let timeout = 511 - green_value
		gosub pulses
	next green_value
	green_value = 255
	; hue circle 2/6: red falling
	for red_value = 252 to 0 step -4
		let timeout = 511 - red_value
		gosub pulses
	next red_value
	red_value = 0
	; hue circle 3/6: blue rising
	for blue_value = 0 to 252 step 4
		let timeout = 511 - blue_value
		gosub pulses
	next 
	blue_value = 255
	; hue circle 4/6: green falling
	for green_value = 252 to 0 step -4
		let timeout = 511 - green_value
		gosub pulses
	next green_value
	green_value = 0
	
	; Set default value
	let timeout = 766 - red_value - green_value - blue_value

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
	pulsout green_led, green_value
	pulsout blue_led, blue_value
	pulsout dummy, timeout
	return

; Interrupt function to read serial data
interrupt:
	; Debugging output:
	;sertxd ("Int", cr,lf)

	; Read serial data
	serin serial_in,N4800_8, ("RGB"), red_value, green_value, blue_value
	let timeout = 766 - red_value - green_value - blue_value
	
	; Debugging output:
	;sertxd ("Rec ", #red_value, ", ", #green_value, " and ", #blue_value, cr,lf)
		
	; re-activate interrupt
	setint %00001000, %00001000
	return