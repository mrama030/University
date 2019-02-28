// Mohamed Ali Ramadan and Andrew Dybka
// SYSC3310 - Lab 8 - Part C

#include <stdint.h>
#include "../inc/msp432p401r.h"
#include "../inc/BSP.h"
#include "../inc/CortexM.h"

// Bai, Page 641 TA0 UP mode (does not use TAxCCR0 in this mode)
//   Using ID = divide by 8 and TAIDEX = divide by 5 to get a total divide by 40.
//   Removes the need for global counter-divide in ISR
		  // Since SMCLK = 3 MHz, the period is 330 ns.
	    // Since using continuous mode, interrupt after 0...FFFF
	    // So the interrupt period is 330 ns * 65535 = 21,626,550 ns = 22,000 us = 22 ms (About 1/40th second)
			
			// With a total divide of 40, that means the interrupt period is now about 1 second = 1 Hz -> LED
			// With a total divide of 20, that means the interrupt period is now about 0.5 second = 2 Hz -> Light Level
			// With a total divide of 80 (closest we can set is 40 twice, so counter is required). 1 second * 2 = 0.5 Hz -> Temperature Level

// Interrupt 13
void TA2_N_IRQHandler(void) // Display the updated temperature at 0.5 Hz, using Timer_A2
{
	static int32_t TEMP_LOCAL;
	static int32_t TEMP_VOLTAGE; // Not printed on LCD screen.
	static int16_t counter = 0;
	
	counter++;
	
	// Acknowledge Interrupt:
	TA2CTL &= ~0x0001; // Clear Bit 0 (IFG Interrupt Flag bit)
	
	if (counter == 2) // Because ISR triggered around every second, but we want it to trigget every 2 seconds (frequency of 0.5 Hz)
	{
		counter = 0; // reset counter
		
		// Display the updated temperature level, only if ready.
		if (BSP_TempSensor_End(&TEMP_VOLTAGE, &TEMP_LOCAL) == 1)
		{
			BSP_LCD_DrawString(13,3,"     ", BSP_LCD_Color565(255,0,0)); // Clear previous value before write
			BSP_LCD_SetCursor(13,3); // Set Cursor
			BSP_LCD_OutUDec((TEMP_LOCAL / 100000), BSP_LCD_Color565(255,0,0)); // Write new value
			BSP_TempSensor_Start(); // Restart the measurement.
		}
	}
}

// Interrupt 11
void TA1_N_IRQHandler(void) // Display the updated light level at 2 Hz, using Timer_A1
{
	static uint32_t LIGHT_INTENSITY;
	
	// Acknowledge Interrupt:
	TA1CTL &= ~0x0001; // Clear Bit 0 (IFG Interrupt Flag bit)
	
	// Display the updated light level only if ready (value passed by reference unchanged if function returns 0).
	if (BSP_LightSensor_End(&LIGHT_INTENSITY) == 1)
	{
		BSP_LCD_DrawString(13,1,"     ", BSP_LCD_Color565(255,0,0)); // Clear previous value before write
		BSP_LCD_SetCursor(13,1); // Set Cursor
		BSP_LCD_OutUDec((LIGHT_INTENSITY / 100), BSP_LCD_Color565(255,0,0)); // Write new value
		BSP_LightSensor_Start(); // Restart the measurement.
	}
}

// Interrupt 9
void TA0_N_IRQHandler(void) // Toggle the Red LED at 1 Hz, using Timer_A0
{
	// Acknowledge Interrupt:
	TA0CTL &= ~0x0001; // Clear Bit 0 (IFG Interrupt Flag bit)

	// Toggle RED LED:
	P1OUT ^= 0x01;
}

int main(void) 
{	
	WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer.
	
//TAxCTL Register:
	// Bit 9:8 = 10 - SMCLK (The default 3 MHz Clock)
	// Bit 7:6 = 11 - Divide by 8
	// Bit 5:4 = 00 - Going to be Continuous Mode (timer counts up to 0xFFFF) but for now STOP mode
	// Bit 2 TACLR = 1 - Timer_A clear. SETTING this bit reset TAxR
	// Bit 1 TAIE = 1 - Enable interrupt
	// Bit 0 TAIFG = 0 - No interrupt pending.
	
	// Configure TimerA_2 for about 1 second (ID=8, TAIEX=5, 5*8=40 divide), but use a counter in ISR:
	TA2CTL &= ~0x0030; 	// User function - Clear Bit 4 and 5 - Stop mode, save power
	TA2CTL = 0x02C2;		// COMPARE interrupts, no I/O 
	TA2EX0 = 0x0004;	// TAIDEX = 100 for Divide by 5 Input Divider expansion (Bits 0 - 2)
	
	// Configure TimerA_1 for about 0.5 seconds (ID=4, TAIEX=5, 4*5=20 divide):
	TA1CTL &= ~0x0030; 	// User function - Clear Bit 4 and 5 - Stop mode, save power
	// ID Divide by 4: 10 (Bits 7:6)
	TA1CTL = 0x0282;		// COMPARE interrupts, no I/O 
	TA1EX0 = 0x0004;	// TAIDEX = 100 for Divide by 5 Input Divider expansion (Bits 0 - 2)
	
	// Configure TimerA_0 for about 1 second (ID=8, TAIEX=5, 5*8=40):
	TA0CTL &= ~0x0030; 	// User function - Clear Bit 4 and 5 - Stop mode, save power
	TA0CTL = 0x02C2;		// COMPARE interrupts, no I/O 
	TA0EX0 = 0x0004; // TAIDEX = 100 for Divide by 5 Input Divider expansion (Bits 0 - 2)
	
	// Enable interrupts on NVIC for Interrupt Number 9 (Bits 15-13) and 11 (Bits 31-29), set both to priority 2:
  NVIC_IPR2 = (NVIC_IPR2 & 0x00FF00FF)|0x40004000;
	
	// Enable interrupts on NVIC for Interrupt Number 13 (Bits 15-13), set to priority 2:
  NVIC_IPR3 = (NVIC_IPR3 & 0xFFFF00FF)|0x00004000;
	
	// Enable interrupt 9, 11 and 13 in NVIC:
  NVIC_ISER0 |= 0x00002A00; 
	
	// Configure RED LED (P1.0) as GPIO:
	P1SEL1 &= ~0x01; // Select GPIO
	P1SEL0 &= ~0x01;// Select GPIO
	P1DS &= ~0x01; // Regular Strength
	P1DIR |= 0x01;	// Select Output
	
	// Initialize Mark II's components:
	BSP_LCD_Init();
	BSP_LightSensor_Init();
	BSP_TempSensor_Init(); 
	BSP_LCD_DrawString(1,1,"Light Lvl:", BSP_LCD_Color565(0,255,0));
	BSP_LCD_DrawString(1,3,"Temp. Lvl:", BSP_LCD_Color565(0,255,0));
	
	// Reset and Start configured timers:
  TA2CTL |= 0x0024;        // reset and start Timer A2 in CONTINUOUS (MC = 10)
	TA1CTL |= 0x0024;        // reset and start Timer A1 in CONTINUOUS (MC = 10)
  TA0CTL |= 0x0024;        // reset and start Timer A0 in CONTINUOUS (MC = 10)
	// 0x0024 = 0000 0000 0010 0100 
	// Set Mode Control (Bit5/4) to 10 for CONTINUOUS Mode and TACLR (Bit 2) to 1 to reset.
	
	__ASM("CPSIE I"); // Global enable interrupts.
	
	// Start measurements.
	BSP_LightSensor_Start();
	BSP_TempSensor_Start();
	
	while(1)
	{
		// Empty, Interrupt driven.
	}
}
