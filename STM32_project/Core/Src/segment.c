/*
 * segment.c
 *
 *  Created on: Sep 19, 2025
 *      Author: acer
 */
#include "segment.h"
int segment_buffer[4] = {0,0,0,0};
GPIO_PinState pinArr[11][7] = {
{0, 0, 0, 0, 0, 0, 1}, //0
{1, 0, 0, 1, 1, 1, 1}, //1
{0, 0, 1, 0, 0, 1, 0}, //2
{0, 0, 0, 0, 1, 1, 0}, //3
{1, 0, 0, 1, 1, 0, 0}, //4
{0, 1, 0, 0, 1, 0, 0}, //5
{0, 1, 0, 0, 0, 0, 0}, //6
{0, 0, 0, 1, 1, 1, 1}, //7
{0, 0, 0, 0, 0, 0, 0}, //8
{0, 0, 0, 0, 1, 0, 0}, //9
{1, 1, 1, 1, 1, 1, 1} //TURN OFF
};

void set7SegH(int num){
	if(num >= 0 && num <= 9){
		for(int i = 0; i < 7;i++){
			HAL_GPIO_WritePin(a_h_GPIO_Port, a_h_Pin << i, pinArr[num][i]);
		}
	}
	else{
		for(int i = 0; i < 7;i++){
			HAL_GPIO_WritePin(a_h_GPIO_Port, a_h_Pin << i, pinArr[10][i]);
	}
	}
}
void set7SegV(int num){
		if(num >= 0 && num <= 9){
			for(int i = 0; i < 7;i++){
				HAL_GPIO_WritePin(a_v_GPIO_Port, a_v_Pin << i, pinArr[num][i]);
			}
		}
		else{
			for(int i = 0; i < 7;i++){
				HAL_GPIO_WritePin(a_v_GPIO_Port, a_v_Pin << i, pinArr[10][i]);
		}
	}
}
void scanLED(int state){
	state = state % 2;
	switch (state){
		case 0:
			HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, GPIO_PIN_RESET); //on
			HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, GPIO_PIN_SET);
			set7SegH(segment_buffer[0]);
			set7SegV(segment_buffer[2]);
			break;
		case 1:
			HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, GPIO_PIN_SET); //on
			HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, GPIO_PIN_RESET);
			set7SegH(segment_buffer[1]);
			set7SegV(segment_buffer[3]);
			break;
	}
}

void updateSegment(int x, int y, int z, int t){
	segment_buffer[0] = x % 10;
	segment_buffer[1] = y % 10;
	segment_buffer[2] = z % 10;
	segment_buffer[3] = t % 10;
}
void updateSegment2Digits(int a, int b){
	segment_buffer[0] = a / 10;
	segment_buffer[1] = a % 10;
	segment_buffer[2] = b / 10;
	segment_buffer[3] = b % 10;
}
