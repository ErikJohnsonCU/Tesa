Tesa
====

Working board design and firmware for Tesa
==========================================

Please note I mis-ordered the 10k resistors as 2k resistors, these will still work as the value of the pull-up resistors on the reset line is very flexible.


Touch pads are numbered as follows:
Power -> 1
Micro -> 2
Accel -> 3
Touch -> 4

Leds are numbered as follows:
Micro -> 0 (rgb positions to be added)
Power -> 1 (rgb positions to be added)
Accel -> 2 (rgb positions to be added)
Touch -> 3 (rgb positions to be added)
r=3,g=2,b=1

Jumper resistor functions:
R105: connects PWRIN pin + to POWER pin 1 (use this to power uC via POWER header or distribute PWRIN pin + to other boards)
RECALL: POWER pin 1 drives LEDs
R108: connects POWER pin 3 to board's Vcc (+3.3V) (use this to run uC off external +3.3V or distribute +3.3V to other boards)

Similar work by other OH designers:
http://www.ofbrooklyn.com/2014/09/6/building-pulse-bloom-biofeedback-burning-man-2014/
