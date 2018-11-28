// /************************************************************************
 // *
 // * File: fifo_unit_test.c
 // *
 // * Author: Sean Duffy
 // * Tools: 
 // * Leveraged Code: See "#include"s
 // * Links: http://cunit.sourceforge.net/index.html
 // *
// ***********************************************************************/

#include "stdio.h"
#include <stdlib.h>
#include "stdint.h"
#include "..\CUnit\CUnit-2.1-3\CUnit\Headers\Basic.h"
#include "..\inc\fifo.h"


void test_FIFO_Init(void)
{
  FIFO_TYPE* fifoPtr;
  
  fifoPtr = FIFO_Init(1);
  CU_ASSERT_EQUAL(fifoPtr, NULL);
  
  fifoPtr = FIFO_Init(10);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
  fifoPtr = FIFO_Init(100);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 100);
  
  fifoPtr = FIFO_Init(0);
  CU_ASSERT_EQUAL(fifoPtr, NULL);
  
  FIFO_Destroy(fifoPtr);
}

void test_FIFO_Put_Get(void)
{
  FIFO_TYPE* fifoPtr;
  uint8_t putData;
  uint8_t getData;
  FIFO_RESULT result;
  
  fifoPtr = FIFO_Init(10);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
  result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_FIFO_EMPTY);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
  result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_FIFO_EMPTY);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
  putData = 0x42;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  
  
  result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0x42);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
  result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_FIFO_EMPTY);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);

  putData =0x43;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 2);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  putData =0xFF;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 3);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  putData =0x00;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 4);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  putData =0x01;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 5);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  putData =0xFE;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 6);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  putData =0xF0;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 7);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  putData =0x0F;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 8);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  putData =0xAA;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 9);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);

  putData =0x55;
  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10); 

  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_FIFO_FULL);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  

  result = FIFO_Put(fifoPtr, putData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_FIFO_FULL);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 1);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
   result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0x43);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 2);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
    result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0xFF);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 3);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
    result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0x00);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 4);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
    result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0x01);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 5);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
    result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0xFE);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 6);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
    result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0xF0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 7);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
    result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0x0F);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 8);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
    result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0xAA);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 9);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
  result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_SUCCESS);
  CU_ASSERT_EQUAL(getData, 0x55);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
 
  result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_FIFO_EMPTY);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);
  
  result = FIFO_Get(fifoPtr, &getData);
  CU_ASSERT_EQUAL(result, FIFO_RESULT_FIFO_EMPTY);
  CU_ASSERT_EQUAL(fifoPtr->metaData.putI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.getI, 0);
  CU_ASSERT_EQUAL(fifoPtr->metaData.sizeInBytes, 10);  
  
  FIFO_Destroy(fifoPtr);
}

int initBankTestSuite(void)
{
	return 0;
}

int cleanBankTestSuite(void)
{
	return 0;
}

int setupBankTestSuite(void) {
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Bank Test Suite", initBankTestSuite, cleanBankTestSuite);
	if (NULL == pSuite) {
		return -1;
	}

	if ((NULL == CU_add_test(pSuite, "test of FIFO_Init()", test_FIFO_Init)))
	{
		return -1;
	}
	if ((NULL == CU_add_test(pSuite, "test of testBankCreation()", test_FIFO_Put_Get)))
	{
		return -1;
	}
	return 0;
}

int main()
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	if (setupBankTestSuite() == -1) { //setupBankTestSuite will add a test suite to the CUnit test registry see further on
		CU_cleanup_registry();
		return CU_get_error();
	}

	// /* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}