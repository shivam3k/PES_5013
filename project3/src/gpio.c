/*
 * gpio.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Preshit
 */

#include "gpio.h"
#include "logger.h"

void GPIO_nrf_init()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; 		//enable clock for PORT D

	PORTD_PCR0 |= PORT_PCR_MUX(1); 				//SPI0_PCS0
	PORTD_PCR1 |= PORT_PCR_MUX(2); 				//SPI0_SCK
	PORTD_PCR2 |= PORT_PCR_MUX(2); 				//SPI0_MOSI
	PORTD_PCR3 |= PORT_PCR_MUX(2); 				//SPI0_MISO
	PTD_BASE_PTR->PDDR |= 0x01; 				//Set pin 1 port D i.e PCS as output direction
	LOG(GPIO_INITIALIZED,NULL);
}

void GPIO_led_init()
{
	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;// enable clock for PORT B
	PORTB_BASE_PTR->PCR[18] = PORT_PCR_MUX(1);  // select pin 18 of PORT B as RED LED
	PORTB_BASE_PTR->PCR[19] = PORT_PCR_MUX(1);	// select pin 18 of PORT B as GREEN LED
	RED_LED_INIT;
	GREEN_LED_INIT;
}
