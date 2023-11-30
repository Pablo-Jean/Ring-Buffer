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

RingBuffer_e RingBuffer_Init(RingBuffer_t *handle, uint8_t ElemSize, uint32_t RingLen, void *buffer){
	if (handle == NULL){
		return RINGBUFFER_UNKNOWN;
	}
	if (handle->_init == RINGBUFFER_INITALIZE_MASK){
		return RINGBUFFER_ALREADY_INIT;
	}

	memset(handle, 0, sizeof(RingBuffer_t));
	handle->ElemSize = ElemSize;
	handle->RingLen = RingLen;
	if (buffer == NULL){
		handle->Ring = malloc(RingLen*(ElemSize*8));
		if (handle->Ring == NULL){
			return RINGBUFFER_FAIL;
		}
		handle->_isDynamic = 1;
	}
	else{
		handle->Ring = buffer;
	}
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

	if (handle->_isDynamic == 1){
		free(handle->Ring);
	}
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
		handle->_isEmpty = 0;
	}
	offset = handle->ElemSize*handle->_head;
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
		next = 0;
	}
	if (handle->_isFull == 1){
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

	memset(handle->Ring, 0 , handle->RingLen*handle->ElemSize);
	handle->_head = 0;
	handle->_tail = 0;
	handle->_isFull = 0;
	handle->_isEmpty = 1;

	return RINGBUFFER_OK;
}
