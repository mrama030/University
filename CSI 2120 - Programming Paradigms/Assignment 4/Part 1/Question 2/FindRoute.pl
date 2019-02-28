% Assignment 4 - Question 2 - Mohamed Ramadan 7688825

sortedPoolList(Spl) :- Spl=[["Glen Cairn",45.29552398823589,-75.88504321403646],["Corkstown",45.34609228122724,-75.82733278768433],["Entrance",45.32631894820216,-75.81675609520583],["Michèle",45.3548865821927,-75.8020190093133],["Britannia",45.36063791083469,-75.79935158132524],["Ruth Wildgen",45.35143574971178,-75.7957485439787],["Frank Ryan",45.35618157210449,-75.78913776510414],["Lisa",45.344203611634356,-75.78888493568607],["Parkway",45.35631278392867,-75.77593080375445],["Woodroffe",45.37607987330218,-75.77225704729584],["McKellar",45.383356299319395,-75.7663355603181],["Kingsmere",45.36492415895533,-75.7625479468355],["Bel Air",45.35750853073128,-75.76237762310991],["Agincourt",45.35959223124413,-75.75360944568821],["Westboro",45.38390614815524,-75.75301290567192],["Lions",45.39427770813794,-75.75232047849263],["Champlain",45.40431589991452,-75.74496450985441],["Iona",45.392425824249926,-75.74247203669871],["Raven",45.376538041017916,-75.74042790502267],["Bellevue Manor",45.37223315413918,-75.73886856878032],["Hampton",45.38742953063268,-75.73836344415304],["Crestview",45.344387632924054,-75.73795670904249],["Alexander",45.380330193754176,-75.73163858599659],["Parkdale",45.40138661908912,-75.73023035094172],["Meadowvale",45.37828145083384,-75.72477696260978],["Reid",45.39809949308152,-75.72389983475932],["General Burns",45.3517223372365,-75.72068192228832],["Chaudiere",45.40984992554796,-75.71353870063207],["Ev Tremblay",45.39934611083154,-75.71148292845268],["Rideauview",45.367907282835596,-75.70673708550083],["McNabb",45.40897618041744,-75.70274498043973],["Carleton Heights",45.35963576001747,-75.70254191613397],["Bingham",45.43364510779131,-75.69570714265845],["St. Luke's",45.41513265659813,-75.68696475924723],["Sylvia Holden",45.40257049489391,-75.68218644953257],["Jules Morin",45.433497486473115,-75.68154277234615],["Heron",45.37955540833377,-75.67726553077785],["Sandy Hill",45.421628374955425,-75.67679178631916],["Pauline Vanier",45.366710168887366,-75.676559014967],["Windsor",45.394532186176534,-75.67593721799336],["Strathcona",45.42814320884978,-75.67270686637411],["Brantwood",45.406132203975446,-75.67162178567759],["Optimiste",45.442237661390195,-75.66850786065743],["Dutchie's Hole",45.420784695340274,-75.66809864107668],["Alta Vista",45.383081724040146,-75.6663971454287],["Owl",45.35438810082107,-75.66479650124089],["Overbrook",45.42506341603979,-75.65712102762836],["Frank Licari",45.36886086041407,-75.65708630346525],["Kiwanis",45.43665037776025,-75.65314626399277],["Alvin Heights",45.45147956435529,-75.65100870365318],["St-Laurent",45.436351255364265,-75.64849014424264],["Pushman",45.35958959542747,-75.64825277394819],["St. Paul's",45.43004145660221,-75.64813126103986],["Cecil Morrison",45.417175891787146,-75.64599611564647],["Balena",45.40505998694386,-75.64341396386098],["Greenboro",45.363297932669155,-75.63644623282283],["Canterbury",45.389521642267944,-75.62883265479898],["Weston",45.39596271646451,-75.62613467769313],["Alda Burt",45.402733068354976,-75.62566700143215],["Elizabeth Manley",45.36999070895657,-75.61936964815708],["Hawthorne",45.39368089918365,-75.615926705023],["Bearbrook",45.43415859594989,-75.56367146417631]].

insertAtEnd(Value,[],[Value]). /* Base Case */ 
 
insertAtEnd(Value,[H|T],[H|NewTail]):- /* Normal Case */
	insertAtEnd(Value,T,NewTail).

calculateDistance(Lat1Deg,Lon1Deg,Lat2Deg,Lon2Deg,D) :-
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

naryTreeNode(Pool,ChildrenNodes,DistanceToParent,[Pool,ChildrenNodes,DistanceToParent]).
		
findRoute(NameDistanceList) :-
	sortedPoolList(Spl), /* Step 1. Get list of sorted pools. */
	createTree(Spl,CreatedTree),/* Step 2. Create a tree from the list of sorted pools. */
	preorder(CreatedTree,NameDistanceList). /* Step 3. Traverse the tree in pre-order to obtain the solution. */
	
createTree([RootPool|OtherPools],CreatedTree) :-
	naryTreeNode(RootPool,[],0,ChildlessRootNode), /* Create the tree's root node with the western most pool. */
	Spl=[RootPool|OtherPools], /* Regroup the sorted pools list. */
	buildTree(ChildlessRootNode,Spl,CreatedTree).

buildTree(RootNode,[RootPool|OtherPools],BuiltTree) :- /* Helper method to start at first pool after root. */
	SPL=[RootPool|OtherPools],
	buildTreeRec(OtherPools,SPL,RootNode,BuiltTree).
	
builTreeRec([],_,TreeSoFar,TreeSoFar). /* Base Case for building the tree. */

buildTreeRec([[Name,Lat,Lon|[]]|PoolsTail],SPL,TreeSoFar,FinalTree) :-
	ChildPool=[Name,Lat,Lon], /* Group attributes back to the pool. */ 
	findClosestParent(ChildPool,SPL,ClosestParentName,MinimumDistance), /* Calculate closest parent's name and distance (minimum) to that parent. */
	naryTreeNode(ChildPool,[],MinimumDistance,CreatedChildNode), /* Create the child node */
	addChild(ClosestParentName,CreatedChildNode,TreeSoFar,NewTreeSoFar), /* Add child to the parent node (using searchTree). */
	buildTreeRec(PoolsTail,SPL,NewTreeSoFar,FinalTree), !. /* Continue processing list of pools. */

minPool(CurrentName,CurrentDistance,_,PotentialDistance,CurrentName,CurrentDistance) :-
	CurrentDistance =< PotentialDistance, !.
	
minPool(_,CurrentDistance,PotentialName,PotentialDistance,PotentialName,PotentialDistance) :-
	CurrentDistance > PotentialDistance, !.	
	
findClosestParent(ChildPool,SPL,ClosestParentName,MinimumDistance) :- /* Helper method. */
	findClosestParentRec(ChildPool,SPL,"NOT DEFINED YET",99999999999999,ClosestParentName,MinimumDistance).

% Base Case	(last step), when you hit the same pool, do not calculate distances, return the values obtained previously.
findClosestParentRec([PoolName,Lat,Lon|[]],[[PoolName,Lat,Lon|[]]|_],ClosestParentNameSoFar,MinimumDistanceSoFar,ClosestParentNameSoFar,MinimumDistanceSoFar).

% Typical Case
findClosestParentRec([PoolName1,Lat1,Lon1|[]],[[PoolName2,Lat2,Lon2|[]]|PoolsTail],ClosestParentNameSoFar,MinimumDistanceSoFar,ClosestParentName,MinimumDistance) :-
	calculateDistance(Lat1,Lon1,Lat2,Lon2,PotentialMinDistance),
	minPool(ClosestParentNameSoFar,MinimumDistanceSoFar,PoolName2,PotentialMinDistance,NameResult,DistanceResult),
	ChildPool = [PoolName1,Lat1,Lon1],
	findClosestParentRec(ChildPool,PoolsTail,NameResult,DistanceResult,ClosestParentName,MinimumDistance), !.

addChild(ParentName,CreatedChildNode,TreeSoFar,NewTree) :- /* Helper method. */
	addChildRec(ParentName,CreatedChildNode,TreeSoFar,NewParentNode),
	replaceOldParent(NewParentNode,TreeSoFar,NewTree).
	
addChildRec(ParentName,[[C-Name,C-Lat,C-Lon|[]],_,C-DistanceToParent|[]],[[[ParentName,O-Lat,O-Lon|[]],O-Children,O-DistanceToParent|[]]|RemainingNodes],NewParentNode) :-	
	ChildNode = [[C-Name,C-Lat,C-Lon],[],C-DistanceToParent],
	insertAtEnd(ChildNode,O-Children,NewChildList),
	Node = [[ParentName,O-Lat,O-Lon],NewChildList,C-DistanceToParent],
	NewParentNode is Node, !.

addChildRec(ParentName,ChildNodeToAdd,[[[NotParentName,_,_|[]],O-Children,_|[]]|RemainingNodes],NewParentNode) :-	
	addChildRec(ParentName,ChildNodeToAdd,O-Children,NewParentNode),
	addChildRec(ParentName,ChildNodeToAdd,RemainingNodes,NewParentNode), !.

/* Helper method. Adds support for a list of previously processed nodes. */
replaceOldParent(NewParentNode,TreeSoFar,NewTree) :- replaceOldParent(NewParentNode,TreeSoFar,[],NewTree).	
	
/* Base case. */	
replaceOldParent([[ParentName,O-Lat,O-Lon|[]],NewChildList,C-DistanceToParent|[]],[[[ParentName,O-Lat,O-Lon|[]],_,_|[]]|RemainingTree],PreviousNodes,NewTree) :-
	NewParentNode=[[ParentName,O-Lat,O-Lon],NewChildList,C-DistanceToParent],
	insertAtEnd(NewParentNode,PreviousNodes,Step1),
	append(Step1,RemainingTree,NewTree).

/* Normal case. */	
replaceOldParent([[ParentName,P-Lat,P-Lon|[]],NewChildList,P-DistanceToParent|[]],[[[NotParentName,O-Lat,O-Lon|[]],ChildrenNodes,DistanceToParent|[]]|RemainingTree],PreviousNodes,NewTree) :-
	NewParentNode=[[ParentName,P-Lat,P-Lon],NewChildList,P-DistanceToParent],
	Node=[[NotParentName,O-Lat,O-Lon],ChildrenNodes,DistanceToParent],
	insertAtEnd(Node,PreviousNodes,Temp),
	replaceOldParent(NewParentNode,RemainingTree,Temp,NewTree).
	
% Step 3. Preorder traversal to find list of pool names and distances. (Tested working.)

% ?- preorder([[[poolB,5,5],[[[poolD,5,5],[[[poolA,5,5],[],2800]],2800],[[poolE,5,5],[],2800]],2800]],R).	
	
preorder(Tree,Solution) :- preorderRec(Tree,[],Solution). /* Helper method. */

preorderRec([],ListSoFar,ListSoFar). /* Base case. */

/* Normal case */	
preorderRec([[[Name,_,_|[]],ChildrenNodes,DistanceToParent|[]]|RemainingTree],ListSoFar,Solution) :-
	SolutionStep=[Name,DistanceToParent],
	insertAtEnd(SolutionStep,ListSoFar,R1),
	preorderRec(ChildrenNodes,R1,A1),
	preorderRec(RemainingTree,A1,Solution), !.
		
% Step 4. Save Route predicate to write solution to a file. (Tested working.)

% ?- preorder([[[poolB,5,5],[[[poolD,5,5],[[[poolA,5,5],[],2800]],2800],[[poolE,5,5],[],2800]],2800]],R), saveRoute(R,"solution.txt").

saveRoute([],_) :- fail.

saveRoute(SolutionList, Filename) :-
	open(Filename, write, Stream),
	recWrite(SolutionList, Stream, 0),
	close(Stream).
	
recWrite([],_) :- !.

recWrite([[Name,Distance|[]]|Tail],Stream, TotalDistance) :-
	write(Stream,Name),
	write(Stream," "),
	Temp is (Distance+TotalDistance),
	write(Stream,Temp),
	nl(Stream),
	recWrite(Tail,Stream,Temp).