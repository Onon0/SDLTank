#pragma once

#include "GameObject.h"
#include "Bullet.h"
#include "Enemy.h"
#include <list>
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
	
	static void spawnBullet(GameObject* obj);
	static SDL_Renderer* renderer;
	static std::list<GameObject*> sceneObjects;
	static std::list<Enemy*> enemyObjects;
	static std::list<GameObject*> bulletObjects;
private:
	
	
	SDL_Window* window;

	

	


};
