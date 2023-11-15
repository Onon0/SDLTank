#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include <vector>
#include <iostream>

extern double origin_x;
extern double origin_y;

extern int screen_width;
extern int screen_height;
extern bool isRunning;
extern double deltaTime;

extern double stime;


class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void update();
	void render();
	void clean();
	
	static void spawn(GameObject* obj);
	static SDL_Renderer* renderer;
	static std::vector<GameObject*> sceneObjects;
	static std::vector<Enemy*> enemyObjects;
private:
	
	
	SDL_Window* window;

	

	


};
