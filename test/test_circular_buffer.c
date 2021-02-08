/*************************************************
* @file test_circular_buffer.c
* @author Zarko Milojicic
*/

/**************************************************
* @brief This file contains tests of Circular Buffer API
*
*/

#include "unity.h"
#include <stddef.h>
#include "circular_buffer.h"
#include <stdbool.h> 
#include <stdio.h>

/***************************************************
* @brief A macro that shortens the initialization process
*
*/ 
#define EMPTY_CIRCULAR_BUFFER(buffer) emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer))


/***********************************************
* @brief A functction that returns a initialized 
* empty circular buffer
*
* @param buffer Pointer to the circular buffer.
* @param capacity A capacity of buffer.
* @param objectSize A object size of one element in buffer.
* @return A created empty circular buffer.
*/   
static CircularBuffer_t emptyCircularBuffer(void *buffer, size_t capacity, size_t objectSize)
{
    // nuliraj sadrzaj buffera
    memset(buffer, 0, capacity * objectSize);

    CircularBuffer_t cbuff;
    CircularBuffer_init(&cbuff, buffer, capacity, objectSize);
    return cbuff;
}

void setUp(void)
{
    
}

void tearDown(void)
{
}


/********************************************    
* @brief A test of CircularBuffer_init() 
* on valid and invalid parameters, and checking
* will it init buffer
*
* @test  
*/   
void test_initFunction(void)
{  
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    
    const size_t objectSize = sizeof(*buffer);
    const size_t capacity = sizeof(buffer) / objectSize; 

    int status;
    // Test for uint64_t
    status = CircularBuffer_init(&cBuff, buffer, capacity, objectSize);
    TEST_ASSERT_EQUAL(CB_OK, status);
    TEST_ASSERT_EQUAL(buffer, cBuff.dataBuffer);
    TEST_ASSERT_EQUAL(10, cBuff.capacity);
    TEST_ASSERT_EQUAL(sizeof(uint64_t), cBuff.objectSize);
    TEST_ASSERT_EQUAL(0, cBuff.writeIndex);
    TEST_ASSERT_EQUAL(0, cBuff.readIndex);
    
    // Test input parametars on invalid value
    status = CircularBuffer_init(&cBuff, buffer, 0, objectSize);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);

    status = CircularBuffer_init(&cBuff, buffer, capacity, 0);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);

    status = CircularBuffer_init(&cBuff, NULL, capacity, objectSize);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);

    status = CircularBuffer_init(NULL, buffer, capacity, objectSize);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);


}


/********************************************    
* @brief A test of CircularBuffer_put()
* on valid and invalid parameters
* 
* @test  
*/ 
void test_inputParametars_of_putFunction(void) 
{
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    uint64_t item = 1;
    // Test on valid and invalid input parametars
    int status = CircularBuffer_put(&cBuff, &item);
    TEST_ASSERT_EQUAL(CB_OK, status);
    status = CircularBuffer_put(&cBuff, NULL);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);
    status = CircularBuffer_put(NULL, &item);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);
}


/********************************************    
* @brief A test that checks are items inserted in
* buffer valid.
*
* @test  
*/
void test_of_putFunction(void)
{
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    // Test if inserted value are ok
    for(size_t i = 0; i < cBuff.capacity; i++)
    {
        uint64_t value = i + 1;
        int status1 = CircularBuffer_put(&cBuff, &value);
        TEST_ASSERT_EQUAL(CB_OK, status1);
        TEST_ASSERT_EQUAL(value, buffer[i]);
        // Test count value
        TEST_ASSERT_EQUAL(i+1, cBuff.count);   
    }
    
}


/********************************************    
* @brief A test that checks will the oldest item
* in buffer be overwritten when overflow occur
* and checks if readIndex goes around in circle. 
*
* @test  
*/
void test_ForgetsOldest_putFunction(void)
{
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    uint64_t item = 0;
    double s=3.542;
    TEST_ASSERT_EQUAL_DOUBLE (0.7, s);
    // Fill buffer
    while(cBuff.count < cBuff.capacity)
    {
        CircularBuffer_put(&cBuff, &item);
        item++;
    }
    // Buffer is now full, readIndex should be moved around when new item is added
    // Try moving it from each possible index
    for (size_t i = 0; i< cBuff.capacity; i++)
    {
        size_t prevReadIndex = cBuff.readIndex;
        
        uint64_t item = 0;
        TEST_ASSERT_EQUAL(CB_OK, CircularBuffer_put(&cBuff, &item));
        
        // Make sure read index was moved
        TEST_ASSERT_EQUAL((prevReadIndex + 1) % cBuff.capacity, cBuff.readIndex);
        TEST_ASSERT_EQUAL(cBuff.writeIndex, cBuff.readIndex);
        
        // Regression test: readIndex could previously overflow due to a bug
        TEST_ASSERT(cBuff.readIndex < cBuff.capacity);
    }
    
     // Finally make sure elements were actually overwritten
        const uint64_t expectedBuffer[10] = { 0 };
        TEST_ASSERT_EQUAL_INT64_ARRAY(expectedBuffer, buffer, cBuff.capacity);
}


/********************************************    
* @brief A test that checks if isEmpty(), isFull() 
* and getSize() works well in normal and boundary conditions.
*
* @test  
*/
void test_isEmptyFunction_isFullFunction(void) {
    uint64_t buffer[10];
    size_t size = 0;
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    // Test when buffer is empty
    TEST_ASSERT_EQUAL(CB_EMPTY, CircularBuffer_isEmpty(&cBuff));
    TEST_ASSERT_EQUAL(CB_NOT_FULL, CircularBuffer_isFull(&cBuff));
    // Test of getSize() when empty
    CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(0, size);
    
    uint64_t item = 0;
    // Test when one item to a full buffer is missing
    while (cBuff.count < (cBuff.capacity - 1))
    {
        CircularBuffer_put(&cBuff, &item);
        TEST_ASSERT_EQUAL(CB_NOT_EMPTY, CircularBuffer_isEmpty(&cBuff));
        TEST_ASSERT_EQUAL(CB_NOT_FULL,  CircularBuffer_isFull(&cBuff));
        
        CircularBuffer_getSize(&cBuff, &size);
        TEST_ASSERT_EQUAL(cBuff.count, size);
    }
    
    CircularBuffer_put(&cBuff, &item);
    // Test when buffer is full
    TEST_ASSERT_EQUAL(CB_NOT_EMPTY, CircularBuffer_isEmpty(&cBuff));
    TEST_ASSERT_EQUAL(CB_FULL,       CircularBuffer_isFull(&cBuff));
    
    // Test of getSize() when buffer is full
    CircularBuffer_getSize(&cBuff,   &size);
    TEST_ASSERT_EQUAL(cBuff.capacity, size);    
    // Test when there is a one item to a empty buffer
    while (cBuff.count > 1)
    {
        CircularBuffer_get(&cBuff, &item);
        TEST_ASSERT_EQUAL(CB_NOT_EMPTY, CircularBuffer_isEmpty(&cBuff));
        TEST_ASSERT_EQUAL(CB_NOT_FULL,  CircularBuffer_isFull(&cBuff));
        
        CircularBuffer_getSize(&cBuff, &size);
        TEST_ASSERT_EQUAL(cBuff.count, size);
    }

    CircularBuffer_get(&cBuff, &item);
    // Test when buffer is empty
    TEST_ASSERT_EQUAL(CB_EMPTY,    CircularBuffer_isEmpty(&cBuff));
    TEST_ASSERT_EQUAL(CB_NOT_FULL, CircularBuffer_isFull(&cBuff));
    
    CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(0, size);
}


/********************************************    
* @brief A test on valid and invalid parameters
* of CircularBuffer_get().
* 
* @test  
*/
void test_inputParametars_getFunction(void)
{
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    
    uint64_t item;
    // Test if return empty
    int status = CircularBuffer_get(&cBuff, &item);
    TEST_ASSERT_EQUAL(CB_EMPTY, status);
     // Test on invalid parametars
    status = CircularBuffer_get(&cBuff, NULL);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);
    status = CircularBuffer_get(NULL, &item);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);  
}


/********************************************    
* @brief A test that checks if readIndex 
* and writeIndex behave right in different
* conditions when use get and put functions.
*
* @test  
*/
void test_indexesWith_getAndPutFunction(void)
{
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    int status;
    
    // Test read after write immediately 
    for(size_t i = 0; i < 2 * cBuff.capacity; i++)
    {
        uint64_t item = i;
        status = CircularBuffer_put(&cBuff, &item);
        
        uint64_t getItem;
        status = CircularBuffer_get(&cBuff, &getItem);
        TEST_ASSERT_EQUAL(item, getItem);      
    }
    
    // Test isEmpty() after reading all 
    status = CircularBuffer_isEmpty(&cBuff);
    TEST_ASSERT_EQUAL(CB_EMPTY, status);
    
    // Test if readIndex same as writeIndex after reading all
    // First fill buffer
    for(size_t i = 0; i < 2 * cBuff.capacity; i++)
    {
        uint64_t item = i;
        status = CircularBuffer_put(&cBuff, &item);
        TEST_ASSERT_EQUAL(CB_OK, status);      
    }
    for(size_t i = 0; i < cBuff.capacity; i++)
    {
        uint64_t item;
        status = CircularBuffer_get(&cBuff, &item);
        
                   
    }
    TEST_ASSERT_EQUAL(cBuff.writeIndex, cBuff.readIndex);
}


/********************************************    
* @brief A test of CircularBuffer_getSize()
* on valid and invalid parameters and check of 
* return value when buffer is empty.
* 
* @test  
*/
void test_inputParametars_getSizeFunction(void) {
    
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    int status;
    uint64_t item;
    
    // Test invalid parametars
    status = CircularBuffer_getSize(&cBuff, NULL);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);
    
    status = CircularBuffer_getSize(NULL, &item);
    TEST_ASSERT_EQUAL(CB_BAD_PARAM, status);
    //Test return value
    status = CircularBuffer_getSize(&cBuff, &item);
    TEST_ASSERT_EQUAL(CB_OK, status);
    TEST_ASSERT_EQUAL(0, item);
    
}
/********************************************    
* @brief A test of basic funcionality of 
* CircularBuffer_getSize() when filled, when overflow
* occur and when everything is read from buffer.
*
* @test  
*/
void test_getSizeFunction(void) {
    
    uint64_t buffer[10];
    CircularBuffer_t cBuff = EMPTY_CIRCULAR_BUFFER(buffer);
    int status;
    size_t size = 0;
    
    //Fill buffer
    for (size_t i = 0; i < cBuff.capacity; i++)
    {
        uint64_t item1 = 1;
        status = CircularBuffer_put(&cBuff, &item1);
        // Test if size increment 
        status = CircularBuffer_getSize(&cBuff, &size);
        TEST_ASSERT_EQUAL(CB_OK, status);
        TEST_ASSERT_EQUAL(i + 1, size);
            
    }
    //Filling with one item over max capacity
    //to test if size stays same
    uint64_t value = 99;
    status = CircularBuffer_put(&cBuff, &value);
    status = CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(cBuff.capacity, size);
    
    uint64_t item;
    // Empty the buffer
    while (cBuff.count > 0)
    {
       CircularBuffer_get(&cBuff, &item);
       status = CircularBuffer_getSize(&cBuff, &size);
       TEST_ASSERT(cBuff.count == size);        
    }
    //Reading empty to see if size stays 0
    status = CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(0, size);
    CircularBuffer_get(&cBuff, &item);
    
    status = CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(0, size);
}


/********************************************    
* @brief A test of all functions when buffer consists
* of only one element.
*
* @test  
*/
void test_bufferWithOneElement(void)
{
    uint8_t bufferSmallest[1];
    CircularBuffer_t cBuff;
    const size_t objectSizeS = sizeof(*bufferSmallest);
    const size_t capacityS = sizeof(bufferSmallest) / objectSizeS; 
    size_t size = 0;
    // Test creating
    int status = CircularBuffer_init(&cBuff, bufferSmallest, capacityS, objectSizeS);
    TEST_ASSERT_EQUAL(CB_OK, status);
    // Test isEmpty() and isFull() and getSize() when empty
    TEST_ASSERT_EQUAL(CB_EMPTY, CircularBuffer_isEmpty(&cBuff));
    TEST_ASSERT_EQUAL(CB_NOT_FULL, CircularBuffer_isFull(&cBuff));
    CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(0, size);
    // Test size when insert one item
    uint8_t value = 1;
    TEST_ASSERT_EQUAL(CB_OK , CircularBuffer_put(&cBuff, &value));
    CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(1, size);
    // Test if indexes are same
    TEST_ASSERT_EQUAL(cBuff.writeIndex, cBuff.readIndex);
    // Test isEmpty() and isFull() when buffer is full
    TEST_ASSERT_EQUAL(CB_NOT_EMPTY, CircularBuffer_isEmpty(&cBuff));
    TEST_ASSERT_EQUAL(CB_FULL, CircularBuffer_isFull(&cBuff));
    // Test if item in buffer is same as inserted one 
    TEST_ASSERT_EQUAL(CB_OK , CircularBuffer_get(&cBuff, &value));
    TEST_ASSERT_EQUAL(1, value);
    //Test if indexes stays same after reading
    TEST_ASSERT_EQUAL(cBuff.writeIndex, cBuff.readIndex);
    //Test size when empty
    CircularBuffer_getSize(&cBuff, &size);
    TEST_ASSERT_EQUAL(0, size);
}
