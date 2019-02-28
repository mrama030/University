// Mohamed Ali Ramadan and Andrew Dybka
// SYSC 3310 - Lab 5c

#include <stdint.h>
#include "../inc/msp432p401r.h"
#include "../inc/CortexM.h"

// Global variables for tracking
volatile uint16_t isHigh; // 1 = TRUE, 0 = FALSE
volatile uint16_t currentPulseIndex;

// Array used to create sine wave.
const uint32_t PulseBuf[100]={
 5000, 5308, 5614, 5918, 6219, 6514, 6804, 7086,
 7361, 7626, 7880, 8123, 8354, 8572, 8776, 8964,
 9137, 9294, 9434, 9556, 9660, 9746, 9813, 9861,
 9890, 9900, 9890, 9861, 9813, 9746, 9660, 9556,
 9434, 9294, 9137, 8964, 8776, 8572, 8354, 8123,
 7880, 7626, 7361, 7086, 6804, 6514, 6219, 5918,
 5614, 5308, 5000, 4692, 4386, 4082, 3781, 3486,
 3196, 2914, 2639, 2374, 2120, 1877, 1646, 1428,
 1224, 1036, 863, 706, 566, 444, 340, 254,
 187, 139, 110, 100, 110, 139, 187, 254,
 340, 444, 566, 706, 863, 1036, 1224, 1428,
 1646, 1877, 2120, 2374, 2639, 2914, 3196, 3486,
 3781, 4082, 4386, 4692};

// Initialize SysTick using DRA-Style Registers.
void SysTick_Init(void){
	
	// Globally disable interrupts before setup.
		__ASM("CPSID I");
	
	// Initially, Set the Control and Status Register to 0.
	SYSTICK_STCSR = 0x00000000;
	
	// Set the Reload Value Register to maximum (24 bits).
	SYSTICK_STRVR = 0x00FFFFFF;			
	
	// Set the Set the Current Value Register to 0.
	SYSTICK_STCVR = 0;						// Any write clears the COUNT bit

	// Locally enable systick interrupt and set NVIC priority.
	SYSPRI3 = (SYSPRI3&0x00FFFFFF)|0x40000000; // priority 2
	SYSTICK_STCSR |= 0x00000007;   		// 0x00000007 to enable interrupts
	
	// Globally enable interrupts at end of setup.
	__ASM("CPSIE I");	
}

void refreshSysTick(uint32_t desiredMicroseconds){
	SYSTICK_STRVR = (10 * (3 * desiredMicroseconds)) - 1; // 3 ticks = 1 microsecond 
	SYSTICK_STCVR = 0;
}

// 1 tick = Period = T = 1 / 3 000 000 Hz = 333 nanoseconds
// 3 ticks = 1 microsecond by definition

void LaunchPad_Init(void){

	// Basic Config:
	P1SEL1 &= ~0x01; 
	P1SEL0 &= ~0x01; // P1.0 set to GPIO by clearing Bit 0 of P1SEL1 and P1SEL0. 
	P1DIR |= 0x01; // P1.0 set to OUTPUT
	
	// Output config:
	P1DS &= ~0x01; // Clear P1.0 Drive Strength to set to regular.
	
	// Systick config with Interrupts:
	SysTick_Init();
	
	// Global variables / LED initial values.
	isHigh = 1;
	currentPulseIndex = 0;
	P1OUT |= 0x01; // red LED on
	
	// Set number of ticks before interrupt is launched. (SET H)
	refreshSysTick(PulseBuf[currentPulseIndex]);
}

void SysTick_Handler(void){   // Name must be identical to that in startupxxxx.s file in Keil
	
	if (isHigh == 1) // HIGH == true
	{
		refreshSysTick(10000 - PulseBuf[currentPulseIndex]); // SET L
		isHigh = 0; // false
		P1OUT &= ~0x01; // turn off RED LED as we are entering LOW mode
	}
	else 
	{
		currentPulseIndex++;
		refreshSysTick(PulseBuf[currentPulseIndex]); // SET H
		isHigh = 1; // true
		P1OUT |= 0x01; // turn on RED LED as we are entering HIGH mode
		
		if (currentPulseIndex == 100)
		{
			currentPulseIndex = 0;
		}
	}
}

int main() {
	// Initialize Port1 and SysTick.
	LaunchPad_Init();
	
	while(1){
	}
}
