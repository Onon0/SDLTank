#pragma once

#include "GameObject.h"
#include <vector>
#include <iostream>
extern double origin_x;
extern double origin_y;

extern int screen_width;
extern int screen_height;
extern bool isRunning;
extern double deltaTime;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void update();
	void render();
	void clean();
	
	
	static SDL_Renderer* renderer;
	std::vector<GameObject*> sceneObjects;
private:
	
	
	SDL_Window* window;

	

	


};
