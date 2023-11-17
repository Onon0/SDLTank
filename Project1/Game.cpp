#include "Game.hpp"
#include "TextureManager.h"
#include "General.h"
#include "Bullet.h"
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

	player = new Player("assets/tank.png", 0,-100, 128,128, true);
	
	
	
	for (int i = 0; i < 10; i++) {
		Game:: sceneObjects.push_back(new GameObject("assets/volume_ellipse.png", 200 * i, 200 + 200 * i, 128, 128));
	}

	for (int i = 0; i < 5; i++) {
		Game::enemyObjects.push_back(new Enemy("assets/tank.png", 200 * i, 400 + 200 * i, 128, 128, player));
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
	std::list<GameObject*>::iterator i = bulletObjects.begin();
	
	while (i != bulletObjects.end()) {
		(*i)->Update();
		
		bool b = false;
		//destroy bullet after certain distance
		if (dynamic_cast<Bullet*>(*i)->getDistance() > 500) {
			bulletObjects.erase(i++);
			b = true;
		}
		//player hit
		if (General::collisionCheck(player->getDestRect(), (*i)->getDestRect())) {
			if (dynamic_cast<Bullet*>(*i)->owner->getID() != player->getID()) {
			
				

				//hit player
				player->getHit(dynamic_cast<Bullet*>(*i)->getDamage());
				std::cout << player->getLife() << std::endl;
				if (player->getLife() == 0) {
					std::cout << "game over" << std::endl;
				}
				bulletObjects.erase(i++);
				b = true;
			}//*/
			
		}

		//destoy bullet if hit obstacle.
		for (GameObject* go : sceneObjects) {
			if (General::collisionCheck((*i)->getDestRect(), go->getDestRect())) {
				sceneObjects.remove(go);
				bulletObjects.erase(i++);
				
				b = true;
				break;
				
			}

		}

		for (Enemy* enemy : enemyObjects) {
			if (General::collisionCheck((*i)->getDestRect(), enemy->getDestRect())) {
				
				//hit enemy damage
				if (dynamic_cast<Bullet*>(*i)->owner->getID() != enemy->getID()) {
					enemy->getHit(dynamic_cast<Bullet*>(*i)->getDamage());
					//enemy dies
					if (enemy->getLife() == 0) enemyObjects.remove(enemy);
					bulletObjects.erase(i++);
					b = true;
					break;
				}
					
				
				

			}

		}


		if (!b) i++;
		
	}

	//*/
	
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
