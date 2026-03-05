/*
 * segment.h
 *
 *  Created on: Sep 19, 2025
 *      Author: acer
 */

#ifndef INC_SEGMENT_H_
#define INC_SEGMENT_H_
#include "global.h"

extern int segment_buffer[4]; //4 led en0 en1 en2 en3
GPIO_PinState pinArr[11][7];

void set7SegH(int);
void set7SegV(int);

void scanLED(int);
void updateSegment(int, int, int, int);
void updateSegment2Digits(int, int);




#endif /* INC_SEGMENT_H_ */
