city(ottawa,ontario).
city(toronto,ontario).
city(kingston,ontario).
city(gatineau,quebec).
city(montreal,quebec).

company(shopify,ottawa).
company(rossvideo,ottawa).
company(dium,gatineau).
company(uber,toronto).
company(deepmind,montreal).
company(google,toronto).

person(annie,gatineau).
person(paul,gatineau).
person(suzy,gatineau).
person(robert,gatineau).
person(tom,ottawa).
person(tim,kingston).
person(joe,montreal).
person(jane,ottawa).
person(marie,ottawa).
person(jack,toronto).
person(simon,toronto).

employee(annie,dium).
employee(tom,shopify).
employee(jane,shopify).
employee(marie,shopify).
employee(joe,deepmind).
employee(jack,google).
employee(simon,google).
employee(suzy,shopify).
employee(paul,rossvideo).
employee(marie,rossvideo).
employee(simon,uber).

busy(X):- employee(X,C1),employee(X,C2),compare(<, C1, C2).
busy(X):- employee(X,C),company(C,toronto).