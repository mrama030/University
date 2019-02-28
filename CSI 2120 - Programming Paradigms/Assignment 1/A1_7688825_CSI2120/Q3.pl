
distance(Lat1Deg,Lon1Deg,Lat2Deg,Lon2Deg,D) :-
	Lat1Rad is (pi*(Lat1Deg/180)),
	Lon1Rad is (pi*(Lon1Deg/180)),
	Lat2Rad is (pi*(Lat2Deg/180)),
	Lon2Rad is (pi*(Lon2Deg/180)),
	A is ((sin((Lat1Rad-Lat2Rad)/2))**2),
	C is ((cos(Lat1Rad))*(cos(Lat2Rad))),
	Dx is ((sin((Lon1Rad-Lon2Rad)/2))**2),
	B is (C*Dx),
	DRad is (2*asin(sqrt(A+B))),
	D is (DRad*6371).
	
	
	
	