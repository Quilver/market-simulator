#pragma once
#include <vector>
#include <math.h>
#include <random>
#include <iostream>
#include "Commodity.h"
#include "Tile.h"
using namespace std;
class Map
{
public:
	const double PI = 3.14159265358979323846;
	int numberOfCivs = 0; const int maxCivs = 100;
	int civStarts[100][2];
	int numberOfFeatures = 20;
	struct tile {
		int preHieght = 0; int hieght = 0; int elevation;
		bool sea, lake, river = false;
		bool land = true;
		bool mountain, desert = false;
		int fertile = 0; int wood = 0; int salt = 0; int rock = 0; int metal = 0; int gold = 0; int hydration = 0;
		int score = 0;
		char type, searchType;
	};
	static const int width = 300;
	static const int hieght = 200;
	struct tile **tileMap;
	//control method
	Map();
	void initMap(int seed);
	//search methods
	int searchLand();
	int searchWetLand(int score = 100);
	int searchArrableLand(int score = 100);
	int searchSaltLand(int score = 100);
	int searchwoodLand(int score = 100);
	int searchRockLand(int score = 100);
	int searchMetalLand(int score = 100);
	int searchGoldLand(int score = 100);
	int scoreTiles(int score = 4);
	int valueTiles(int value = 101);
	void searchTile(int x, int y);
	int getWidth();
private:
	//functions fill map
	int scoreResource(int resource, int high, int medium, int low = 0);
	void spawnRiver();// int x = 0, int y = 0, int radius = 0);
	void fillvalues();
	void terrainEffect(char terrain, int x, int y);
	//terrain map
	int dropPointRange[2]; int dropPoints;
	void landGenorater();
	void fillIn();
	void islandHieghtMap();
	void findSea(int x = 0, int y = 0);
	bool isSea(int x, int y);
	//resource map
	void resourceGenerator();
	void resourceHieghtMap(int drops);
	void water(); void food(); void salt(); void wood(); void rock(); void metal(); void gold();
	//utility functions
	//hieght map utilities
	void heightMapGenerarter(int x, int y, int deviation = 0);
	void resetHieghtMap();
	void trickle(int x, int y, int stabilityRadius = 3);
	void gaussianBlur();
	//geometry utilities
	bool lineGoesThroughBox(double gradient, double intercept, int position[2]);
	bool pointInCircle(int position[2], int locusOfCircle[2], int radius);
};

