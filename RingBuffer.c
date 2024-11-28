/*
 * RingBuffer.c
 *
 *  Created on: Nov 29, 2023
 *      Author: pablo-jean
 */


#include "RingBuffer.h"

/**
 * Privates
 */

/**
 * Publics
 */

RingBuffer_e RingBuffer_Init(RingBuffer_t *handle, size_t ElemSize, uint32_t RingLen, void *buffer){
	if (handle == NULL){
		return RINGBUFFER_UNKNOWN;
	}
	if (handle->_init == RINGBUFFER_INITALIZE_MASK){
		return RINGBUFFER_ALREADY_INIT;
	}

	// check if size of element is zero (invalud value)
	// and if the Buffer of the Ring is, at least, of 2 bytes
	if (ElemSize == 0 || RingLen < 2){
		return RINGBUFFER_INVALID_PARAMS;
	}
	// clears the handle and attribute the Element Size and Ring Len
	memset(handle, 0, sizeof(RingBuffer_t));
	handle->ElemSize = ElemSize;
	handle->RingLen = RingLen;
	// check if the developer provided an pre-alocated buffer
	if (buffer == NULL){
		// if the buffer was Null, use dynamic allocation
		handle->Ring = malloc(RingLen*ElemSize);
		if (handle->Ring == NULL){
			return RINGBUFFER_FAIL;
		}
		handle->_isDynamic = 1;
	}
	else{
		handle->Ring = buffer;
	}
	// finish handle initialization
	handle->_isEmpty = 1;
	handle->_init = RINGBUFFER_INITALIZE_MASK;

	return RINGBUFFER_OK;
}

RingBuffer_e RingBuffer_Destroy(RingBuffer_t *handle){
	if (handle == NULL){
		return RINGBUFFER_UNKNOWN;
	}
	if (handle->_init != RINGBUFFER_INITALIZE_MASK){
		return RINGBUFFER_NOT_INIT;
	}

	if (handle->_isDynamic == 1 && handle->Ring != NULL){
		// free the allocated memory
		free(handle->Ring);
	}
	// clear all parameters of Ring Buffer handle
	memset(handle, 0, sizeof(RingBuffer_t));

	return RINGBUFFER_OK;
}

RingBuffer_e RingBuffer_Push(RingBuffer_t *handle, void* Element){
	uint32_t next, offset;

	if (handle == NULL){
		return RINGBUFFER_UNKNOWN;
	}
	if (handle->_init != RINGBUFFER_INITALIZE_MASK){
		return RINGBUFFER_NOT_INIT;
	}

	if (handle->_isFull == 1){
		// Ring Buffer is full!!
		return RINGBUFFER_FULL;
	}
	if (handle->_isEmpty == 1){
		// If the Ring Buffer is empty, when we insert elements
		// the Ring Buffer is not empty anymore.
		handle->_isEmpty = 0;
	}
	// calculate the offset bytes of the array
	offset = handle->ElemSize*handle->_head;
	// copy the data of Element into the Ring Buffer array
	memcpy((void*)(handle->Ring + offset), Element, handle->ElemSize);

	next = handle->_head + 1;
	if (next >= handle->RingLen){
		// We've reached the end of the Buffer, come back to the begin
		next = 0;
	}
	if (next == handle->_tail){
		// Ring Buffer is full of data
		handle->_isFull = 1;
	}
	handle->_head = next;

	return RINGBUFFER_OK;
}

RingBuffer_e RingBuffer_Pop(RingBuffer_t *handle, void* Element){
	uint32_t next, offset;

	if (handle == NULL){
		return RINGBUFFER_UNKNOWN;
	}
	if (handle->_init != RINGBUFFER_INITALIZE_MASK){
		return RINGBUFFER_NOT_INIT;
	}

	if (handle->_isEmpty == 1){
		// our buffer is empty!!
		return RINGBUFFER_EMPTY;
	}
	next = handle->_tail + 1;
	if (next >= handle->RingLen){
		// We've reached the end of the Buffer, come back to the begin
		next = 0;
	}
	if (handle->_isFull == 1){
		// if the Buffer is full, and we remove an element,
		// Te Ring Buffer is not full anymore
		handle->_isFull = 0;
	}
	offset = handle->ElemSize*handle->_tail;
	memcpy(Element, (void*)(handle->Ring + offset), handle->ElemSize);
	handle->_tail = next;

	if (handle->_head == handle->_tail){
		// the tail reached the head, so, all data is over
		// the buffer is empty
		handle->_isEmpty = 1;
	}

	return RINGBUFFER_OK;
}

RingBuffer_e RingBuffer_State(RingBuffer_t *handle){
	if (handle == NULL){
		return RINGBUFFER_UNKNOWN;
	}
	if (handle->_init != RINGBUFFER_INITALIZE_MASK){
		return RINGBUFFER_NOT_INIT;
	}

	if (handle->_isEmpty == 1){
		return RINGBUFFER_EMPTY;
	}
	else if (handle->_isFull == 1){
		return RINGBUFFER_FULL;
	}

	return RINGBUFFER_OK;
}

RingBuffer_e RingBuffer_Clear(RingBuffer_t *handle){
	if (handle == NULL){
		return RINGBUFFER_UNKNOWN;
	}
	if (handle->_init != RINGBUFFER_INITALIZE_MASK){
		return RINGBUFFER_NOT_INIT;
	}

	// fill the Ring Buffer array with 0's
	memset(handle->Ring, 0 , handle->RingLen*handle->ElemSize);
	// reset the state flags
	handle->_head = 0;
	handle->_tail = 0;
	handle->_isFull = 0;
	handle->_isEmpty = 1;

	return RINGBUFFER_OK;
}
