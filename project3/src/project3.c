/*
 * project3.c
 *
 *  Created on: Dec 5, 2017
 *      Author: Preshit
 */

#include "project3.h"


/*----- Global Variables ------------------------------------- -------------*/

uint8_t Rx_Data;
uint8_t Tx_Data;
uint8_t Rxd_Data;

uint8_t character_count[4]={0,0,0,0};
uint8_t char_str[4][10];
uint8_t *num = &char_str[0][0];
uint8_t *alpha = &char_str[1][0];
uint8_t *punc = &char_str[2][0];
uint8_t *misc = &char_str[3][0];
uint8_t time[4];
uint32_t start_time;
uint32_t end_time;
uint8_t t;

void project3()
{
	SystemInit();
	int i;
	for(i=0;i<10;i++)
	{
		*(num+i)=0;
		*(alpha+i)=0;
		*(punc+i)=0;
		*(misc+i)=0;
	}
	log_mode = BLOCKING_MODE;

	CB_init(&Rx_Buffer,50);

	RTC_init();
	UART_configure();

	while(1)
	{
		CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);
		if(Rxd_Data==61)
		{
			Log_buffer_init(&log_buffer,500);
			Rxd_Data=0;
			LOG(LOG_INITIALIZED,NULL);
			LOG(SYSTEM_INITIALIZED,NULL);
			GPIO_nrf_init();
			RTC_IER |= RTC_IER_TSIE(1); 	//Seconds interrupt enable

			while(1)
			{
				CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);
				if(Rxd_Data==47)
				{
					RTC_IER &= ~RTC_IER_TSIE(1); 	//Seconds interrupt disable
					Rxd_Data=0;
					LOG(DATA_INPUT_ENABLED,NULL);
					data();
					RTC_IER |= RTC_IER_TSIE(1); 	//Seconds interrupt enable
				}

				if(Rxd_Data==46)
				{
					RTC_IER &= ~RTC_IER_TSIE(1); 	//Seconds interrupt disable
					Rxd_Data=0;
					LOG(PROFILING_STARTED,NULL);
					profiling();
					RTC_IER |= RTC_IER_TSIE(1); 	//Seconds interrupt enable
				}

				if(Rxd_Data==61)
				{
					RTC_IER &= ~RTC_IER_TSIE(1); 	//Seconds interrupt disable
					Rxd_Data=0;
					break;
				}
			}

			LOG(SYSTEM_HALTED,NULL);
			Log_buffer_destroy(&log_buffer);
		}

		if(Rxd_Data==44)
		{
			profile_test();
		}

		if(Rxd_Data==39)
		{
			spi_nrf_test();
		}
	}
}


void data()
{
	while(1)
	{

    	//----- Removing Data from Rx Buffer  -------------------------------------------- ------

		CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);
		//LOG(DATA_RECEIVED);
	   	//----- Check for Numeric characters  -------------------------------------------- ------
		if((Rxd_Data>47) && (Rxd_Data<58))
	    {
			LOG(DATA_RECEIVED,NULL);
			character_count[0]++;
			*num = Rxd_Data;
			num++;
			Rxd_Data=0;
	    }

	    //----- Check for Alphabetic characters  ----------------------------------------- ------

		else if(((Rxd_Data>64) && (Rxd_Data<91))||((Rxd_Data>96) && (Rxd_Data<123)))
	    {
			LOG(DATA_RECEIVED,NULL);
			character_count[1]++;
			*alpha = Rxd_Data;
			alpha++;
			Rxd_Data=0;
	    }

	    //----- Check for Punctuation characters  ----------------------------------------- ----

		else if(((Rxd_Data>32) && (Rxd_Data<46))||((Rxd_Data>57) && (Rxd_Data<61))||((Rxd_Data>90) && (Rxd_Data<97))||((Rxd_Data>122) && (Rxd_Data<127)))
		{
			LOG(DATA_RECEIVED,NULL);
			character_count[2]++;
			*punc = Rxd_Data;
			punc++;
			Rxd_Data=0;
		}

	    //----- Check for Tab character - ------------------------------------------------ ------

		else if(Rxd_Data==9)
	    {
			num = &char_str[0][0];
			alpha = &char_str[1][0];
			punc = &char_str[2][0];
			misc = &char_str[3][0];
			LOG(DATA_ANALYSIS_STARTED,NULL);
			LOG(DATA_ALPHA_COUNT,NULL);
			LOG(DATA_NUMERIC_COUNT,NULL);
			LOG(DATA_PUNCTUATION_COUNT,NULL);
			LOG(DATA_MISC_COUNT,NULL);
			character_count[0]=0;
			character_count[1]=0;
			character_count[2]=0;
			character_count[3]=0;
			LOG(DATA_ANALYSIS_COMPLETED,NULL);
	        Rxd_Data=0;
	    }

		//----- Check for Miscellaneous characters  ---------------------------------------------

		else if(((Rxd_Data>90)&&(Rxd_Data<97))||(Rxd_Data==127)||(Rxd_Data==27))
	    {
			LOG(DATA_RECEIVED,NULL);
			character_count[3]++;
			*misc = Rxd_Data;
			misc++;
	        Rxd_Data=0;
	    }

		if(Rxd_Data==47)
		{
			Rxd_Data=0;
			LOG(DATA_INPUT_DISABLED,NULL);
			break;
		}
	}
}


void profiling()
{
	while(1)
	{
		CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);
		if(Rxd_Data==49)
		{
			Rxd_Data=0;
			lib_memmove_test(10);
			LOG(INFO,"lib-memmove for 10 bytes");
		}

		if(Rxd_Data==50)
		{
			Rxd_Data=0;
			lib_memset_test(10);
			LOG(INFO,"lib-memset for 10 bytes");
		}

		if(Rxd_Data==51)
		{
			Rxd_Data=0;
			my_memmove_test(10);
			LOG(INFO,"my-memmove for 10 bytes");
		}


		if(Rxd_Data==52)
		{
			Rxd_Data=0;
			my_memset_test(10);
			LOG(INFO,"my-memset for 10 bytes");
		}

		if(Rxd_Data==53)
		{
			Rxd_Data=0;
			dma_memmove_test(10);
			LOG(INFO,"dma-memmove for 10 bytes");
		}

		if(Rxd_Data==54)
		{
			Rxd_Data=0;
			dma_memset_test(10);
			LOG(INFO,"dma-memset for 10 bytes");
		}

		if(Rxd_Data==48)
		{
			Rxd_Data=0;
			LOG(PROFILING_COMPLETED,NULL);
			break;
		}
	}
}
