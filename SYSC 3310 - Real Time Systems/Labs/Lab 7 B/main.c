// Lab 7 - Part B
// Mohamed Ali Ramadan and Andrew Dybka

// Joystick Inputs:
// SELECT (GPIO): P4.1
// X (Analog): P6.0
// Y (Analog): P4.4

#include <stdint.h>
#include "../inc/msp432p401r.h"
#include "../inc/BSP.h"				// Need to also Add Corresponding  BSP.c to the project
#include "../inc/CortexM.h"   // Need to also Add Corresponding  CortexM.c to the project

// Global variables:
volatile uint32_t counts = 0;

// Locally enables interrupts on the ADC for the Joystick.
void BSP_Joystick_Int_Init(void)
{
	// Interrupt Enable 0 Register: Set bits A9 (Y) on MEM1 only
	ADC14IER0 |= 0x00000002;
	
	// GPIO on SELECT button
	P4IFG &= ~0x02; // Clear P4.1 flag
	P4IE |= 0x02; // Enable interrupts on P4.1
	
	// Enable Interrupt 24 (ADC) on NVIC
	NVIC_IPR6 = (NVIC_IPR6 & 0xFFFFFF00) | 0x00000040;
	NVIC_ISER0 |= 0x01000000;
	
	// Enable Interrupt 38 (Port 4 for SELECT Button of Joystick) on NVIC
	NVIC_IPR9 = (NVIC_IPR9 & 0xFF00FFFF) | 0x00400000;
	NVIC_ISER1 |= 0x00000040;
}

// SysTick_Handler now initiates an ADC conversion but it does not wait around until the conversion finishes
void SysTick_Handler(void)
{
	if (++counts == 10) // triggered once every 10 * 333ns
	{
		counts = 0;
		
		// Initiate the ADC Conversion sequence
		ADC14CTL1 = (ADC14CTL1 & ~0x001F0000) | (0 << 16);
		ADC14CTL0 |= 0x00000003;
	}
}

void ADC14_IRQHandler(void) // ADC14 ISR for Joystick X/Y, Triggered at the end of a conversion.
{
	uint16_t x,y;
	
	// Get X’s data from ADC’s MEM register
	x = ADC14MEM0>>4; // ADC14IFG0 is reset to 0 when the ADC14MEM0 register is read
	
	// Get Y’s data from ADC’s MEM
	y = ADC14MEM1>>4; // ADC14IFG0 is reset to 0 when the ADC14MEM1 register is read
	
	// Update LCD Screen with values:
	BSP_LCD_DrawString(10, 1, "     ", BSP_LCD_Color565(0,255,0));  // To erase larger number before display of smaller number
	BSP_LCD_SetCursor(10, 1);
	BSP_LCD_OutUDec(x, BSP_LCD_Color565(0,255,0));
	BSP_LCD_DrawString(10, 2, "     ", BSP_LCD_Color565(0,255,0));  // To erase larger number before display of smaller number
	BSP_LCD_SetCursor(10, 2);
	BSP_LCD_OutUDec(y, BSP_LCD_Color565(0,255,0));
}

void PORT4_IRQHandler(void) // Port 4 ISR for Joystick SELECT
{
	static int selectPushes = 0;
	
	if ((P4IFG & 0x02) != 0) // If Select button (P4.1) was pressed.
	{
		P4IFG &= ~0x02; // Clear Port 4.1 ISR flag.
		selectPushes++;
		// Update LCD with number of Select Button Presses.
		BSP_LCD_SetCursor(12, 3);
		BSP_LCD_OutUDec(selectPushes, BSP_LCD_Color565(0,255,0));
	}
}

int main(void) 
{	
	WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer.
	
	BSP_Joystick_Init(); // Initialize Joystick.
	
	BSP_Joystick_Int_Init(); // Initialize interrupts from Joystick.
	
	BSP_Clock_InitFastest(); // Initialize Clock.
	
	BSP_LCD_Init(); // Initialize LCD.
	
	// Write initial values to LCD.
	BSP_LCD_DrawString(0,0,"Joystick Demo", BSP_LCD_Color565(255,0,0));
 	BSP_LCD_DrawString(2, 1,"x = ", BSP_LCD_Color565(255,0,0));
	BSP_LCD_DrawString(2, 2,"y = ", BSP_LCD_Color565(255,0,0));
	BSP_LCD_DrawString(2, 3,"select = ", BSP_LCD_Color565(255,0,0));
	BSP_LCD_SetCursor(12, 3);
	BSP_LCD_OutUDec(0, BSP_LCD_Color565(0,255,0));
	
	// Setup Systick registers.
	SYSTICK_STCSR = 0;		// Disable SysTick during setup
	SYSTICK_STRVR = 300000-1;	// If clock is 3 MHz, period is 333ns. Maximum is 2^24-1. Minimum = length of ISR
	SYSTICK_STCVR = 0;	// Any write clear the COUNT bit
	
	// Enable Systick interrupts.
	SYSPRI3 = (SYSPRI3&0x00FFFFFF)|0x40000000; // priority 2
	SYSTICK_STCSR = BIT0 | BIT1 | BIT2;   		// 0x00000007 to enable interrupts
	
	// Globally enable interrupts.
  EnableInterrupts();
	
	while(1){
		__ASM("wfi");
	}
}
