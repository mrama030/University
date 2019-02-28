// Mohamed Ali Ramadan (101135828) and Andrew Dybka
// SYSC 3310 - Lab 5b

#include <stdint.h>
#include "../inc/msp432p401r.h"
#include "../inc/CortexM.h"

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

void LaunchPad_Init(void)
{
	// Port 1 Config:
	P1SEL1 &= ~0x01; 
	P1SEL0 &= ~0x01; // P1.0 set to GPIO by clearing Bit 0 of P1SEL1 and P1SEL0. 
	P1DIR |= 0x01; // P1.0 set to OUTPUT
	P1DS &= ~0x01; // Clear P1.0 Drive Strength to set to regular.
	P1OUT &= ~0x01; // Clear output value of P1.0 just in case.
}

// Initialize SysTick using DRA-Style Registers.
void SysTick_Init(void)
{
	SYSTICK_STCSR = 0x00000000; // Initially, Set the Control and Status Register to 0.
	SYSTICK_STRVR = 0x00FFFFFF; // Set the Reload Value Register to maximum (24 bits).
	SYSTICK_STCVR = 0; // Set the Set the Current Value Register to 0. Any write clears the COUNT bit
	SYSTICK_STCSR |= 0x00000005; 	// Set the Control and Status Register's Bit0 to 1 to ENABLE systick. Set Bit2 to 1 to activate the core clock of 3 MHz.   		
}

void SysTick_Wait1us(uint32_t delay)
{
	// Each tick = 1/3000000 Hz = 333 ns
	
	int i;
	
	for(i = 0; i < delay; i++)
	{
		SYSTICK_STRVR = 3; 	// It takes 3 ticks to make 1 microsecond.
		SYSTICK_STCVR = 0;
		// While SysTick is not done counting (COUNTFLAG/Bit16 is not set to 1), wait...
		while((SYSTICK_STCSR & 0x00010000) == 0) {}			
	}
}

int main() 
{
	// Initialize Port1 and SysTick.
	LaunchPad_Init();
	SysTick_Init();
	
	uint16_t pulseIndex = 0;
	
	while(1){
		
		// Note: To wait one second, call Wait1us(1000000)
		
		// Step 1. Look up a new value of H.
		uint16_t H = PulseBuf[pulseIndex];
		
		// Step 2. Calculate L = 10 000 - H
		uint16_t L = 10000 - H;
		
		// Step 3. Set P1.0 High
		P1OUT |= 0x01; // red LED on
		
		// Step 4. Wait H microseconds.
    SysTick_Wait1us(H);

		// Step 5. Clear P1.0 low
    P1OUT &= ~0x01; // red LED off
		
		// Step 6. Wait L microseconds.
    SysTick_Wait1us(L);
		
		// Step 7. Deal with index counter.
		pulseIndex++;
		
		if (pulseIndex == 100)
		{
			pulseIndex = 0;
		}
	}
}
