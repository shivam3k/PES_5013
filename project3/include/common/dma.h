/*
 * dma.h
 *
 *  Created on: Dec 3, 2017
 *      Author: Preshit
 */

#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_

#include "MKL25Z4.h"
#include <stdlib.h>
#include <stdint.h>
#include "project3.h"

#define EIGHT_BIT		8
#define SIXTEEN_BIT		16
#define THIRTYTWO_BIT	32

#define EIGHT_BIT_SOURCE_MASK		(DMA_DCR_SSIZE(1))
#define SIXTEEN_BIT_SOURCE_MASK		(DMA_DCR_SSIZE(2))
#define THIRTYTWO_BIT_SOURCE_MASK	(DMA_DCR_SSIZE(0))

#define EIGHT_BIT_DESTINATION_MASK		(DMA_DCR_DSIZE(1))
#define SIXTEEN_BIT_DESTINATION_MASK	(DMA_DCR_DSIZE(2))
#define THIRTYTWO_BIT_DESTINATION_MASK	(DMA_DCR_DSIZE(0))

void memmove_dma(void *src, void *dst, uint32_t length, uint8_t size);
void memset_dma(uint8_t value, void *dst, uint32_t length, uint8_t size);
void DMA0_IRQHandler();

#endif /* SOURCES_DMA_H_ */
