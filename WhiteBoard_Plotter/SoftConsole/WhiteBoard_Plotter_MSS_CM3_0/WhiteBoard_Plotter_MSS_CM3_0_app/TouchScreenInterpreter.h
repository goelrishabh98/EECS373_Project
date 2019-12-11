/*
 * TouchScreenInterpreter.h
 *
 *  Created on: Dec 6, 2019
 *      Author: sarth
 */

#ifndef TOUCHSCREENINTERPRETER_H_
#define TOUCHSCREENINTERPRETER_H_

//Converts drawing on touch screen to board positions
//Since touchscreen is 320 pixels tall and 240 pixels wide,
//use 32x24cm rectangle on whiteboard
//Top left corner of rectangle is therefore (25.91, 15.305)
//Top right: (57.91, 15.305)
//Bottom left: (25.91, 39.305)
//Bottom right: (57.91, 39.305)
#include <math.h>
#include <stdint.h>
#include "stepper.h"

#define HORIZONTALSCALE 10
#define VERTICALSCALE 10
#define DISCRETIZESTEP 10	//How many points to throw away when recreating drawn line
#define RECEIVEDBUFFERSIZE 300	//How many TSPoints buffer should store
#define BOARDWIDTH 83.82
#define BOARDHEIGHT 54.61
#define PI 3.141592654

enum side{LEFT, RIGHT};

//Pythagoras thm: NOTE!! RETURNS c^2 since calculating motor direction only compares two distances, not their true distances
double calculateSquaredDistance(double oneX, double oneY, double twoX, double twoY) {
	return pow(twoX - oneX, 2) + pow(twoY - oneY, 2);
}

int calculateMotorDir(double currentX, double currentY, double targetX, double targetY, int side) {
	//If right motor
	if(side) {
		//If current radius is more than final radius, then right motor needs to spin CW
		if(calculateSquaredDistance(currentX, currentY, BOARDWIDTH, 0.0) >
			calculateSquaredDistance(targetX, targetY, BOARDWIDTH, 0.0)) {
			return CW;
		}
		else {
			return CCW;
		}
	}
	//If left motor
	else {
		//If current radius is more than final radius, then left motor needs to spin CCW
		if(calculateSquaredDistance(currentX, currentY, 0.0, 0.0) >
			calculateSquaredDistance(targetX, targetY, 0.0, 0.0)) {
			return CCW;
		}
		else {
			return CW;
		}
	}
	return -1;	//Should never be here
}

#endif /* TOUCHSCREENINTERPRETER_H_ */
