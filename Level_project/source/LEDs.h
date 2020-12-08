/*
 * LEDs.h
 *
 *  Created on: Dec 3, 2020
 *      Author: aditya.vny95
 */

#ifndef LEDS_H
#define LEDS_H

// Freedom KL25Z LEDs
#define RED_LED_POS (18)					// on port B
#define GREEN_LED_POS (19)					// on port B
#define BLUE_LED_POS (1)					// on port D
#define PWM_PERIOD (48000)					// PWM period 48000
#define LED_COLOR_STEP (187.5)				// Calculated step size by 48000/256 = 187.5

// function prototypes
void Init_RGB_LEDs(void);
/*
 * This function initiates the LEDs and GPIOs for output
 * Arguments	:		Integer
 * Return type	:		None
 * Return		: 		None
 */

void LED_control(int r,int g,int b);
/*
 * To set the PWM output for all the three LEDs.
 * Arguments	:		Integer, values ranging between 0-255
 * Return type	:		None
 * Return		: 		None
 */

#endif
