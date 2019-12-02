#include "stepper.h"
#include "timer.h"

int main(){

	stepper_config(SIXTEENTH, SIXTEENTH);

	startTimerContinuous(1, 1000);
	startTimerContinuous(0, 2000);

	start_hardware_timer();

	while(1);

	return 0;
}
