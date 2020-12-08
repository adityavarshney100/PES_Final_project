# PES_Final_project
Topic - Level using Accelerometer 
In this project I am trying to replicate a Level using the accelerometer available in the FRDMKL25Z
In addition to the Accelerometer, I have also used the LEDs and the UART features of the board.

Working
When the board is started, I perform a number of checks which are listed below:
- I2C communication check - By reading a byte from a register using I2C
- MMA initialization check - By verifying the 'WHO AM I' bit value  
- Accelerometer output check - By setting the Self Test bit and veryfying its value as mentioned in the data sheet
- After the checks are successful the board is set to work as a Level
- At normal position of the board, The LED shows WHILE color.
- When the value of any of the angles is less than 5 degrees in any direction, the LED continues to show WHITE color. 
- When the board is tilted on its long edge and when the value of the angle exceeds 5 degrees, green LED lights up. The intensity of the light increases as the angle increases
- When the board is tilted on its short edge and when the value of the angle exceeds 5 degrees, blue LED lights up. The intensity of the light increases as the angle increases
- When the board is tilted in such a way that their is angle between both the axis, the LED shows combination of green and blue color 
- Also as the board is tilted the value of the angle is displayed through the UART.
- The output on the UART is similar to any LEVEL, whose value ranges from 0-90 degrees.
