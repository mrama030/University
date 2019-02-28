; Mohamed Ali Ramadan 7688825
; A2 - Q3

#lang racket

; Predicates required for question 3.

; 1. Built in predicate: member

; > (member 2 (list 1 2 3 4))
; '(2 3 4)
; > (member 9 (list 1 2 3 4))
; #f

; Locates the first element of lst that is equal? to v. 
; If such an element exists, the tail of lst starting with that element is returned. 
; Otherwise, the result is #f.

; 2. Custom predicate: countRec

; L: List to search.
; E: Element that we want to know how many times appears in L.
; Returns the number of time E appears in list L. (Tested working.)
(define countRec
	(lambda (L E)
		(if (null? L)
			0 ; return 0 and end recursion
			(if (eqv? (car L) E)
				(+ 1 (countRec (cdr L) E)) ; return 1 and continue recursion
				(countRec (cdr L) E) ; continue recursion
			)
		)
	)
)

; Question 3 A) Evaluates to a list of pairs.

; Tests:
; (duplicatePair '(1 a 5 6 2 b a 5 5)) - Pass
; (duplicatePair '(a b a)) - Pass

(define (duplicatePair InputList)
	(define duplicatePairRec
		; L1: List to process.
		; L2: List of already processed (seen) elements.
		; L3: Original list untouched, used for element counting.
		(lambda (L1 L2 L3)
			(if (null? L1)
				'() ; Base Case: Return null instead of a pair.
				(if (eqv? #f (member (car L1) L2)) ; has not been precessed/seen before?
					(append (list (cons (car L1) (countRec L3 (car L1)))) (duplicatePairRec (cdr L1) (cons (car L1) L2) L3))
					(duplicatePairRec (cdr L1) L2 L3) ; has been processed/seen before, just continue recursion
				)
			)
		)
	)
	(if	(null? InputList) 
		'() ; true, return null
		(duplicatePairRec InputList '() InputList) ; false, process list
	)
)

; Question 3 B) Evaluates to a list of lists.

; Tests:
; (duplicateList '(1 a 5 6 2 b a 5 5)) - Pass
; (duplicateList '(a b a)) - Pass

(define (duplicateList InputList)
	(define duplicateListRec
		; L1: List to process.
		; L2: List of already processed (seen) elements.
		; L3: Original list untouched, used for element counting.
		(lambda (L1 L2 L3)
			(if (null? L1)
				'() ; Base Case: Return null instead of a list of two elements.
				(if (eqv? #f (member (car L1) L2)) ; has not been precessed/seen before?
					(append (list (list (car L1) (countRec L3 (car L1)))) (duplicateListRec (cdr L1) (cons (car L1) L2) L3))
					(duplicateListRec (cdr L1) L2 L3) ; has been processed/seen before, just continue recursion
				)
			)
		)
	)
	(if	(null? InputList) 
		'() ; true, return null
		(duplicateListRec InputList '() InputList) ; false, process list
	)
)

; Question 3 C) Evaluates to a sorted by decreasing order list of lists.

; Tests:
; (duplicateListSorted '(1 a 5 6 2 b a 5 5)) - Pass
; (duplicateListSorted '(b a b a a)) - Pass

(define (duplicateListSorted InputList)
	(define duplicateListRec
		; L1: List to process.
		; L2: List of already processed (seen) elements.
		; L3: Original list untouched, used for element counting.
		(lambda (L1 L2 L3)
			(if (null? L1)
				'() ; Base Case: Return null instead of a list of two elements.
				(if (eqv? #f (member (car L1) L2)) ; has not been precessed/seen before?
					(append (list (list (car L1) (countRec L3 (car L1)))) (duplicateListRec (cdr L1) (cons (car L1) L2) L3))
					(duplicateListRec (cdr L1) L2 L3) ; has been processed/seen before, just continue recursion
				)
			)
		)
	)
	(define sortByDecreasingCountRec
		(lambda (List)
			; Internal lists always have two elements, so compare their second elements.
			(sort List (lambda (x y) (> (cadr x) (cadr y))))
		)
	)
	(if	(null? InputList) 
		'() ; true, return null
		(sortByDecreasingCountRec (duplicateListRec InputList '() InputList)) ; false, process and sort results list of lists
	)
)								