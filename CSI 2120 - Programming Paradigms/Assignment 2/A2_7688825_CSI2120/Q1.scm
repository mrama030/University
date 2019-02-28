; Mohamed Ali Ramadan 7688825
; A2 - Q1

#lang racket

(define (calculateA Lat1Rad Lat2Rad) (expt (sin (/ (- Lat1Rad Lat2Rad) 2)) 2))

(define (calculateB Lat1Rad Lat2Rad) (* (cos Lat1Rad) (cos Lat2Rad)))

(define (calculateC Lon1Rad Lon2Rad) (expt (sin (/ (- Lon1Rad Lon2Rad) 2)) 2))

(define (calculateABC Lat1Rad Lon1Rad Lat2Rad Lon2Rad) (+ (calculateA Lat1Rad Lat2Rad) (* (calculateB Lat1Rad Lat2Rad) (calculateC Lon1Rad Lon2Rad))))

(define (calculateDRad Lat1Rad Lon1Rad Lat2Rad Lon2Rad) (* 2 (asin (sqrt (calculateABC Lat1Rad Lon1Rad Lat2Rad Lon2Rad)))))

(define (distanceGPSRad Lat1Rad Lon1Rad Lat2Rad Lon2Rad) (* (calculateDRad Lat1Rad Lon1Rad Lat2Rad Lon2Rad) 6371))

(define (toRad Deg) (* pi (/ Deg 180))) ; Deg to Rad function.

; Called by user. Converts degree inputs to radians and calls distanceGPSRad.
(define (distanceGPS Lat1Deg Lon1Deg Lat2Deg Lon2Deg) (distanceGPSRad (toRad Lat1Deg) (toRad Lon1Deg) (toRad Lat2Deg) (toRad Lon2Deg)))
	
; (distanceGPS 45.421016 -75.690018 45.4222 -75.6824)