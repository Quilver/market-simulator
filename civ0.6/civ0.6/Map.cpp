#include "Map.h"
using namespace std;


Map::Map()
{
}
void Map::initMap(int seed)
{
	//width = 300; hieght = 200;
	numberOfCivs = 0;
	tileMap = new tile*[width];
	for (int i = 0; i < width; i++) {
		tileMap[i] = new tile[hieght];
	}
	srand(seed);
	landGenorater();
}
int Map::getWidth() {
	cout << width << endl;
	return width;
}
//populate map methods
//fill in terrain
void Map::landGenorater() {
	islandHieghtMap();
	gaussianBlur();// gaussianBlur(); gaussianBlur(); gaussianBlur(); gaussianBlur(); gaussianBlur();
	fillIn();
	findSea();
	fillvalues();
	for (int k = 0; k < 200; k++) {
		spawnRiver();
	}
}
void Map::fillIn() {
	tile *province;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			province = &tileMap[x][y];
			(*province).elevation = (*province).hieght;
			if ((*province).hieght > 20) {
				(*province).mountain = true;
				tileMap[x][y].type = '^';
			}
			else if ((*province).hieght > 3) {
				(*province).land = true;
				tileMap[x][y].type = '.';
			}
			else {
				tileMap[x][y].type = '~';
				tileMap[x][y].lake = true; tileMap[x][y].sea = false; tileMap[x][y].river = false;
				tileMap[x][y].land = false;
			}
		}
	}
}
void Map::islandHieghtMap() {
	dropPointRange[0] = 150; dropPointRange[1] = 200;
	int islandRange[2] = { 5, 10 };
	dropPoints = rand() % (dropPointRange[1] - dropPointRange[0]) + dropPointRange[0]; int islands = rand() % (islandRange[1] - islandRange[0]) + islandRange[0];
	int islandDrops = dropPoints*0.6; int freeDrops = dropPoints - islandDrops;
	int radius = 55 / islands;
	int dropHieght;
	int x, y;
	int a, b;
	//int numOfPasses;
	for (int i = 0; i < islandDrops; i++) {
		a = 15 + rand() % (width - 30);
		b = 15 + rand() % (hieght - 30);
		for (int j = 0; j < freeDrops; j++) {
			dropHieght = 20 + rand() % 40;
			x = a - radius + rand() % (radius * 2);
			y = b - radius + rand() % (radius * 2);
			tileMap[x][y].preHieght += dropHieght;
			trickle(x, y);
		}
	}
	for (int i = 0; i < freeDrops; i++) {
		dropHieght = 30 + rand() % 50;
		x = 5 + rand() % (width - 10);
		y = 5 + rand() % (hieght - 10);
		tileMap[x][y].preHieght += dropHieght;
		trickle(x, y);
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].hieght = tileMap[x][y].preHieght;
		}
	}
}
void Map::findSea(int x, int y) {
	tileMap[0][0].sea = true; tileMap[0][0].type = 's';
	tileMap[0][0].lake = false;
	printf("finding sea tiles\n");
	for (int k = 0; k < 25; k++) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < hieght; j++) {
				if (isSea(i, j)) {
					tileMap[i][j].sea = true; tileMap[i][j].type = 's';
					tileMap[i][j].lake = false;
				}
			}
		}
		for (int i = width - 1; i > 0; i--) {
			for (int j = hieght - 1; j > 0; j--) {
				if (isSea(i, j)) {
					tileMap[i][j].sea = true; tileMap[i][j].type = 's';
					tileMap[i][j].lake = false;
				}
			}
		}
	}
}
bool Map::isSea(int x, int y) {
	if (tileMap[x][y].lake == true) {
		if (x > 0) {
			if (tileMap[x - 1][y].sea == true) return true;
		}
		if (y > 0) {
			if (tileMap[x][y - 1].sea == true) return true;
		}
		if (x < width - 1) {
			if (tileMap[x + 1][y].sea == true) return true;
		}
		if (y < hieght - 1) {
			if (tileMap[x][y + 1].sea == true) return true;
		}
	}
	return false;
}
void Map::spawnRiver()// int x, int y, int radius)
{
	int x = rand() % width; int y = rand() % hieght;
	while (tileMap[x][y].land != true) {
		x = rand() % width;
		y = rand() % hieght;
	}
	char horizontal, vertical;
	if (rand() % 2)horizontal = 'r';
	else horizontal = 'l';
	if (rand() % 2)vertical = 'u';
	else vertical = 'd';
	while (tileMap[x][y].land) {
		tileMap[x][y].river = true; tileMap[x][y].type = 'r';
		tileMap[x][y].land = false;
		if (rand() % 2) {
			if (horizontal == 'r')x++;
			else x--;
		}
		else {
			if (vertical = 'u')y--;
			else y++;
		}
	}
}

//fill in values for tiles
void Map::fillvalues() {
	resourceGenerator();
	for (int x = 3; x < width - 3; x++) {
		for (int y = 3; y < hieght - 3; y++) {
			if (tileMap[x][y].mountain) {
				terrainEffect('^', x, y);
			}
			if (tileMap[x][y].lake) {
				terrainEffect('l', x, y);
			}
			if (tileMap[x][y].river) {
				terrainEffect('r', x, y);
			}
			if (tileMap[x][y].sea) {
				terrainEffect('s', x, y);
			}
		}
	}
}
void Map::terrainEffect(char terrain, int x, int y) {
	switch (tileMap[x][y].type) {
	case '^':
		//rock
		if (50 < (rand() % 50 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			rock();
		}
		//metal
		if (50 < (rand() % 50 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			metal();
		}
		//gold
		if (100 < (rand() % 100 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			gold();
		}
		break;
	case 'l':
		//water
		if (30 < (rand() % 30 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			water();
		}
		//food
		if (50 < (rand() % 50 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			food();
		}
		//wood
		if (100 < (rand() % 100 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			wood();
		}
		break;
	case 'r':
		//water
		if (30 < (rand() % 30 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			water();
		}
		//food
		if (50 < (rand() % 50 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			food();
		}
		//wood
		if (100 < (rand() % 100 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			wood();
		}
		break;
	case 's':
		//water
		if (100 < (rand() % 100 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			water();
		}
		//food
		if (50 < (rand() % 50 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			food();
		}
		//salt
		if (50 < (rand() % 50 + 1)) {
			heightMapGenerarter(x, y);
			gaussianBlur();
			salt();
		}
		break;
	}
}
//resource map
void Map::resourceGenerator() {
	resetHieghtMap();
	resourceHieghtMap(1400); gaussianBlur(); water();
	resourceHieghtMap(800); gaussianBlur(); food();
	resourceHieghtMap(600); gaussianBlur(); salt();
	resourceHieghtMap(600); gaussianBlur(); wood();
	resourceHieghtMap(600); gaussianBlur(); rock();
	resourceHieghtMap(400); gaussianBlur(); metal();
	resourceHieghtMap(200); gaussianBlur(); gold();
}
void Map::water() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].hydration += tileMap[x][y].hieght;
		}
	}
	resetHieghtMap();
}
void Map::food() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].fertile += tileMap[x][y].hieght;
		}
	}
	resetHieghtMap();
}
void Map::salt() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].salt += tileMap[x][y].hieght;
		}
	}
	resetHieghtMap();
}
void Map::wood() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].wood += tileMap[x][y].hieght;
		}
	}
	resetHieghtMap();
}
void Map::rock() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].rock += tileMap[x][y].hieght;
		}
	}
	resetHieghtMap();
}
void Map::metal() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].metal += tileMap[x][y].hieght;
		}
	}
	resetHieghtMap();
}
void Map::gold() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].gold += tileMap[x][y].hieght;
		}
	}
	resetHieghtMap();
}

void Map::resourceHieghtMap(int drops) {
	int dropHieght; int x, y;
	for (int i = 0; i < drops; i++) {
		dropHieght = 600 + rand() % 1500;
		do {
			x = 5 + rand() % (width - 10);
			y = 5 + rand() % (hieght - 10);
		} while (tileMap[x][y].land == false);

		tileMap[x][y].preHieght += dropHieght;
		trickle(x, y, 2);
	}
}

//utility methods
//geometry
bool Map::lineGoesThroughBox(double gradient, double intercept, int position[2]) {
	double x, y;
	y = gradient*position[0] + intercept;
	if (position[1] <= y && position[1] + 1 >= y) {
		return true;
	}
	y = gradient*(position[0] + 1) + intercept;
	if (position[1] <= y && position[1] + 1 >= y) {
		return true;
	}
	x = (position[1] - intercept) / gradient;
	if (position[0] <= x && position[0] + 1 >= x) {
		return true;
	}
	x = (position[1] + 1 - intercept) / gradient;
	if (position[0] <= x && position[0] + 1 >= x) {
		return true;
	}
	return false;
}
bool Map::pointInCircle(int position[2], int locusOfCircle[2], int radius) {
	int deltaX = (position[0] - locusOfCircle[0]);
	int deltaY = (position[1] - locusOfCircle[1]);
	int distance = deltaX*deltaX + deltaY*deltaY;
	bool value = (distance <= radius*radius);
	return value;
}
//hieght map
void Map::heightMapGenerarter(int x, int y, int deviation) {
	int dropHieght = 1000 + rand() % 1000;
	if (deviation != 0) {
		do {
			x = x + rand() % (deviation);
			y = y + rand() % (deviation);
		} while (x < width && x >= 0 && y < hieght && y >= 0);
	}
	tileMap[x][y].preHieght += dropHieght;
	trickle(x, y, 4);
}
void Map::resetHieghtMap() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < hieght; j++) {
			tileMap[i][j].hieght = 0;
			tileMap[i][j].preHieght = 0;
		}
	}
}
void Map::trickle(int x, int y, int stabilityRadius) {
	//const int stabilityRadius = 3;//should be from 1-3
	bool cont = true;
	while (cont) {
		cont = false;
		for (int i = x - stabilityRadius; i < (x + stabilityRadius); i++) {

			for (int j = y - stabilityRadius; j < (y + stabilityRadius); j++) {

				if (tileMap[x][y].preHieght>tileMap[i][j].preHieght + 1) {

					cont = true;
					tileMap[x][y].preHieght -= 1;
					tileMap[i][j].preHieght += 1;
				}
			}
		}
	}
}
void Map::gaussianBlur() {
	int total; int sum = 16;
	for (int x = 1; x < width - 1; x++) {
		for (int y = 1; y < hieght - 1; y++) {
			total = 0;
			total += (tileMap[x - 1][y - 1].preHieght + tileMap[x + 1][y - 1].preHieght + tileMap[x - 1][y + 1].preHieght + tileMap[x + 1][y + 1].preHieght);
			total += (tileMap[x - 1][y].preHieght + tileMap[x + 1][y].preHieght + tileMap[x][y - 1].preHieght + tileMap[x][y + 1].preHieght) * 2;
			total += (tileMap[x][y].preHieght) * 4;
			tileMap[x][y].hieght = total / sum;
		}
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			tileMap[x][y].preHieght = tileMap[x][y].hieght;
		}
	}
}
//search map methods
int Map::searchLand() {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].land) {
				amount++;
				tileMap[x][y].searchType = '!';
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::searchArrableLand(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].fertile >= score && tileMap[x][y].land) {
				amount++;
				tileMap[x][y].searchType = '!';
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::searchWetLand(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].hydration >= score && tileMap[x][y].land) {
				amount++;
				tileMap[x][y].searchType = '!';
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::searchwoodLand(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].wood >= score && tileMap[x][y].land) {
				amount++;
				tileMap[x][y].searchType = '!';
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::searchSaltLand(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].salt >= score && tileMap[x][y].land) {
				amount++;
				tileMap[x][y].searchType = '!';
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::searchRockLand(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].rock >= score && tileMap[x][y].land) {
				amount++;
				tileMap[x][y].searchType = '!';
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::searchMetalLand(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].metal >= score && tileMap[x][y].land) {
				amount++;
				tileMap[x][y].searchType = '!';
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::searchGoldLand(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].gold >= score && tileMap[x][y].land) {
				tileMap[x][y].searchType = '!';
				amount++;
			}
			else
			{
				tileMap[x][y].searchType = '_';
			}
		}
	}
	return amount;
}
int Map::scoreTiles(int score) {
	int amount = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < hieght; y++) {
			if (tileMap[x][y].land) {
				if (tileMap[x][y].hydration >= 100) {
					tileMap[x][y].score++;
				}
				if (tileMap[x][y].fertile >= 100) {
					tileMap[x][y].score++;
				}
				if (tileMap[x][y].salt >= 100) {
					tileMap[x][y].score++;
				}
				if (tileMap[x][y].wood >= 100) {
					tileMap[x][y].score++;
				}
				if (tileMap[x][y].rock >= 100 && (tileMap[x][y].wood >= 100)) {
					tileMap[x][y].score++;
				}
				if (tileMap[x][y].metal >= 100) {
					tileMap[x][y].score++;
				}
				if (tileMap[x][y].gold >= 100) {
					//tileMap[x][y].score++;
				}
				if (tileMap[x][y].score >= score) {
					amount++;
					tileMap[x][y].type = 'x';
					if (numberOfCivs < maxCivs && 50 <= tileMap[x][y].fertile && 50 <= tileMap[x][y].hydration) {
						civStarts[numberOfCivs][0] = x; civStarts[numberOfCivs][1] = y;
						numberOfCivs++;
					}
				}
			}
		}
	}
	printf("number of tiles that score %d or greater is %d \n", score, amount);
	return amount;
}
int Map::valueTiles(int value) {
	int score; int amount = 0;
	//value added
	int nextToWater = 35; int high = 16; int medium = 6;
	for (int x = 2; x < width - 2; x++) {
		for (int y = 2; y < hieght - 2; y++) {
			score = 0;
			tile province = tileMap[x][y];
			if (!tileMap[x - 1][y].land || !tileMap[x][y - 1].land || !tileMap[x + 1][y].land || !tileMap[x][y + 1].land) {
				score += nextToWater;
			}
			//
			score += scoreResource(province.hydration, high, medium, -15); score += scoreResource(province.fertile, high, medium, -15);
			score += scoreResource(province.salt, high, medium); score += scoreResource(province.wood, high, medium);
			score += scoreResource(province.rock, high, medium); score += scoreResource(province.metal, high, medium);
			score += scoreResource(province.gold, high, medium);
			if (!province.land) {
				score = 0;
			}
			if (score >= value) {
				amount += 1;
				if (numberOfCivs < maxCivs) {
					civStarts[numberOfCivs][0] = x; civStarts[numberOfCivs][1] = y;
					numberOfCivs++;
				}
				if (province.type == 'c') {
					tileMap[x][y].type = 'm';
				}
				else {
					tileMap[x][y].type = 'x';
				}
			}
		}
	}
	printf("number of tiles that score %d or greater is %d \n", value, amount);
	return amount;
}
int Map::scoreResource(int resource, int high, int medium, int low) {
	int score;
	if (resource >= 100) {
		score = high;
	}
	else if (resource >= 50) {
		score = medium;
	}
	else {
		score = low;
	}
	return score;
}
void Map::searchTile(int x, int y) {
	printf("tile %d, %d has score: %d. ", x, y, tileMap[x][y].score);
	if (tileMap[x][y].hydration >= 100) {
		printf("wet, ");
	}
	if (tileMap[x][y].fertile >= 100) {
		printf("fertile, ");
	}
	if (tileMap[x][y].salt >= 100) {
		printf("salt, ");
	}
	if (tileMap[x][y].wood >= 100) {
		printf("wood, ");
	}
	if (tileMap[x][y].rock >= 100) {
		printf("rock, ");
	}
	if (tileMap[x][y].metal >= 100) {
		printf("metal, ");
	}
	if (tileMap[x][y].gold >= 100) {
		printf("gold, ");
	}
}
