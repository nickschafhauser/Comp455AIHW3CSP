#include "Reducer.h"
#include <iostream>
#include <vector>
#include <queue> // std::queue
#include <utility> // std::pair, std::make_pair
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

		while (possibleColors.size() > 1){
			ConnectionMap modifiedConnectionMap = ConnectionMap(m);
			modifiedConnectionMap.setColor(i, possibleColors.front());

			//then that color we picked ended up not providing a complete solution
			//go back and try and different color
			if (ac3(modifiedConnectionMap) == false){
				m.removeColorFrom(i, possibleColors.front());
				possibleColors = m.getPossibleColors(i);

				//Then we just locked in an answer without making sure there were not any contradictions
				if(possibleColors.size() == 1){
					return false;
				}
			}else{
				//We found a solution
				//That was a good color that we picked, lets lock it in permanently
				//m.setColor(i, possibleColors.front());
				m = modifiedConnectionMap;
				return true;
			}
		}
	}
	return true;
}

// Takes a connection map and an index to which it should assign a value.
// Returns true if a COMPLETE solution was found and false otherwise.
// I assume backtrack() is recursive, but you can create whatever functions you want
// However, this is the ONLY file you should modify.
bool backtrack(ConnectionMap &m, int assign)
{

	vector<unsigned int> possibleColors = m.getPossibleColors(assign);
	if (possibleColors.size() > 0){
		m.setColor(assign, possibleColors.front());
		//m.setColor(assign, 2);
	}else{
		//then the user is trying to solve for a scenario where there are no colors to choose from
		//that is unsolvable.
		return false;
	}

	return ac3(m);
}

