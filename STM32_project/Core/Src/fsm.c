/*
 * fsm.c
 *
 *  Created on: Sep 19, 2025
 *      Author: acer
 */
#include "global.h"

int autoStateH = INIT; //mode tu dong
int autoStateV = INIT;
int man_state = IDLE;

int red_duration = 5;
int yel_duration = 2;
int green_duration = 3;

int man_Red = 1; //gtri man
int man_Yel = 1;
int man_Grn = 1;

int horCount = 0;
int verCount = 0;
int scan = 0;
void segmentUpdateAuto(){ //update cho trang thai tu dong
	updateSegment2Digits(horCount, verCount);
}
void fsm_run(){
	fsm_auto_hor();
	fsm_auto_ver();
	fsm_man();
}
void button0_Signal(){ //first button pressed
	if (isButtonNoPressed(0) == 1) {
	resetTimer(-1); // reset all state
	horCount = 0;
	verCount = 0;
	updateSegment(IDLE, IDLE, IDLE, IDLE);
	scan = 0;
	setLedH(IDLE);
	setLedV(IDLE);
	autoStateH = IDLE;
	autoStateV = IDLE;
	man_state = MAN_RED; //manual cua red vao dau tien
	set1(100);
	set3(100);
	return;
	}
}
void fsm_auto_hor(){
	switch(autoStateH){
		case INIT:
			set1(red_duration*1000); //timer1 for hor state
			set2(1000); //for counter (1s)
			set3(100); //scanning LEDs
			horCount = red_duration - 1;
			autoStateH = RED;
			break;
		case RED:
			setLedH(RED);
			if(flag2 == 1){
				horCount--;
				if(verCount < 0){verCount = 9;}
				set2(1000);
			}
		   if(flag1 == 1){
			  set1(green_duration*1000);
			  horCount = green_duration - 1;
			  autoStateH = GRN;
		   }
		   if(flag3 == 1){
			   segmentUpdateAuto();
			   scan = (scan == 1) ? 0 : 1;
//			   scan = (scan + 1) % 2;
			   scanLED(scan);
			   set3(100);
		   }
		   button0_Signal();
		   break;
		case GRN:
			setLedH(GRN);
			if(flag2 == 1){
			horCount--;
			if(verCount < 0) {verCount = 9;}
				set2(1000);
			}
			if(flag1 == 1){
				set1(yel_duration*1000);
				horCount = yel_duration - 1;
				autoStateH = YEL;
			}
			if(flag3 == 1){
				segmentUpdateAuto();
				scan = (scan == 1) ? 0 : 1;
//				scan = (scan + 1) % 2;
				scanLED(scan);
				set3(100);
			}
			button0_Signal();
			break;
		case YEL:
					setLedH(YEL);
					if(flag2 == 1){
					horCount--;
					if(verCount < 0) {verCount = 9;}
					set2(1000);
					}
					if(flag1 == 1){
						set1(red_duration*1000);
						horCount = red_duration - 1;
						autoStateH = RED;
					}
					if(flag3 == 1){
						segmentUpdateAuto();
						scan = (scan == 1) ? 0 : 1;
//						scan = (scan + 1) % 2;
						scanLED(scan);
						set3(100);
					}
					button0_Signal();
					break;
		default:
			break;
	}

}
void fsm_auto_ver(){
	switch(autoStateV){
		case INIT:
			set4(green_duration*1000); //timer1 for ver state
			set5(1000); //for counter (1s)
			verCount = green_duration - 1;
			autoStateV = GRN;
			break;
		case GRN:
			setLedV(GRN);
			if(flag5 == 1){
				verCount--;
				set5(1000);
			}
		   if(flag4 == 1){
			  set4(yel_duration*1000);
			  verCount = yel_duration - 1;
			  autoStateV = YEL;
		   }
		   break;
		case YEL:
			setLedV(YEL);
			if(flag5 == 1){
				verCount--;
				set5(1000);
			}
			if(flag4 == 1){
				set4(red_duration*1000);
				verCount = red_duration - 1;
				autoStateV = RED;
			}
			break;
		case RED:
					setLedV(RED);
					if(flag5 == 1){
						verCount--;
						set5(1000);
					}
					if(flag4 == 1){
						set4(green_duration*1000);
						verCount = green_duration - 1;
						autoStateV = GRN;
					}
					break;
		default:
			break;
	}
}
void fsm_man() {
    switch (man_state) {
        case MAN_RED:
        	updateSegment2Digits(man_Red, 2); //gtri va mode
        	if(isButtonNoPressed(0) == 1){
        		man_Yel = 1;
        		man_state = MAN_YEL;
        		setLedH(IDLE);
        		setLedV(IDLE);
        		set1(100); //for next state
        		set3(100);	//scan led
        	}
        	if(isButtonNoPressed(1) == 1){
        		man_Red = (man_Red == 99 ) ? 1 : man_Red + 1;
        	}
            if(isButtonNoPressed(2) == 1){
            	red_duration = man_Red;
            	man_Red = 1;
            }
            if(flag1 == 1){
            	HAL_GPIO_TogglePin(red_h_GPIO_Port, red_h_Pin);
            	HAL_GPIO_TogglePin(red_v_GPIO_Port, red_v_Pin);
            	set1(500); //2hz la 0.5s
            }
            if(flag3 == 1){
            	scan = (scan + 1)%2;
            	scanLED(scan);
            	set3(100);
            }
            break;
        case MAN_YEL:
        	updateSegment2Digits(man_Yel, 3); //gtri va mode
        	        	if(isButtonNoPressed(0)== 1){
        	        		man_Grn = 1;
        	        		man_state = MAN_GRN;
        	        		setLedH(IDLE);
        	        		setLedV(IDLE);
        	        		set1(100); //for next state
        	        		set3(100);	//scan led
        	        	}
        	        	if(isButtonNoPressed(1) == 1){
        	        		man_Yel = (man_Yel== 99 ) ? 1 : man_Yel + 1;
        	        	}
        	            if(isButtonNoPressed(2)== 1){
        	            	yel_duration = man_Yel;
        	            	man_Yel = 1;
        	            }
        	            if(flag1 == 1){
        	            	HAL_GPIO_TogglePin(yel_h_GPIO_Port, yel_h_Pin);
        	            	HAL_GPIO_TogglePin(yel_v_GPIO_Port, yel_v_Pin);
        	            	set1(500); //2hz la 0.5s
        	            }
        	            if(flag3 == 1){
        	            	scan = (scan + 1)%2;
        	            	scanLED(scan);
        	            	set3(100);
        	            }
            break;

        case MAN_GRN:
        	updateSegment2Digits(man_Grn, 4);
        	        	if(isButtonNoPressed(0)== 1){
        	        		//logic setting
        	        		if (yel_duration > green_duration){  //yellow must lower than green
        	        		    green_duration += yel_duration;
        	        		}
        	        		if (red_duration < green_duration + yel_duration){ // red must be total of green and yel
        	        		    red_duration = green_duration + yel_duration;
        	        		}
        	        		if (green_duration >= red_duration + yel_duration){ //adjust green light
        	        		    green_duration = red_duration - yel_duration;
        	        		}
									setLedH(ALL);
									setLedV(ALL);
									set7SegH(0);
									set7SegV(0);
									for (int i = 0; i < 4; i++) {
										HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin << i, 0);
									}
									HAL_Delay(1000);
									setLedH(IDLE);
									setLedV(IDLE);
									resetTimer(NONE);
									man_state = IDLE;
									autoStateH = INIT;
									autoStateV = INIT;
									return;
        	        	}
        	        	if(isButtonNoPressed(1)== 1){
        	        		man_Grn = (man_Grn == 99 ) ? 1 : man_Grn + 1;
        	        	}
        	            if(isButtonNoPressed(2) == 1){
        	            	green_duration = man_Grn;
        	            	man_Grn = 1;
        	            }
        	            if(flag1 == 1){
        	            	HAL_GPIO_TogglePin(grn_h_GPIO_Port, grn_h_Pin);
        	            	HAL_GPIO_TogglePin(grn_v_GPIO_Port, grn_v_Pin);
        	            	set1(500); //2hz la 0.5s
        	            }
        	            if(flag3 == 1){
        	            	scan = (scan + 1)%2;
        	            	scanLED(scan);
        	            	set3(100);
        	            }
            break;

        default:
            break;
    }
}
