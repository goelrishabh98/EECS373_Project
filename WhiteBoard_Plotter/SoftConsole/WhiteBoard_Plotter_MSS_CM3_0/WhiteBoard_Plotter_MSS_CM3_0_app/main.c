#include "stepper.h"
#include "timer.h"

int main(){
	startTimerContinuous(1, 100000);
	startTimerContinuous(0, 200000);

	start_hardware_timer();

	while(1);

	return 0;
}
