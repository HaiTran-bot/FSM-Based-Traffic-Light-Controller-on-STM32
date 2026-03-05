/*
 * global.h
 *
 *  Created on: Sep 18, 2025
 *      Author: acer
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "button.h"
#include "main.h"
#include "timer.h"
#include "segment.h"
#include "led.h"

#define NONE 0
#define RED 11
#define YEL 21
#define GRN 31
#define ALL 41

#define INIT 1

#define MAN_RED 10
#define MAN_YEL 20
#define MAN_GRN 30

#define IDLE -1

void segmentUpdateAuto();

void fsm_run();
void fsm_auto_hor();
void fsm_auto_ver();
void fsm_man();

void button0_Signal(); //check first button

#endif /* INC_GLOBAL_H_ */
