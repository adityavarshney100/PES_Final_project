/*
 * Level_project.c
 *
 *  Created on: Dec 3, 2020
 *
 *      Author: aditya.vny95
 *		Reference: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8
 *
 */

/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include <math.h>
#include <board.h>
#include "gpio_defs.h"
#include "LEDs.h"
#include "i2c.h"
#include "mma8451.h"
#include "delay.h"
#include "fsl_debug_console.h"
#include "peripherals.h"
#include "pin_mux.h"

#define PWM_STEP_SIZE (2.83)													// 255/90  i.e. PWM max value divided by the maximum angle calculated


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {

	BOARD_InitBootPins();														// All the necessary initializations
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	BOARD_InitDebugConsole();
#endif
	Init_RGB_LEDs();
	i2c_init();																	// Initialize I2C
	PRINTF("Welcome to the LEVEL\n\r");
	if (!init_mma()) {															// Initialize MMA peripheral
		LED_control(255, 0, 0);													// If the initialization fails, RED LED is switched on at highest intensity i.e. 255
		while (1)																// Unable to Initialize MMA
			;
	}

	test_mma();																	// Testing function to test MMA and I2C
	self_test();																// Testing function to test accelerometer output validity
	while (1) {
		read_xyz();
		convert_xyz_to_roll_pitch();
		float xaxis=fabs(roll);
		float yaxis=fabs(pitch);
		if(xaxis > 5 && yaxis < 5)												// Checking for angle with respect to X-axis if greater than 5 Degrees
		{																		// and if angle with respect to Y-axis is less than 5 Degrees
			LED_control(0,(int)PWM_STEP_SIZE*xaxis, 0);							// Light green LED if xaxis > 5 degrees
			PRINTF("X: %f \t\n\r", xaxis);										// Printing the angle on the UART
		}
		else if (yaxis > 5 && xaxis <5)											// Checking for angle with respect to Y-axis if greater than 5 Degrees
		{																		// and if angle with respect to X-axis is less than 5 Degrees
			LED_control(0,0,(int)PWM_STEP_SIZE*yaxis);							// Light blue LED if yaxis > 5 degrees
			PRINTF("Y: %f \t\n\r", yaxis);										// Printing the angle on the UART
		}
		else if ( xaxis > 5 && yaxis > 5)										// Checking for angle with respect to X-axis & Y-axis if greater
		{																		// than 5 Degrees
			LED_control(0,(int)PWM_STEP_SIZE*xaxis, (int)PWM_STEP_SIZE*yaxis);	// Light green and blue LED if xaxis > 5 Degrees & yaxis > 5 degrees
			PRINTF("X: %f \t", fabs(roll));										// Printing the angle on the UART
			PRINTF("Y: %f\n\r", fabs(pitch));
		}
		else
		{
			LED_control(255, 255, 255);											// Turn on White LED if both (x axis and y axis) angles are less than 5 degrees
			PRINTF("X: %f \t", fabs(roll));										// Printing the angle on the UART
			PRINTF("Y: %f\n\r", fabs(pitch));
		}
		Delay(100);																// Delay for legible output on UART
	}
}
