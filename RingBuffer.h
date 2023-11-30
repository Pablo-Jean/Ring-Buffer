/*
 * RingBuffer.h
 *
 *  Created on: Nov 29, 2023
 *      Author: pablo-jean
 */

#ifndef RINGBUFFER_RINGBUFFER_H_
#define RINGBUFFER_RINGBUFFER_H_

/**
 * Includes
 */
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/**
 * Macros
 */

#define RINGBUFFER_INITALIZE_MASK		0x5D

/**
 * Enumerates
 */

typedef enum{
	RINGBUFFER_OK,
	RINGBUFFER_FAIL,
	RINGBUFFER_FULL,
	RINGBUFFER_EMPTY,
	RINGBUFFER_NOT_INIT,
	RINGBUFFER_ALREADY_INIT,

	RINGBUFFER_UNKNOWN = 0xFF
}RingBuffer_e;

typedef enum{
	RINGBUFFER_ELEM_SIZE_8BYTES = 1,
	RINGBUFFER_ELEM_SIZE_16BYTES = 2,
	RINGBUFFER_ELEM_SIZE_32BYTES = 4,
	RINGBUFFER_ELEM_SIZE_64BYTES = 8
}RingBuffer_Elem_Size_e;

/**
 * Structs
 */

typedef struct{
	void* Ring;
	uint32_t RingLen;
	RingBuffer_Elem_Size_e ElemSize;
	uint32_t _head;
	uint32_t _tail;
	uint8_t _init;
	uint8_t _isFull :1;
	uint8_t _isEmpty :1;
	uint8_t _isDynamic :1;
}RingBuffer_t;

/**
 * Publics
 */

RingBuffer_e RingBuffer_Init(RingBuffer_t *handle, RingBuffer_Elem_Size_e ElemSize, uint32_t RingLen, void *buffer);

RingBuffer_e RingBuffer_Destroy(RingBuffer_t *handle);

RingBuffer_e RingBuffer_Push(RingBuffer_t *handle, void* Element);

RingBuffer_e RingBuffer_Pop(RingBuffer_t *handle, void* Element);

RingBuffer_e RingBuffer_State(RingBuffer_t *handle);

RingBuffer_e RingBuffer_Clear(RingBuffer_t *handle);

#endif /* RINGBUFFER_RINGBUFFER_H_ */