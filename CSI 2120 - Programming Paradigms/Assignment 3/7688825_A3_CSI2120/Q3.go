// Mohamed Ali Ramadan (7688825)
// Question 3

package main

import (
	"math/rand"
	"fmt"
	"errors"
	"math"
)

func RandomArray(len int) []float32 {
	array := make([]float32,len)
	for i:= range array {
		array[i] = rand.Float32()
	}
	return array
}

// GoRoutine
func Process(randomArray []float32, ch chan float32) {

	// Calculate N/2.
	var halfSize int = len(randomArray)/2

	// Split the array into two equal sized ones (using slices).
	var firstSlice = randomArray[0:halfSize]
	var secondSlice = randomArray[halfSize:halfSize*2]

	// Calculate the absolute difference array of floats.
	var absDiffArray,_ = absDiff(firstSlice,secondSlice,0)

	// Sum all elements in the absolute difference array of floats.
	var absDiffSum float32 = 0.0

	for _,value := range absDiffArray {
		absDiffSum = absDiffSum + value
	}

	// Write the sum result to the channel.
	ch <- absDiffSum
}

func main() {
	rand.Seed(100)

	out := make(chan float32)
	defer close(out)

	for i := 0; i < 1000; i++ {
		a := RandomArray(2*(50 + rand.Intn(50)))
		go Process(a,out)
	}

	// Read here the results of processing
	// and sum these results

	var sum float32 = 0.0
	var valuesRead int = 0

	// Read 1000 values from the channel then break loop.
	for value := range out {
		sum = sum + value
		valuesRead++
		// To view all 1000 results individually, uncomment line below.
		// fmt.Println(value)
		if valuesRead == 1000 {
			// Avoid deadlock.
			break
		}
	}

	fmt.Print("Final Result: ")
	fmt.Println(sum)
}

// The following functions are from Question 1.

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