/*
 * stepper.c
 *
 *  Created on: Nov 14, 2019
 *      Author: rishgoel
 */
#include "stepper.h"

void config(int ms1, int ms2, int ms3){
	//TODO
}

void step(int dir1, int dir2){
	int data = (dir2-1)<<1 | (dir1-1);

	if(dir1){
		data |= (1<<2);
	}
	if(dir2){
		data |= (1<<3);
	}
	*PADDR = data;
}
