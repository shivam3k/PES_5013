/*
 * nordic.h
 *
 *  Created on: Nov 26, 2017
 *      Author: Preshit
 */

#ifndef SOURCES_NORDIC_H_
#define SOURCES_NORDIC_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include "MKL25Z4.h"
#include "spi.h"
#include "gpio.h"

#define nrf_chip_enable()  			(PTD_BASE_PTR->PCOR = 1)
#define nrf_chip_disable() 			(PTD_BASE_PTR->PSOR = 1)
#define nrf_transmit_enable()		(PTD_BASE_PTR->PCOR = 1<<5)
#define nrf_transmit_disable()		(PTD_BASE_PTR->PSOR = 1<<5)

#define CONFIG_REG 			(0x00)
#define EN_AA_REG 			(0x01)
#define EN_RXADDR_REG 		(0x02)
#define SETUP_AW_REG 		(0x03)
#define SETUP_RETR_REG 		(0x04)
#define RF_CH_REG 			(0x05)
#define RF_SETUP_REG 		(0x06)
#define STATUS_REG 			(0x07)
#define RX_ADDR_P0_REG 		(0x0A)
#define RX_ADDR_P1_REG 		(0x0B)
#define TX_ADDR 			(0x10)
#define FIFO_STATUS_REG 	(0x17)

#define R_REGISTER     		(0x00)
#define W_REGISTER		    (0x20)
#define W_TX_PAYLOAD 		(0xA0)
#define R_RX_PAYLOAD 		(0x61)
#define FLUSH_TX		    (0xE1)
#define FLUSH_RX		    (0xE2)

// STATUS Register Bits
#define STATUS_RX_DR(x)    	 (uint8_t)((uint8_t)(x)<<6)
#define STATUS_TX_DS(x)      (uint8_t)((uint8_t)(x)<<5)
#define STATUS_MAX_RT(x)     (uint8_t)((uint8_t)(x)<<4)
#define STATUS_RX_P_NO_0   	 (0x00)
#define STATUS_RX_P_NO_1   	 (0x02)
#define STATUS_RX_P_NO_2   	 (0x04)
#define STATUS_RX_P_NO_3   	 (0x06)
#define STATUS_RX_P_NO_4   	 (0x08)
#define STATUS_RX_P_NO_5   	 (0x0A)

// CONFIG Register Bits
#define CONFIG_MASK_RX_DR(x)  (uint8_t)((uint8_t)(x)<<6)
#define CONFIG_MASK_TX_DS(x)  (uint8_t)((uint8_t)(x)<<5)
#define CONFIG_MASK_MAX_RT(x) (uint8_t)((uint8_t)(x)<<4)
#define CONFIG_EN_CRC(x)      (uint8_t)((uint8_t)(x)<<3)
#define CONFIG_CRCO_1      	  (0x00)
#define CONFIG_CRCO_2 	  	  (0x04)
#define CONFIG_POWER_UP    	  (0x02)
#define CONFIG_POWER_DOWN  	  (0x00)
#define CONFIG_PRIM_RX     	  (0x01)
#define CONFIG_PRIM_TX     	  (0x00)

// RF_SETUP Register Bits
#define RF_SETUP_PLL_LOCK(x)  (uint8_t)((uint8_t)(x)<<4)
#define RF_SETUP_RF_DR(x)  	  (uint8_t)((uint8_t)(x)<<3)
#define RF_SETUP_LNA_HCURR(x) (uint8_t)((uint8_t)(x))

// RF_CH Register Bits
#define RF_CH(x)			  (uint8_t)(x);

// FIFO_STATUS Register Bits
#define FIFO_STATUS_TX_REUSE  (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<6))
#define FIFO_STATUS_TX_FULL   (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<5))
#define FIFO_STATUS_TX_EMPTY  (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<4))
#define FIFO_STATUS_RX_FULL   (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<1))
#define FIFO_STATUS_RX_EMPTY  (FIFO_STATUS_REG & (uint8_t)((uint8_t)(1)<<0))


uint8_t nrf_read_register(uint8_t reg);
void nrf_write_register(uint8_t reg, uint8_t value);
uint8_t nrf_read_status();
uint8_t nrf_read_config();
void nrf_write_config(uint8_t config);
uint8_t nrf_read_rf_setup();
void nrf_write_rf_setup(uint8_t config);
uint8_t nrf_read_rf_ch();
void nrf_write_rf_ch(uint8_t channel);
void nrf_read_TX_ADDR(uint8_t *address);
void nrf_write_TX_ADDR(uint8_t *tx_addr);
uint8_t nrf_read_fifo_status();
void nrf_flush_tx_fifo();
void nrf_flush_rx_fifo();

#endif /* SOURCES_NORDIC_H_ */
