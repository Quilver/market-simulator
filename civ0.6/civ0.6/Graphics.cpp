#include "Graphics.h"



Graphics::Graphics(World& source) :
	window(NULL), renderer(NULL), texture(NULL), buffer(NULL), world(source)
{
	cout << ": "<< world.map.width << ", " << world.map.hieght << endl;
	init();
	initMap();
	//
}
bool Graphics::eventLoop() {
	update();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;
	}
	return true;
}
void Graphics::update() {
	for (int x = 0; x < world.map.width; x++) {
		for (int y = 0; y < world.map.hieght; y++) {
			drawBox(map[x][y]);
		}
	}
	SDL_UpdateTexture(texture, NULL, buffer, WIDTH * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
bool Graphics::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("civ simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	buffer = new Uint32[WIDTH * HEIGHT];
	SDL_memset(buffer, 10, WIDTH*HEIGHT * sizeof(Uint32));
	return true;
}
void Graphics::initMap() {
	map = new Box*[world.map.getWidth()];
	for (int i = 0; i < world.map.width; i++) {
		map[i] = new Box[world.map.hieght];
	}
	cout << "created variable to hold tile map." << endl;
	int width = WIDTH / world.map.width;
	int height = HEIGHT / world.map.hieght;
	world.map.searchGoldLand();
	for (int x = 0; x < world.map.width; x++) {
		for (int y = 0; y < world.map.hieght; y++) {
			map[x][y].width = width;
			map[x][y].height = height;
			map[x][y].x = width*x;
			map[x][y].y = height*y;
			//cout << "X:" << x << ", Y: " << y << endl;
			tileToColour(&(map[x][y]), world.map.tileMap[x][y].type);
		}
	}
	cout << "finished running map" << endl;
}
void Graphics::tileToColour(Box *square, char type) {
	switch (type)
	{
	case 'c'://city
		(*square).red = 200;
		(*square).green = 0;
		(*square).blue = 150;
		break;
	case 'p':
		(*square).red = 150;
		(*square).green = 20;
		(*square).blue = 50;
		break;
	case 't'://town
		(*square).red = 140;
		(*square).green = 40;
		(*square).blue = 50;
		break;
	case '^'://mountain
		(*square).red = 100;
		(*square).green = 100;
		(*square).blue = 100;
		break;
	case '-'://desert
		(*square).red = 200;
		(*square).green = 200;
		(*square).blue = 0;
		break;
	case '.'://land
		(*square).red = 50;
		(*square).green = 250;
		(*square).blue = 50;
		break;
	case 's'://sea
		(*square).red = 20;
		(*square).green = 0;
		(*square).blue = 150;
		break;
	case 'r'://river
		(*square).red = 20;
		(*square).green = 40;
		(*square).blue = 150;
		break;
	case '~'://lake
		(*square).red = 20;
		(*square).green = 30;
		(*square).blue = 150;
		break;
	default:
		(*square).red = 200;
		(*square).green = 100;
		(*square).blue = 150;
		break;
	}
}
void Graphics::setPixel(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, Uint32 *pixel) {
	Uint32 colour = red;
	colour <<= 8;
	colour += green;
	colour <<= 8;
	colour += blue;
	colour <<= 8;
	colour += alpha;
	*pixel = colour;
}
void Graphics::drawBox(Box square) {
	bool inX;
	bool inY;
	for (int y = square.y; y <= (square.y + square.height); y ++) {
		for (int x = square.x; x <= (square.x + square.width); x++) {
			inX = 0 <= x && x <= WIDTH;
			inY = 0 <= y && y <= HEIGHT;
			if(inX && inY)
			setPixel(square.red, square.green, square.blue, square.alpha, &(buffer[y * WIDTH + x]));
		}
	}
}
Graphics::~Graphics()
{
}
