// Lab 7 - Part C
// Mohamed Ali Ramadan and Andrew Dybka

#include <stdint.h>
#include "../inc/msp432p401r.h"
#include "../inc/BSP.h"				// Need to also Add Corresponding  BSP.c to the project
#include "../inc/CortexM.h"   // Need to also Add Corresponding  CortexM.c to the project

// Global variables:
volatile uint32_t counts = 0;

// Locally enables interrupts on the ADC for the Accelerometer.
void BSP_Accelerometer_Int_Init(void)
{
	// Interrupt Enable 0 Register: Set bits A11 (Z) on MEM4 only
	ADC14IER0 |= 0x00000010; // Set Bit 4
	
	// Enable Interrupt 24 (ADC) on NVIC
	NVIC_IPR6 = (NVIC_IPR6 & 0xFFFFFF00) | 0x00000040;
	NVIC_ISER0 |= 0x01000000;
}

// SysTick_Handler now initiates an ADC conversion but it does not wait around until the conversion finishes
void SysTick_Handler(void)
{
	if (++counts == 10) // triggered once every 10 * 333ns
	{
		counts = 0;
		
		// Initiate the ADC Conversion sequence
		ADC14CTL1 = (ADC14CTL1&~0x001F0000) | // clear STARTADDx bit field (bits 16 to 20)
			(2 << 16); // Set STARTADDx bit to 2 (start at MEM2)
		ADC14CTL0 |= 0x00000003;
	}
}

void ADC14_IRQHandler(void) // ADC14 ISR for Accelerometer X/Y/Z, Triggered at the end of a conversion.
{
	uint16_t x,y,z;
	
	// Get X’s data from ADC’s MEM register
	x = ADC14MEM2>>4; // ADC14IFG0 is reset to 0 when the ADC14MEM0 register is read
	
	// Get Y’s data from ADC’s MEM
	y = ADC14MEM3>>4; // ADC14IFG0 is reset to 0 when the ADC14MEM1 register is read
	
	// Get Z’s data from ADC’s MEM
	z = ADC14MEM4>>4; // ADC14IFG0 is reset to 0 when the ADC14MEM1 register is read
	
	// Update LCD Screen with values:
	BSP_LCD_DrawString(10, 1, "     ", BSP_LCD_Color565(0,255,0));  // To erase larger number before display of smaller number
	BSP_LCD_SetCursor(10, 1);
	BSP_LCD_OutUDec(x, BSP_LCD_Color565(0,255,0));
	BSP_LCD_DrawString(10, 2, "     ", BSP_LCD_Color565(0,255,0));  // To erase larger number before display of smaller number
	BSP_LCD_SetCursor(10, 2);
	BSP_LCD_OutUDec(y, BSP_LCD_Color565(0,255,0));
	BSP_LCD_DrawString(10, 3, "     ", BSP_LCD_Color565(0,255,0));  // To erase larger number before display of smaller number
	BSP_LCD_SetCursor(10, 3);
	BSP_LCD_OutUDec(z, BSP_LCD_Color565(0,255,0));
}

int main(void) 
{	
	WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer.
	
	BSP_Accelerometer_Init(); // Initialize Accelerometer.
	
	BSP_Accelerometer_Int_Init(); // Initialize interrupts from Accelerometer.
	
	BSP_Clock_InitFastest(); // Initialize Clock.
	
	BSP_LCD_Init(); // Initialize LCD.
	
	// Write initial values to LCD.
	BSP_LCD_DrawString(0,0,"Accelerometer Demo", BSP_LCD_Color565(255,0,0));
 	BSP_LCD_DrawString(2, 1,"x = ", BSP_LCD_Color565(255,0,0));
	BSP_LCD_DrawString(2, 2,"y = ", BSP_LCD_Color565(255,0,0));
	BSP_LCD_DrawString(2, 3,"z = ", BSP_LCD_Color565(255,0,0));
	
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
