//Converts drawing on touch screen to board positions
//Since touchscreen is 320 pixels tall and 240 pixels wide,
//use 32x24cm rectangle on whiteboard
//Top left corner of rectangle is therefore (25.91, 15.305)
//Top right: (57.91, 15.305)
//Bottom left: (25.91, 39.305)
//Bottom right: (57.91, 39.305)
#include <math.h>
#include <stdint.h>

#define HORIZONTALSCALE 10
#define VERTICALSCALE 10
#define DISCRETIZESTEP 10	//How many points to throw away when recreating drawn line
#define RECEIVEDBUFFERSIZE 300	//How many TSPoints buffer should store
#define BOARDWIDTH 83.82
#define BOARDHEIGHT 54.61
#define PI 3.141592654

struct TSPoint {
	uint16_t x;
	uint16_t y;
	uint16_t z;
};

struct DrawPoint {
	double x;
	double y;
};

struct TSPoint receivedPoints[RECEIVEDBUFFERSIZE];
struct DrawPoint drawnPoints[RECEIVEDBUFFERSIZE / DISCRETIZESTEP];

enum side{LEFT, RIGHT};
enum dir{NO, CCW, CW};

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

//Draw out line saved in receivedPoints
void drawReceivedLine() {
	int i;	//For loop counter, indexes into receivedBuffer
	int leftDirection;	//CW or CCW
	int rightDirection;	//CW or CCW
	//Calculates what direction motor should spin in for first movement
	leftDirection = calculateMotorDir(BOARDWIDTH, BOARDHEIGHT, receivedPoints[0].x, receivedPoints[0].y, LEFT);
	rightDirection = calculateMotorDir(BOARDWIDTH, BOARDHEIGHT, receivedPoints[0].x, receivedPoints[0].y, RIGHT);
	for(i = 0; i <= RECEIVEDBUFFERSIZE - DISCRETIZESTEP; i += DISCRETIZESTEP) {
		//To simulate drawing, save points that makeLine would draw to
		drawnPoints[i / DISCRETIZESTEP].x = 25.91 + (double)receivedPoints[i].x / HORIZONTALSCALE;
		drawnPoints[i / DISCRETIZESTEP].y = 15.305 + (double)receivedPoints[i].y / VERTICALSCALE;
		//makeLine(leftDirection, rightDirection, 25.91 + (double)receivedPoints[i].x / HORIZONTALSCALE, 15.305 + (double)receivedPoints[i].y / VERTICALSCALE);
		if(i < RECEIVEDBUFFERSIZE) {
			//Calculates direction that motors should spin in for next point
			leftDirection = calculateMotorDir(receivedPoints[i].x, receivedPoints[i].y, receivedPoints[i + DISCRETIZESTEP].x, receivedPoints[i + DISCRETIZESTEP].y, LEFT);
			rightDirection = calculateMotorDir(receivedPoints[i].x, receivedPoints[i].y, receivedPoints[i + DISCRETIZESTEP].x, receivedPoints[i + DISCRETIZESTEP].y, RIGHT);
		}
	}
}

int main()
{
	int i;
	//----------------------------Test Cases---------------------------
	//Fill up received buffer with artificial data defining a straight horizontal line
	/*
	for(i = 0; i < RECEIVEDBUFFERSIZE; ++i) {
		receivedPoints[i].x = (240 * i) / RECEIVEDBUFFERSIZE;
		receivedPoints[i].y = 160;
		receivedPoints[i].z = 1;
	}
	*/

	//Fill up received buffer with rectangle with corners at
	//Top left: (120, 85)
	//Top right: (195, 85)
	//Bottom left: (120, 160)
	//Bottom right: (195, 160)
	/*
	for(i = 0; i < 75; ++i) {
		receivedPoints[i].x = 120;
		receivedPoints[i].y = 160 - i;
		receivedPoints[i].z = 1;
	}
	for(i = 0; i < 75; ++i) {
		receivedPoints[i + 75].x = 120 + i;
		receivedPoints[i + 75].y = 85;
		receivedPoints[i + 75].z = 1;
	}
	for(i = 0; i < 75; ++i) {
		receivedPoints[i + 150].x = 195;
		receivedPoints[i + 150].y = 85 + i;
		receivedPoints[i + 150].z = 1;
	}
	for(i = 0; i < 75; ++i) {
		receivedPoints[i + 225].x = 195 - i;
		receivedPoints[i + 225].y = 160;
		receivedPoints[i + 225].z = 1;
	}
	*/
	/*
	//Fill up received buffer with circle centered at (120, 160), with radius 80
	for(i = 0; i < RECEIVEDBUFFERSIZE; ++i) {
		receivedPoints[i].x = 120 + 80 * cos(2.0 * PI * (double)i / (double)RECEIVEDBUFFERSIZE);
		receivedPoints[i].y = 160 + 80 * sin(2.0 * PI * (double)i / (double)RECEIVEDBUFFERSIZE);
		receivedPoints[i].z = 1;
	}
	*/

	drawReceivedLine();
	//----------------------------Test Cases End---------------------------
	while( 1 )
	{
		int a = 0;
	}
}
