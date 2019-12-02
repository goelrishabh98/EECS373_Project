#include "stepper.h"
#include "interface.h"


//Current Dimensions: 54.61, 83.82

int main(){
	stepper_config(SIXTEENTH, SIXTEENTH);
	interfaceConfig(54.61, 83.82);

	//makeLine(CCW, CW, 41.91, 20);
	//makeLine(CW, CW, 55, 20);
	//makeLine(CW, CCW, 55, 27.305);
	//makeLine(CCW, CCW, 41.91, 27.305);
	makeLine(CW, CCW, 41.91, 40);
	makeLine(CW, CW, 60, 40);
	makeLine(CCW, CW, 60, 27.305);
	makeLine(CCW, CCW, 41.91, 27.305);
	return 0;
}
