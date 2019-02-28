%How to add 2 lists together...

sumTwo(A,B,Result) :- sumTwo(A,B,0,Result).

sumTwo([],[],Result,Result).

sumTwo([AH|AT],[BH|BT],SoFar,Result) :- 
	Temp is (AH+BH),
	SoFar2 is (Temp+SoFar),
	sumTwo(AT,BT,SoFar2,Result).
	
%sumTwo([5,5,5],[5,5,5],X).
%absDiff([5,5,5],[3,-2,-9],X).

%Question 4 of Assignment 1

absDiff(A,B,Result) :- absDiff(A,B,[],Result). %Helper

absDiff([],[],Result,Result). %Boundary case

absDiff([AH|AT],[BH|BT],SoFar,Result) :-
	%https://en.wikipedia.org/wiki/Absolute_difference
	Temp is (abs(AH-BH)),
	SoFar2 = [Temp|SoFar],
	absDiff(AT,BT,SoFar2,Result).












