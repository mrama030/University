// Mohamed Ali Ramadan and Andrew Dybka
// SYSC3310 - Lab 8 - Part B

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
			// With a total divide of 40, that means the interrupt period is now about 1 second

void TA0_N_IRQHandler(void) 
{
	static uint32_t LIGHT_INTENSITY;
	static int32_t TEMP_LOCAL;
	static int32_t TEMP_VOLTAGE; // Not printed on LCD screen.
	
	// 1. Acknowledge Interrupt 0
	TA0CTL &= ~0x0001; // Clear Bit 0 (IFG Interrupt Flag bit)

	// 2. Toggle RED LED
	P1OUT ^= 0x01;
		
	// 3. Display the updated light level only if ready (value passed by reference unchanged if function returns 0).
	if (BSP_LightSensor_End(&LIGHT_INTENSITY) == 1)
	{
		BSP_LCD_DrawString(13,1,"     ", BSP_LCD_Color565(255,0,0)); // Clear previous value before write
		BSP_LCD_SetCursor(13,1); // Set Cursor
		BSP_LCD_OutUDec((LIGHT_INTENSITY / 100), BSP_LCD_Color565(255,0,0)); // Write new value
		BSP_LightSensor_Start(); // Restart the measurement.
	}
	
	// 4. Display the updated temperature level, only if ready.
	if (BSP_TempSensor_End(&TEMP_VOLTAGE, &TEMP_LOCAL) == 1)
	{
		BSP_LCD_DrawString(13,3,"     ", BSP_LCD_Color565(255,0,0)); // Clear previous value before write
		BSP_LCD_SetCursor(13,3); // Set Cursor
		BSP_LCD_OutUDec((TEMP_LOCAL / 100000), BSP_LCD_Color565(255,0,0)); // Write new value
		BSP_TempSensor_Start(); // Restart the measurement.
	}
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
	
	// Configure TimerA_0:
	TA0CTL &= ~0x0030; 	// User function - Clear Bit 4 and 5 - Stop mode, save power
	TA0CTL = 0x02C2;		// COMPARE interrupts, no I/O 
	TA0EX0 = 0x0004;	// TAIDEX = 100 for Divide by 5 Input Divider expansion (Bits 0 - 2)
	
	// Enable interrupts on NVIC for Interrupt Number 9, set to priority 2.
  NVIC_IPR2 = (NVIC_IPR2&0xFFFF00FF)|0x00004000; // priority 2 in bits 13-15
  NVIC_ISER0 |= BIT9;				// enable interrupt 9 in NVIC
	
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
	
	// Reset and Start configured timer:
  TA0CTL |= 0x0024;        // reset and start Timer A0 in CONTINUOUS (MC = 10)
	// 0x0024 = 0000 0000 0010 0100 
	// Set Mode Control (Bit5/4) to 10 for CONTINUOUS Mode and TACLR (Bit 2) to 1 to reset.
	
	__ASM("CPSIE I"); // Global enable interrupts.
	
	// Start Measurements.
	BSP_LightSensor_Start();
	BSP_TempSensor_Start();
	
	while(1)
	{
		// Empty, Interrupt driven
	}
}
