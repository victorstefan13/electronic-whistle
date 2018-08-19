#include "MKL25Z4.h"
#include "play_tone.h" // include the header files for play_tone.c file

#define SW1 (13) // selecting ping 13 on port A for switch 1
#define SW2 (12) // selecting ping 12 on port A for switch 2
#define SW3 (5) // selecting ping 4 on port A for switch 3

#define MASK(x) (1UL << (x))
#define SWITCH_PRESSED_A(x) ((PTA->PDIR & MASK(x))>>x) // defined macro which checks to see if the switch is pressed or not.

void init_sw(void){ // creating a function to initialize the switches and interrupts
	
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //enable clock on port A 
		
		PORTA->PCR[SW1] = PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(10); //Setting up the switch 1 as general purpose input output and initialising 
																																																	//the interrupt to treigger on the falling adge
	
		PORTA->PCR[SW2] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(10); //Setting up the switch 2 as general purpose input output and initialising 
																																																	//the interrupt to treigger on the falling adge
		
		PORTA->PCR[SW3] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(10); //Setting up the switch 3 as general purpose input output and initialising 
																																																	//the interrupt to treigger on the falling adge
		NVIC_SetPriority(PORTA_IRQn, 2); // setting the interrupt priority to 2 
		NVIC_ClearPendingIRQ(PORTA_IRQn); // clears the interrupt pending flag for IRQn
		NVIC_EnableIRQ(PORTA_IRQn); // enable interrupt of type IRQn
		
		__enable_irq(); // configure  the PRIMASK in case interrupts were disabled.

}


void PORTA_IRQHandler(void){ // creating an interrrupt handler function
	
		if((PORTA->ISFR & MASK(SW1))){ //the interrupt is triggered if switch 2 is pressed
			if(!(SWITCH_PRESSED_A(SW1))){ 
				freq_change(500); // call the freq_change function and add 500 to integer freq
		}
	}
		
	if((PORTA->ISFR & MASK(SW3))){ // the interrupt is triggered if switch 3 is pressed
		if(!(SWITCH_PRESSED_A(SW3))){
			freq_change(-500); // call the freq_change function and subtract 500 from integer freq
		}
	}
		
	if((PORTA->ISFR & MASK(SW2))){ // the interrupt is triggered if switch 1 is pressed
		if (!(SWITCH_PRESSED_A(SW2))){
			play_buzzer(); // call play_buzzer function from play_tone.c file which outputs to the buzzer
		}
	}
	

		PORTA->ISFR = 0xffffffff; // clear the status flag
	
}


