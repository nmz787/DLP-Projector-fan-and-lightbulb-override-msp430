DLP-Projector-fan-and-bulb-override-msp430
==========================================

Basically a voltage to frequency converter for low KHz tachometer signals.
It was written to control an Acer 1220H DLP Projector that had 3 bad fan speed encoders and no light bulb.

* P1.0 is the onboard Red LED, it blinks during the light bulb 'warm up' period, it's blinking roughly precedes a Red LED on the projector itself.

* P1.1 connects to the positive lead of an optoisolator. This opto was originally turned on by the high-voltage lamp power supply board, the would cause the brown wire in the cable to the main DLP board to be pulled low to ground.

* P1.2 connects to the (A) fan speed sensor input on the DLP control board. This is a 2 pulse per revolution PC fan.

* P1.3 connects to the (B) fan speed sensor input on the DLP control board. This is a 2 pulse per revolution PC fan.

* P1.4 connects to the (C) fan speed sensor input on the DLP control board. This is a 2 pulse per revolution PC fan.

* P1.5 connects to the (A) fan Vcc output on the DLP control board via a voltage divider since the MSP430 is a 3.3V device

* P1.2 connects to the (B) fan Vcc output on the DLP control board via a voltage divider since the MSP430 is a 3.3V device

* P1.2 connects to the (C) fan Vcc output on the DLP control board via a voltage divider since the MSP430 is a 3.3V device


The min and max voltage I read on the fan Vcc lines was 5V and 10V. I happened to have 1KOhm resistors, and 3 of them take 10V to 3.3V so it was easy.

I haven't found the perfect value for the lampOffTime, it seems to jump around a bit on me, that said, when it works, it keeps the projector on for hours.


P.S. I wrote this using Energia as the compiler/IDE, etc... it has the same look and feel as Arduino... == EASIER!:
http://energia.nu/
https://github.com/energia/Energia