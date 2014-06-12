Tesa
====

Working board design and firmware for Tesa
==========================================

Location of part files in libraries:
uC(AtMega328) -> SparkFun-Eagle-Libraries-master/SparkFun-DigitalIC/ATMEGA328_SMT
Touch capacitance(AT42QT1070) -> Adafruit-Eagle-Library-master/adafruit/AT42QT1070
Accelerometer(MMA8452Q) -> SparkFun-Eagle-Libraries-master/Sparkfun-Sensors/MMA8452Q
LED driver(TLC59711) -> Adafruit-Eagle-Library-master/adafruit/TLC59711

Radius of board cut is: 2.436 cm or 0.96"

Size of text is 40 (ratio 10 %) for refdes, and 60 (ratio 16 %) for header names
(these might need to be made larger for readability)

Size of signal traces is 8 mils
Size of power (LED, not Vcc or +3.3V) traces is 16 mils

Touch pads are numbered as follows:
Power -> 1
Micro -> 2
Accel -> 3
Touch -> 4

Leds are numbered as follows:
Power -> 0 (rgb positions to be added)
Micro -> 1 (rgb positions to be added)
Accel -> 2 (rgb positions to be added)
Touch -> 3 (rgb positions to be added)
r=3,g=2,b=1

Logo label text size = 150

Erik, don't forget to label the + and - on the LEDs or everyone will hate you!!!

Double check LED routing on ALL boards!