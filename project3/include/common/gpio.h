/*
 * gpio.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Preshit
 */

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_

#include "MKL25Z4.h"
#include "project3.h"

#define RED_LED_INIT		(GPIOB->PDDR |= 1 << 18)	//set port B pin 18 direction as output
#define GREEN_LED_INIT		(GPIOB->PDDR |= 1 << 19)	//set port B pin 19 direction as output
#define BLUE_LED_INIT		(GPIOD->PDDR |= 1 << 1)		//set port D pin 1 direction as output

#define RED_LED_ON			(GPIOB->PCOR |= 1 << 18)	//port B pin 18 set as pin is active low
#define GREEN_LED_ON		(GPIOB->PCOR |= 1 << 19)	//port B pin 19 set as pin is active low
#define BLUE_LED_ON			(GPIOD->PCOR |= 1 << 1)		//port D pin 1 set as pin is active low

#define RED_LED_OFF			(GPIOB->PSOR |= 1 << 18)	//port B pin 18 clear as pin is active low
#define GREEN_LED_OFF		(GPIOB->PSOR |= 1 << 19)	//port B pin 19 clear as pin is active low
#define BLUE_LED_OFF		(GPIOD->PSOR |= 1 << 1)		//port D pin 1 clear as pin is active low

#define RED_LED_TOGGLE		(GPIOB->PTOR |= 1 << 18)	//port B pin 18 toggle
#define GREEN_LED_TOGGLE	(GPIOB->PTOR |= 1 << 19)	//port B pin 19 toggle
#define BLUE_LED_TOGGLE		(GPIOD->PTOR |= 1 << 1)		//port D pin 1 toggle

void GPIO_nrf_init();
void GPIO_led_init();



#endif /* SOURCES_GPIO_H_ */
