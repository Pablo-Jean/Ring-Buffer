<center>
<img src="imgs/logo-education.png"  width="300">

Created for Ouroboros Embedded Education.
</center>

## Versions Changelog

V1.0.0

- Initial Release


# RingBuffer C Library Documentation

<center><img src="imgs/ring.png"  width="400"></center>

This documentation describes the **RingBuffer** C library, which provides a flexible, type-agnostic ring (circular) buffer implementation for embedded and general-purpose applications. The library supports dynamic or static buffer allocation, efficient push/pop operations, and robust state management.

---

## Table of Contents

- [RingBuffer C Library Documentation](#ringbuffer-c-library-documentation)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Features](#features)
  - [File Structure](#file-structure)
  - [Data Structures](#data-structures)
    - [`RingBuffer_t`](#ringbuffer_t)
  - [Enumerations](#enumerations)
    - [`RingBuffer_e`](#ringbuffer_e)
  - [API Reference](#api-reference)
    - [Initialization](#initialization)
    - [Destruction](#destruction)
    - [Push](#push)
    - [Pop](#pop)
    - [State](#state)
    - [Clear](#clear)
  - [Usage Example](#usage-example)
  - [Notes](#notes)
  - [License](#license)

---

## Overview

The `RingBuffer` library implements a generic circular buffer for storing arbitrary data elements. It is suitable for buffering data streams, implementing queues, or handling producer-consumer problems in embedded systems or desktop applications.

---

## Features

- **Generic:** Supports any element type and size.
- **Dynamic or Static Allocation:** Use a user-provided buffer or let the library allocate memory dynamically.
- **Efficient:** Constant-time push and pop operations.
- **State Management:** Detects and reports full, empty, and uninitialized states.
- **Safe:** Robust error checking and cleanup.

---

## File Structure

- **RingBuffer.h**: Public API, data structures, and macros.
- **RingBuffer.c**: Implementation of all functions.

---

## Data Structures

### `RingBuffer_t`

```c
typedef struct{
    void*    Ring;        // Pointer to buffer memory
    uint32_t RingLen;     // Number of elements in the buffer
    size_t   ElemSize;    // Size of each element
    uint32_t _head;       // Head index (write position)
    uint32_t _tail;       // Tail index (read position)
    uint8_t  _init;       // Initialization flag
    uint8_t  _isFull  :1; // Buffer is full
    uint8_t  _isEmpty :1; // Buffer is empty
    uint8_t  _isDynamic :1; // Buffer was dynamically allocated
} RingBuffer_t;
```


---

## Enumerations

### `RingBuffer_e`

```c
typedef enum{
    RINGBUFFER_OK,
    RINGBUFFER_FAIL,
    RINGBUFFER_INVALID_PARAMS,
    RINGBUFFER_FULL,
    RINGBUFFER_EMPTY,
    RINGBUFFER_NOT_INIT,
    RINGBUFFER_ALREADY_INIT,
    RINGBUFFER_UNKNOWN = 0xFF
} RingBuffer_e;
```


---

## API Reference

### Initialization

```c
RingBuffer_e RingBuffer_Init(RingBuffer_t *handle, size_t ElemSize, uint32_t RingLen, void *buffer);
```

- Initializes the ring buffer.
- If `buffer` is `NULL`, memory is allocated dynamically.
- Returns `RINGBUFFER_OK` on success.

---

### Destruction

```c
RingBuffer_e RingBuffer_Destroy(RingBuffer_t *handle);
```

- Frees dynamic memory (if used) and clears the handle.
- Returns `RINGBUFFER_OK` on success.

---

### Push

```c
RingBuffer_e RingBuffer_Push(RingBuffer_t *handle, void* Element);
```

- Adds an element to the buffer.
- Returns `RINGBUFFER_OK` on success, `RINGBUFFER_FULL` if buffer is full.

---

### Pop

```c
RingBuffer_e RingBuffer_Pop(RingBuffer_t *handle, void* Element);
```

- Removes an element from the buffer and copies it to `Element`.
- Returns `RINGBUFFER_OK` on success, `RINGBUFFER_EMPTY` if buffer is empty.

---

### State

```c
RingBuffer_e RingBuffer_State(RingBuffer_t *handle);
```

- Returns current buffer state: `RINGBUFFER_EMPTY`, `RINGBUFFER_FULL`, or `RINGBUFFER_OK` (not empty or full).

---

### Clear

```c
RingBuffer_e RingBuffer_Clear(RingBuffer_t *handle);
```

- Clears the buffer contents and resets state.

---

## Usage Example

```c
#include "RingBuffer.h"

RingBuffer_t rb;
int buffer[^8];

// Initialize with static buffer for 8 integers
RingBuffer_Init(&rb, sizeof(int), 8, buffer);

int value = 42;
RingBuffer_Push(&rb, &value);

int out;
if (RingBuffer_Pop(&rb, &out) == RINGBUFFER_OK) {
    // out now contains 42
}

// Clean up (not needed for static buffer, but safe)
RingBuffer_Destroy(&rb);
```


---

## Notes

- The buffer length (`RingLen`) must be at least 2.
- Always check return codes for robust error handling.
- For dynamic allocation, remember to call `RingBuffer_Destroy` to avoid memory leaks.
- The implementation is not thread-safe by default.

---

## License

See source files for license details.
Author: Pablo Jean (pablo-jean), November 2023

---

**For further details, refer to the code and comments in `RingBuffer.h` and `RingBuffer.c`.**

