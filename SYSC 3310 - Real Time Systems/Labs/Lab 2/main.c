// Mohamed Ali Ramadan (Student Number: 101135828) and Andrew Dybka (Student Number: )
// SYSC 3310 - Lab 2

#include <stdint.h>

int main(void) 
{ 
	// 1. Initialize aByte to 0x33 
	uint8_t aByte = 0x33;
	// Expected Result = 0011 0011 = 0x33
	
	// 2. Set Bits 0 and 7 on aByte
	// Use the OR bit operator with the value: 1000 0001 = 0x81
	aByte |= 0x81;
	// Expected Result = 1011 0011 = 0xB3
	
	// 3. Clear Bits 0 and 7 on aByte, using & only
	// Use the AND bit operator with value: 0111 1110 = 0x7E
	aByte &= 0x7E;
	// Expected Result = 0011 0010 = 0x32

	// 4. Clear Bit 7 on aByte, using both & and ~ operators in the same statement.
	// Use the AND bit operator with value: 0111 1111 = 0x7F = ~(1000 0000) = ~0x80
	aByte &= ~0x80;
	// Expected Result = 0011 0010 = 0x32
	
	// 5. Shift the bits of aByte left by 5 places
	aByte = aByte << 5;
	// Expected Result = 0100 0000 = 0x40
	
	// 6. Shift the bits of aByte right by 5 places
	aByte = aByte >> 5;
	// Expected Result = 0000 0010 = 0x02
	
	// 7. Initialize aWord to zero
	uint16_t aWord = 0x0000;
	// Expected Result = 0000 0000 0000 0000 = 0x0000
	
	// 8. Set the high byte of aWord to all ones
	aWord |= 0xFF00;
	// Expected Result = 1111 1111 0000 0000 = 0xFF00
	
	// 9. OR the contents of aWord with the contents of aByte
	aWord |= aByte;
	// Expected Result = 0xFF00 | 0x02 = 1111 1111 0000 0010 = 0xFF02
	
	// 10. You’ve given the code for this next step. In the comment (in addition to the current contents of aWord) you must describe what the code does (in a similar fashion to Steps 1 to 9)
	aWord &= ~(aByte << 8);
	// Expected Result = 0xFF02 & ~0x0200 = 0xFF02 & 0xFDFF = 1111 1101 0000 0010 = 0xFD02
		
	// 11. Shift the contents of aWord 8 bits to the right.
	aWord = aWord >> 8;
	// Expected Result = 0000 0000 1111 1101 = 0x00FD
	
	return 0;
}
