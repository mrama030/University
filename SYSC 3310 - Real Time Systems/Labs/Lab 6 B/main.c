// Mohamed Ali Ramadan and Andrew Dybka
// SYSC3310 - Lab 6 - Part B

// Mark II Pins mapped to MSP432:

// RGB LEDs (using GPIO):
// RED: P2.6
// GREEN: P2.4
// BLUE: P5.6

// Buttons (Negative Logic, using GPIO):
// S1: P5.1
// S2: P3.5

#include <stdint.h>
#include "../inc/CortexM.h"
#include "../inc/msp432p401r.h"

// Constants
const uint8_t Pin1 = 0x02;
const uint8_t Pin4 = 0x10;
const uint8_t Pin5 = 0x20;
const uint8_t Pin6 = 0x40;

// Global Variables
int8_t IS_GREEN = -1; // -1=BOTH OFF, 0=RED LED ONLY, 1=GREEN LED ONLY
uint8_t SAME_BUTTON_PRESSES = 0;
uint8_t BUTTON_1_STATUS = 0xFF;
uint8_t BUTTON_2_STATUS = 0xFF;

void LAB6B_Init()
{
	// RGB LEDs Configuration:
	P2SEL1 &= ~(Pin4 | Pin6); // GPIO
	P2SEL0 &= ~(Pin4 | Pin6); // GPIO
	P2DIR |= (Pin4 | Pin6); // OUTPUT
	P2DS &= ~(Pin4 | Pin6); // REGULAR STRENGTH
	P2OUT &= ~(Pin4 | Pin6); // TURN OFF LEDs
	
	// Buttons Configuration:
	P5SEL1 &= ~Pin1; // GPIO
	P5SEL0 &= ~Pin1; // GPIO
	P3SEL1 &= ~Pin5; // GPIO
	P3SEL0 &= ~Pin5; // GPIO
	
	P5DIR &= ~Pin1; // INPUT
	P3DIR &= ~Pin5; // INPUT
	
	P5REN |= Pin1; // USE INTERNAL RESISTOR
	P3REN |= Pin5; // USE INTERNAL RESISTOR
	
	P5OUT |= Pin1; // PULL-UP RESISTOR for NEGATIVE LOGIC
	P3OUT |= Pin5; // PULL-UP RESISTOR for NEGATIVE LOGIC
}

void long_delay() // Good time balance. Don't release buttons super fast though, hold for 1/3 of a second.
{
	int x;
	for(x = 200000; x > 0; x--)
	{
		// delay
	}
}

void Poll_Buttons()
{
	// Button 1 = P5.1
	// Button 2 = P3.5
	BUTTON_1_STATUS = (P5IN & 0x02); // Only keeps the value in BIT1.
	BUTTON_2_STATUS = (P3IN & 0x20); // Only keeps the value in BIT5.
	long_delay();
}

void Green_LED_Mode()
{
	IS_GREEN = 1;
	P2OUT |= Pin4; // Turn on GREEN LED
	P2OUT &= ~Pin6; // Turn off RED LED
	SAME_BUTTON_PRESSES = 1;
}

void Red_LED_Mode()
{
	IS_GREEN = 0;
	P2OUT |= Pin6; // Turn on RED LED
	P2OUT &= ~Pin4; // Turn off GREEN LED
	SAME_BUTTON_PRESSES = 1;
}

void Toggle_Red_LED()
{
	P2OUT ^= Pin6;
}

void Toggle_Green_LED()
{
	P2OUT ^= Pin4;
}

int main(void)
{
	LAB6B_Init();
	
	while(1) 
	{
		Poll_Buttons(); // includes delay to avoid button bouncing
		
		if (BUTTON_1_STATUS == 0) // Button 1 (for RED LED) pressed.
		{
			if (IS_GREEN == 0 && SAME_BUTTON_PRESSES == 1) // If LED was already RED.
			{
				// Activate LOOPING ON and OFF for RED LED.
				while(1)
				{
					long_delay();
					Toggle_Red_LED();
					Poll_Buttons(); // includes delay
					if (BUTTON_2_STATUS == 0) // Check if Button 2 (for GREEN LED) is pressed.
					{
						Green_LED_Mode();
						break;
					}
				}
			}
			else if (IS_GREEN == -1 || IS_GREEN == 1) // Both were off, or was GREEN.
			{
				Red_LED_Mode();
			}
		}
		else if (BUTTON_2_STATUS == 0) // Button 2 (for GREEN LED) pressed.
		{
			if (IS_GREEN == 1 && SAME_BUTTON_PRESSES == 1) // If LED was already GREEN.
			{
				// Activate LOOPING ON and OFF for RED LED.
				while(1)
				{
					long_delay();
					Toggle_Green_LED();
					Poll_Buttons(); // includes delay
					if (BUTTON_1_STATUS == 0) // Check if Button 1 (for RED LED) is pressed.
					{
						Red_LED_Mode();
						break;
					}
				}
			}
			else if (IS_GREEN == -1 || IS_GREEN == 1) // Both were off, or was RED.
			{
				Green_LED_Mode();
			}
		}
	}
}

/* Tests that LEDs and Buttons of Mark II are working properly.
int main(void)
{
	LAB6B_Init();
	
	while(1) 
	{
		Poll_Buttons(); // includes delay to avoid button bouncing
		
		if (BUTTON_1_STATUS == 0) // Button 1 (for RED LED) pressed.
		{
			Red_LED_Mode();
		}
		else if (BUTTON_2_STATUS == 0) // Button 2 (for GREEN LED) pressed.
		{
			Green_LED_Mode();
		}
	}
}
*/
