#include "Commodity.h"



Commodity::Commodity(string resource, Need &supplies, int quantity, bool mineral, int estimatedValue, int numOfPoint, int amountOfconcentration, int deviation, int seed)
	:need(supplies)
{
	srand(seed);
	name = resource;
	amountSupplied = quantity;
	rawResource = mineral;
	value = estimatedValue;
	variation = deviation;
	points = (numOfPoint - variation / 2) + (variation / 100)*(rand() % 100);
	concentraion = (amountOfconcentration - variation / 2) + (variation / 100)*(rand() % 100);
}


Commodity::~Commodity()
{
}
