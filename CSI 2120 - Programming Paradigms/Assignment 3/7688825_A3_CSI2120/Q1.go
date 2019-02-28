// Mohamed Ali Ramadan (7688825)
// Question 1

package main

import (
	"fmt"
	"math"
	"errors"
	"strings"
	"strconv"
	"bufio"
	"os"
)

func main() {

	var start = [4]float32{-10.0, 20.0, -30.0, 40.0}
	var previousSlice = start[0:4]
	var inputString string
	var validInput_1 bool = false

	// Infinite while loop.
	for true {
		validInput_1 = true
		fmt.Print("Previous slice: ")
		fmt.Println(previousSlice)
		fmt.Println("Enter another slice of floating point numbers, seperated by spaces (no extras at end), and press enter to confirm it.")
		scanner := bufio.NewScanner(os.Stdin)
		scanner.Scan()
		inputString = scanner.Text()
		if err := scanner.Err(); err != nil {
			os.Exit(1)
		}

		// Convert to seperate strings.
		floatStrings := strings.Split(inputString, " ")
		// Convert each seperate string to a float.
		floatsSlice := make([]float32, len(floatStrings))
		for i := range floatStrings {
			tempFloat, err := strconv.ParseFloat(floatStrings[i], 32)
			if err == nil {
				floatsSlice[i] = (float32)(tempFloat)
			} else {
				validInput_1 = false
				fmt.Println("There was a problem with the set of floats you entered.")
				break
			}
		}

		if validInput_1 == false {
			break
		}
		fmt.Println("Please enter -1, 0 or 1 to select processing method, and press the enter key to confirm it.")
		fmt.Scanf("%s", &inputString)
		option,errorInt := strconv.Atoi(inputString)

		if errorInt != nil || (option != -1 && option != 0 && option != 1) {
			fmt.Println("There was a problem with the processing option selection.")
			break
		} else {
			processed, lengthError := absDiff(previousSlice, floatsSlice, (int)(option))
			if lengthError != nil {
				fmt.Println(lengthError)
			} else {
				fmt.Print("Result: ")
				fmt.Println(processed)
				previousSlice = processed
			}
		}
		fmt.Println("Enter \"q\" to quit or anything else to continue.")
		fmt.Scanf("%s", &inputString)
		if inputString == "q" {
			break
		}

		fmt.Println()
	}

	fmt.Println("Program has terminated.")
}

func absDiff(sliceA, sliceB []float32, version int)(res []float32, err error) {

	err = nil

	if version == -1 { // length equal to longer slice (missing elements equal zero)

		if len(sliceA) >= len(sliceB) {
			res = make([]float32, len(sliceA))
			for i,value := range sliceA {
				if i + 1 > len(sliceB) {
					res[i] = absDiffNum(value,0.0)
				} else {
					res[i] = absDiffNum(value, sliceB[i])
				}
			}
		} else {
			res = make([]float32, len(sliceB))
			for i,value := range sliceB {
				if i + 1 > len(sliceA) {
					res[i] = absDiffNum(0.0,value)
				} else {
					res[i] = absDiffNum(sliceA[i],value)
				}
			}
		}

	} else if version == 0 { // error if slices are not the same length

		if len(sliceA) != len(sliceB) {
			err = errors.New("Slices are not the same length.")
			res = nil
			return
		} else {
			// sliceA and sliceB have the same length.
			res = make([]float32, len(sliceA))
			for i,value := range sliceA {
					res[i] = absDiffNum(value, sliceB[i])
			}
		}

	} else if version == 1 { // length equal to the shorter list (ignore extra values)

		if len(sliceA) <= len(sliceB) {
			res = make([]float32, len(sliceA))
			for i,value := range sliceA {
				res[i] = absDiffNum(value,sliceB[i])
			}
		} else {
			res = make([]float32, len(sliceB))
			for i,value := range sliceB {
				res[i] = absDiffNum(sliceA[i],value)
			}
		}

	}
	return
}

func absDiffNum(num1 float32, num2 float32) (float32) {
	return (float32)(math.Abs((float64)(num1 - num2)))
}