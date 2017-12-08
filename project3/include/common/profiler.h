/*
 * profiler.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Preshit
 */

#ifndef SOURCES_PROFILER_H_
#define SOURCES_PROFILER_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include <stdlib.h>
#include "project3.h"

#define SYSTICK_MAX_VALUE 0x00FFFFFFU


uint32_t overflow;

void profiler_start();
void profiler_stop();
volatile uint32_t gettime();
volatile uint32_t execution_time(uint32_t start_time,uint32_t end_time);
void SysTick_Handler(void);




#endif /* SOURCES_PROFILER_H_ */
