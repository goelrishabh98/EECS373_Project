//3.8 cm for 20 teeth on belt
//01so 3.8cm per revolution

#ifndef STEPPER_H_
#define STEPPER_H_

#define PADDR (int*)0x40050000

enum dir{NO, CCW, CW};
enum mode{FULL, HALF, QUATER, EIGHT, X, X_X, X_X_X, SIXTEENTH};

//GPIO map Stepper 1--- ms1 = 0  ms2 = 1  ms3 = 2
//GPIO map Stepper 2--- ms1 = 3  ms2 = 4  ms3 = 5
void stepper_config(int mode1, int mode2);
void step(int dir1, int dir2);


#endif /* STEPPER_H_ */
