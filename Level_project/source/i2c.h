/*
 * i2c.h
 *
 *  Created on: Dec 3, 2020
 *      Author: aditya.vny95
 */

#include <stdint.h>

#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 			i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           I2C0->C1 &= ~I2C_C1_TXAK_MASK

void i2c_init(void);
/*
 *  Initializing I2C
 * Arguments	:		None
 * Return type	:		None
 * Return		: 		None
 */

void i2c_start(void);
/*
 * send start sequence
 * Arguments	:		None
 * Return type	:		None
 * Return		: 		None
 */
void i2c_read_setup(uint8_t dev, uint8_t address);
/*
 * Send device and register addresses
 * Arguments	:		Dev and address
 * Return type	:		None
 * Return		: 		None
 */

uint8_t i2c_repeated_read(uint8_t);
/*
 * read a byte and ack/nack as appropriate
 * Arguments	:		Integer
 * Return type	:		Integer
 * Return		: 		Data
 */

uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
/*
 * using 7bit addressing reads a byte from dev:address
 * Arguments	:		Dev, Address
 * Return type	:		Integer
 * Return		: 		Data
 */

void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);
/*
 * using 7bit addressing writes a byte data to dev:address
 * Arguments	:		Dev, Address, Data
 * Return type	:		None
 * Return		: 		None
 */
