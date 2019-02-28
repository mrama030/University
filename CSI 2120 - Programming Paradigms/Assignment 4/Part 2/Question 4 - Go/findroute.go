// Mohamed Ali Ramadan (7688825) // Assignment 4 - Question 4 (Go)
package main
import (
	"fmt"
	"bufio"
	"os"
	"math"
	"strconv"
	"runtime"
)

type Pool struct {
	name string
	latitude float64
	longitude float64
}
type Node struct {
	pool Pool
	childrenNodes []*Node
	parentNode *Node
	distanceToParent float64
}
type Edge struct {
	poolName string
	distanceToParent float64
}
type ChildParentLink struct {
	childIndex int
	closestParentIndex int
	distanceToParent float64
}

// Used for searching the parent node in the in-progress built tree.
func findNode(poolName string, currentNode *Node)(foundNode *Node){
	foundNode = nil
	if currentNode.pool.name == poolName {
		foundNode = currentNode
	} else if children := currentNode.childrenNodes; children != nil {
		for i := 0; foundNode == nil && i < len(children); i++ {
			foundNode = findNode(poolName,children[i])
		}
	}
	return
}
// Used for obtaining the solution from the built tree.
func traverseTree(currentNode *Node)(solution []Edge) {
	if currentNode == nil {
		return nil
	}
	var solutionStep = Edge{currentNode.pool.name,currentNode.distanceToParent}
	solution = append(solution, solutionStep)

	if children := currentNode.childrenNodes; children != nil {
		for i := 0; i < len(children); i++ {
			temp := traverseTree(children[i])
			for _,v := range temp {
				solution = append(solution,v)
			}
		}
	}
	return
}
// Go Routine: For finding each child's closest parent.
func findClosestParentForNode(ch chan ChildParentLink, sliceToSearch []Pool, childIndex int, childPool Pool) {
	var minimumDistanceSoFar float64 = calculateDistance(childPool,sliceToSearch[0])
	var indexOfClosestParent int = 0

	for index,potentialMinimum := range sliceToSearch {
		if temp := calculateDistance(childPool,potentialMinimum); temp < minimumDistanceSoFar {
			indexOfClosestParent = index
			minimumDistanceSoFar = temp
		}
	}
	ch <- ChildParentLink{childIndex,indexOfClosestParent,minimumDistanceSoFar}
}
// Calculates distance between two pools.
func calculateDistance(pool1 Pool, pool2 Pool)(result float64) {
	var Lat1Rad float64 = math.Pi*(pool1.latitude/180)
	var Lon1Rad float64 = math.Pi*(pool1.longitude/180)
	var Lat2Rad float64 = math.Pi*(pool2.latitude/180)
	var Lon2Rad float64 = math.Pi*(pool2.longitude/180)
	var A float64 = math.Pow(math.Sin((Lat1Rad-Lat2Rad)/2),2.0)
	var C float64 = math.Cos(Lat1Rad)*math.Cos(Lat2Rad)
	var D float64 = math.Pow(math.Sin((Lon1Rad-Lon2Rad)/2),2.0)
	var B float64 = C*D
	var DRad float64 = 2*math.Asin(math.Sqrt(A+B))
	return DRad*6371
}
// Reads a sorted pools list and solves the problem and returns the solution as an array of edges.
func findRoute(fileName string, numGoRoutines int)(route []Edge) {
	// 1. Open the file.
	fileSortedPools, openError := os.Open(fileName)
	if openError != nil {
		fmt.Println("Unable to open the file specified.")
		return nil
	}

	// 2. Extract the file data into an array of strings.
	fileScanner := bufio.NewScanner(fileSortedPools)
	var lines []string
	var tempLine string

	for fileScanner.Scan() {
		if tempLine = fileScanner.Text(); tempLine != "" {
			lines = append(lines, tempLine)
		}
	}
	if fileReadError := fileScanner.Err(); fileReadError != nil {
		fmt.Println("Unable to read the file specified.")
		return nil
	}
	if math.Mod((float64)(len(lines)),3.0) != 0.0 {
		fmt.Println("The file should have 3 lines per pool, which means the line count must be a multiple of 3.")
		fmt.Printf("The provided file has %d lines and is not acceptable. Please try again.\n", len(lines))
		return nil
	}

	// 3. Create an array of pools.
	var tempPool Pool
	var sortedPools []Pool

	for c := 0; c < len(lines); c = c + 3 {
		tempLatitude, errLat := strconv.ParseFloat(lines[c + 1], 64)
		if errLat != nil {
			fmt.Println("Failed pool creation because a float was expected for a pool's latitude but was not received.")
			return nil
		}
		tempLongitude, errLon := strconv.ParseFloat(lines[c + 2], 64)
		if errLon != nil {
			fmt.Println("Failed pool creation because a float was expected for a pool's longitude but was not received.")
			return nil
		}
		tempPool = Pool{lines[c], tempLatitude,tempLongitude}
		sortedPools = append(sortedPools, tempPool)
	}

	// 4. Find closest parent for each pool (except first one, the root) with multiple go routines.

	runtime.GOMAXPROCS(numGoRoutines)

	var channel = make(chan ChildParentLink)
	defer close(channel)

	// Call Go routine for each child pool after root.
	for i := 1; i < len(sortedPools); i++ {
		// 0 to i-1 = 0 to i in Go slices
		go findClosestParentForNode(channel, sortedPools[0:i], i, sortedPools[i])
	}

	var valuesRead int = 0
	var closestParents = make([]ChildParentLink, len(sortedPools))
	// Root does not have a closest parent. Attempting to use the index -5 will cause problems.
	closestParents[0] = ChildParentLink{-5,-5,-5}

	// Complete the array of closest parents.
	for childParentLink := range channel {
		closestParents[childParentLink.childIndex] = ChildParentLink{childParentLink.childIndex,childParentLink.closestParentIndex,childParentLink.distanceToParent}
		valuesRead++
		// The channel will have the one result for every pool except root pool.
		if valuesRead == len(sortedPools) - 1 {
			// Avoid infinite loop.
			break
		}
	}

	// 5. Build the tree.

	// Create the root node.
	var rootValue Pool = Pool{sortedPools[0].name,sortedPools[0].latitude,sortedPools[0].longitude}
	var root Node = Node{rootValue,nil,nil,0.0}

	// Build the remaining tree.
	for x:=1; x < len(sortedPools); x++ {

		var parentIndex int = closestParents[x].closestParentIndex
		var closestParentName string = sortedPools[parentIndex].name

		// Get the closest parent node (pointer) by searching the tree for the closest parent node's name.
		var closestParentNode *Node = findNode(closestParentName,&root)

		// Create the child node from the child pool.
		var childValue = Pool{sortedPools[x].name,sortedPools[x].latitude,sortedPools[x].longitude}
		var childNode = Node{childValue,nil,closestParentNode,closestParents[x].distanceToParent}

		// Add child to parent's list of children.
		closestParentNode.childrenNodes = append(closestParentNode.childrenNodes, &childNode)
	}

	// 6. Pre order traverse the created tree and return the solution.
	return traverseTree(&root)
}
// Saves the solution to the specified file path.
func saveRoute(route []Edge, fileName string) bool {
	// Attempt to create an output file.
	outputFile, err := os.Create(fileName)
	if err != nil {
		fmt.Println("Problem creating output file.")
		return false
	}
	defer outputFile.Close()

	var previousDistance float64 = 0.0

	for _,edge := range route {

		_,err1 := outputFile.WriteString(edge.poolName)
		if err1 != nil {
			fmt.Println("Problem writing to created output file.")
			return false
		}

		temp := fmt.Sprintf(" %.3f\n",edge.distanceToParent + previousDistance)
		_,err2 := outputFile.WriteString(temp)
		if err2 != nil {
			fmt.Println("Problem writing to created output file.")
			return false
		}
		previousDistance = previousDistance + edge.distanceToParent
	}
	return true
}
// Main function. Interacts with the user and calls findRoute and saveRoute.
func main() {

	// Test code without user interaction:
	/*
	testSolution := findRoute("/Users/MohamedRamadan/Desktop/ParsedPools.txt",5)
	saveRoute(testSolution,"/Users/MohamedRamadan/Desktop/Solution.txt")
	*/

	scanner := bufio.NewScanner(os.Stdin)
	var fileName string
	var numRoutinesString string
	var outputPath string

	var foundSolution bool = false
	var savedSolution bool = false
	var solution []Edge

	// While true, used to restart when something goes wrong.
	for true {
		foundSolution = false

		for foundSolution == false {

			// 1. Try to scan the user's input for the file name into a string.
			fmt.Println("Please type in the path and filename containing the list of sorted pools in .txt format (example: /Users/MohamedRamadan/Desktop/ParsedPools.txt):")
			scanner.Scan()
			fileName = scanner.Text()
			if scanLineError := scanner.Err(); scanLineError != nil {
				fmt.Println("A line scanning error has occured.")
				break
			}

			// 2. Try to scan the user's input for the number of go routines into a string.
			fmt.Println("Please type in the number (positive integer, 1 or more) of Go routines to use when calculating the solution:")
			scanner.Scan()
			numRoutinesString = scanner.Text()
			if scanLineError := scanner.Err(); scanLineError != nil {
				fmt.Println("A line scanning error has occured.")
				break
			}
			numRoutinesInt, parseError := strconv.Atoi(numRoutinesString)
			if parseError != nil {
				fmt.Println("There was a problem with number you entered. Try again.")
				break
			} else if numRoutinesInt < 1 {
				fmt.Println("There was a problem with number you entered. Try again.")
				break
			}

			// 3. Calculate the solution.
			solution = findRoute(fileName,numRoutinesInt)
			if solution == nil {
				fmt.Println("There was a problem with the filename or contents. Try again.")
				break
			}

			foundSolution = true // break
		}
		if foundSolution == true {
			break
		}
	}

	// At this point the solution is ready for exporting.

	// While true, used to restart when something goes wrong.
	for true {
		savedSolution = false

		for savedSolution == false {

			// 4. Obtain a valid output path/file from the user.
			fmt.Println("Please type in the output path and filename where the solution will be stored in .txt format (example: /Users/MohamedRamadan/Desktop/solution.txt):")
			scanner.Scan()
			outputPath = scanner.Text()
			if scanLineError := scanner.Err(); scanLineError != nil {
				fmt.Println("A line scanning error has occured.")
				break
			}

			// 6. Try to save the solution to the specified file path.
			savedSolution = saveRoute(solution,outputPath) // can act like a break if true
		}
		if savedSolution == true {
			break
		}
	}
	fmt.Println("Solution file created in specified path. Program has terminated.")
}