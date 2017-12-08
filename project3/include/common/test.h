/*
 * test.h
 *
 *  Created on: Dec 6, 2017
 *      Author: Preshit
 */

#ifndef SOURCES_TEST_H_
#define SOURCES_TEST_H_

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
#include "project3.h"
#include "spi.h"
#include "nordic.h"

enum{
CONFIG=0,
TXADDR=1,
RFSETUP=2,
RFCH=3,
STATUS=4,
FIFO=5
};

/*----- Macros for character strings -------------------------------------------------------*/

#define CON_REG			"Config register write	:"
#define TXADDR_REG 		"TXADDR register write	:"
#define RFSETUP_REG 	"RFSETUP register write	:"
#define RFCH_REG 		"RFCH register write	:"
#define STAT_REG 		"STATUS register read	:"
#define FIFO_REG		"FIFO register read	:"


void profile_test();
void spi_nrf_test();


void dma_memmove_test(uint32_t len);
void dma_memset_test(uint32_t len);
void my_memmove_test(uint32_t len);
void my_memset_test(uint32_t len);
void lib_memmove_test(uint32_t len);
void lib_memset_test(uint32_t len);
void config_reg_test();
void tx_addr_test();
void rf_setup_test();
void rf_ch_reg_test();
void status_reg_test();
void fifo_status_reg_test();
void transmit(uint8_t result);

#endif /* SOURCES_TEST_H_ */
