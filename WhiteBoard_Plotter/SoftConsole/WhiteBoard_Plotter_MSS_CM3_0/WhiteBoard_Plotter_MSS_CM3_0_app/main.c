#include "stepper.h"

int main()
{volatile int i = 0;

	while( 1 )
	{
		step(CW_CW);
		for(i =0; i<10000; i++){

		}
	}
}
