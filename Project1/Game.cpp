#include "Game.hpp"
#include "TextureManager.h"
#include "General.h"
#include <cmath>
std::vector<GameObject*> Game::sceneObjects;
std::vector<Enemy*> Game::enemyObjects;

Player* player;

SDL_Renderer* Game::renderer = nullptr;
double origin_x = 0;
double origin_y = 0;

int screen_width = 600;
int screen_height = 600;

double deltaTime = 0;
double stime = 0;
bool isRunning = true;
Game::Game()
{
	
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { isRunning = false; return; }
	
	std::cout << "Subsystem Initialized!..." << std::endl;
	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window) {
		std::cout << "Window created..." << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		std::cout << "Render Created..." << std::endl;
	}
	
	isRunning = true;

	player = new Player("assets/volume_ellipse.png", 0,-100, 100,100, true);
	
	
	
	for (int i = 0; i < 10; i++) {
		Game:: sceneObjects.push_back(new GameObject("assets/volume_ellipse.png", 120 * i, 200 + 120 * i, 100, 100));
	}

	for (int i = 0; i < 5; i++) {
		Game::enemyObjects.push_back(new Enemy("assets/volume_ellipse.png", 120 * i, 400 + 110 * i, 100, 100));
	}

}



void Game::update()
{
	player->handleEvents();
	
	player->setCollided(false);
	for (int i = 0; i < sceneObjects.size(); i++){
		
		sceneObjects[i]->Update();
		if (General::collisionCheck(player->GetCollisionBox(), sceneObjects[i]->getDestRect())) {
			player->setCollided(true);
		}
	}
	for (Enemy* enemy : enemyObjects) {
		enemy->Update();
	}
	player->Update();
	if((int)ceil(stime) % 2 == 0)
	{
		for (Enemy* enemy : enemyObjects) {
			enemy->handleMovement();
		}
	}
		
}

void Game::render()
{
	SDL_RenderClear(renderer);
	player->Render();
	for (GameObject* go: sceneObjects) {
		go->Render();
	}

	for(Enemy* enemy: enemyObjects) {
		enemy->Render();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}

void Game::spawn(GameObject* obj)
{
	sceneObjects.push_back(obj);
}
