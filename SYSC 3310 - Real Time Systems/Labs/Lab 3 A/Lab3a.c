// Lab 3 - Part A
// By Mohamed Ali Ramadan and Andrew Dybka

#include "msp.h"

int main(void)
{
	volatile uint32_t i;
	
	// Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	// The following code toggles P1.0 port
	// Configure P1.0 as output
	P1DIR |= BIT0;

	while(1)
	{
		// Toggle P1.0
		P1OUT ^= BIT0;
		for(i=10000; i>0; i--);                  // Delay
	}
}
