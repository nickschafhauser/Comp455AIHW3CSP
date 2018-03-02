#include "ConnectionMap.h"
#include <iostream>
using namespace std;

// DO NOT MODIFY
ConnectionMap::ConnectionMap(unsigned int size, unsigned int numColors, string file)
{
	this->size = size;
	this->numColors = numColors;

	possibleColors.resize(size);
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < numColors; j++)
		{
			possibleColors[i].push_back(j+1);
		}
	}

	connections.resize(size);
	for (unsigned int i = 0; i < size; i++)
	{
		connections[i].resize(size);
	}

	ifstream fin;
	fin.open(file);

	if (fin.fail())
	{
		cout << "Failed to open file." << endl;
		exit(1);
	}

	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			if (!fin.eof())
			{
				fin >> connections[i][j];
			}
		}
	}
}

ConnectionMap::ConnectionMap(const ConnectionMap& c)
{
	size = c.size;
	numColors = c.numColors;
	possibleColors = c.possibleColors;
	connections = c.connections;
}

ConnectionMap::ConnectionMap()
{
	size = 0;
	numColors = 0;
}

int ConnectionMap::getXY(unsigned int x, unsigned int y)
{
	if (x < size && y < size)
	{
		return connections[x][y];
	}
	else
	{
		return -1;
	}
}

unsigned int ConnectionMap::getNumColors()
{
	return numColors;
}

unsigned int ConnectionMap::getSize()
{
	return size;
}

vector<unsigned int> ConnectionMap::getPossibleColors(unsigned int i)
{
	return possibleColors[i];
}

void ConnectionMap::removeColorFrom(unsigned int index, int color)
{
	if (index < possibleColors.size())
	{
		vector<unsigned int> tempColors;
		for (unsigned int i = 0; i < possibleColors[index].size(); i++)
		{
			if (possibleColors[index][i] != color)
			{
				tempColors.push_back(possibleColors[index][i]);
			}
		}
		possibleColors[index] = tempColors;
	}
}

void ConnectionMap::setColor(unsigned int index, int color)
{
	if (index < possibleColors.size())
	{
		for (unsigned int i = 0; i < possibleColors[index].size(); i++)
		{
			if (possibleColors[index][i] == color)
			{
				possibleColors[index].clear();
				possibleColors[index].push_back(color);
				break;
			}
		}
	}
}

void ConnectionMap::print()
{
	for (unsigned int i = 0; i < size; i++)
	{
		cout << "Possible colors for " << i << ": ";
		for (unsigned int j = 0; j < possibleColors[i].size(); j++)
		{
			cout << possibleColors[i][j] << " ";
		}
		cout << endl;
	}
}