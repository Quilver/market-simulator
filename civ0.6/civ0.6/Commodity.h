#pragma once
#include <string>
#include <random>
#include "Need.h"
using namespace std;
class Commodity
{
public:
	string name;
	Need &need;
	int amountSupplied;
	bool rawResource;
	int value;
	int points, concentraion, variation;
	Commodity(string resource, Need &supplies, int quantity, bool mineral, int estimatedValue, int numOfPoint, int amountOfconcentration, int deviation, int seed);
	~Commodity();
};

