%absDiffA([10,10,10],[-8,2,-4],X).
%absDiffA([10,10,10,10],[-8,2,-4],X).
%absDiffA([10,10,10],[-8,2,-4,6],X).

absDiffA(A,B,Result) :- absDiffA(A,B,[],Result). %Helper

absDiffA([],[],Result,Reverse) :- mirrorAcc(Result,Reverse),!. %Boundary case

absDiffA([AH|AT],[BH|BT],SoFar,Result) :-
	Temp is (abs(AH-BH)),
	SoFar2 = [Temp|SoFar],
	absDiffA(AT,BT,SoFar2,Result).

absDiffA([AH|AT],[],SoFar,Result) :-
	Temp is (abs(AH)),
	SoFar2 = [Temp|SoFar],
	absDiffA(AT,[],SoFar2,Result).

absDiffA([],[BH|BT],SoFar,Result) :-
	Temp is (abs(BH)),
	SoFar2 = [Temp|SoFar],
	absDiffA([],BT,SoFar2,Result).

%For reversing our calculated result.	
reverseList([],L,L) :- !.
reverseList([H|T],L,R) :- reverseList(T,[H|L],R).
mirrorAcc(L,R) :- reverseList(L,[],R).