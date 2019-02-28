// Mohamed Ali Ramadan (7688825)
// Question 2
package main

import (
	"fmt"
)

// Part 1 of Q2
type Baking struct {
	bakeTime int
	coolTime int
	temperature int
}
type Item struct {
	weight int
}
type Bread struct {
	name string
	ingredients map[string]Item
	weight float32
	baking Baking
}

// Part 2 of Q2
type Baker interface{
	shoppingList(map[string]Item)(map[string]Item, map[string]Item)
	printBakeInstructions()
	printBreadInfo()
}

// Part 3 of Q2
func NewBread()(bread *Bread) {
	// Define a map of ingredients.
	m := make(map[string]Item)
	m["whole wheat flour"] = Item{500}
	m["yeast"] = Item{25}
	m["salt"] = Item{25}
	m["sugar"] = Item{50}
	m["butter"] = Item{50}
	m["water"] = Item{350}
	// Define baking struct.
	var bakingInfo Baking
	bakingInfo = Baking{120,60,180}
	// Calculate total weight.
	var w float32 = 0
	for _, ingredient := range m {
		w = w + (float32)(ingredient.weight)
	}
	// Create bread struct and return a pointer to it.
	var temp Bread = Bread{"Whole Wheat",m,w,bakingInfo}
	bread = &temp
	return
}
func NewBreadVariation(newName string, toAdd map[string]Item, toRemove map[string]Item)(bread *Bread) {
	// Get a basic bread.
	bread = NewBread()
	// Apply name change to it.
	bread.name = newName

	if nothingToAdd := toAdd == nil; nothingToAdd == false {
		var isNewIngredient bool = true
		// Process ingredients to add.
		for toAddKey, toAddValue := range toAdd {
			isNewIngredient = true

			for ingredientKey, ingredientValue := range bread.ingredients {
				if toAddKey == ingredientKey {
					// If ingredient is already on list, just add the additional amount (weight).
					bread.ingredients[toAddKey] = Item{ingredientValue.weight + toAddValue.weight}
					isNewIngredient = false
					break
				}
			}
			if isNewIngredient == true {
				// Add a completely new ingredient to the bread.
				bread.ingredients[toAddKey] = toAddValue
			}
		}
	}

	if nothingToRemove := toRemove == nil; nothingToRemove == false {
		// Process ingredients to remove.
		for toRemoveKey, toRemoveValue := range toRemove {
			for ingKey, ingValue := range bread.ingredients {
				if toRemoveKey == ingKey {
					if toRemoveValue.weight >= ingValue.weight {
						// Remove ingredient from map completely.
						delete(bread.ingredients,toRemoveKey)
					} else {
						bread.ingredients[toRemoveKey] = Item{ingValue.weight - toRemoveValue.weight}
					}
					break
				}
			}
		}
	}

	// Update the new weight after removing and adding all ingredients.
	var newWeight float32 = 0
	for _, ingredient := range bread.ingredients {
		newWeight = newWeight + (float32)(ingredient.weight)
	}
	bread.weight = newWeight

	return
}

// Part 4 of Q2
func (b *Bread) printBreadInfo() {
	fmt.Printf("%s bread\n", b.name)
	fmt.Println(b.ingredients)
	weightInKg := b.weight / 1000
	fmt.Printf("Weight: %.3f", weightInKg)
}
func (b *Bread) printBakeInstructions() {
	fmt.Printf("Bake at %d Celcius for %d minutes and let cool for %d minutes.\n", b.baking.temperature, b.baking.bakeTime, b.baking.coolTime)
}
func (b *Bread) shoppingList(available map[string]Item)(missing map[string]Item, remainder map[string]Item) {
	// Instantiate results to empty maps.
	missing = make(map[string]Item)
	remainder = make(map[string]Item)

	// Set missing to required ingredients list.
	for k,v := range b.ingredients {
		missing[k] = v
	}

	// Go through all the required ingredients and compare them to what we have available.
	for requiredKey, requiredValue := range b.ingredients {
		// Search the available ingredients.
		for availableKey, availableValue := range available {
			// Exists in the available list.
			if requiredKey == availableKey {
				// If not enough of the ingredient is available, add difference to shopping list.
				if requiredValue.weight > availableValue.weight {
					// Use all of the amount we have.
					remainder[requiredKey] = Item{0}
					// Add what we still need to the shopping list.
					missing[requiredKey] = Item{requiredValue.weight - availableValue.weight}
				} else if requiredValue.weight == availableValue.weight {
					// All used up so nothing remains.
					remainder[requiredKey] = Item{0}
					// This ingredient is not missing.
					delete(missing, requiredKey)
				} else {
					remainder[requiredKey] = Item{availableValue.weight - requiredValue.weight}
					// This ingredient is not missing.
					delete(missing, requiredKey)
				}
				break
			}
		}
	}
	return
}

// Part 5 of Q2
func main() {
	// My Initial Ingredients
	myIngredients := make(map[string]Item)
	myIngredients["whole wheat flour"] = Item{5000}
	myIngredients["salt"] = Item{500}
	myIngredients["sugar"] = Item{1000}

	// Empty array of 2 Bakers
	var bakersArray = [2]Baker {nil,nil}
	// Slice for bakers 0 and 1 of the array bakersArray.
	var bakersSlice []Baker = bakersArray[0:2]

	// Ingredients to remove and add to create Sesame bread instead of regular bread.
	toAdd := make(map[string]Item)
	toAdd["white flour"] = Item{250}
	toAdd["sesame"] = Item{50}
	toRemove := make(map[string]Item)
	toRemove["whole wheat flour"] = Item{250}

	bakersSlice[0] = NewBread()
	wwMissing, wwRemainder := bakersSlice[0].shoppingList(myIngredients)

	bakersSlice[1] = NewBreadVariation("Sesame",toAdd,toRemove)
	sesameMissing,_ := bakersSlice[1].shoppingList(wwRemainder)

	// Combine sesameMissing and wwMissing to get all missing ingredients for shopping list.
	allMissing := combineMissing(wwMissing,sesameMissing)

	// Print Results
	bakersSlice[0].printBreadInfo()
	fmt.Println("\n")
	bakersSlice[1].printBreadInfo()
	fmt.Println("\n")

	fmt.Println("Shopping List:")
	fmt.Println(allMissing)
	fmt.Println()

	fmt.Println("Baking Instructions:")
	bakersSlice[0].printBakeInstructions()
	bakersSlice[1].printBakeInstructions()
}

func combineMissing(missing_1 map[string]Item, missing_2 map[string]Item)(combined map[string]Item) {
	// Instantiate result to empty map.
	combined = make(map[string]Item)
	// Duplicate missing_1 into combined.
	for k,v := range missing_1 {
		combined[k] = v
	}

	// Next step is to go through the map missing_2 and add its values to combined.
	var added bool = false

	for m2_key, m2_value := range missing_2 {
		added = false

		for m1_key, m1_value := range missing_1 {
			if m2_key == m1_key {
				combined[m1_key] = Item{m1_value.weight + m2_value.weight}
				added = true
				break
			}
		}
		if added == false {
			// add a new pair to the map
			combined[m2_key] = Item{m2_value.weight}
		}
	}
	return
}