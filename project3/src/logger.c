/*
 * logger.c

 *
 *  Created on: 03-Dec-2017
 *      Author: defaultuser0
 */

#include "logger.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


Log_t log_buffer;
uint8_t Log_Tx_Data;

uint8_t log_tag[20][26] = 		   {"<LOG INITIALIZED>	",
									"<GPIO INITIALIZED>	",
									"<SYSTEM INITIALIZED>	",
									"<SYSTEM HALTED>   	",
									"<INFO>			",
									"<WARNING>			",
									"<ERROR>			",
									"<PROFILING STARTED>	",
									"<PROFILING RESULT>	",
									"<PROFILING COMPLETED>	",
									"<DATA RECIEVED>		",
									"<DATA ANALYSIS STARTED>	",
									"<DATA ALPHA COUNT>	 ",
									"<DATA NUMERIC COUNT> 	",
									"<DATA PUNCTUATION COUNT>",
									"<DATA MISC COUNT>	",
									"<DATA ANALYSIS COMPLETED>",
									"<HEARTBEAT>		",
									"<DATA INPUT DISABLED>	",
									"<DATA INPUT ENABLED>	"};

void log_pass(Log_Status id0,uint8_t *log_payload, uint8_t length){

	//START_CRITICAL();
	Log_Struct log_struct;					// log structure declared
	log_struct.log_id0 = id0;				// log id
	log_struct.timestamp = RTC->TSR;
	log_struct.payload = log_payload;
	log_struct.len_payload = length;

	log_item(&log_struct);					// calling log_item to add log structure to log buffer
	//END_CRITICAL();
	//log_flag = 0x78;

}

void log_flush(void){
	while(Log_buffer_is_empty(&log_buffer) != LOG_BUFFER_EMPTY){ //wait until log buffer is empty
		Log_buffer_remove_item(&log_buffer, &Log_Tx_Data);
		UART_send(&Log_Tx_Data);
	}
}

void log_id(Log_Status id,uint8_t *str){
	switch(id){
		case LOG_INITIALIZED:								//matching log id to pass the required payload
			log_pass(LOG_INITIALIZED,NULL,0);
			if(log_mode != 0x43){							//send data using log flush if interrupt mode is not enabled
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
		    break;

		case GPIO_INITIALIZED:
			log_pass(GPIO_INITIALIZED,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
          break;

		case SYSTEM_INITIALIZED:
			log_pass(SYSTEM_INITIALIZED,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
             break;

		case SYSTEM_HALTED:
			log_pass(SYSTEM_HALTED,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case INFO:
			log_pass(INFO,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			delay();
			log_string(str);
			break;

		case WARNING:
			log_pass(WARNING,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			log_string(str);
			break;

		case ERROR:
			log_pass(ERROR,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			log_string(str);
			break;

		case PROFILING_STARTED:
			log_pass(PROFILING_STARTED,NULL,0);
			if(log_mode != 0x43){							//send data using log flush if interrupt mode is not enabled
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case PROFILING_RESULT:
			log_pass(PROFILING_RESULT,&time[1],3);
			if(log_mode != 0x43){							//send data using log flush if interrupt mode is not enabled
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case PROFILING_COMPLETED:
			log_pass(PROFILING_COMPLETED,NULL,0);
			if(log_mode != 0x43){							//send data using log flush if interrupt mode is not enabled
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case DATA_RECEIVED:
			log_pass(DATA_RECEIVED,&Rxd_Data,1);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case DATA_ANALYSIS_STARTED:
			log_pass(DATA_ANALYSIS_STARTED,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case DATA_ALPHA_COUNT:
			log_pass(DATA_ALPHA_COUNT,alpha,character_count[1]);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case DATA_NUMERIC_COUNT:
			log_pass(DATA_NUMERIC_COUNT,num,character_count[0]);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case DATA_PUNCTUATION_COUNT:
			log_pass(DATA_PUNCTUATION_COUNT,punc,character_count[2]);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case DATA_MISC_COUNT:
			log_pass(DATA_MISC_COUNT,misc,character_count[3]);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case DATA_ANALYSIS_COMPLETED:
			log_pass(DATA_ANALYSIS_COMPLETED,NULL,0);
			if(log_mode != 0x43){
				log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			break;

		case HEARTBEAT:
			//START_CRITICAL();
			log_pass(HEARTBEAT,NULL,0);
			if(log_mode != 0x43){
			log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
			//END_CRITICAL();
            break;

		case DATA_INPUT_DISABLED:
			log_pass(DATA_INPUT_DISABLED,NULL,0);
			if(log_mode != 0x43){							//send data using log flush if interrupt mode is not enabled
			log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
		    break;

		case DATA_INPUT_ENABLED:
			log_pass(DATA_INPUT_ENABLED,NULL,0);
			if(log_mode != 0x43){							//send data using log flush if interrupt mode is not enabled
			log_flush();}
			else{
				UART0_C2 &= ~UART0_C2_TIE_MASK;
				UART0_C2 |= UART0_C2_TIE_MASK;}
		    break;

		default:
             break;
	}
}

void log_item(Log_Struct *ab){

	uint8_t buffer[80];	//buffer to store ascii values and add them to log buffer
	uint8_t checksum;
	my_itoa(ab->timestamp,buffer,10);
	uint8_t i = 1;
			while(buffer[i] != 0){					//adding timestamp to log buffer
				Log_buffer_add_item(&log_buffer, &buffer[i]);
				checksum ^= buffer[i];
				i++;
				buffer[i-1] = 0;
			}
	i=' ';
	Log_buffer_add_item(&log_buffer,&i);
	uint8_t y;
	y = 0;
	y = (uint8_t)(ab->log_id0);
	my_itoa(y,buffer,10);

	i = '\t';
		Log_buffer_add_item(&log_buffer,&i);

	i = 0;
		while(log_tag[y-100][i] != 0){							// adding log tag to log buffer
			checksum ^= log_tag[y-100][i];
			Log_buffer_add_item(&log_buffer, &log_tag[y-100][i]);
			i++;
		}
	i = '\t';
	Log_buffer_add_item(&log_buffer,&i);


	i = 1;
		while(buffer[i] != 0){
			checksum ^= buffer[i];
			Log_buffer_add_item(&log_buffer, &buffer[i]);		//adding log id to log buffer
			i++;
			buffer[i-1] = 0;
		}

	//Log_buffer_add_item(&log_buffer, &bu);

	i='	';
	Log_buffer_add_item(&log_buffer,&i);

	if(ab->payload != NULL){				//pass payload and length only if payload is not null
		if(ab->log_id0==PROFILING_RESULT || ab->log_id0==DATA_RECEIVED)
		{
		my_itoa(ab->len_payload,buffer,10);
		i=1;
		while(buffer[i] != 0){
		//Log_buffer_add_item(&log_buffer, &buffer[i]);
		i++;
		//buffer[i-1] = 0;
		}
		i = ' ';
		Log_buffer_add_item(&log_buffer,&i);
		Log_buffer_add_item(&log_buffer,&i);
		}
		else
		{
			my_itoa(ab->len_payload,buffer,10);
			i=1;
			while(buffer[i] != 0){
				checksum ^= buffer[i];
			Log_buffer_add_item(&log_buffer, &buffer[i]);
			i++;
			//buffer[i-1] = 0;
		}
			i = ' ';
			Log_buffer_add_item(&log_buffer,&i);
			Log_buffer_add_item(&log_buffer,&i);
		}
		for(i=0;i<ab->len_payload;i++){
			checksum ^= *(ab->payload+i);
			Log_buffer_add_item(&log_buffer,ab->payload +i);
		}
	}

	else{
		i = ' ';
		Log_buffer_add_item(&log_buffer,&i);
		Log_buffer_add_item(&log_buffer,&i);
	}
	i = ' ';
	Log_buffer_add_item(&log_buffer,&i);
	Log_buffer_add_item(&log_buffer,&i);
	my_itoa(checksum,buffer,10);
	Log_buffer_add_item(&log_buffer,&buffer[1]);

	if(ab->log_id0!=INFO){
		i='\r';
		Log_buffer_add_item(&log_buffer,&i);
		i='\n';
		Log_buffer_add_item(&log_buffer,&i);
		i='\r';
		Log_buffer_add_item(&log_buffer,&i);
		i='\n';
		Log_buffer_add_item(&log_buffer,&i);
		}
}

void log_string(uint8_t *str){
	uint8_t d;
	uint8_t i;
	while(*str != 0){
		d = *str;
		UART_send(&d);
		str++;
	}
	i='\r';
	UART_send(&i);
	i='\n';
	UART_send(&i);
	i='\r';
	UART_send(&i);
	i='\n';
	UART_send(&i);
}

void log_data(uint8_t *data, uint8_t length){
	uint8_t i = '\t';
	UART_send(&i);
	i = 0;
	uint8_t l;
	while(i<length){
		l = *(data + i);
		UART_send(&l);
		i++;
	}
}

void log_int(int32_t num){
	uint8_t i = '\t';
	UART_send(&i);
	uint8_t buffer[10];
	uint8_t o = 1;
	my_itoa(num,buffer,10);
	while(buffer[o] != 0){
		UART_send(&buffer[o]);
		o++;
	}
}

void uart_flush(uint8_t *str){
	uint8_t d;
	uint8_t i = '\t';
	UART_send(&i);
	while(*str != 0){
		d = *str;
		UART_send(&d);
		str++;
	}
}
