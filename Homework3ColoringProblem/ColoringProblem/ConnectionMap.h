#ifndef CONNECTIONMAP_H
#define CONNECTIONMAP_H

#include <string>
#include <fstream>
#include <vector>


class ConnectionMap
{
public:
	ConnectionMap(unsigned int size, unsigned int numColors, std::string file);
	ConnectionMap(const ConnectionMap& c);
	ConnectionMap();
	// Returns value of connection map at (x, y).
	int getXY(unsigned int x, unsigned int y);
	// Returns the number of possible colors
	unsigned int getNumColors();
	// Returns the number of variables in the coloring problem.
	unsigned int getSize();
	// Returns the set of all possible colors for a given variable.
	std::vector<unsigned int> getPossibleColors(unsigned int i);
	// Removes "color" from the possible colors for variable "index."
	void removeColorFrom(unsigned int index, int color);
	// Sets variable "index" to value "color."
	void setColor(unsigned int index, int color);
	// Outputs the possible colors for each variable.
	void print();
private:
	unsigned int size;
	unsigned int numColors;
	std::vector<std::vector<unsigned int> > possibleColors;
	std::vector<std::vector<int> > connections;
};

#endif