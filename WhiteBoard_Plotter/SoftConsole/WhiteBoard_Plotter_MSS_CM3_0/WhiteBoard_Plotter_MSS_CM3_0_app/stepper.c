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

void step(int dir){
	*PADDR = dir;
}