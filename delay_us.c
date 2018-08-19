#include "MKL25Z4.h" 

void Delay_us(volatile unsigned int time){
	while(time--){ //this function will decrement the argument input until its value reaches 0
		;
	}
}
