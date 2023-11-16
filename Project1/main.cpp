#include "Game.hpp"
#include <SDL_timer.h>
Game* game = nullptr;

Uint32 timerCall(Uint32 interval, void* name) {
	std::cout << "fds" << std::endl;
	return 0;
}
int main(int argc, char* argv[]) {
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	
	
	game = new Game();
	game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, false);

	
	while (isRunning) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		
		stime = (NOW)/SDL_GetPerformanceFrequency();
		game->update();
		game->render();
	}
	

	game->clean();

	return 0;
}