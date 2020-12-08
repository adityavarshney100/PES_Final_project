/*
 * delay.c
 *
 *  Created on: Dec 3, 2020
 *      Author: aditya.vny95
 */
#include <MKL25Z4.H>

void Delay (uint32_t dly) 						// Delay function to give a small delay between 2 commands, takes no of ticks as input
{
  volatile uint32_t t;

	for (t=dly*10000; t>0; t--)
		;
}

