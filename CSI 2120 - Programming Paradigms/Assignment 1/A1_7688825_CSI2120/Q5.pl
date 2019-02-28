flower(rose,red).
flower(marigold,yellow).
flower(tulip,red).
flower(daffodil,yellow).
flower(rose,yellow).
flower(maigold,red).
flower(rose,white).
flower(cornflower,purple).


bouquet(L) :- setof(([F1,C1],[F2,C2],[F3,C3]),(flower(F1,C1),flower(F2,C2),flower(F3,C3),F1\==F2,F1\==F3,F2\==F3,C1==red, C2==red),L), !.

bouquet(L) :- setof(([F1,C1],[F2,C2],[F3,C3]),(flower(F1,C1),flower(F2,C2),flower(F3,C3),F1\==F2,F1\==F3,F2\==F3,C1\==C2,C1\==C3,C2\==C3),L).
