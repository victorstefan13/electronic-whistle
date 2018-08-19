#include "MKL25Z4.h"
#include "delay_us.h" // include the header file for delay_us.c delay_us.c file
#include "play_tone.h" //include the header file for this particular file
#include <stdbool.h> // include libary in oredr to use boolean variables 

#define buzzer (4) // selecting ping 4 on port D for the buzzer

#define MASK(x) (1UL << (x))

void init_buzzer(void){  // creating a function to initialize the buzzer
	
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; // This is enable clock on port D
		
		PORTD->PCR[buzzer] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[buzzer] |= PORT_PCR_MUX(1); // This is setting up the buzzer as a General purpose input/output
		
		PTD->PDDR |= MASK(buzzer); // This is setting up the buzzer as output
	
}

void play_buzzer(void){ // creating a function to play the buzzer
	
	int period = freq_change(0); // Here the value of the interger is assigned to the period interger
	int duration = 0; // declaring a new interger called period and assigning the value 0
	
	while(duration != 500){ // while duration is not equal to 500
		PTD->PTOR = MASK(buzzer); // play the buzzer
		Delay_us(period); // wait the value of the interger period which at this point is 5000
		duration++; // incremeant duration by 1 each time.
	}
	return;   
}

int freq_change(int input){ // creating a function with the argument input of the integer input
		
	static int freq; // declaring a static integer frequency 
	static bool init; // declaring a static boolean init
	
	if(!init) // if the boolean init is false (0)
	{
		init = true; // make init boolean true (1)
		freq = 5000; // set the value of the frequency to 5000;
	}
	if(freq<10000 && freq>500) // if the integer freq is less than 10000 and bigger than 500
	{
		freq = freq + input; // frequency is equal to frequency plus input
	}
	
	return freq; // return the value of the integer frequency

	
}	

