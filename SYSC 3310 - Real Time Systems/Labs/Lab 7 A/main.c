// Lab 7 - Part A

#include <stdint.h>
#include "../inc/msp432p401r.h"
#include "../inc/BSP.h"				// Need to also Add Corresponding  BSP.c to the project
#include "../inc/CortexM.h"   // Need to also Add Corresponding  CortexM.c to the project

volatile uint32_t counts = 0;		// Global variables for tracking

// Interrupt service routine
// Executed every 333 ns*(period)
void SysTick_Handler(void){   // Name must be identical to that in startupxxxx.s file. 
  uint16_t x,y; // x and y of JoyStick
	uint8_t select;

	if (++counts == 10) {  	// Originally 10
     counts=0;
		 BSP_Joystick_Input(&x,&y,&select);
		 BSP_LCD_DrawString(10, 1, "     ", BSP_LCD_Color565(0,255,0));  // To erase larger number before display of smaller number
		 BSP_LCD_SetCursor(10, 1);
		 BSP_LCD_OutUDec(x, BSP_LCD_Color565(0,255,0));
		 BSP_LCD_DrawString(10, 2, "     ", BSP_LCD_Color565(0,255,0));  // To erase larger number before display of smaller number
		 BSP_LCD_SetCursor(10, 2);
		 BSP_LCD_OutUDec(y, BSP_LCD_Color565(0,255,0));		
	}
}


int main(void) {
	
	WDTCTL = WDTPW | WDTHOLD;
	
	BSP_Clock_InitFastest();
	BSP_LCD_Init();
	BSP_Joystick_Init();
	
	BSP_LCD_DrawString(0,0,"Joystick Demo", BSP_LCD_Color565(255,0,0));
	
 	BSP_LCD_DrawString(2, 1,"x = ", BSP_LCD_Color565(255,0,0));
	BSP_LCD_DrawString(2, 2,"y = ", BSP_LCD_Color565(255,0,0));
	
	SYSTICK_STCSR = 0;		// Disable SysTick during setup
	SYSTICK_STRVR = 300000-1;	// If clock is 3 MHz, period is 333ns. Maximum is 2^24-1. Minimum = length of ISR
	SYSTICK_STCVR = 0;	// Any write clear the COUNT bit
	
	SYSPRI3 = (SYSPRI3&0x00FFFFFF)|0x40000000; // priority 2
	SYSTICK_STCSR = BIT0 | BIT1 | BIT2;   		// 0x00000007 to enable interrupts
	
  EnableInterrupts();
	
	while(1){
		__ASM("wfi");
	}
}
