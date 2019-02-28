#include <stdint.h>
#include <msp.h>

#define OUTER_SPIN 1000
#define INNER_SPIN 1000
// BITs are defined in msp.h

// Mark II Pins mapped to MSP432:

// RGB LEDs (using GPIO):
// RED: P2.6
// GREEN: P2.4
// BLUE: P5.6

void delay(void)
{	
	uint32_t i,j,k;
	
	for(i=OUTER_SPIN; i>0; i--)
	{
		for (j=INNER_SPIN;j>0; j--) // Delay
		{
			k = 5;
		}
	}	
}

int main(void) 
{	
	WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer.

	// Set GREEN and RED as GPIO:
	P2SEL1 &= ~(BIT4 | BIT6); // Clear RED and GREEN P2SEL1
	P2SEL0 &= ~(BIT4 | BIT6); // Clear RED and GREEN P2SEL0
	
	// Set GREEN and RED as OUTPUT
	P2DIR |= BIT4 | BIT6;

	// Set BLUE as GPIO:
	P5SEL1 &= ~BIT6;
	P5SEL0 &= ~BIT6;
	
	// Set BLUE as OUTPUT
	P5DIR |= BIT6;

	// Turn off GREEN and RED LEDs
	P2OUT &= ~(BIT4 | BIT6);
	// Truen off BLUE LED
	P5OUT &= ~BIT6;

	while(1)
	{
		// Turn on RED LED, wait, turn off.
		P2OUT |= BIT6;
		delay();
		P2OUT &= ~BIT6;

		// Turn on GREEN LED, wait, turn off.
		P2OUT |= BIT4;
		delay();
		P2OUT &= ~BIT4;

		// Turn on BLUE LETD, wait, turn off.
		P5OUT |= BIT6;
		delay();
		P5OUT &= ~BIT6;			
	}
}