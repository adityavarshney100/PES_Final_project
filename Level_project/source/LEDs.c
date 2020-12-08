/*
 * LEDs.c
 *
 *  Created on: Dec 3, 2020
 *      Author: aditya.vny95
 */
#include <MKL25Z4.H>
#include "LEDs.h"
#include "gpio_defs.h"

void Init_RGB_LEDs(void)
{
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;						// Blue FTM0_CH1
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(3);							// Mux Alt 4
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;					// Red FTM0_CH1
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(3);						// Mux Alt 3
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;						// Green FTM0_CH1
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(4);						// Mux Alt 3

	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);

	SIM->SOPT2 |=(SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);		// Set clock source for 48Mhz

	SIM->SCGC6 |=SIM_SCGC6_TPM0_MASK;									// Enabling clock for TPM0
	SIM->SCGC6 |=SIM_SCGC6_TPM2_MASK;									// Enabling clock for TPM2

	// BLUE LED
	TPM0->MOD = PWM_PERIOD-1;											// Load the counter and MOD
	TPM0->SC = TPM_SC_PS(1);											//Set TPM count direction to UP with divide by 2 prescalar
	TPM0->CONF |= TPM_CONF_DBGMODE(3);									// Continue operation in Debug mode
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;	//Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnV = 0;											// Set initial duty-cycle
	TPM0->SC |= TPM_SC_CMOD(1);											//Start TPM

	// GREEN LED
	TPM2->MOD = PWM_PERIOD-1;											// Load the counter and MOD for TPM2
	TPM2->SC = TPM_SC_PS(1);											//Set TPM count direction to UP with divide by 2 prescalar for TPM2
	TPM2->CONF |= TPM_CONF_DBGMODE(3);									// Continue operation in Debug mode for TPM2
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;	//Set channel 1 to edge-aligned low-true PWM
	TPM2->CONTROLS[1].CnV = 0;											// Set initial duty-cycle
	TPM2->SC |= TPM_SC_CMOD(1);											//Start TPM

	// RED LED
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;	//Set channel 0 to edge-aligned low-true PWM
	TPM2->CONTROLS[0].CnV = 0;											// Set initial duty-cycle

}

void LED_control(int r,int g,int b)
{
	TPM2->CONTROLS[0].CnV = LED_COLOR_STEP*r;							// Setting the PWM value for RED LED
	TPM2->CONTROLS[1].CnV = LED_COLOR_STEP*g;							// Setting the PWM value for GREEN LED
	TPM0->CONTROLS[1].CnV = LED_COLOR_STEP*b;							// Setting the PWM value for BLUE LED
}


