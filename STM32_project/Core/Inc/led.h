/*
 * led.h
 *
 *  Created on: Sep 19, 2025
 *      Author: acer
 */
#include "global.h"

#ifndef INC_LED_H_
#define INC_LED_H_

#define LED_ON GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET

extern int horState;
extern int verState;

void setLedH(int);
void setLedV(int);

#endif /* INC_LED_H_ */
