// Mohamed Ali Ramadan (Student Number: 101135828)
// SYSC 3310 - Lab 1 - Part G

#include "main.h"

// Global variables:
uint32_t seed;

int main(void){
		
	// Initialize the seed to a value equal to the current time, expressed in seconds from the beginning of the this year.
	randomInit();
		
	// Array
	uint32_t randomNumbers[1000];
	
	// Set seed as first element in array.
	randomNumbers[0] = 23556477;
		
	// Counter for use in FOR loops.
	uint16_t counter = 0;	
	
	// Fill the array with randomly generated numbers.	
	for(counter = 1; counter < NUMBER_OF_ELEMENTS; counter++)
	{
		randomNumbers[counter] = random(randomNumbers[counter - 1]);
	}
	
	// Calculate the sum of all the randomly generated numbers.
	float sum = 0.0;
	
	for(counter = 0; counter < NUMBER_OF_ELEMENTS; counter++)
	{
		sum += randomNumbers[counter];
	}
	
	// Calculate the average by dividing the sum of the elements by the number of elements summed. 
	float average = sum / NUMBER_OF_ELEMENTS;
	
	return 0;
}

uint32_t random(uint32_t previousRandomNumber){
	// Calculate M (n+1) using the formula.
	return (A_MULTIPLIER * previousRandomNumber + C_INCREMENT) % M;
}

void randomInit(void){
	
	// Get the current system time.
	time_t currentTime;
	time(&currentTime);
	
	// Get the number of seconds representing the start of the year 2018.
	struct tm *start;
	start->tm_year = 118;
	start->tm_mon = 0;
	start->tm_mday = 1;
	start->tm_hour = 0;
	start->tm_min = 0;
	start->tm_sec = 0;
	
	time_t start_in_seconds;
	start_in_seconds = mktime(start);

	// Initialize seed (global variable).
	seed = (currentTime - start_in_seconds);
	
	return;
}
