/************************************************************************
 *
 * File: fifo.c
 *
 * Author: Sean Duffy
 * Tools: 
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "../inc/fifo.h"

#define MAX_NUM_FIFOS 10

typedef struct {
  uint64_t putI;
  uint64_t getI;
  uint64_t sizeInBytes;
} FIFO_META_DATA_TYPE;

typedef struct {
  FIFO_META_DATA_TYPE metaData;
  uint8_t* data;
} FIFO_TYPE;

typedef enum {
  FIFO_RESULT_SUCCESS = 0,
  FIFO_RESULT_FIFO_FULL,
  FIFO_RESULT_FIFO_EMPTY,
} FIFO_RESULT;

FIFO_TYPE* FIFO_Init(uint64_t sizeInBytes)
{
  if(sizeInBytes)
  {
    return NULL;
  }
  
  FIFO_TYPE* newFifoPtr = malloc (sizeInBytes + sizeof(FIFO_META_DATA_TYPE));
  
  newFifoPtr->metaData.putI = 0;
  newFifoPtr->metaData.getI = 0;
  newFifoPtr->metaData.sizeInBytes = sizeInBytes;
}

FIFO_RESULT FIFO_Put(FIFO_TYPE* fifo, uint8_t dataByte)
{
  if((fifo->metaData.putI + 1) == (fifo->metaData.getI) ||
     ((fifo->metaData.putI == (fifo->metaData.sizeInBytes -1)) && (fifo->metaData.getI == 0)))
  {
    return FIFO_RESULT_FIFO_FULL; 
  }
	
  fifo->metaData.putI += 1;
  
  if(fifo->metaData.putI == fifo->metaData.sizeInBytes)
  {
    fifo->metaData.putI = 0;
  }
  
  fifo->data[fifo->metaData.putI] = dataByte;
  
  return FIFO_RESULT_SUCCESS;
}

FIFO_RESULT FIFO_Get(FIFO_TYPE* fifo, uint8_t* dataByte)
{
  if((fifo->metaData.getI) == (fifo->metaData.putI))
  {
    return FIFO_RESULT_FIFO_EMPTY; 
  }
	
  fifo->metaData.getI += 1;
  
  if(fifo->metaData.getI == fifo->metaData.sizeInBytes)
  {
    fifo->metaData.getI = 0;
  }

  *dataByte = fifo->data[fifo->metaData.getI];
  
  return FIFO_RESULT_SUCCESS;
}

void FIFO_Destroy(FIFO_TYPE* fifo)
{
  free(fifo);
}