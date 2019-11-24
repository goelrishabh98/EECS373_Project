/*
 * stepper.c
 *
 *  Created on: Nov 14, 2019
 *      Author: rishgoel
 */
#include "stepper.h"
#include "mss_gpio.h"

void stepper_config(int mode1, int mode2){
	MSS_GPIO_set_outputs(mode1 | (mode2<<3));
}

void step(int dir1, int dir2){
	int data = 0;

	if(dir1){
		data |= ((1<<2) | (dir1-1));
	}
	if(dir2){
		data |= ((1<<3)| ((dir2-1)<<1));
	}
	*PADDR = data;
}
