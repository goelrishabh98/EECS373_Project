#include "stepper.h"
#include "interface.h"

//Current Dimensions: 54.61, 83.82
//center: 41.91, 27.305
int main(){
	stepper_config(SIXTEENTH, SIXTEENTH);
	interfaceConfig(54.61, 83.82);

	//One A
	makeLine(47.91, 18.305);
	makeLine(53.91, 27.305);
	makeLine(50.91, 22.805);
	makeLine(44.91, 22.805);

	//One Box
	//makeLine(41.91, 20);
	//makeLine(55, 20);
	//makeLine(55, 27.305);
	//makeLine(41.91, 27.305);

	//One Box
	//makeLine(41.91, 40);
	//makeLine(60, 40);
	//makeLine(60, 27.305);
	//makeLine(41.91, 27.305);
	return 0;
}
