#include "stepper.h"
#include "timer.h"


//Current Dimensions: 54.61, 83.82

int main(){
	stepper_config(FULL, FULL);
	interfaceConfig(54.61, 83.82);

	makeLine(CCW, CCW, 12, 12);

	return 0;
}
