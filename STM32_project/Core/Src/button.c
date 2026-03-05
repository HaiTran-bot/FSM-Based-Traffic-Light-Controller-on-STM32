/*
 * button.c
 *
 *  Created on: Sep 17, 2025
 *      Author: acer
 */

#include "button.h"

int button_flag[NO_BUTTON] = {0,0,0};
int timerForKeyPress[NO_BUTTON] = {100,100,100}; //xu li nhan de moi 1s

int KeyReg0[NO_BUTTON] = {RELEASED, RELEASED, RELEASED};
int KeyReg1[NO_BUTTON] = {RELEASED, RELEASED, RELEASED};
int KeyReg2[NO_BUTTON] = {RELEASED, RELEASED, RELEASED};
int KeyReg3[NO_BUTTON] = {RELEASED, RELEASED, RELEASED};


int isButtonNoPressed(int no){
	if(button_flag[no] == 1){
		button_flag[no] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
    for (int i = 0; i < NO_BUTTON; i++){
        KeyReg2[i] = KeyReg1[i];
        KeyReg1[i] = KeyReg0[i];
        KeyReg0[i] = HAL_GPIO_ReadPin(sw0_GPIO_Port, sw0_Pin << i);

        if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
            if (KeyReg2[i] != KeyReg3[i]){
                KeyReg3[i] = KeyReg2[i];
                if (KeyReg0[i] == PRESSED){
                    timerForKeyPress[i] = 100;
                    button_flag[i] = 1;
                }
            } else {
                timerForKeyPress[i]--;
                if (timerForKeyPress[i] == 0){
                    timerForKeyPress[i] = 10;
                    if (KeyReg3[i] == PRESSED){
                        button_flag[i] = 1;
                    }
                }
            }
        }
    }
}
