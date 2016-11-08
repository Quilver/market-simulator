#pragma once
#include "Map.h"
#include "Market.h"
#include "Person.h"
using namespace std;
class City
{
public:
	struct district {
		int location[2];
		int maxPopulation;
		vector<Person> population;
		int water, food, salt, wood, rock, metal, gold;
	};
	struct route {
		int start[2], end[2];
		vector<int[2]> path;
	};
	Map& map;
	Market market;
	vector<Person> population;
	//location of the city
	int location[2] = { 0,0 };
	vector<district> districts;
	//sets up city
	City(int position[2], int numberOfDistricts, Map& source);
	void developCity();
	void developTown();
	void updateCity();
	void addDistrict(int x, int y);
	void spreadResources();
	void printResources(int x, int y);
	void checkMap();
	int getX();
	int getY();
	~City();
};

