#include "Reducer.h"
#include <iostream>
#include <vector>
#include <queue>          // std::queue
#include <utility>      // std::pair, std::make_pair
using namespace std;

bool revise(ConnectionMap &m, int x1, int x2){
	bool revised = false;
	vector<unsigned int> x1sPossibleColors = m.getPossibleColors(x1);
	vector<unsigned int> x2sPossibleColors = m.getPossibleColors(x2);
	if (x2sPossibleColors.size() == 1){
		for(int i = 0; i < x1sPossibleColors.size(); i++){
			if (x1sPossibleColors[i] == x2sPossibleColors.front()){
				//Then that neighbor has a color locked in and x1 has that color in his domain
				//remove that color from x1s vector of possible colors
				m.removeColorFrom(x1, x2sPossibleColors.front());
				revised = true;

				//if x1 now only has only possible color left, lock it in.
				x1sPossibleColors =  m.getPossibleColors(x1);
				if(x1sPossibleColors.size() == 1){
					m.setColor(x1, x1sPossibleColors.front());
				}
			}
		}
	}
	return revised;
}

bool ac3(ConnectionMap &m){

	//need to make our queue of all arcs in csp
	queue< pair <int,int> > arcs;   

	for (int currentIndex = 0; currentIndex < m.getSize(); currentIndex++){
		//Find out who all of currentIndex's neighbors are and add them to neighbors vector
		for (int i = 0; i < m.getSize(); i++){
			//don't add yourself as a neightbor
			if(i != currentIndex){
				if (m.getXY(currentIndex, i)){
					//then i is a neighbor of currentIndex. add him to neighbors
					std::pair <int,int> neighborPair; 

					neighborPair.first = currentIndex;
					neighborPair.second = i;

					arcs.push(neighborPair);

					/*neighborPair.first = i;
					neighborPair.second = currentIndex;

					arcs.push(neighborPair);*/
				}
			}
		}
	}

	while (!arcs.empty()){
		std::pair <int,int> neighborPair = arcs.front();
		arcs.pop();

		if (revise(m, neighborPair.first, neighborPair.second)){
			if (m.getPossibleColors(neighborPair.first).size() == 0){
				//then our current setup does not provide a solution.
				//this is where we would begin backtracking
				return false;
			}else{
				//add all of x1s neighbors to the queue

				//Find out who all of x1's neighbors are
				for (int i = 0; i < m.getSize(); i++){
					//don't add yourself as a neightbor
					if(i != neighborPair.first){
						if (m.getXY(neighborPair.first, i)){
							//then i is a neighbor of x1. add him to neighbors

							std::pair <int,int> x1sNeighbor; 
							x1sNeighbor.first = i;
							x1sNeighbor.second = neighborPair.first;

							arcs.push(x1sNeighbor);
						}
					}
				}
			}
		}
	}

	//make our next guess
	//go through all of the indicies and find the first one that doesn't have a color set yet
	for (int i = 0; i < m.getSize(); i++){
		vector<unsigned int> possibleColors = m.getPossibleColors(i);
		if (possibleColors.size() > 1){
			ConnectionMap modifiedConnectionMap = m;
			modifiedConnectionMap.setColor(i, possibleColors.front());

			//then that color we picked ended up not providing a complete solution
			//go back and try and different color
			if (ac3(modifiedConnectionMap) == false){
				m.removeColorFrom(i, possibleColors.front());
				possibleColors = m.getPossibleColors(i);
				if (possibleColors.size() > 1){
					m.setColor(i, possibleColors.front());
					ac3(m);
				}
			}else{
				//We found a solution
				return true;
			}
			break;
			/*for (int j = 0; j < possibleColors.size(); j++){
				ConnectionMap modifiedConnectionMap = m;
				modifiedConnectionMap.setColor(j, possibleColors[i]);
				ac3(modifiedConnectionMap);
			}
			break;*/


		}
	}

	//Check to see if all of the indicies have a color locked in.
	//If so, then we have found a solution
	/*for(int i = 0; i < m.getSize(); i++){
		if (m.getPossibleColors(i).size() != 1){
			return false;
		}
	}*/
	return true;
	
}

// Takes a connection map and an index to which it should assign a value.
// Returns true if a COMPLETE solution was found and false otherwise.
// I assume backtrack() is recursive, but you can create whatever functions you want
// However, this is the ONLY file you should modify.
bool backtrack(ConnectionMap &m, int assign)
{

	////Make a copy of our connection map that will be modified
	//ConnectionMap modifiedConnectionMap = m;

	////vector that holds assign's neighbors
	//vector<int> neighbors;

	////Find out who all of assign's neighbors are and add them to neighbors vector
	//for (int i = 0; i < modifiedConnectionMap.getSize(); i++){
	//	//don't add yourself as a neightbor
	//	if(i != assign){
	//		if (modifiedConnectionMap.getXY(assign, i)){
	//			//then i is a neighbor of assign. add him to neighbors
	//			neighbors.push_back(i);
	//		}
	//	}
	//}

	////now we know all of the neighbors of assign
	////remove all of the neighbor's current colors from assign's list of possible colors
	//for (int i = 0; i < neighbors.size(); i++){
	//	vector<unsigned int> neighborsPossibleColors = modifiedConnectionMap.getPossibleColors(neighbors[i]);
	//	if (neighborsPossibleColors.size() == 1){
	//		//Then that neighbor has a color locked in
	//		//remove that color from assign's vector of possible colors
	//		modifiedConnectionMap.removeColorFrom(assign, neighborsPossibleColors.front());
	//	}
	//}

	////if assign only has one color available in possible colors, lock that in as his color
	//vector<unsigned int> assignsPossibleColors = modifiedConnectionMap.getPossibleColors(assign);
	//if (assignsPossibleColors.size() == 1){
	//	modifiedConnectionMap.setColor(assign, assignsPossibleColors.front());
	//}


	m.setColor(0,2);


	return ac3(m);
}

