; Mohamed Ali Ramadan 7688825
; A2 - Q2

#lang racket

; Q2 a) Length of the longest list.
(define 
	(absDiffA L1 L2) 
	(cond 
		; Both L1 and L2 are empty, return empty list.
		((and (null? L1) (null? L2)) '())
		; L1 not empty, L2 is empty.
		((and (not (null? L1)) (null? L2)) (cons (abs (car L1)) (absDiffA (cdr L1) '())))
		; L1 is empty, L2 not empty.
		((and (null? L1) (not (null? L2))) (cons (abs (car L2)) (absDiffA '() (cdr L2))))
		; L1 and L2 are non-empty.
		(#t (cons (abs (- (car L1) (car L2))) (absDiffA (cdr L1) (cdr L2)))) 
	) 
)

; Tests
; (absDiffA '() '())
; (absDiffA '(-3 -5 6) '())
; (absDiffA '() '(-3 -7 -8))
; (absDiffA '(-1 -3 -70 -5) '(2 -4 16))

; Q2 b) Length of the shortest list.
(define 
	(absDiffB L1 L2) 
	(cond 
		; Both L1 and L2 are empty, return empty list.
		((and (null? L1) (null? L2)) '())
		; L1 not empty, L2 is empty, ignore extra values.
		((and (not (null? L1)) (null? L2)) '())
		; L1 is empty, L2 not empty, ignore extra values.
		((and (null? L1) (not (null? L2))) '())
		; L1 and L2 are non-empty.
		(#t (cons (abs (- (car L1) (car L2))) (absDiffB (cdr L1) (cdr L2)))) 
	) 
)

; Tests
; (absDiffB '() '())
; (absDiffB '(-3 -5 6) '())
; (absDiffB '() '(-3 -7 -8))
; (absDiffB '(-1 -3 -70 -5) '(2 -4 16))
	


; My personal testing stuff, please ignore below.
; (define (test L1 L2) (cond ((null? L1) L2) ((null? L2) L1) (#t "Both are not null")))
; (test '(5 5 5) '())
