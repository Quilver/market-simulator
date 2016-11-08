#pragma once
#include "Commodity.h"
#include <vector>
using namespace std;
class Tile
{
public:
	int height;
	int type; 
	vector<Commodity> resources;
	Tile();
	int getValue();
	~Tile();
};

