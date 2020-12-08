/*
 * mma8451.h
 *
 *  Created on: Dec 3, 2020
 *      Author: aditya.vny95
 */

#ifndef MMA8451_H
#define MMA8451_H
#include <stdint.h>
#include "fsl_debug_console.h"

#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL2  0x2B
#define REG_CTRL4  0x2D

#define CTRL_REG1_ACTIVE 0x01
#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)
#define x_ref_STmode (181)					// Reference Value of x axis when used in Self test mode
#define y_ref_STmode (255)					// Reference Value of y axis when used in Self test mode
#define z_ref_STmode (1680)					// Reference Value of z axis when used in Self test mode

#define ON (1)								// This is the variable to switch ON the self test mode
#define OFF (0)								// This is the variable to switch OFF the self test mode

int init_mma(void);
/*
 * Initializes mma8451 sensor
 * Arguments	:		Dev, Address
 * Return type	:		Integer
 * Return		: 		1 if initialized correctly, 0 if incorrect initialization
 */

void read_xyz(void);
/*
 * Used to read the values from the MMA accelerometer and stores them in acc_x, acc_y & acc_z variables
 * Arguments	:		NONE
 * Return type	:		NONE
 * Return		: 		NONE
 */

void convert_xyz_to_roll_pitch(void);
/*
 * This function is used to convert accelerometer x,y,z values to roll and pitch
 * Arguments	:		NONE
 * Return type	:		NONE
 * Return		: 		NONE
 */

void test_mma(void);
/*
 * Test function to check the MMA 'WHO AM I' register value
 * Arguments	:		NONE
 * Return type	:		NONE
 * Return		: 		NONE
 */

void self_test(void);
/*
 * Function to verify the accelerometer readings
 * Arguments	:		NONE
 * Return type	:		NONE
 * Return		: 		NONE
 */

void self_test_mode(int mode);
/*
 * Function to switch on and off the self test mode of the MMA,
 * Arguments	:		takes ON or OFF as arguments
 * Return type	:		NONE
 * Return		: 		NONE
 */
extern float roll, pitch;					// Roll is the angle made about the x axis,Pitch is the angle made about the y axis
extern int16_t acc_X, acc_Y, acc_Z;

#endif
