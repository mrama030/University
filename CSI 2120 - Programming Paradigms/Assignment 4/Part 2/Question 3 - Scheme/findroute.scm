; Mohamed Ali Ramadan 7688825 (A4 - Q3 Scheme)

#lang racket

;
; [TESTED PASS]
; User Function #1: Save Route function called by user.
; Test : (saveRoute '(("A A" 5.3333333333) ("B" 2.555555555) ("C" 4.44444444444)) "C:/Users/MohamedRamadan/Desktop/SchemeSolution.txt")
(define (saveRoute SolutionToPrint OutputFileName)
	; Responsible for writing the solution list to the file recursively.
	(define (writeToFileRec SolutionToPrint OutputPort PreviousDistance)
		(if (null? SolutionToPrint)
			#t ; End recursion when nothing id left to print.
			(begin
				(display (format "~a " (caar SolutionToPrint)) OutputPort)
				(display (real->decimal-string (+ PreviousDistance (cadar SolutionToPrint)) 3) OutputPort)
				(newline OutputPort)
				(writeToFileRec (cdr SolutionToPrint) OutputPort (+ PreviousDistance (cadar SolutionToPrint)))
			)
		)
	)
	; Expression to evaluate to.
	(let 
		((OutputPort (open-output-file OutputFileName))) ; Create output port.
		(begin
			(writeToFileRec SolutionToPrint OutputPort 0.0) ; Write all elements in solution list.
			(close-output-port OutputPort) ; Close output port.
			#t
		)
	)
)
;
; User Function #2: Find Route function called by user.
(define (findRoute InputFile)
	;
	; [TESTED PASS]
	; Calculation Function #1: Calculates the distance between two pools. 
	; Test: (distanceGPS 45.421016 -75.690018 45.4222 -75.6824) 
	(define (distanceGPS Lat1Deg Lon1Deg Lat2Deg Lon2Deg)
		; Define functions to be used by distanceGPS\4. 
		(define (calculateA Lat1Rad Lat2Rad) (expt (sin (/ (- Lat1Rad Lat2Rad) 2)) 2))
		(define (calculateB Lat1Rad Lat2Rad) (* (cos Lat1Rad) (cos Lat2Rad)))
		(define (calculateC Lon1Rad Lon2Rad) (expt (sin (/ (- Lon1Rad Lon2Rad) 2)) 2))
		(define (calculateABC Lat1Rad Lon1Rad Lat2Rad Lon2Rad) (+ (calculateA Lat1Rad Lat2Rad) (* (calculateB Lat1Rad Lat2Rad) (calculateC Lon1Rad Lon2Rad))))
		(define (calculateDRad Lat1Rad Lon1Rad Lat2Rad Lon2Rad) (* 2 (asin (sqrt (calculateABC Lat1Rad Lon1Rad Lat2Rad Lon2Rad)))))
		(define (distanceGPSRad Lat1Rad Lon1Rad Lat2Rad Lon2Rad) (* (calculateDRad Lat1Rad Lon1Rad Lat2Rad Lon2Rad) 6371))
		(define (toRad Deg) (* pi (/ Deg 180))) ; Deg to Rad function.
		; Expression to evaluate to.
		(distanceGPSRad (toRad Lat1Deg) (toRad Lon1Deg) (toRad Lat2Deg) (toRad Lon2Deg))
	)
	;
	; [TESTED PASS]
	; Calculation Function #2: Finds a child's closest parent name and distance, returns a list of two elements. 
	; Test: (findParent '("Bel Air" 45.35750853073128 -75.76237762310991) (getSortedPoolsList "C:/Users/MohamedRamadan/Desktop/ParsedPools.txt"))
	(define (findParent ChildPool SortedPoolsList)
		; Calculates the closest parent's name and distance for a child recursively.
		(define (findParentRec ChildPool SortedPoolsList ParentNameSoFar DistanceToParentSoFar)
			(if (equal? (car ChildPool) (caar SortedPoolsList)) ; We reach the child / processing is done.
				; Return the minimum distance parent information in a list.
				(list ParentNameSoFar DistanceToParentSoFar) 
				; Processing is not complete yet, continue.
				(let ((distance (distanceGPS (cadr ChildPool) (caddr ChildPool) (cadr (car SortedPoolsList)) (caddr (car SortedPoolsList)))))
					(if (> DistanceToParentSoFar distance)
						; A new minimum (closer parent) WAS found.
						(findParentRec ChildPool (cdr SortedPoolsList) (caar SortedPoolsList) distance)
						; A new minimum (closer parent) was NOT found.
						(findParentRec ChildPool (cdr SortedPoolsList) ParentNameSoFar DistanceToParentSoFar)
					)
				)
			)
		)
		; Expression to evaluate to. Sets initial closest parent as root pool.
		(findParentRec 
			ChildPool
			SortedPoolsList 
			(caar SortedPoolsList) ; Root Node Pool's Name 
			(distanceGPS 
				(cadr ChildPool) ; Latitude of Child Pool 
				(caddr ChildPool) ; Longitude of Child Pool
				(cadr (car SortedPoolsList)) ; Latitude of Root Pool
				(caddr (car SortedPoolsList)) ; Longitude of Root Pool
			)
		)
	)
	;
	; [TESTED PASS]
	; Step 1. Get a list of sorted pools from a file.
	; Test: (getSortedPoolsList "C:/Users/MohamedRamadan/Desktop/ParsedPools.txt")
	(define (getSortedPoolsList InputFile)
		; Generates a list of strings containing all the lines from a file.
		(define (getFileLines FileName)
			(file->lines FileName)
		)
		; Converts a string containing a number into a number.
		(define (toNumber StrIn)
			(string->number StrIn)
		)
		; Creates a list of pools from the lines of the sorted pools string list. 
		(define (getSortedPoolsListRec ListOfLines)
			(if (null? ListOfLines)
				'()
				(append 
					(list (list (car ListOfLines) (toNumber (cadr ListOfLines)) (toNumber (caddr ListOfLines)))) 
					(getSortedPoolsListRec (cdddr ListOfLines))
				)
			)
		)
		; Expression to evaluate to.
		(getSortedPoolsListRec (getFileLines InputFile))
	)
	;
	; [TESTED PASS]
	; Step 2. Build a tree from the SortedPoolsList.
	; Test: (createTree (getSortedPoolsList "C:/Users/MohamedRamadan/Desktop/ParsedPools.txt"))
	(define (createTree SortedPoolsList)
		;
		; Creates a tree with only the root node.
		(define (createTreeWithRootNode SortedPoolsList) ; TESTED PASS
			(list ; A list representing the tree
				(list ; A list representing a node
					(list (caar SortedPoolsList) 0.0) ; Node Value = List of 2 elements: Pool Name and Distance To Parent.
					'() ; List of Children Nodes
				)
			)
		)
		;
		; Builds the remaining tree recursively.
		(define (createRemainingTreeRec PoolsToProcess TreeSoFar SortedPoolsList)
			(if (null? PoolsToProcess)
				TreeSoFar ; Return the tree that was built.
				(let ((parentInfo (findParent (car PoolsToProcess) SortedPoolsList))) ; Else Process and continue.
					(createRemainingTreeRec
						(cdr PoolsToProcess) ; Parameter 1: Remaining pools to process.
						(addChildRec ; Parameter 2: The new tree created with the child node inserted at parent node.
							TreeSoFar ; The tree to add the child node to.
							(car parentInfo) ; Parent Node's Pool Name
							(list ; Child Node To Add
								(list ; Node Value = List of 2 elements (child name, distance to parent)
									(caar PoolsToProcess) ; Child Node's Pool Name
									(cadr parentInfo) ; Distance between closest parent node and child node.
								)
								'() ; Child node created without children node of its own.
							)
						)
						SortedPoolsList ; Parameter 3: Does not change.
					)
				)
			)
		)
		;
		; Returns a new tree with the child node added to the parent node.
		; Test 1 [PASS]: (addChildRec '((("a" 5.3) ()) (("b" 7.2) ()) (("c" 0.8) ())) "b" '(("test" 0.5) ()))
		(define (addChildRec TreeToProcess ParentKey ChildNodeToAdd)
			(if (null? TreeToProcess)
				'() ; Return null.
				(if (equal? (caaar TreeToProcess) ParentKey) ; Compare PoolName to ParentKey.
					; We are at the parent node, key was found.
					(if (null? (cadar TreeToProcess)) ; Current Node's Child List is Null ?
						(append ; No children yet.
							(list (list (caar TreeToProcess) (list ChildNodeToAdd))) ; TESTED
							(addChildRec (cdr TreeToProcess) ParentKey ChildNodeToAdd) ; siblings
						)
						(append ; Parent node already has children.
							(list 
								(list 
									(caar TreeToProcess)
									(append 
										(addChildRec (cadar TreeToProcess) ParentKey ChildNodeToAdd) ; Existing children and their children.
										(list ChildNodeToAdd) ; New child node.
									)
								)
							)
							(addChildRec (cdr TreeToProcess) ParentKey ChildNodeToAdd) ; siblings
						)
					)
					; We are not at the parent node.
					(if (null? (cadar TreeToProcess)) ; Current Node's Child List is Null ?
						(append ; No children , just recurse on siblings.
							(list (car TreeToProcess)) ; current node
							(addChildRec (cdr TreeToProcess) ParentKey ChildNodeToAdd) ; siblings
						)
						(append ; Recurse on siblings and children.
							(list ; Eliminated by append.
								(list ; Recreate the list.
									(caar TreeToProcess) ; ParentNodeValue
									(addChildRec (cadar TreeToProcess) ParentKey ChildNodeToAdd) ; Combined to children nodes.
								)
							)
							(addChildRec (cdr TreeToProcess) ParentKey ChildNodeToAdd) ; siblings
						)
					)
				)
			)
		)
		; 
		; Expression to evaluate to.
		(createRemainingTreeRec 
			(cdr SortedPoolsList) ; All pools except for the first one.
			(createTreeWithRootNode SortedPoolsList) ; Create TreeSoFar as a tree with a root node created from the western most pool.
			SortedPoolsList ; Required for calling findParent.
		)
	)
	;
	; [UNTESTED]
	; Step 3. From thee built tree, obtain a list of solution steps and return this as the solution.
	; Test: Too long to include. Use result from Step 2 test.
	(define (traverseTreeForSolution TreeToProcess)
		(if (null? TreeToProcess) 
			'() ; Return null.
			(if (null? (cadar TreeToProcess)) ; No children ?
				(append
					(list (caar TreeToProcess)) ; current solution step
					(traverseTreeForSolution (cdr TreeToProcess)) ; siblings
				)
				(append
					(list (caar TreeToProcess)) ; current solution step
					(traverseTreeForSolution (cadar TreeToProcess)) ; children
					(traverseTreeForSolution (cdr TreeToProcess)) ; siblings
				)
			)
		)
	)
	;
	; findRoute : Expression to evaluate to.
	(traverseTreeForSolution (createTree (getSortedPoolsList InputFile)))
)
; [Global TEST PASS]
; Global Test:
; (saveRoute (findRoute "C:/Users/MohamedRamadan/Desktop/ParsedPools.txt") "C:/Users/MohamedRamadan/Desktop/SchemeSolution.txt")