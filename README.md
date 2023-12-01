<center>
<img src="imgs/logo-education.png"  width="300">

Created for Ouroboros Embedded Education.
</center>

## Description

This is a simple, but flexible, Ring Buffer library, for Embedded Devices, like PIC, STM32, ATMega microcontrollers, and others.

All build in C code, and not chipset dependent. Just clone into your project, and starts using!

## How to Use

- Include the `RingBuffer.h` on your Application file.
- Create one, or more, Ring Buffers instances `RingBuffer_t My_RingBUffer;`.
- Initialize your Ring Buffer `RingBuffer_Init(&My_RingBuffer, ElemSize, RingLen, buffer);`, where:
  - **ElemSize** is the size of each element of the Buffer
  - **RingLen** is the Amount of elements in my buffer
  - **buffer** is the array where the Ring Buffer will insert the Pushed elements. If was NULL, then, the library will use dynamic allocation
- Start **Pushing** and **Popping** elements, using `RingBuffer_Push(&My_RingBuffer, &Element);`, and `RingBuffer_Pop(&My_RingBuffer, &Element);`.
- You, at the end, can deinit your Ring Buffer, justi call `RingBuffer_Destroy(&My_RingBuffer);`.

## Functions

## Examples

I will be build examples in other moment.
