#pragma once
#include "Map.h"
#include "City.h"
#include "Person.h"
#include "Commodity.h"
#include "Need.h"
#include <vector>
#include <string>
using namespace std;
class World
{
public:
	struct route {
		int start[2], end[2];
		vector<int[2]> path;
	};
	Map map = Map();
	City **cities;
	World(int seed);
	//create commodities & needs
	vector<Commodity> mapResources, labour, crafts;
	vector<Need> landNeeds, humanNeeds, craftNeed;
	//city creation
	int start[2];
	void initResources();
	void initCities();
	bool findCity();
	vector<int> x, y, weight;
	int exploration(int position[2], int range = 40);
	void exploreTile(int a, int b, int index);
	int valueTile(int position[2]);
	//route finding
	struct node {
		node *parent;
		bool open = true;
		int weight, distance, position[2];
	};
	vector<route> tradeRoutes;
	vector<node> paths;
	//will create routes until all the cities are linked
	void selectRoutes();
	//uses the A* algorithm to find the route
	void findRoutes(int position1[2], int position2[2]);
	void exploreNode(int index);
	void findDistance(int position1[2], int position2[2], int *delta);
	//end world
	~World();
};

