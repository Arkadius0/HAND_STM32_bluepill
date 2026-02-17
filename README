### DESCRIPTION OF CODE 
    The project enables control of five servos using five potentiometers with an STM32F103 microcontroller. The system reads values from the potentiometers using an ADC, maps them to a safe angle range (10°-170°) and sets the appropriate servos using PWM.

### FUNCTIONS:
- Control of 5 servos simultaneously
- Reading of 5 potentiometers via ADC
- Safe limitation of servo rotation angle (10°-170°)
- Dead zone eliminating vibrations
- Position update every 20 ms (standard frequency for servos)

### Hardware requirements

* Microcontroller: STM32F103C8 (Blue Pill)
* 5x servo (SG92R or similar)
* 5x potentiometer (10kΩ)

<Power> <supply:>

* STM32: 3.3V
* Servos: 5V (separate power supply!)
* Programmer: ST-Link

### MAP PINS
___________________________________________________
|Serwo	|Pin PWM |	Potentiometer   |	Pin ADC   |
|Servo 0|  PA0	 |       Pot1	    |   PA4 (CH4) |
|Servo 1|  PA1	 |       Pot2	    |   PA5 (CH5) |
|Servo 2|  PA2	 |       Pot3	    |   PA6 (CH6) |
|Servo 3|  PA3	 |       Pot4	    |   PA7 (CH7) |
|Servo 4|  PB0	 |       Pot5	    |   PB1 (CH9) |
---------------------------------------------------

### Startup

- # Preparing the equipment:>

- Connect the potentiometers to the ADC pins.
- Connect the servos to the PWM pins.
- Provide a separate 5V power supply for the servos.
- Connect the ST-Link for programming.

 - # Compilation and uploading:

'pio run --target upload'

- # Testing:

- After uploading the program, all servos will move to the center position (90°).
- Turn the potentiometers – the servos should respond smoothly.
- The ends of the potentiometers correspond to the safe limits of the servos (10° and 170°).

- # Troubleshooting

Problem: Servo shakes or makes noise
 - Solution: Increase DEADZONE in main.c (e.g., to 20-30)
Problem: Servo does not respond across the full range of the potentiometer
 - Solution: Adjust ANGLE_MIN and ANGLE_MAX in pwm_servo.c
Problem: Servo rotates 360° at the ends
 - Solution: Reduce the angle range (e.g., 20°-160°)
Problem: Unstable ADC readings
 - Solution: Add a 100nF capacitor between the potentiometer output and ground

### Author

Arkadiusz
GitHub: https://github.com/Arkadius0

#### License

This project is licensed under the Apache License 2.0.
For details, see the [LICENSE](https://github.com/Arkadius0/Auto_Gate/blob/main/LICENSE) file.