#include "Game.hpp"

Game* game = nullptr;


int main(int argc, char* argv[]) {
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	
	
	game = new Game();
	game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, false);
	while (isRunning) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		stime += deltaTime/1000;
		
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}