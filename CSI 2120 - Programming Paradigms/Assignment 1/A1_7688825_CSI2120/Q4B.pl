%absDiffB([10,10,10],[-8,2,-4],X).
%absDiffB([10,10,10,10],[-8,2,-4],X).
%absDiffB([10,10,10],[-8,2,-4,6],X).

absDiffB(A,B,Result) :- absDiffB(A,B,[],Result). %Helper

absDiffB([],[],Result,Reverse) :- mirrorAcc(Result,Reverse),!. %Boundary case

absDiffB([AH|AT],[BH|BT],SoFar,Result) :-
	Temp is (abs(AH-BH)),
	SoFar2 = [Temp|SoFar],
	absDiffB(AT,BT,SoFar2,Result).

absDiffB([AH|AT],[],SoFar,Result) :-
	absDiffB([],[],SoFar,Result), !.

absDiffB([],[BH|BT],SoFar,Result) :-
	absDiffB([],[],SoFar,Result), !.

%For reversing our calculated result.	
reverseList([],L,L) :- !.
reverseList([H|T],L,R) :- reverseList(T,[H|L],R).
mirrorAcc(L,R) :- reverseList(L,[],R).