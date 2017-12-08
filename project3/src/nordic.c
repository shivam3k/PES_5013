/*
 * nordic.c
 *
 *  Created on: Nov 26, 2017
 *      Author: Preshit
 */

#include "nordic.h"

uint8_t nrf_read_register(uint8_t reg)
{
	uint8_t a;
	SPI_write_byte(R_REGISTER|reg);			//sending read command
	delay();
	SPI_read_byte();
	SPI_write_byte(0xFF);					//sending dummy value
	delay();
	a=SPI_read_byte();						//reading value from register
	return a;
}

void nrf_write_register(uint8_t reg, uint8_t value)
{
	SPI_write_byte(W_REGISTER|reg);			//sending write command
	delay();
	SPI_read_byte();
	SPI_write_byte(value);					//sending value to be written
	delay();
	SPI_read_byte();
}

uint8_t nrf_read_status()
{
	uint8_t a;
	nrf_chip_enable();						//chip enable
	a = nrf_read_register(STATUS_REG);		//read value of status register and return value in a
	nrf_chip_disable();						//chip disable
	return a;
}

uint8_t nrf_read_config()
{
	uint8_t a;
	nrf_chip_enable();						//chip enable
	a = nrf_read_register(CONFIG_REG);		//read value of config register and return value in a
	nrf_chip_disable();
	return a;
}

void nrf_write_config(uint8_t config)
{
	nrf_chip_enable();						//chip enable
	nrf_write_register(CONFIG_REG,config); 	//send config register address and value to be written in the register
	nrf_chip_disable();						//chip disable
}

uint8_t nrf_read_rf_setup()
{
	uint8_t a;
	nrf_chip_enable();						//chip enable
	a = nrf_read_register(RF_SETUP_REG);	//read value of rf setup register and return value in a
	nrf_chip_disable();						//chip disable
	return a;
}

void nrf_write_rf_setup(uint8_t config)
{
	nrf_chip_enable();						//chip enable
	nrf_write_register(RF_SETUP_REG,config);//send rf setup register address and value to be written in the register
	nrf_chip_disable();						//chip disable
}

uint8_t nrf_read_rf_ch()
{
	uint8_t a;
	nrf_chip_enable();						//chip enable
	a = nrf_read_register(RF_CH_REG);		//read value of rf ch register and return value in a
	nrf_chip_disable();						//chip disable
	return a;
}

void nrf_write_rf_ch(uint8_t channel)
{
	nrf_chip_enable();						//chip enable
	nrf_write_register(RF_CH_REG,channel);	//send rf ch register address and value to be written in the register
	nrf_chip_disable();						//chip disable
}

void nrf_read_TX_ADDR(uint8_t *address)
{
	uint8_t i;
	nrf_chip_enable();						//chip enable
	SPI_write_byte(R_REGISTER|TX_ADDR);		//sending read command in tx_addr register
	delay();
	SPI_read_byte();
	for(i=0;i<5;i++)
	{
		SPI_write_byte(0xFF);				//sending dummy value
		delay();
		*(address+i) = SPI_read_byte();		//reading value from register and storing it in a pointer
	}
	nrf_chip_disable();						//chip disable
}

void nrf_write_TX_ADDR(uint8_t *tx_addr)
{
	uint8_t i=0;
	nrf_chip_enable();						//chip enable
	SPI_write_byte(W_REGISTER|TX_ADDR);		//sending write command in tx_addr register
	delay();
	SPI_read_byte();
	for(i=0;i<5;i++)
	{
		SPI_write_byte(*(tx_addr+i));		//writing value in tx_addr register
		delay();
		SPI_read_byte();
	}
	nrf_chip_disable();						//chip disable
}

uint8_t nrf_read_fifo_status()
{
	uint8_t a;
	nrf_chip_enable();						//chip enable
	a= nrf_read_register(FIFO_STATUS_REG);	//read value of fifo status register and return value in a
	nrf_chip_disable();						//chip disable
	return a;
}

void nrf_flush_rx_fifo()
{
	nrf_chip_enable();						//chip enable
	SPI_write_byte(FLUSH_RX);				//writing flush_rx command
	SPI_read_byte();
	nrf_chip_disable();						//chip disable
}

void nrf_flush_tx_fifo()
{
	nrf_chip_enable();						//chip enable
	SPI_write_byte(FLUSH_TX);				//writing flush_tx command
	SPI_read_byte();
	nrf_chip_disable();						//chip disable
}
