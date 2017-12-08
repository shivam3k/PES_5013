/*
 * profiler.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Preshit
 */

#include "profiler.h"
#include "project3.h"

void profiler_start()
{
	SysTick->LOAD = SYSTICK_MAX_VALUE;
	SysTick->VAL = 5;
	SysTick->CTRL = 0x00000007;
	overflow=0;
}

void profiler_stop()
{
	SysTick->CTRL = 0x00;
}

volatile uint32_t gettime()
{
	return SysTick->VAL;
}

volatile uint32_t execution_time(uint32_t start_time,uint32_t end_time)
{
	uint32_t start = SYSTICK_MAX_VALUE - start_time;
	uint32_t end = (SYSTICK_MAX_VALUE - end_time)+(overflow*SYSTICK_MAX_VALUE);
	uint32_t clocks = end - start;
	uint8_t time1 = clocks/48;
	return time1;
}

void SysTick_Handler(void)
{
	overflow++;
	if(TPM2_SC & TPM_SC_TOF_MASK)
	{
		TPM2->CNT = 10;							 // clear count
		TPM2_SC &= ~TPM_SC_TOF_MASK;			 // clear timer overflow flag
	}
}
