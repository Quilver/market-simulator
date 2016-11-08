#include "World.h"
#include <iostream>
using namespace std;


World::World(int seed)
{
	map.initMap(seed);
	
	cout << seed << ": " << map.width << ", " << map.hieght << endl;
}

void World::initResources() {
	//Need thurst, hunger, saltiness, fuel, bricks, ore, material, farmTool, axeTool, miningTool, smithTool;

	landNeeds.push_back(Need("water"));mapResources.push_back(Commodity("water", landNeeds[0], 1, true, 2, 2800, 700, 250, rand()));
	landNeeds.push_back(Need("food")); mapResources.push_back(Commodity("food", landNeeds[1], 1, true, 4, 2400, 900, 250, rand()));
	landNeeds.push_back(Need("salt")); mapResources.push_back(Commodity("salt", landNeeds[2], 1, true, 3, 1000, 1000, 250, rand()));
	landNeeds.push_back(Need("wood")); mapResources.push_back(Commodity("wood", landNeeds[3], 1, true, 3, 1000, 1000, 250, rand()));
	landNeeds.push_back(Need("rock")); mapResources.push_back(Commodity("rock", landNeeds[4], 1, true, 3, 1000, 1000, 250, rand()));
	landNeeds.push_back(Need("metal")); mapResources.push_back(Commodity("metal", landNeeds[5], 1, true, 3, 1000, 1000, 250, rand()));
	landNeeds.push_back(Need("gold")); mapResources.push_back(Commodity("gold", landNeeds[6], 1, true, 3, 500, 2000, 250, rand()));
}

void World::initCities() {
	cities = new City*[map.maxCivs];
	int counter = 0; bool running = true; start[0] = 10; start[1] = 10;
	while (counter<map.maxCivs && running) {
	running = findCity();
	counter++;
	cout << "running: " << running << endl;
	if (running == false) {
	cout << "The map has run out of desirable locations" << endl;
	break;
	}
	}
	cout << map.numberOfCivs << endl;
}
//finding new cities
bool World::findCity() {
	int score, position[2], desiredScore = 240;
	bool nextToSea;
	for (int i = start[0]; i < map.width - 10; i += 3) {
		for (int j = start[1]; j < map.hieght - 10; j += 3) {
			position[0] = i; position[1] = j;
			nextToSea = map.tileMap[i - 1][j].land != true || map.tileMap[i + 1][j].land != true || map.tileMap[i][j - 1].land != true || map.tileMap[i][j + 1].land != true;
			if (map.tileMap[i][j].land && map.tileMap[i][j].type == '.' && nextToSea) {
				score = exploration(position);
				if (score>desiredScore && (map.maxCivs>map.numberOfCivs)) {
					cities[map.numberOfCivs] = &City(position, weight.size(), map);
					cout << "City was created at: " << (*cities[map.numberOfCivs]).getX() << ", " << (*cities[map.numberOfCivs]).getY() << ".\n";
					for (int k = 1; k < weight.size(); k++) {
						(*cities[map.numberOfCivs]).addDistrict(x[k], y[k]);
					}
					cout << "number of districts: " << (*cities[map.numberOfCivs]).districts.size() << endl;
					cout << "score was: " << score << endl;
					map.numberOfCivs++;
					cout << map.numberOfCivs << " out of " << map.maxCivs << ".\n";
					start[0] = i; start[1] = j;
					x.clear(); y.clear(); weight.clear();
					return true;
				}
			}
			//cout << "new spot to search" << endl;
			x.clear(); y.clear(); weight.clear();
		}
		start[1] = 10;
	}
	x.clear(); y.clear(); weight.clear();
	return false;
}
int World::exploration(int position[2], int range) {
	//cout << "Exploring a tile." << endl;
	if (map.tileMap[position[0]][position[1]].type == 'c' || map.tileMap[position[0]][position[1]].type == 't')
	{
		//cout << "Overlaps another city at :" << position[0] << ", " << position[1] << endl;
		return 0;
	}
	int deltaX, deltaY;
	if (map.numberOfCivs > 0) {

		for (int i = 0; i < map.numberOfCivs; i++) {
			deltaX = (*cities[i]).location[0] - position[0];
			if (deltaX < 0)deltaX *= -1;
			deltaY = (*cities[i]).location[1] - position[1];
			if (deltaY < 0)deltaY *= -1;
			if (deltaX < range && deltaY < range)
			{
				//cout << "Too close to another city at: " << position[0] << ", " << position[1] << endl;
				return 0;
			}
		}
	}
	int index = 0;
	x.push_back(position[0]); y.push_back(position[1]); weight.push_back(0);
	do {
		if (x[index] - 1 >= 0) exploreTile(x[index] - 1, y[index], index);
		if (x[index] + 1<map.width) exploreTile(x[index] + 1, y[index], index);
		if (y[index] - 1 >= 0) exploreTile(x[index], y[index] - 1, index);
		if (y[index] + 1<map.hieght) exploreTile(x[index], y[index] + 1, index);
		index++;
	} while (index < weight.size());
	int score = 0; int location[2];
	for (int i = 1; i<weight.size(); i++) {
		//cout << i << " out of " << weight.size() << endl;
		location[0] = x[i]; location[1] = y[i];
		if (map.tileMap[x[i]][y[i]].land)score += valueTile(location);
	}
	//if (score > 0 && map.numberOfCivs > 0)cout << "city(" << x[0] << ", " << y[0] << ") has a score of: " << score << endl;
	//if (map.numberOfCivs > 0)cout << "city has no score";
	return score;
}
void World::exploreTile(int a, int b, int index) {
	//cout << "discovering a new tile" << endl;
	int mountain, land, dock, water;
	mountain = 20; land = 8; dock = 12; water = 1;
	int newWieght = weight[index];
	if (map.tileMap[x[index]][y[index]].type == '.' && map.tileMap[a][b].type == '.')newWieght += land;
	else if (map.tileMap[x[index]][y[index]].land && map.tileMap[a][b].land) {}
	else if (map.tileMap[x[index]][y[index]].land || map.tileMap[a][b].land)newWieght += dock;
	else newWieght += water;
	bool unique = true; int j = 0;
	for (int i = 0; i<weight.size(); i++) {
		if (a == x[i] && b == y[i]) {
			unique = false;
			j = i;
		}
	}
	if (map.tileMap[a][b].type == '^' || map.tileMap[a][b].type == 'c' || map.tileMap[a][b].type == 't') {}
	else if (unique && newWieght<40) {
		x.push_back(a); y.push_back(b); weight.push_back(newWieght);
	}
	else if (weight[j]>newWieght) {
		weight[j] = newWieght;
		if (a - 1 >= 0) exploreTile(a - 1, b, j);
		if (a + 1<map.width) exploreTile(a + 1, b, j);
		if (b - 1 >= 0) exploreTile(a, b - 1, j);
		if (b + 1<map.hieght) exploreTile(a, b + 1, j);
	}
}
int World::valueTile(int position[2]) {
	//cout << "Valueing tile... ";
	int score = 0;
	if (map.tileMap[position[0]][position[1]].type != '.')return score;
	int high = 2; int medium = 1; int low = 0;
	int food = 1; int water = 1; int salt = 2; int wood = 2; int rock = 2; int metal = 2; int gold = 4;
	if (map.tileMap[position[0]][position[1]].hydration >= 50) {
		if (map.tileMap[position[0]][position[1]].hydration >= 100) score += water*high;
		else score += water*medium;
	}
	if (map.tileMap[position[0]][position[1]].fertile >= 50) {
		if (map.tileMap[position[0]][position[1]].fertile >= 100) score += food*high;
		else score += food*medium;
	}
	if (map.tileMap[position[0]][position[1]].salt >= 50) {
		if (map.tileMap[position[0]][position[1]].salt >= 100) score += salt*high;
		else score += salt*medium;
	}
	if (map.tileMap[position[0]][position[1]].wood >= 50) {
		if (map.tileMap[position[0]][position[1]].wood >= 100) score += wood*high;
		else score += wood*medium;
	}
	if (map.tileMap[position[0]][position[1]].rock >= 50) {
		if (map.tileMap[position[0]][position[1]].rock >= 100) score += rock*high;
		else score += rock*medium;
	}
	if (map.tileMap[position[0]][position[1]].metal >= 50) {
		if (map.tileMap[position[0]][position[1]].metal >= 100) score += metal*high;
		else score += metal*medium;
	}
	if (map.tileMap[position[0]][position[1]].gold >= 50) {
		if (map.tileMap[position[0]][position[1]].gold >= 100) score += gold*high;
		else score += gold*medium;
	}
	//cout << "finished valueing tile." << endl;
	return score;
}
//selects route
void World::selectRoutes() {
	int deltaX, deltaY, index[2], weight = 999999;
	for (int i = 0; i < map.numberOfCivs; i++) {
		for (int j = 0; j < map.numberOfCivs; j++) {
			if (i != j) {
				//
				deltaX = (*cities[i]).getX() - (*cities[j]).getX();
				if ((*cities[i]).getX() < (*cities[j]).getX())deltaX *= -1;
				deltaY = (*cities[i]).getY() - (*cities[j]).getY();
				if ((*cities[i]).getY() < (*cities[j]).getY())deltaY *= -1;
				//
				if ((deltaX + deltaY) < weight) {
					index[0] = i; index[1] = j;
				}
			}
		}
	}
	int start[2] = { (*cities[index[0]]).getX(), (*cities[index[0]]).getY() };
	int end[2] = { (*cities[index[1]]).getX(), (*cities[index[1]]).getY() };
	findRoutes(start, end);
}
//finds a route between 2 points. Uses A* algorithm.
void World::findRoutes(int start[2], int end[2]) {
	node startNode, midNode;
	paths.clear();
	startNode.parent = NULL; startNode.position[0] = start[0]; startNode.position[1] = start[1]; startNode.weight = 0;
	int deltaX, deltaY;
	findDistance(start, end, &(startNode.distance));
	startNode.distance *= 8;
	paths.push_back(startNode);
	bool searching = true;
	int weight, index = 0;
	while (searching) {
		weight = 1000000;
		for (int i = 0; i < paths.size(); i++) {
			if (paths[i].open && (paths[i].distance + paths[i].weight)<weight) {
				index = i;
				weight = (paths[i].distance + paths[i].weight);
			}
		}
		exploreNode(index);
		for (int i = 0; i < paths.size(); i++) {
			if (paths[i].position == end) {
				searching = false;
				index = i;
				break;
			}
		}
	}
	//tracing backward to find the path and put it the tradeRoutes 
	/*
	route road;
	node point = paths[index];
	road.end[0] = point.position[0]; road.end[1] = point.position[1];
	//road.path.push_back(point.position);
	while(paths[0].position != start){
	point = *(point.parent);
	road.path.push_back(point.position);
	}
	road.start[0] = point.position[0]; road.start[1] = point.position[1];
	map.tileMap[point.position[0]][point.position[1]].type = 'p';
	tradeRoutes.push_back(road);*/
}
void World::exploreNode(int index) {

}
void World::findDistance(int position1[2], int position2[2], int *delta) {
	int deltaX, deltaY;
	deltaX = position1[0] - position2[0];
	if (deltaX < 0)deltaX *= -1;
	deltaY = position1[1] - position2[1];
	if (deltaY < 0)deltaY *= -1;
	(*delta) = deltaX + deltaY;
}

World::~World()
{
}
