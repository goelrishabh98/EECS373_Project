#ifdef __cplusplus
extern "C" {
#endif

#include "stepper.h"
#include "mss_timer.h"
#include <stdio.h>
#include <stdlib.h>
typedef void (*handler_t)(int);

typedef struct Timer {
    int			left;//function pointer (called after timer period)
    uint32_t	time;//time remaining for this counter
    uint32_t	period;//period
    uint32_t	mode;//continuous or one shot timer
    struct Timer*  next;//points to next timer
    struct Timer* prev;
} timer_tt;

timer_tt *root = NULL;
int dirLeft = CCW;
int dirRight = CW;

void updateDir(int dirL, int dirR){
	dirLeft = dirL;
	dirRight = dirR;
}

//used to initialize hardware
void start_hardware_timer(){
	// mode == 1 One shot mode == 0 continuous
	MSS_TIM1_init(MSS_TIMER_PERIODIC_MODE);

	MSS_TIM1_load_immediate(root->period);
	MSS_TIM1_start();
	MSS_TIM1_enable_irq();
}

void insert_timer(timer_tt* newtimer){

	if(root == NULL){
		root = newtimer;
		return;
	}

	timer_tt* curr = root;
	while( curr != NULL){
		if(curr->time > newtimer->time){
			if(curr->prev == NULL){
				root = newtimer;
			}
			if(curr->prev != NULL){
				curr->prev->next = newtimer;
			}
			newtimer->prev = curr->prev;
			curr->prev = newtimer;
			newtimer->next = curr;
			return;
		}
		else{
			if(curr->next == NULL){
				curr->next = newtimer;
				newtimer->prev = curr;
				return;
			}
			curr = curr->next;
		}
	}
}

void motorLeft(int dir) {
	step(dir, NO);
}
void motorRight(int dir) {
	step(NO, dir);
}

//add a continuous (periodic) timer to linked list.
void startTimerContinuous(int isLeft, uint32_t period){
	timer_tt* newTimer = NULL;
	newTimer = (timer_tt*)malloc(sizeof(struct Timer));
	newTimer->left = isLeft;
	newTimer->period = period;
	newTimer->time = period;
	newTimer->mode = 0;
	newTimer->next = NULL;
	newTimer->prev = NULL;

	insert_timer(newTimer);
}
//example
//startTimerContinuous(&led0, 50000000);

//update down count with elapsed time, call fnc if timer zero, update continuous timers
//with new down count
void update_timers(){
	timer_tt *curr = root;
	curr = curr->next;
	while(curr != NULL){
		curr->time = curr->time - root->time;
		curr = curr->next;
	}
	if(root->next == NULL){
		if(!root->mode){
			root->time = root->period;
			return;
		}
		else{
			root = NULL;
			return;
		}
	}
	timer_tt *temp = root;
	root = root->next;
	temp->next = NULL;
	root->prev = NULL;
	if(!temp->mode){
		startTimerContinuous(temp->left, temp->period);
		free(temp);
		return;
	}
	return;
}

void Timer1_IRQHandler( void ){

	if(root->left){
		motorLeft(dirLeft);
	}
	else{
		motorRight(dirRight);
	}
	update_timers();

	timer_tt* temp = root;
	while(temp != NULL){
		int not_change = 0;
		if(temp->time == 0){
			if(root->left){
				motorLeft(dirLeft);
			}
			else{
				motorRight(dirRight);
			}
			update_timers();
			not_change = 1;
		}
		if(not_change){
			temp = root;
		}
		else{
			temp = temp->next;
		}
	}

	MSS_TIM1_clear_irq();
	MSS_TIM1_load_immediate(root->time);
	start_hardware_timer();
};

#ifdef __cplusplus
}
#endif
