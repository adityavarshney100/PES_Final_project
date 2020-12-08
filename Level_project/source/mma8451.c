/*
 * mma8451.c
 *
 *  Created on: Dec 3, 2020
 *
 *      Author: aditya.vny95
 *
 *
 */
#include <MKL25Z4.H>
#include "mma8451.h"
#include "i2c.h"
#include "delay.h"
#include <math.h>
#include <stdio.h>
#include "fsl_debug_console.h"


int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

//mma data ready
extern uint32_t DATA_READY;



//initializes mma8451 sensor
int init_mma()
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, CTRL_REG1_ACTIVE);
	Delay(5);															// Delay for I2C to settle the value
	if(i2c_read_byte(MMA_ADDR, REG_CTRL1) == CTRL_REG1_ACTIVE)			// Condition to check if the MMA was initialized correctly
	{
		PRINTF("MMA in Active State now\n\r");
		return 1;
	}
	else
		return 0;
}

void test_mma()															// Test function to check the MMA 'WHO AM I' register value
{																		// Verifies the identity of the MMA
	if(i2c_read_byte(MMA_ADDR, REG_WHOAMI) == WHOAMI)
	{
		PRINTF("I2C tested Successfully!!!\n\r");
		PRINTF("MMA Initialized Successfully!!!\n\r");
	}
}


void read_xyz()
{
	int i;																	// Temporary variable for loop
	uint8_t data[6];														// variable to capture repeated read from I2C
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

												// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}
												// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

												// Align for 14 bits
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;
}

void self_test()													// Testing function to verify the output thrown by the accelerometer
{
	PRINTF("Testing Accelerometer Readings.........\n\r");
	int x_test[10], y_test[10], z_test[10];
	int x_sum=0, y_sum=0, z_sum=0;
	for(int i=0;i<10;i++)											// Taking 10 samples to verify our output
	{
		self_test_mode(ON);											// Switching on SELF test mode and storing values
		read_xyz();
		x_test[i]=acc_X;
		y_test[i]=acc_Y;
		z_test[i]=acc_Z;

		self_test_mode(OFF);										// Switching off the SELF test mode and storing values
		read_xyz();
		x_test[i]-=acc_X;											// Calculating the difference between the 2 modes
		y_test[i]-=acc_Y;
		z_test[i]-=acc_Z;

		x_sum+=x_test[i];											// To calculate the average, finding their sum
		y_sum+=y_test[i];
		z_sum+=z_test[i];

	}
	if((x_sum/10 > x_ref_STmode) && (y_sum/10 > y_ref_STmode) && (z_sum/10 > z_ref_STmode))			// checking the average with the reference values
	{
		PRINTF("Accelerometer Readings Verified Successfully!!!\n\r");
	}
	else
	{
		PRINTF("Accelerometer Readings Verification FAILED\n\r");
	}
}

void self_test_mode(int mode)
{
	if(mode == 1)
	{
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);		// Putting into standby mode by clearing the active bit in REG_CTRL1
		Delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL2, 0x80);		// Putting into Self_test mode by setting the ST bit as 1 in REG_CTRL2
		Delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);		// Putting into Active mode by setting the Active bit as 1 in REG_CTRL1
		Delay(5);
	}
	else if(mode == 0)
	{
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);		// Putting into standby mode by clearing the active bit in REG_CTRL1
		Delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL2, 0x00);		// Getting out of the Self test mode by clearing the ST bit in REG_CTRL2
		Delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);		// Going back to the Active mode by setting the active bit to 1 in REG_CTRL1
		Delay(5);
	}

}

void convert_xyz_to_roll_pitch(void)
{
	float ax = acc_X/COUNTS_PER_G,						// Calibrating value of the acceleration for all x,y & z axis
				ay = acc_Y/COUNTS_PER_G,
				az = acc_Z/COUNTS_PER_G;
	roll = atan2(ay, sqrt(ax*ax + az*az))*180/M_PI;		// Converting the values to degrees through inverse tan function
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;

}
