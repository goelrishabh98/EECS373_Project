#ifdef __cplusplus
extern "C" {
#endif

#include "stepper.h"
#include "mss_timer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "TouchScreenInterpreter.h"
#include "xbee.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Globals //////////////////////////////////////////////////////////
int dirLeft = CCW;
int dirRight = CW;

//all in cm
double boardHeight;
double boardWidth;

double xPos;
double yPos;

double RadiusLeft;
double RadiusRight;

int period1 = 100000;
int period2 = 100000;
int counter;
double thres = .01;
double ratio;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// TIMER //////////////////////////////////////////////////////////

void motorLeft(int dir) {
	step(dir, NO);
	if(dir == CW){
		RadiusLeft = RadiusLeft + 3.8*1.8/360/16;
	}
	else if(dir == CCW){
		RadiusLeft = RadiusLeft - 3.8*1.8/360/16;
	}
	++counter;
}
void motorRight(int dir) {
	step(NO, dir);
	if(dir == CCW){
		RadiusRight = RadiusRight + 3.8*1.8/360/16;
	}
	else if(dir == CW){
		RadiusRight = RadiusRight - 3.8*1.8/360/16;
	}
	++counter;
}

//used to initialize hardware
void start_hardware_timer1(){
	MSS_TIM1_init(MSS_TIMER_PERIODIC_MODE);

	MSS_TIM1_load_immediate(period1);
	MSS_TIM1_start();
	MSS_TIM1_enable_irq();
}

void start_hardware_timer2(){
	MSS_TIM2_init(MSS_TIMER_PERIODIC_MODE);

	MSS_TIM2_load_immediate(period2);
	MSS_TIM2_start();
	MSS_TIM2_enable_irq();
}

void Timer1_IRQHandler( void ){
	motorLeft(dirLeft);

	MSS_TIM1_clear_irq();
	MSS_TIM1_load_immediate(period1);
	MSS_TIM1_start();
	MSS_TIM1_enable_irq();
}

void Timer2_IRQHandler( void ){
	motorRight(dirRight);

	MSS_TIM2_clear_irq();
	MSS_TIM2_load_immediate(period2);
	MSS_TIM2_start();
	MSS_TIM2_enable_irq();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// INTERFACE //////////////////////////////////////////////////////////

void interfaceConfig(double height, double width){
	boardHeight = height;
	boardWidth = width;

	xPos = boardWidth/2;
	yPos = boardHeight/2;

	RadiusLeft = sqrt(pow(xPos, 2) + pow(yPos, 2));
	RadiusRight = sqrt(pow(boardWidth - xPos, 2) + pow(yPos, 2));

	counter = 0;
}

void periodFinder(double ratio){
	if(ratio <= 1){
		period1 = 100000/ratio;
		period2 = 100000;
	}
	else{
		period1 = 100000;
		period2 = 100000*ratio;
	}
}

void makeLine(double relX, double relY){
	if(relX < 0.05 && relX > -0.05 && relY < 0.05 && relY > -0.05) {
		return;
	}
	MSS_TIM2_start();
	MSS_TIM1_start();
	double endX = relX + xPos;
	double endY = relY + yPos;
	int dirL = calculateMotorDir(xPos, yPos, endX, endY, 0);
	int dirR = calculateMotorDir(xPos, yPos, endX, endY, 1);
	while(1){
		dirLeft = dirL;
		dirRight = dirR;
		double newRL = sqrt(pow(endX, 2) + pow(endY, 2));
		double newRR = sqrt(pow(boardWidth - endX, 2) + pow(endY, 2));
		double rateChangeL = RadiusLeft - newRL;
		double rateChangeR = RadiusRight - newRR;
		if(rateChangeL < 0) rateChangeL = rateChangeL * -1;
		if(rateChangeR < 0) rateChangeR = rateChangeR * -1;
		ratio = rateChangeL/rateChangeR;

		if(fabs(newRL - RadiusLeft) <= thres && fabs(newRR - RadiusRight) > thres){
			dirLeft = NO;
			ratio = 1;
		}
		else if(fabs(newRL - RadiusLeft) > thres && fabs(newRR - RadiusRight) <= thres){
			dirRight = NO;
			ratio = 1;
		}
		else if(fabs(newRL - RadiusLeft) <= thres && fabs(newRR - RadiusRight) <= thres) {
			break;
		}

		periodFinder(ratio);
		start_hardware_timer1();
		start_hardware_timer2();
		while(1){
			if(counter >= 10){
				counter = 0;
				break;
			}
		}
	}
	xPos = (pow(RadiusLeft, 2) - pow(RadiusRight, 2) + pow(boardWidth, 2))/(2*boardWidth);
	yPos = sqrt(pow(RadiusLeft, 2) - pow(xPos, 2));
	MSS_TIM1_stop();
	MSS_TIM2_stop();
}

void returnToCenter(){
	double disX = 42.5 - xPos;
	double disY = 28.5 - yPos;
	makeLine(disX, disY);
}

void returnToPoint(double x, double y){
	double disX = x - xPos;
	double disY = y - yPos;
	makeLine(disX, disY);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// HARDCODING /////////////////////////////////////////////////////////

void drawCharacter(uint8_t character) {
	if(character == '0') {
		makeLine(2.0, -1);	//Start at bottom of 0
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-1.0, -2.5);
		makeLine(0.0, -1.5);
		makeLine(1.0, -2.5);
		makeLine(1.0, 0.0);
		makeLine(1.0, 2.5);
		makeLine(0.0, 1.5);
		makeLine(-1.0, 1.5);
		makeLine(-1.0, 0.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(3.0, 1.0);
	}
	else if(character == '1') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.5, 0.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(-1.75, 0.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -4.5);
		makeLine(-1.5, 1.5);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(3.75, 4.0);
	}
	else if(character == '2') {
		makeLine(4.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3.0, 0.0);
		makeLine(0.0, -2.0);
		makeLine(3.0, 0.0);
		makeLine(0.0, -1.5);
		makeLine(-3.0, 0.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4.0, 4.5);
	}
	else if(character == '3') {
		makeLine(1.0, -2.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 1.0);
		makeLine(1.5, -1.0);
		makeLine(-1.5, -1.5);
		makeLine(1.5, -1.5);
		makeLine(-1.5, -1.0);
		makeLine(-1.5, 1.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4.0, 5.0);
	}
	else if(character == '4') {
		makeLine(3.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -4.5);
		makeLine(-2.0, 2.0);
		makeLine(3.5, 0.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.5, 4.5);
	}
	else if(character == '5') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 0.0);
		makeLine(0.0, -2.0);
		makeLine(-3.0, 0.0);
		makeLine(0.0, -1.5);
		makeLine(3.0, 0.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 4.5);
	}
	else if(character == '6') {
		makeLine(1.0, -3.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -2.0);
		makeLine(3.0, 0.0);
		makeLine(0.0, -2.0);
		makeLine(-3.0, 0.0);
		makeLine(0.0, -1.5);
		makeLine(3.0, 0.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 4.5);
	}
	else if(character == '7') {
		makeLine(1.0, -5.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 0.0);
		makeLine(-2.0, 4.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 1.0);
	}
	else if(character == '8') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -5.0);
		makeLine(3.0, 0.0);
		makeLine(0.0, 5.0);
		makeLine(-3.0, 0.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, -2.5);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 0.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 3.5);
	}
	else if(character == '9') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 0.0);
		makeLine(0.0, -5.0);
		makeLine(-3.0, 0.0);
		makeLine(0.0, 2.5);
		makeLine(3.0, 0.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 3.5);
	}
	else if(character == 'A') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(3, 0);
		makeLine(0, 6);
		makeLine(0, -3);
		makeLine(-3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4, 4);
	}
	else if(character == 'B') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(3, 0);
		makeLine(0, 3);
		makeLine(-3, 0);
		makeLine(3, 0);
		makeLine(0, 3);
		makeLine(-3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4, 1);
	}
	else if(character == 'C') {
		makeLine(4, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, -6);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'D') {
		makeLine(4, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, .5);
		makeLine(0, -7);
		makeLine(0, .5);
		makeLine(3, 0);
		makeLine(0, 6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'E') {
		makeLine(4, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, 3);
		makeLine(3, 0);
		makeLine(-3, 0);
		makeLine(0, 3);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'F') {
		makeLine(4, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, 3);
		makeLine(3, 0);
		makeLine(-3, 0);
		makeLine(0, 3);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'G') {
		makeLine(4, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, 6);
		makeLine(3, 0);
		makeLine(0, 3);
		makeLine(-2, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(3, 4);
	}
	else if(character == 'H') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(0, 3);
		makeLine(-3, 0);
		makeLine(0, -3);
		makeLine(0, 6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'I') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3, 0);
		makeLine(-1.5, 0);
		makeLine(0, -6);
		makeLine(-1.5, 0);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'J') {
		makeLine(4, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(-1.5, 0);
		makeLine(0, 6);
		makeLine(-1.5, 0);
		makeLine(0, 3);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4, 4);
	}
	else if(character == 'K') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(0, 3);
		makeLine(3, -3);
		makeLine(-3, 3);
		makeLine(3, 3);
		makeLine(-3, -3);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4, 4);
	}
	else if(character == 'L') {
		makeLine(1.0, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, 6);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'M') {
		makeLine(1.0, -1);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(1.5, 6);
		makeLine(1.5, -6);
		makeLine(0, 6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'N') {
		makeLine(1.0, -1);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(3, 6);
		makeLine(0, -6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'O') {
		makeLine(4, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, -6);
		makeLine(3, 0);
		makeLine(0, 6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'P') {
		makeLine(1, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(3, 0);
		makeLine(0, 3);
		makeLine(-3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4, 4);
	}
	else if(character == 'Q') {
		makeLine(1, -2);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -5);
		makeLine(3, 0);
		makeLine(0, 5);
		makeLine(-3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.5, 2.5);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 3.5);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'R') {
		makeLine(1, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(3, 0);
		makeLine(0, 3);
		makeLine(-3, 0);
		makeLine(3, 3);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'S') {
		makeLine(1, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3, 0);
		makeLine(0, -3);
		makeLine(-3, 0);
		makeLine(0, -3);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'T') {
		makeLine(2.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(-1.5, 0);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'U') {
		makeLine(1, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, 6);
		makeLine(3, 0);
		makeLine(0, -6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'V') {
		makeLine(1, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 6);
		makeLine(1.5, -6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'W') {
		makeLine(1, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, 6);
		makeLine(1.5, -6);
		makeLine(1.5, 6);
		makeLine(0, -6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'X') {
		makeLine(1, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3, 6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0, -6);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'Y') {
		makeLine(2.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -3);
		makeLine(-1.5, -3);
		makeLine(1.5, 3);
		makeLine(1.5, -3);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
	}
	else if(character == 'Z') {
		makeLine(1, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3, 0);
		makeLine(-3, 6);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
	}
	else if(character == 'a') {
		makeLine(1.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.0, -1.0);
		makeLine(1.0, 1.0);
		makeLine(0.0, 2.0);
		makeLine(-2.0, -1.0);
		makeLine(2.0, -1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 4.0);
	}
	else if(character == 'b') {
		makeLine(2.0, -6.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, 4.0);
		makeLine(2.0, -1.0);
		makeLine(-2.0, -1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(3.0, 4.0);
	}
	else if(character == 'c') {
		makeLine(4.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-1.5, -1.0);
		makeLine(-1.5, 1.0);
		makeLine(0.0, 1.5);
		makeLine(1.5, 1.0);
		makeLine(1.5, -1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 2.0);
	}
	else if(character == 'd') {
		makeLine(3.0, -3.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-2.0, 1.0);
		makeLine(2.0, 1.0);
		makeLine(0.0, -4.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(2.0, 5.0);
	}
	else if(character == 'e') {
		makeLine(1.5, -3.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(2.0, 0.0);
		makeLine(-1.0, -1.5);
		makeLine(-2.0, 1.5);
		makeLine(0.0, 1.0);
		makeLine(1.0, 1.5);
		makeLine(2.0, -1.5);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.5, 4.0);
	}
	else if(character == 'f') {
		makeLine(2.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -4.0);
		makeLine(1.0, -1.0);
		makeLine(1.0, 1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(-2.5, 2.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(2.5, 0.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 3.0);
	}
	else if(character == 'g') {
		makeLine(1.0, -2.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 1.0);
		makeLine(1.5, -1.0);
		makeLine(0.0, -2.5);
		makeLine(-1.5, -1.5);
		makeLine(-1.5, 1.5);
		makeLine(1.5, 1.5);
		makeLine(1.5, -1.5);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 4.5);
	}
	else if(character == 'h') {
		makeLine(1.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -4.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, 2.5);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.0, -1.0);
		makeLine(1.0, 1.0);
		makeLine(0.0, 2.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.5, 1.0);
	}
	else if(character == 'i') {
		makeLine(2.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(2.5, 5.0);
	}
	else if(character == 'j') {
		makeLine(1.5, -1.5);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.0, 1.0);
		makeLine(1.0, -1.0);
		makeLine(0.0, -2.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.5, 4.5);
	}
	else if(character == 'k') {
		makeLine(1.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -4.5);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.5, 1.5);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-1.5, 1.5);
		makeLine(1.5, 1.5);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(2.0, 1.0);
	}
	else if(character == 'l') {
		makeLine(2.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -4.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(2.5, 5.0);
	}
	else if(character == 'm') {
		makeLine(1.0, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.75, -2.5);
		makeLine(0.75, 2.5);
		makeLine(0.75, -2.5);
		makeLine(0.75, 2.6);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 1.0);
	}
	else if(character == 'n') {
		makeLine(1.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, 1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, -1.0);
		makeLine(1.5, 1.0);
		makeLine(0.0, 2.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.5, 1.0);
	}
	else if(character == 'o') {
		makeLine(1.5, -2.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.0, -1.0);
		makeLine(1.0, 1.0);
		makeLine(-1.0, 1.0);
		makeLine(-1.0, -1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(3.5, 2.0);
	}
	else if(character == 'p') {
		makeLine(1.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -3.0);
		makeLine(1.0, -1.0);
		makeLine(1.0, 1.0);
		makeLine(-1.0, 1.0);
		makeLine(-1.0, -1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(3.5, 4.0);
	}
	else if(character == 'q') {
		makeLine(3.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-1.0, 1.0);
		makeLine(-1.0, -1.0);
		makeLine(1.0, -1.0);
		makeLine(1.0, 1.0);
		makeLine(0.0, 3.0);
		makeLine(1.0, -1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 2.0);
	}
	else if(character == 'r') {
		makeLine(1.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, -3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, 1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, -1.5);
		makeLine(1.5, 1.5);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.5, 3.0);
	}
	else if(character == 's') {
		makeLine(1.0, -1.5);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 1.0);
		makeLine(1.5, -1.0);
		makeLine(-3.0, -1.5);
		makeLine(1.5, -1.0);
		makeLine(1.5, 1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 3.0);
	}
	else if(character == 't') {
		makeLine(1.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 0.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(-1.5, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, 4.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(2.5, 1.0);
	}
	else if(character == 'u') {
		makeLine(1.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, 2.0);
		makeLine(1.0, 1.0);
		makeLine(1.0, 0.0);
		makeLine(1.0, -1.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, -2.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0.0, 3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 1.0);
	}
	else if(character == 'v') {
		makeLine(1.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 3.0);
		makeLine(1.5, -3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 4.0);
	}
	else if(character == 'w') {
		makeLine(0.5, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.0, 3.0);
		makeLine(1.0, -3.0);
		makeLine(1.0, 3.0);
		makeLine(1.0, -3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.5, 4.0);
	}
	else if(character == 'x') {
		makeLine(1.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(0.0, -3.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3.0, 3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4.0, 1.0);
	}
	else if(character == 'y') {
		makeLine(1.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 1.5);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.5, -1.5);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3.0, 3.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4.0, 1.0);
	}
	else if(character == 'z') {
		makeLine(1.0, -4.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 0.0);
		makeLine(-3.0, 3.0);
		makeLine(3.0, 0.0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 1.0);
	}
	else if(character == ' '){
		makeLine(5, 0);
	}
	else if(character == '['){
		makeLine(2, -1);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(0, -6);
		makeLine(6, 0);
		makeLine(0, 6);
		makeLine(-6, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(8, 1);
	}
	else if(character == '<'){
		makeLine(-20.0, 0.0);
		//E
		makeLine(4, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, 3);
		makeLine(3, 0);
		makeLine(-3, 0);
		makeLine(0, 3);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
		//E
		makeLine(4, -7);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, 3);
		makeLine(3, 0);
		makeLine(-3, 0);
		makeLine(0, 3);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 1);
		//C
		makeLine(4, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-3, 0);
		makeLine(0, -6);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
		//S
		makeLine(1, -1.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3, 0);
		makeLine(0, -3);
		makeLine(-3, 0);
		makeLine(0, -3);
		makeLine(3, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1, 7);
		//3
		makeLine(1.0, -2.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 1.0);
		makeLine(1.5, -1.0);
		makeLine(-1.5, -1.5);
		makeLine(1.5, -1.5);
		makeLine(-1.5, -1.0);
		makeLine(-1.5, 1.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4.0, 5.0);
		//7
		makeLine(1.0, -5.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3.0, 0.0);
		makeLine(-2.0, 4.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(1.0, 1.0);
		//3
		makeLine(1.0, -2.0);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(1.5, 1.0);
		makeLine(1.5, -1.0);
		makeLine(-1.5, -1.5);
		makeLine(1.5, -1.5);
		makeLine(-1.5, -1.0);
		makeLine(-1.5, 1.0);
		//Get ready for next character
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(4.0, 5.0);
		/*
		makeLine(2, -1);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(3, -5.19);
		makeLine(3, 5.19);
		makeLine(-6, 0);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(8, 1);
		*/
	}
	else if(character == '('){
		makeLine(8, -4);
		sendMessage(servoExtend, 1, 0x373A);
		makeLine(-0.0576400000000007,-0.58527);
		makeLine(-0.17072,-0.56278);
		makeLine(-0.277229999999999,-0.51866);
		makeLine(-0.373090000000001,-0.45461);
		makeLine(-0.45461,-0.373090000000001);
		makeLine(-0.518660000000001,-0.277229999999999);
		makeLine(-0.56278,-0.17072);
		makeLine(-0.58527,-0.0576400000000007);
		makeLine(-0.58527,0.0576400000000007);
		makeLine(-0.56278,0.17072);
		makeLine(-0.51866,0.277229999999999);
		makeLine(-0.45461,0.373090000000001);
		makeLine(-0.37309,0.45461);
		makeLine(-0.27723,0.51866);
		makeLine(-0.17072,0.56278);
		makeLine(-0.05764,0.58527);
		makeLine(0.05764,0.58527);
		makeLine(0.17072,0.56278);
		makeLine(0.27723,0.51866);
		makeLine(0.37309,0.45461);
		makeLine(0.45461,0.37309);
		makeLine(0.51866,0.27723);
		makeLine(0.56278,0.17072);
		makeLine(0.58527,0.05764);
		makeLine(0.58527,-0.05764);
		makeLine(0.56278,-0.17072);
		makeLine(0.518660000000001,-0.27723);
		makeLine(0.45461,-0.37309);
		makeLine(0.373090000000001,-0.45461);
		makeLine(0.277229999999999,-0.51866);
		makeLine(0.17072,-0.56278);
		makeLine(0.0576400000000007,-0.58527);
		sendMessage(servoRetract, 1, 0x373A);
		makeLine(2, 4);
	}
}
/*
void letterA(double height){
	makeLine(height * cos(60), -height * sin(60));
	makeLine(height * cos(60), height * sin(60));
	makeLine(-height * cos(60) * .5, -height * sin(60) * .5);
	makeLine(-height * cos(60) * .5, 0);
}

void letterI(double height){
	makeLine(height * .5, 0);
	makeLine(-height * .25, 0);
	makeLine(0, height);
	makeLine(-height * .25, 0);
	makeLine(height * .5, 0);
}

void letterE(double height){
	makeLine(height * .5, 0);
	makeLine(-height * .5, 0);
	makeLine(0, -height);
	makeLine(height * .5, 0);
	makeLine(-height * .5, 0);
	makeLine(0, height * .5);
	makeLine(height * .5, 0);
	makeLine(-height * .5, 0);
}
*/
#ifdef __cplusplus
}
#endif
