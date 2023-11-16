#include "Game.hpp"
#include "TextureManager.h"
#include "General.h"
#include <cmath>
std::list<GameObject*> Game::sceneObjects;
std::list<Enemy*> Game::enemyObjects;
std::list<GameObject*> Game::bulletObjects;
Player* player;

SDL_Renderer* Game::renderer = nullptr;
double origin_x = 0;
double origin_y = 0;

int screen_width = 600;
int screen_height = 600;

double deltaTime = 0;
double stime = 0;
bool isRunning = true;

int temp = -1;
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
	

	for (GameObject* go : sceneObjects){
		
		go->Update();
		if (General::collisionCheck(player->GetCollisionBox(), go->getDestRect())) {
			player->setCollided(true);
		}
	}
	for (Enemy* enemy : enemyObjects) {
		enemy->setCollided(false);
		if (General::collisionCheck(player->GetCollisionBox(), enemy->GetCollisionBox())) {
			enemy->setCollided(true);
			player->setCollided(true);
		}

		for (GameObject* go : sceneObjects) {
			if (General::collisionCheck(enemy->GetCollisionBox(), go->getDestRect())) {
				enemy->setCollided(true);
			}
		}

		for (Enemy* other : enemyObjects) {
			if (enemy != other) {
				if (General::collisionCheck(enemy->GetCollisionBox(), other->GetCollisionBox())) {
					enemy->setCollided(true);
				}
			}
		}

		enemy->Update();
	}
	for (GameObject* bullet : bulletObjects) {
		bullet->Update();

		for (GameObject* go : sceneObjects) {
			if (General::collisionCheck(bullet->getDestRect(), go->getDestRect())) {
				sceneObjects.remove(go);
				bulletObjects.remove(bullet);
				break;
			}
		}
	}

	
	
	player->Update();


	if((int)ceil(stime) % 2 == 0)
	{
		if (temp != (int)ceil(stime)) {
			temp = (int)ceil(stime);
			
			for (Enemy* enemy : enemyObjects) {

				enemy->handleMovement();
			}
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

	for (GameObject* bullet : bulletObjects) {
		bullet->Render();
		
		
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

void Game::spawnBullet(GameObject* obj)
{
	
	bulletObjects.push_back(obj);
}
