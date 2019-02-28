// View Lab 9 - Part B for additional comments.

// Mohamed Ali Ramadan and Andrew Dybka
// SYSC 3310 - Lab 9 - Part C

#include <stdint.h>
#include "../inc/msp432p401r.h"
#include "../inc/BSP.h"				// Need to also Add Corresponding  BSP.c to the project
#include "../inc/CortexM.h"   // Need to also Add Corresponding  CortexM.c to the project

#define PWM_PERIOD 40000
#define PWM_PULSE_MAX  20000		  // Experienced Value = Maximum high pulse is 2 ms for +90 degrees
#define PWM_PULSE_MIN	 4500		// Experienced Value = Maximum high pulse is 2 ms for -90 degrees
#define PWM_PULSE_AT_CENTER 12000 // Experienced value is around 1.5 ms or 12000 ticks @ 8MHz
#define DELAY 800

// Constants
const uint8_t Pin1 = 0x02;
const uint8_t Pin4 = 0x10;
const uint8_t Pin5 = 0x20;
const uint8_t Pin6 = 0x40;

// Global variable
static int8_t position = 1; //-1 = -90 deg, 0 = 0 deg, 1 = +90 deg
static uint32_t high = PWM_PERIOD/10;

void Buttons_Init()
{	
	// S1 and S2 Buttons Configuration:
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
	
	BSP_Joystick_Init(); // Joystick Initialization (includes SELECT button)
}

void Buttons_Interrupts_Init()
{
		// Globally disable interrupts before setup.
	__ASM("CPSID I");
	
	// Joystick SELECT button
	P4IE |= Pin1; // ARM INTERRUPTS FOR P4.1
	P4IES &= ~Pin1; // SELECT RISING EDGE
	P4IFG &= ~Pin1; // CLEAR FLAG ON SETUP
	
	// S1 Button
	P5IE |= Pin1; // ARM INTERRUPTS FOR P5.1
	P5IES &= ~Pin1; // SELECT RISING EDGE
	P5IFG &= ~Pin1; // CLEAR FLAG ON SETUP

	// S2 Button
	P3IE |= Pin5; // ARM INTERRUPTS FOR P3.5
	P3IES &= ~Pin5; // SELECT RISING EDGE 
	P3IFG &= ~Pin5; // CLEAR FLAG ON SETUP
	
	// Enable Interrupt 39,38,37 
	NVIC_IPR9 = (NVIC_IPR9 & 0x000000FF) | 0x40404000;
	NVIC_ISER1 |= 0x000000E0;
	
	// Globally enable interrupts at end of setup.
	__ASM("CPSIE I");	
}

void PORT5_IRQHandler(void) // ISR for Button 1 - Go to LEFT Position
{
	if ((P5IFG & Pin1) != 0)
	{
		P5IFG &= ~Pin1; // Acknowledge flag
		
		uint32_t i = 0;
		
		if (position != -1)
		{
			while(high < PWM_PULSE_MAX)   // CCW: to -90
			{
				TA0CCR2 = PWM_PERIOD - high;
				high += 2;
				for(i=DELAY; i>0; i--);
			}	
		}
		
		position = -1;
	}
}

void PORT3_IRQHandler(void) // ISR for Button 2 - Go to RIGHT Position
{
	if ((P3IFG & Pin5) != 0)
	{
		P3IFG &= ~Pin5; // Acknowledge flag
		
		uint32_t i = 0;
		
		if (position != 1)
		{
			while (high > PWM_PULSE_MIN)		// CW: to +90
			{
				TA0CCR2 = PWM_PERIOD - high;
				high -= 2;
				for(i=DELAY; i>0; i--);
			}
		}
		
		position = 1;
	}
}

void PORT4_IRQHandler(void) // Port 4 ISR for Joystick SELECT - Go to CENTER Position
{	
	if ((P4IFG & Pin1) != 0) // If Select button (P4.1) was pressed.
	{
		P4IFG &= ~Pin1; // Clear Port 4.1 ISR flag.
		
		uint32_t i = 0;
		
		if (position == -1) // -90 degrees (Left)
		{
			while(high > PWM_PULSE_AT_CENTER)   // CCW: -90 to 0 deg
			{
				TA0CCR2 = PWM_PERIOD - high;
				high -= 2;
				for(i=DELAY; i>0; i--);
			}	
		}
		else if (position == 1) // +90 degrees (Right)
		{
			while(high < PWM_PULSE_AT_CENTER)   // CCW: +90 to 0 deg
			{
				TA0CCR2 = PWM_PERIOD - high;
				high += 2;
				for(i=DELAY; i>0; i--);
			}	
		}	
		
		position = 0;
	}
}

int main(void)
{	
		// Stop WatchDog Timer:
		WDTCTL = WDTPW | WDTHOLD;
         
	  P2DIR |= BIT5;			// Configure P12.5 as output
	  P2SEL1 &= ~BIT5;	
	  P2SEL0 |= BIT5;			// Set P2.5 as TA0.2 PWM output pin (Primary module function)
	
		CSKEY = CSKEY_VAL;
	  CSCTL0 = 0;
	  CSCTL0 = DCOEN | DCORSEL_2 | 0x485;     	 // (From Bia, page 667)
	
		TA0CCTL2 = OUTMOD_3 | CCIE;
	  TA0CTL = TASSEL_2 | MC_1 | TACLR;		// SMCLK = 3 MHz, Divide by 1, Up Mode
		TA0CCR0 = PWM_PERIOD;
		TA0CCR2 = PWM_PULSE_MAX;
	
		Buttons_Init();
		Buttons_Interrupts_Init();
		
		// Ensure the program always starts at +90 degree position.
		uint32_t i;
		
		position = 1; // Indicates that position is at +90 degrees.

		while (1) 
		{
			// Interrupt Driven
			__ASM("wfi");
		}
}
