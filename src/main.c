/************************************************************************
 *
 * File: main.c
 *
 * Author: Sean Duffy
 * Tools: 
 * Leveraged Code: See "#include"s
 * Links: NA
 *
***********************************************************************/

#include "stdio.h"
#include "stdint.h"
#include "C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\inc\uart.h"
#include "C:\Freescale\KSDK_1.3.0\examples\frdmkl25z\demo_apps\hello_world\kds\inc\fifo.h"
#include "board.h"

extern uint8_t printingBlock;

void MAIN_PutFifoDigits(FIFO_TYPE* fifo, uint64_t value)
{
  if(value >= 10)
  {
    MAIN_PutFifoDigits(UARTTxFifoPtr, value/10);
    value = value%10;
  }

  FIFO_Put(UARTTxFifoPtr, '0' + value);
}

// 6. A main() function that uses the uart blocking
// functions to echo received characters one
// at a time back to the sender
int main(void)
{
//  uint8_t receivedCharacter;

  UART_Init();

  newDataSemaphore = 0;

  while(1)
  {
	// Blocking Implementation - Echo Characters
//	  UART_BlockInChar(&receivedCharacter);
//    UART_BlockOutChar(receivedCharacter);

    // Non-Blocking Implementation - Echo Characters
	if(newDataSemaphore == 1)
	{
        newDataSemaphore = 0;
        printingBlock = 1;
        for(uint16_t i = '0'; i < 256; i+=1)
        {
          if(characterHistogram[i] != 0)
          {
        	FIFO_Put(UARTTxFifoPtr, i);
        	UART0_C2 |= UART0_C2_TIE_MASK;
        	FIFO_Put(UARTTxFifoPtr, '-');
        	MAIN_PutFifoDigits(UARTTxFifoPtr, characterHistogram[i]);
        	FIFO_Put(UARTTxFifoPtr, 0x0A); // New Line
        	FIFO_Put(UARTTxFifoPtr, 0x0D); // Carriage Return
          }
        }
        FIFO_Put(UARTTxFifoPtr, '-');
        FIFO_Put(UARTTxFifoPtr, '-');
        FIFO_Put(UARTTxFifoPtr, '-');
        FIFO_Put(UARTTxFifoPtr, '-');
        FIFO_Put(UARTTxFifoPtr, '-');
    	FIFO_Put(UARTTxFifoPtr, 0x0A); // New Line
    	FIFO_Put(UARTTxFifoPtr, 0x0D); // Carriage Return
    	printingBlock = 0;
	}
	else
	{
      // toggle GPIO pin
	}
  }

	
	return 0;
}
