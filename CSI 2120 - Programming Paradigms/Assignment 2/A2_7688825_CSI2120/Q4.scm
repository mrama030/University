; Mohamed Ali Ramadan 7688825
; A2 - Q4

#lang racket

; Observations:
; 1. We are dealing with n-ary trees.
; 2. If the list representing the n-ary tree was flattened (no parentheses other than initial open and close)
;    then the result corresponds to the preorder traversal of the tree.
; 3. The first step would be to search for the correct node using the key provided.
; 4. The second step would be to extract the direct childrens' node values.
; 5. The list of extracted values of the direct children should be sorted in decreasing order.

(define test 
	'(10
		(2 (4 (9 (3))
				(12 (1 (2)))
				(16)))
		(5 (7)
			(21))
		(6))
)

(define test2 
	'(1
		(2 (6) (7) (8))
		(3)
		(4 (9 (12)))
		(5 (10) (11)))
)

; Test: (children 5 test) - PASSED
; Expected Result: '(21 7)
; Other random tests pass as well.

; Test for search function - PASSED
; (preorderSearch 2 test2)
; Expected Result: '(6 7 8)

; Test for getDirectChildren
; (getDirectChildren '(5 (6 (7 8 9)) (9 8) (4 (7)) 8))
; Expected Result: '(5 6 9 4 8) - Pass

(define (children Key Tree)
	; Searches for the parent node and returns its children nodes. [Step 1 - Tested Working]
	(define preorderSearch
		(lambda (K L)
			(if (null? L)
				'() ; Return null.
				(cond ; Element is not null.
					((number? (car L)) ; Element is a number.
						(if (eqv? K (car L)) ; Did we hit the key?
							(cdr L) ; Return the children nodes.
							(preorderSearch K (cdr L)) ; Return the result found by continuing the search.
						)
					)
					((list? (car L)) ; Element is a list.
						(if (eqv? K (caar L)) ; Did we hit the key?
							(cdar L) ; Return the children nodes.
							(append (preorderSearch K (cdar L)) (preorderSearch K (cdr L)))
						)	
					)
				)
			)
		)
	)
	; Extracts only the direct children's values and returns them in an unsorted list. [Step 2 - Tested Working]
	(define getDirectChildren
		(lambda (L)
			(if (null? L)
				'() ; Return null.
				(cond ; Element is not null.
					((number? (car L)) (append (list (car L)) (getDirectChildren (cdr L))))
					((list? (car L)) (append (list (caar L)) (getDirectChildren (cdr L))))
				) 
			)
		)
	)
	; Predicate used to sort a list from biggest to smallest values. [Step 3 - Tested Working]
	(define (sortDescending List) (sort List >))
	; Expression to evaluate.
	(if (null? Tree)
		'("Error: Empty Tree Provided")
		(sortDescending (getDirectChildren (preorderSearch Key Tree)))
	)
) 


; Please ignore below.	
	
; Test for getAll - PASSED !!!
; (getAll '(5 (6 (7 8 9)) (9 8) (4 (7)) 8))
; (getAll '(1 (2 (6) (7) (8)) (3) (4 (9 (12))) (5 (10) (11)))) - PASSED !!!

;(define getAll ; [Tested Working, preorderSearch should be near identical in concept.]
;	(lambda (L)
;		(if (null? L)
;			'() ; Return null.
;			(cond ; Element is not null.
;				((number? (car L)) (append (list (car L)) (getAll (cdr L))))
;				((list? (car L)) (append (list (caar L)) (getAll (cdar L)) (getAll (cdr L))))
;			) 
;		)
;	)
;)