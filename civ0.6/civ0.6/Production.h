#pragma once
#include <vector>
#include <string>
#include "Commodity.h"
using namespace std;

class Production
{
public:
	struct resource {
		Commodity *commodity;
		int quantity;
	};
	struct resourceSet {
		resource *resources;
		int numOfResources;
	};
	string name;
	resourceSet inputs;
	resourceSet output;
	Production(string process);
	void setInputs(vector<Commodity> resourcesUsed, vector<int> amountUsed);
	void setOutputs(vector<Commodity> resourcesProduced, vector<int> amountProduced);


	~Production();
};

