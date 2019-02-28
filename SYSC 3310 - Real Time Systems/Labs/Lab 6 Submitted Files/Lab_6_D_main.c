// Mohamed Ali Ramadan and Andrew Dybka
// SYSC3310 - Lab 6 - Part D

// Mark II Pins mapped to MSP432:

// Buttons (Negative Logic, using GPIO):
// S1: P5.1
// S2: P3.5

#include <stdint.h>
#include <stdio.h>
#include "..\inc\BSP.h"
#include "..\inc\msp432p401r.h"

// Constants
const uint8_t Pin1 = 0x02;
const uint8_t Pin5 = 0x20;

// Global Variables
volatile uint32_t BUTTON_1_PRESSES = 0;
volatile uint32_t BUTTON_2_PRESSES = 0;

void LAB6D_Init()
{
	// Globally disable interrupts before setup.
	__ASM("CPSID I");
	
	// Stop WatchDog Timer:
	WDTCTL = WDTPW | WDTHOLD;
	
	// LCD Screen Configuration:
	BSP_LCD_Init();
	
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
	
	// Interrupt Configuration (for Buttons):
	
	P5IE |= Pin1; // ARM INTERRUPTS FOR P5.1
	P3IE |= Pin5; // ARM INTERRUPTS FOR P3.5
	
	P5IES &= ~Pin1; // SELECT RISING EDGE
	P3IES &= ~Pin5; // SELECT RISING EDGE 
	
	P5IFG &= ~Pin1; // CLEAR FLAG ON SETUP
	P3IFG &= ~Pin5; // CLEAR FLAG ON SETUP
	
	// NVIC Enable Interrupts For Ports 3 (IRQ37) and 5 (IRQ39) and Priorities Configuration:
	
			// Clears BYTE3 (IRQ39 priority) and BYTE1 (IRQ37 priority).
			// Priority 3 means first 3 bits of the byte are: 011 meaning the byte is 011x xxxx = 0x60
			// Set BYTE3 and BYTE1 to 0x60
	NVIC_IPR9 = (NVIC_IPR9 & 0x00FF00FF) | 0x60006000;
	
	NVIC_ISER1 |= 0x000000A0; // For IRQ32 to IRQ63
	
	// Globally enable interrupts at end of setup.
	__ASM("CPSIE I");	
}

void Refresh_LCD()
{
	BSP_LCD_SetCursor(18, 4);
	BSP_LCD_OutUDec(BUTTON_1_PRESSES, BSP_LCD_Color565(255,0,0));
	BSP_LCD_SetCursor(18, 8);
	BSP_LCD_OutUDec(BUTTON_2_PRESSES, BSP_LCD_Color565(0,255,0));
}

void PORT5_IRQHandler(void) // ISR for Button 1
{
	if ((P5IFG & Pin1) != 0)
	{
		BUTTON_1_PRESSES++;
		Refresh_LCD();
		P5IFG &= ~Pin1; // Acknowledge flag
	}
}

void PORT3_IRQHandler(void) // ISR for Button 2
{
	if ((P3IFG & Pin5) != 0)
	{
		BUTTON_2_PRESSES++;
		Refresh_LCD();
		P3IFG &= ~Pin5; // Acknowledge flag
	}
}

int main(void)
{
	LAB6D_Init();
	// Initalize Screen with Labels:
	BSP_LCD_DrawString(2,4,"Button1 Clicks:", BSP_LCD_Color565(255,0,0));
	BSP_LCD_DrawString(2,8,"Button2 Clicks:", BSP_LCD_Color565(0,255,0));
		
	while(1) 
	{
		// Empty loop, expected to be interrupted by ISRs.
	}
}
