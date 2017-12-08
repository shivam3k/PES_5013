/*
 * project3.h
 *
 *  Created on: Dec 5, 2017
 *      Author: Preshit
 */

#ifndef SOURCES_PROJECT3_H_
#define SOURCES_PROJECT3_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "rtc.h"
#include "logger.h"
#include "logbuf.h"
#include "uart.h"
#include "circbuf.h"
#include "gpio.h"
#include "dma.h"
#include "profiler.h"
#include "test.h"

#define START_CRITICAL()	__disable_irq()
#define END_CRITICAL()		__enable_irq()

#define NON_BLOCKING_MODE			(0x43)
#define BLOCKING_MODE				(0x44)

/*------------------------extern variables---------------------------*/
extern uint8_t Tx_Data;
extern uint8_t Rx_Data;
extern uint8_t Rxd_Data;
extern uint8_t character_count[4];
extern uint8_t char_str[4][10];
extern uint8_t *num;
extern uint8_t *alpha;
extern uint8_t *punc;
extern uint8_t *misc;
extern uint8_t time[4];
extern uint8_t t;

void project3();
void data();
void profiling();

#endif /* SOURCES_PROJECT3_H_ */
