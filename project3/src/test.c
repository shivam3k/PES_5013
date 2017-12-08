/*
 * test.c
 *
 *  Created on: Dec 6, 2017
 *      Author: Preshit
 */

#include "test.h"


void profile_test()
{
	uart_flush("\n\r");
	uart_flush("Number of bytes  ");
	log_int(10);
	log_int(100);
	log_int(1000);
	log_int(5000);
	uart_flush("\n\r");
	uart_flush("lib-memmove	   ");
	lib_memmove_test(10);
	log_int(t);
	lib_memmove_test(100);
	log_int(t);
	lib_memmove_test(1000);
	log_int(t);
	lib_memmove_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("my-memmove	   ");
	my_memmove_test(10);
	log_int(t);
	my_memmove_test(100);
	log_int(t);
	my_memmove_test(1000);
	log_int(t);
	my_memmove_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("dma-memmove	   ");
	dma_memmove_test(10);
	log_int(t);
	dma_memmove_test(100);
	log_int(t);
	dma_memmove_test(1000);
	log_int(t);
	dma_memmove_test(5000);
	log_int(t);
	uart_flush("\n\r\n\r");
	uart_flush("Number of bytes  ");
	log_int(10);
	log_int(100);
	log_int(1000);
	log_int(5000);
	uart_flush("\n\r");
	uart_flush("lib-memset	   ");
	lib_memset_test(10);
	log_int(t);
	lib_memset_test(100);
	log_int(t);
	lib_memset_test(1000);
	log_int(t);
	lib_memset_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("my-memset      	 ");
	my_memset_test(10);
	log_int(t);
	my_memset_test(100);
	log_int(t);
	my_memset_test(1000);
	log_int(t);
	my_memset_test(5000);
	log_int(t);
	uart_flush("\n\r");
	uart_flush("dma-memset	   ");
	dma_memset_test(10);
	log_int(t);
	dma_memset_test(100);
	log_int(t);
	dma_memset_test(1000);
	log_int(t);
	dma_memset_test(5000);
	log_int(t);
	uart_flush("\n\r\n\r");
	Rxd_Data=0;
}

void spi_nrf_test()
{
	SPI_init();								//initialize SPI
	tx_addr_test();							//test function for tx_addr register
	rf_setup_test();						//test function for rf_setup register
	rf_ch_reg_test();						//test function for rf_ch register
	config_reg_test();						//test function for config register
	status_reg_test();						//test function for status register
	fifo_status_reg_test();					//test function for fifo_status register
	Rxd_Data=0;
}

void config_reg_test()
{
	nrf_write_config(0x74);
	uint8_t config;
	config = nrf_read_config();
	delay();
	transmit(CONFIG);
	if(config==0x74){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}

void tx_addr_test()
{
	uint8_t write[5]={0xAA,0x99,0x88,0x77,0x66};
	nrf_write_TX_ADDR(write);
	uint8_t read[5];
	nrf_read_TX_ADDR(read);
	delay();
	uint8_t i=0;
	uint8_t j=0;
	transmit(TXADDR);
	while(i<5)
	{
		if(*(read+i)==*(write+i))
		{
			j++;
		}
		i++;
	}
	if(j==5){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}

void rf_setup_test()
{
	nrf_write_rf_setup(0x09);
	uint8_t setup;
	setup = nrf_read_rf_setup();
	delay();
	transmit(RFSETUP);
	if(setup==0x09){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}

void rf_ch_reg_test()
{
	nrf_write_rf_ch(0x79);
	uint8_t channel;
	channel = nrf_read_rf_ch();
	delay();
	transmit(RFCH);
	if(channel==0x79){
		uart_flush("SUCCESSFUL");
	}
	else{
		uart_flush("FAILED");
	}
	SPI_flush();
}

void status_reg_test()
{
	uint8_t status = nrf_read_status();
	delay();
	transmit(STATUS);
	uart_flush("SUCCESSFUL");
	SPI_flush();
}

void fifo_status_reg_test()
{
	uint8_t fifo = nrf_read_fifo_status();
	delay();
	transmit(FIFO);
	uart_flush("SUCCESSFUL");
	SPI_flush();
}

void transmit(uint8_t result)
{
	uart_flush("\n\r");
	switch (result){
	case CONFIG:
		uart_flush(CON_REG);
		delay();
		break;
	case TXADDR:
		uart_flush(TXADDR_REG);
		delay();
		break;
	case RFSETUP:
		uart_flush(RFSETUP_REG);
		delay();
		break;
	case RFCH:
		uart_flush(RFCH_REG);
		delay();
		break;
	case STATUS:
		uart_flush(STAT_REG);
		delay();
		break;
	case FIFO:
		uart_flush(FIFO_REG);
		delay();
		break;
	}
}

void lib_memmove_test(uint32_t len)
{
	uint32_t i=0;
	uint8_t source[len];
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];

	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memmove(source,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

void my_memmove_test(uint32_t len)
{
	uint32_t i=0;
	uint8_t source[len];
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];

	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	my_memmove(source,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

void dma_memmove_test(uint32_t len)
{
	uint32_t i=0;
	uint8_t source[len];
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];

	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memmove_dma(source,destination,len,EIGHT_BIT);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

void dma_memset_test(uint32_t len)
{
	uint32_t value = 10;
	uint8_t destination[len];
	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memset_dma(value,destination,len,EIGHT_BIT);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

void my_memset_test(uint32_t len)
{
	uint32_t value = 10;
	uint8_t destination[len];
	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	my_memset(value,destination,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}

void lib_memset_test(uint32_t len)
{
	uint32_t value = 10;
	uint8_t destination[len];
	uint32_t start_time;
	uint32_t end_time;

	profiler_start();
	start_time=gettime();
	memset(destination,value,len);
	end_time=gettime();
	profiler_stop();

	t = execution_time(start_time,end_time);

	my_itoa(t,time,10);
	if(Rxd_Data!=44)
	{
		LOG(PROFILING_RESULT,NULL);
	}
	time[0]='\0';
	time[1]='\0';
	time[2]='\0';
	time[3]='\0';
}


