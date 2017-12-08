/*
 * rtc.c
 *
 *  Created on: 01-Dec-2017
 *      Author: defaultuser0
 */


#include "rtc.h"
#include "logger.h"
#include "project3.h"

void RTC_init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_RTC(1);
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);

	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow

		//**RTC_CLKIN**//
	PORTC_PCR1 |= (PORT_PCR_MUX(1));
	  //32 Khz clock source for RTC
	       //PTC1 as RTC_CLKIN
		//**32KHz Frequency**//
	 //Clockout pin --> 32 KHz
	PORTC_PCR3 |= (PORT_PCR_MUX(0x5));
	SIM_SOPT2 &= ~(SIM_SOPT2_CLKOUTSEL_MASK);
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(4);
	SIM_SOPT1 &= ~(SIM_SOPT1_OSC32KSEL_MASK);
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(2);//PTC3 as CLKOUT

	if (RTC_SR & RTC_SR_TIF_MASK){
		RTC_TSR = 0;   //  this action clears the TIF
	}

	RTC_SR |= RTC_SR_TCE(1);
	RTC_IER &= ~RTC_IER_TSIE(1); 	//Seconds interrupt disable

	    /*Timer enable*/
	//RTC_SR |= RTC_SR_TCE(1);
	NVIC_SetPriority(RTC_Seconds_IRQn,21);
	NVIC_ClearPendingIRQ(RTC_Seconds_IRQn);
	NVIC_EnableIRQ(RTC_Seconds_IRQn);

}

void RTC_Seconds_IRQHandler(void){
	//START_CRITICAL();
	//GPIOB->PTOR |= 1<<18;
	LOG(HEARTBEAT,NULL);
	//END_CRITICAL();

}

uint32_t RTC_read(void){
	return RTC->TSR;
}
