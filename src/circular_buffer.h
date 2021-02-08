/**
* @file circular_buffer.h
* @author Zarko Milojicic
*/

/**************************************
* @mainpage Circular buffer
* Api for Circular buffer which can hold any type of object              
*
* First step in using this API is to initiate circular buffer using CircularBuffer_init,
* which will return status massage if CBuffer is successfully created or not.
*
* Another two functions of importance are CircularBuffer_put() and CircularBuffer_get() function, which
* are used for pushing item in buffer and reading item from it.
*
* At the beginning the pointer value of field readIndexPtr and writeIndexPtr will be same,
* as the items are inserted and read over time, the pointers will increase.
*
* If the buffer is full and there are more items to push in it, the oldest items
* will be overwritten.
*
*THIS API IS NOT THREAD SAFETY
*/

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H


/***********************************************
* @brief Structure for circular buffer that can
* hold any type of object
*
*/
typedef struct CircularBuffer {
    uint8_t   *dataBuffer;   /**< data buffer which can be any type */
    size_t   readIndex;      /**< where to get next */
    size_t   writeIndex;      /**< where to put next */
	
	
    size_t  capacity ;     /**< max number of items in buffer */
    size_t  objectSize;   /**< size of each object in buffer */
    size_t  count;        /**< current number of items in buffer */
	
} CircularBuffer_t;

/************************************************
* @brief return status message of some functions
*
*
*/
typedef enum CB_Status {
    
    CB_OK,
    CB_FULL,
    CB_NOT_FULL,
    CB_EMPTY,
    CB_NOT_EMPTY,
    CB_BAD_PARAM,
    
} CB_Status_t;

/************************************************
* Function for initialization of the circular buffer.
*
* At the beggining pointer value of readIndexPtr and writeIndexPtr
* will be the same.
* @param cBuff Pointer to the circular buffer.
* @param dataBuffer Pointer to data.
* @param capacity Number of items you have in buffer.
/ @param objectSize Size of data.
* @return a status message of function -- CB_OK or CB_BAD_PARAM.
*/
CB_Status_t CircularBuffer_init(CircularBuffer_t *cBuff, void *dataBuffer, size_t capacity, size_t objectSize);

/************************************************
* Function for adding one item to the buffer
*
* After pushing item to the buffer count will be incremented by one and writeIndex will be
* incremented for objectSize.
* If buffer is full the oldest item will be overwritten,
* if readIndex is at the oldest item in the moment of overwritting
* readIndex will be incremented for object size and count field wont.
*
* @param[in] cBuff Pointer to the circular buffer to which you
* want to add item
* @param[in] item pointer to the Item you want add to the buffer
* @return a status message of function -- CB_OK or CB_BAD_PARAM
*/
CB_Status_t CircularBuffer_put(CircularBuffer_t *cBuff,const void *item);

/*************************************************
* Function for reading one item from the buffer.
*
* After reading item from the buffer, readIndex will be incremented
* and count field will be decremented.
* If buffer is empty readIndex cant be incremented.
* 
* @param[in] cBuff Pointer to the circular buffer from which you
* want to read item.
* @param[out] item Pointer to the var where you want to push the read item .
* @return a status message of function -- CB_OK or CB_BAD_PARAM, CB_EMPTY.
*/
CB_Status_t CircularBuffer_get(CircularBuffer_t *cBuff, void *item);

/**************************************************
* Function for reading current size of buffer.
*
* @param[in] cBuff Pointer to the circular buffer.
* @param[out] bufferSize Pointer to the circular buffer.
* @return CB_OK or CB_BAD_PARAM.
*/
CB_Status_t CircularBuffer_getSize(const CircularBuffer_t *cBuff, size_t *bufferSize);

/**************************************************
* Function for checking if buffer is full.
*
* @param[in] cBuff Pointer to the circular buffer.
* @return CB_FULL, CB_NOT_FULL, BAD_PARAM
*/
CB_Status_t CircularBuffer_isFull(const CircularBuffer_t *cBuff);

/**************************************************
* Function for checking if buffer is empty.
*
* @param[in] cBuff Pointer to the circular buffer.
* @return CB_EMPTY, CB_NOT_EMPTY, BAD_PARAM
*/
CB_Status_t CircularBuffer_isEmpty(const CircularBuffer_t *cBuff);

#endif

