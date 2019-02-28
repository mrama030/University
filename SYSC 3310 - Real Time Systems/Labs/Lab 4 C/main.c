// Mohamed Ali Ramadan (101135828) and Andrew Dybka

// built-in LED1 connected to P1.0
// negative logic built-in Button 1 connected to P1.1 (increment counter on falling edge)
// negative logic built-in Button 2 connected to P1.4 (increment counter on falling edge)
// built-in red LED connected to P2.0
// built-in green LED connected to P2.1
// built-in blue LED connected to P2.2

#include <stdint.h>
#include "..\inc\msp432p401r.h"

#define RED       0x01
#define YELLOW    0x03
#define GREEN     0x02
#define TIME_RED 5
#define TIME_YELLOW 5
#define TIME_GREEN 10

// global variables:
uint32_t timeRemaining = 10;
uint8_t colour = GREEN; // GREEN, YELLOW, RED

// Delays by 1 millisecond:
void delay1m(int number){
	uint32_t i,j;
	for (i=0; i<number;i++){
		for (j=0;j<900;j++);
	}
}

// Delays thread by one second:
void tickOneSecond(void){
	if(timeRemaining > 0) 
	{
		delay1m(1000); // 1000 ms = 1 second
		timeRemaining--;
	}
}

void Port1_Init(void){
	
	__ASM("CPSID I"); // Disable all exceptions with programmable priority.
	
  P1SEL0 &= ~0x12;
  P1SEL1 &= ~0x12;    // 1) configure P1.4 and P1.1 as GPIO
  P1DIR &= ~0x12;     // 2) make P1.4 and P1.1 in
  P1REN |= 0x12;      // 3) enable pull resistors on P1.4 and P1.1
  P1OUT |= 0x12;      // 1.4 and P1.1 are pull-up
	
	P1IES |= 0x12;                   // P1.4 and P1.1 are falling edge event
  P1IFG &= ~0x12;                  // clear flag4 and flag1 (reduce possibility of extra interrupt)
  P1IE |= 0x12;                    // arm interrupt on P1.4 and P1.1
	
	NVIC_IPR8 = (NVIC_IPR8&0x00FFFFFF)|0x40000000; // priority 2
  NVIC_ISER1 = 0x00000008;         // enable interrupt 35 in NVIC
		
	__ASM("CPSIE I");								// Globally enable interrupts
}

void Port2_Output(uint8_t colorToSet){  // write three outputs bits of P2
  P2OUT = (P2OUT & 0xF8) | colorToSet;
}

void Port2_Init(void){
	P2SEL0 &= ~0x07;
  P2SEL1 &= ~0x07;                 // configure built-in RGB LEDs as GPIO
  P2DS |= 0x07;                    // make built-in RGB LEDs high drive strength
  P2DIR |= 0x07;                   // make built-in RGB LEDs out
  P2OUT = 0x00;                  
	Port2_Output(colour); // RGB = GREEN
}

// Handles Switch 1 (P1.1) and 2 (1.4):
void PORT1_IRQHandler(void) {

	// Switch 1 (P1.1) Interrupt received / Pedestrian clicks crosswalk button:
	if ((P1IFG & 0x02) != 0) 
	{
		P1IFG &= ~0x02;		// clear flag1, acknowledge
		
		// Only change if the light is currently green, change to yellow immediately.
		if (colour == GREEN)
		{
				colour = YELLOW;
				timeRemaining = TIME_YELLOW;
				Port2_Output(YELLOW);
		}
  }
	
	// Switch 2 (P1.4) Interrupt received / Car arrives at traffic light:
	else if ((P1IFG & 0x10) != 0) 
	{
		P1IFG &= ~0x10;		// clear flag4, acknowledge
		
		if (colour == RED)
		{
			if (timeRemaining > 2)
			{
				timeRemaining = 2;
			}
		}
  }
}

int main(void){
	Port1_Init();
	Port2_Init();

  while(1){
		
		if (colour == GREEN)
		{			
			if (timeRemaining == 0)
			{
				colour = YELLOW;
				timeRemaining = TIME_YELLOW;
				Port2_Output(YELLOW);
			}
		}
		else if (colour == YELLOW)
		{
			if (timeRemaining == 0)
			{
				colour = RED;
				timeRemaining = TIME_RED;
				Port2_Output(RED);
			}
		}
		else if (colour == RED)
		{
			if (timeRemaining == 0)
			{
				colour = GREEN;
				timeRemaining = TIME_GREEN;
				Port2_Output(GREEN);
			}
		}	
		
		tickOneSecond();
  }
}
