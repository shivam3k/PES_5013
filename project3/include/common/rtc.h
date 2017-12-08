/*
 * rtc.h
 *
 *  Created on: 01-Dec-2017
 *      Author: defaultuser0
 */

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include "project3.h"

void RTC_init(void);
void RTC_Seconds_IRQHandler(void);
uint32_t RTC_read(void);


#endif /* SOURCES_RTC_H_ */
