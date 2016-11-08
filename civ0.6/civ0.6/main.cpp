#include <SDL.h>
#include "Graphics.h"
#include "World.h"
#include <random>
#include <time.h>
using namespace std;
int main(int argc, char **argv) {
	srand(time(NULL));
	int seed = rand(); cout << "Seed: " << seed << endl;
	World world = World(seed);
	Graphics screen = Graphics(world);
	bool running = true;
	while (running) {
		running = screen.eventLoop();
	}
	//SDL_QUIT();
	return 0;
}