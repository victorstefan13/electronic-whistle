#include "MKL25Z4.h"
#include "play_tone.h" // include the header files for play_tone.c file
#include "whistle.h" // include the header files for whistle.c file

int main(void){
	
	init_sw(); // call the init_sw function from whistle.c file
	
	init_buzzer();	// call init_buzzer function from play_tone.c file
	
	
	while(1){ // infinate loop
		
		__wfi(); // this will send the microcontroller to sleep until any of the interrupts will be triggered
		
	}
}
