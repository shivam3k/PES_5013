/*
 * dma.c
 *
 *  Created on: Dec 3, 2017
 *      Author: Preshit
 */

#include "dma.h"

void memmove_dma(void *src, void *dst, uint32_t length, uint8_t size)
{
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;		//enable clock for DMA
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;		//enable clock for DMAMUX

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA MUX channel
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	//clear DMA0 status bits and DMA0 interrupt bit

	DMA_SAR0 = (uint32_t)src;				//copy source address
	DMA_DAR0 = (uint32_t)dst;				//copy destination address

	DMA_DSR_BCR0 |= length;  				// number of bytes to transfer
	DMA_DCR0 |= DMA_DCR_SINC_MASK;			// increment SAR
	DMA_DCR0 |= DMA_DCR_DINC_MASK;			// increment DAR

	if(size==EIGHT_BIT)
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;				// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	else if(size==SIXTEEN_BIT)
		{
			DMA_DCR0 |= SIXTEEN_BIT_SOURCE_MASK;		// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= SIXTEEN_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else if(size==THIRTYTWO_BIT)
		{
			DMA_DCR0 |= THIRTYTWO_BIT_SOURCE_MASK;		// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= THIRTYTWO_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;				// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	DMA_DCR0 |= DMA_DCR_AA_MASK;						//enable auto align

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;			//enable DMA MUX channel

	DMA_DCR0 |= DMA_DCR_EINT_MASK;						//enable DMA interrupt

	NVIC_SetPriority(DMA0_IRQn,0);
	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq;

	DMA_DCR0 |= DMA_DCR_START_MASK;						//start DMA transfer
}

void memset_dma(uint8_t value, void *dst, uint32_t length, uint8_t size)
{
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;		//enable clock for DMA
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;		//enable clock for DMAMUX

	DMAMUX0_CHCFG0 = 0x00;					//disable DMA MUX channel
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	//clear DMA0 status bits and DMA0 interrupt bit

	DMA_SAR0 = (uint32_t)&value;			//copy source address
	DMA_DAR0 = (uint32_t)dst;				//copy destination address

	DMA_DSR_BCR0 |= length;  				// number of bytes to transfer
	DMA_DCR0 |= DMA_DCR_SINC_MASK;			// increment SAR
	DMA_DCR0 |= DMA_DCR_DINC_MASK;			// increment DAR

	if(size==EIGHT_BIT)
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;			// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	else if(size==SIXTEEN_BIT)
		{
			DMA_DCR0 |= SIXTEEN_BIT_SOURCE_MASK;	// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= SIXTEEN_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else if(size==THIRTYTWO_BIT)
		{
			DMA_DCR0 |= THIRTYTWO_BIT_SOURCE_MASK;	// source size: 8-bit, 16-bit or 32-bit
			DMA_DCR0 |= THIRTYTWO_BIT_DESTINATION_MASK;	// destination size: 8-bit, 16-bit or 32-bit
		}

	else
	{
		DMA_DCR0 |= EIGHT_BIT_SOURCE_MASK;			// source size: 8-bit, 16-bit or 32-bit
		DMA_DCR0 |= EIGHT_BIT_DESTINATION_MASK;			// destination size: 8-bit, 16-bit or 32-bit
	}

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;	//enable DMA MUX channel

	DMA_DCR0 |= DMA_DCR_EINT_MASK;			//enable DMA interrupt

	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq;

	DMA_DCR0 |= DMA_DCR_START_MASK;			//start DMA transfer

	//while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));		//check if transfer is completed
}

void DMA0_IRQHandler()
{
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;		//clear DMA0 status bits and DMA0 interrupt bit
}
