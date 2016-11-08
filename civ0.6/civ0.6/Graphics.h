#pragma once
#include <SDL.h>
#include "World.h"
#include "Map.h"
#include <iostream>
using namespace std;
//#include <SDL2/SDL_ttf.h>
class Graphics
{
public:
	struct tile {
		int preHieght = 0; int hieght = 0; int elevation;
		bool sea, lake, river = false;
		bool land = true;
		bool mountain, desert = false;
		int fertile = 0; int wood = 0; int salt = 0; int rock = 0; int metal = 0; int gold = 0; int hydration = 0;
		int score = 0;
		char type, searchType;
	};
	struct Box {
		int x, y;
		int width, height;
		Uint8 red, green, blue, alpha = 0;
	};
	const int WIDTH = 1200;
	const int HEIGHT = 900;
	Box **map;
	World &world;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	Uint32 *buffer;
	SDL_Event event;
	Graphics(World& world);
	void drawMap();
	bool eventLoop();
	~Graphics();
private:
	bool init();
	void initMap();
	void tileToColour(Box *square, char type);
	void update();
	void setPixel(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, Uint32 *pixel);
	void drawBox(Box square);
};

