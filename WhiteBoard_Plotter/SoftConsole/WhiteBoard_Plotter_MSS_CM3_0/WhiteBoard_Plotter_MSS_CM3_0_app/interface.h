#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "timer.h"
#include <math.h>

double boardHeight;
double boardWidth;
double rigWidth;

double xPos = boardWidth/2;
double yPos = boardHeight/2;

double curRadiusLeftOld;
double curRadiusRightOld;

double curRadiusLeft;
double curRadiusRight;

double getRateChange(double startX, double startY, double endX, double endY){
	double oldR1 = sqrt(pow(startX - .5*boardWidth, 2) + pow(startY, 2));
	double oldR2 = sqrt(pow(boardWidth - startX - .5*boardWidth, 2) + pow(startY, 2));
	double newR1 = sqrt(pow(endX - .5*boardWidth, 2) + pow(endY, 2));
	double newR2 = sqrt(pow(boardWidth - endX - .5*boardWidth, 2) + pow(endY, 2));

	double rateChange1 = (newR1 - oldR1);
	double rateChange2 = (newR2 - oldR2);

	return rateChange2/rateChange1;
}

double makeLine(int dirLeft, int dirRight, double endX, double endY){
	while(1){
		double ratio = getRateChange(xPos, yPos, endX, endY);
		startTimerContinuous(1, 100000);
		startTimerContinuous(0, 100000/ratio);
		updateLocation(curRadiusLeftOld, curRadiusRightOld);
	}
}

#endif /* INTERFACE_H_ */
