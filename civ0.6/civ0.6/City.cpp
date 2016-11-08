#include "City.h"
#include <iostream>
using namespace std;

City::City(int position[2], int Districts, Map& source) :map(source) {
	location[0] = position[0]; location[1] = position[1];
	spreadResources();
	map.tileMap[location[0]][location[1]].type = 'c';
	cout << "city " << "(" << location[0] << ", " << location[1] << "):" << endl;
}
void City::addDistrict(int x, int y) {
	district plot;
	if (map.tileMap[x][y].land) {
		plot.location[0] = x; plot.location[1] = y;
		plot.food = map.tileMap[x][y].fertile; plot.water = map.tileMap[x][y].hydration; plot.salt = map.tileMap[x][y].salt;
		plot.wood = map.tileMap[x][y].wood; plot.rock = map.tileMap[x][y].rock; plot.metal = map.tileMap[x][y].metal; plot.gold = map.tileMap[x][y].gold;
		districts.push_back(plot);
		//cout << "District " << "(" << x << ", " << y << "):" << endl;
		//printResources(x, y);
		map.tileMap[x][y].type = 't';
	}
}
void City::spreadResources() {

}
void City::checkMap() {
	const int water = 1; const int embark = 12; const int land = 4; const int warf = 6; const int mountain = 20;
}

void City::printResources(int x, int y) {

	cout << "	  " << "water: " << map.tileMap[x][y].hydration << endl;
	cout << "	  " << "food: " << map.tileMap[x][y].fertile << endl;
	cout << "	  " << "salt: " << map.tileMap[x][y].salt << endl;
	cout << "	  " << "wood: " << map.tileMap[x][y].wood << endl;
	cout << "	  " << "rock: " << map.tileMap[x][y].rock << endl;
	cout << "	  " << "metal: " << map.tileMap[x][y].metal << endl;
	cout << "	  " << "gold: " << map.tileMap[x][y].gold << endl;
}
int City::getX() {
	return location[0];
}
int City::getY() {
	return location[1];
}
City::~City()
{
}
