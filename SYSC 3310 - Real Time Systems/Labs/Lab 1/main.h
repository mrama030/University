// Mohamed Ali Ramadan (Student Number: 101135828)
// SYSC 3310 - Lab 1 - Part G

#include <stdint.h>
#include <time.h>

#ifndef MAIN_H

#define MAIN_H

// Define contant values.
#define NUMBER_OF_ELEMENTS 1000
#define A_MULTIPLIER 1664525
#define C_INCREMENT 1013904223
#define M 4294967296 // 2^32

// Variables:
extern uint32_t seed;

// Functions:
void randomInit(void);
uint32_t random(uint32_t previousRandomNumber);

#endif
