//3.8 cm for 20 teeth on belt
//01so 3.8cm per revolution

#ifndef STEPPER_H_
#define STEPPER_H_

#define PADDR (int*)0x40050000

enum dir{NO, CCW, CW};

void config(int ms1, int ms2, int ms3);
void step(int dir1, int dir2);


#endif /* STEPPER_H_ */
