/*
 * button.h
 *
 *  Created on: Sep 17, 2025
 *      Author: acer
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"
#include "main.h"
#define NO_BUTTON 3

#define PRESSED GPIO_PIN_RESET
#define RELEASED GPIO_PIN_SET

int isButtonNoPressed(int);
void getKeyInput();



#endif /* INC_BUTTON_H_ */
