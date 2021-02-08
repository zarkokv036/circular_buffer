/**
* @file circular_buffer.c
* @author Zarko Milojicic
*/

#include "circular_buffer.h"


CB_Status_t CircularBuffer_init(CircularBuffer_t *cBuff, void *dataBuffer, size_t capacity, size_t objectSize) {
    if ((cBuff == NULL) || ((dataBuffer == NULL)) || (capacity == 0) || (objectSize == 0))
    {
        return CB_BAD_PARAM;
    }
    
    cBuff->dataBuffer = dataBuffer;
    cBuff->capacity = capacity;
    cBuff->objectSize = objectSize;
    cBuff->count = 0;
    cBuff->readIndex = 0;
    cBuff->writeIndex = 0;
    return CB_OK; 
}


CB_Status_t CircularBuffer_put(CircularBuffer_t *cBuff, const void *item) {

    if ((cBuff == NULL) || (cBuff->dataBuffer == NULL) || (item == NULL))
    {
        return CB_BAD_PARAM;
    }
 
    const size_t objectIndex = cBuff->writeIndex * cBuff->objectSize;
    memcpy(&(cBuff->dataBuffer[objectIndex]), item, cBuff->objectSize); 
    cBuff->writeIndex = (cBuff->writeIndex + 1) % cBuff->capacity;     // this makes it go around in a circle
    
    if (cBuff->count == cBuff->capacity)
    {
        cBuff->readIndex = (cBuff->readIndex + 1) % cBuff->capacity; 
    }
    else
    {
        cBuff->count++;
    }
    return CB_OK;
    
}


CB_Status_t CircularBuffer_get(CircularBuffer_t *cBuff, void *item) {

    if ((cBuff == NULL) || (cBuff->dataBuffer == NULL) || (item == NULL))
    {
        return CB_BAD_PARAM;
    }
    if (cBuff->count == 0)
    {
        return CB_EMPTY;
    }
    
    const size_t objectIndex = cBuff->readIndex * cBuff->objectSize;
    memcpy(item, &(cBuff->dataBuffer[objectIndex]), cBuff->objectSize);
    cBuff->readIndex = (cBuff->readIndex + 1) % cBuff->capacity;// this makes it go around in a circle
    cBuff->count--;
    return CB_OK;
    
}


CB_Status_t CircularBuffer_getSize(const CircularBuffer_t *cBuff, size_t *bufferSize) {
    
    if ((cBuff == NULL) || (cBuff->dataBuffer == NULL) || (bufferSize == NULL))
    {
        return CB_BAD_PARAM;
    }
    *bufferSize = cBuff->count;
    return CB_OK;
}


CB_Status_t CircularBuffer_isFull(const CircularBuffer_t *cBuff) {
    
    if ((cBuff == NULL) || (cBuff->dataBuffer == NULL))
    {
        return CB_BAD_PARAM;
    }
    if (cBuff->count == cBuff->capacity)
    {
        return CB_FULL;
    }
    else
    {
        return CB_NOT_FULL;
    }     
}


CB_Status_t CircularBuffer_isEmpty(const CircularBuffer_t *cBuff) {
    
    if ((cBuff == NULL) || (cBuff->dataBuffer == NULL))
    {
        return CB_BAD_PARAM;
    }
    if (cBuff->count == 0)
    {
        return CB_EMPTY;
    }
    else
    {
        return CB_NOT_EMPTY;
    }
}

