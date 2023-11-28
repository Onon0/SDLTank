#include "Game.hpp"
#include "TextureManager.h"
#include "General.h"
#include "Bullet.h"
#include "Button.h"
#include "Map.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <cmath>
#include <string>
std::list<GameObject*> Game::sceneObjects;
std::vector<Enemy*> Game::enemyObjects;
std::vector<GameObject*> Game::bulletObjects;
Player* player;

SDL_Renderer* Game::renderer = nullptr;
double origin_x = 0;
double origin_y = 0;

int screen_width = 600;
int screen_height = 600;

double deltaTime = 0;
double stime = 0;
bool isRunning = true;
bool isPlaying = false;
Map* map = new Map();
int cool_off = -1;
Button* button;

TTF_Font* font;
SDL_Texture* lifeDisplay;

int spawnCount = 0;
bool showSpawn = false;
SDL_Texture* spawnCountDisplay;
int spawnAvailable = -1;

Mix_Chunk* music = NULL;

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
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	music = Mix_LoadWAV("assets/bg_music.wav");
	std::cout << "Subsystem Initialized!..." << std::endl;
	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window) {
		std::cout << "Window created..." << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		std::cout << "Render Created..." << std::endl;
	}
	
	isRunning = true;
	player = new Player("assets/tank.png", 0, 0, 128, 128, true);
	

	//initiliaze reset button
	button = new Button("assets/volume_ellipse.png", screen_width/2 - 150, screen_height/2 - 50, 300, 100);
	button->Register(std::bind(&Game::reset, this));
	//open font
	if (TTF_Init() < 0) {
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
	}

	font = TTF_OpenFont("assets/bahnschrift.ttf", 48);
	if (!font) {
		std::cout << "Failed to open Font\n";
	}
	
	isPlaying = false;

	Mix_PlayChannel(-1, music, -1);
	
}



void Game::update()
{
	
	if (!isPlaying) {
		button->handleInput();
		return;
	}

	if (player->destroyed) {
		isPlaying = false;

	}

	player->handleEvents();
	
	player->setCollided(false);
	int i = 0;

	for (GameObject* go : sceneObjects){
		
		go->Update();
		if (General::collisionCheck(player->GetCollisionBox(), go->getDestRect())) {
			player->setCollided(true);
		}
	}
	if (enemyObjects.size() > 0) {
		i = 0;
		while (i < enemyObjects.size()) {
			enemyObjects[i]->setCollided(false);
			if (General::collisionCheck(player->GetCollisionBox(), enemyObjects[i]->GetCollisionBox())) {
				enemyObjects[i]->setCollided(true);
				player->setCollided(true);
			}

			for (GameObject* go : sceneObjects) {
				if (General::collisionCheck(enemyObjects[i]->GetCollisionBox(), go->getDestRect())) {
					enemyObjects[i]->setCollided(true);
				}
			}

			for (Enemy* other : enemyObjects) {
				if (enemyObjects[i] != other) {
					if (General::collisionCheck(enemyObjects[i]->GetCollisionBox(), other->GetCollisionBox())) {
						enemyObjects[i]->setCollided(true);
					}
				}
			}
			//if enemy object not destroyed index++ and updated
			if (!enemyObjects[i]->destroyed) {
				enemyObjects[i]->Update();
				i++;
			}
			//if enemy destroyed index same; remove from vector
			else {
				GameObject* temp_enemy =  enemyObjects[i];
				enemyObjects.erase(enemyObjects.begin() + i);

				
				
			}
		}
	}
	
	
	
	if (bulletObjects.size() > 0) {
		i = 0;
		


			while (i < bulletObjects.size()) {
				bulletObjects[i]->Update();
				if (!dynamic_cast<Bullet*>(bulletObjects[i])->hitTarget) {
					//bullet object interaction
					for (GameObject* go : sceneObjects) {
						if (General::collisionCheck(bulletObjects[i]->getDestRect(), go->getDestRect())) {

							//mark hit target bullet;
							dynamic_cast<Bullet*>(bulletObjects[i])->hitTarget = true;
						}

					}
					//bullet enemy interactiion
					for (Enemy* enemy : enemyObjects) {
						if (General::collisionCheck(bulletObjects[i]->getDestRect(), enemy->getDestRect()) && dynamic_cast<Bullet*>(bulletObjects[i])->owner->getID() != enemy->getID()) {

							//mark hit target bullet;
							dynamic_cast<Bullet*>(bulletObjects[i])->hitTarget = true;
							//enemy damage
							enemy->getHit(dynamic_cast<Bullet*>(bulletObjects[i])->getDamage());
						}
					}
					//bullet player interaction
					if (General::collisionCheck(bulletObjects[i]->getDestRect(), player->getDestRect()) && dynamic_cast<Bullet*>(bulletObjects[i])->owner->getID() != player->getID()) {
						//mark hit target bullet;
						dynamic_cast<Bullet*>(bulletObjects[i])->hitTarget = true;
						//player damage
						player->getHit(dynamic_cast<Bullet*>(bulletObjects[i])->getDamage());
						lifeDisplay = TextureManager::loadText(std::to_string(int(player->getLife())).c_str(), font);
						//if (player->destroyed) {
						//	isPlaying = false;

						//}

					}
				}
				if (!bulletObjects[i]->destroyed) i++;
				else {
					bulletObjects.erase(bulletObjects.begin() + i);
				}
			}
		
	}
	player->Update();


	if((int)ceil(stime) % 2 == 0)
	{
		if (cool_off != (int)ceil(stime)) {
			cool_off = (int)ceil(stime);
			
			for (Enemy* enemy : enemyObjects) {

				enemy->handleMovement();

			}
		}
		
	}
	
	if ((int)ceil(stime) % 10 == 0) {
		
		if (spawnAvailable != (int)ceil(stime)) {
			showSpawn = true;
			spawnAvailable = (int)ceil(stime);
			std::cout << "new wave" << std::endl;
			spawnWave();

		}
		
		
	}
	else {
		showSpawn = false;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	for (GameObject* bullet : bulletObjects) {
		bullet->Render();


	}
	
	player->Render();


	for (GameObject* go: sceneObjects) {
		go->Render();
	}

	for(Enemy* enemy: enemyObjects) {
		enemy->Render();
	}
	
	if (!isPlaying) {
		button->Render();
	}
	
	SDL_Rect dest = { 0, 0, 200, 100 };
	if (isPlaying) {
		SDL_RenderCopy(renderer, lifeDisplay, NULL, &dest);
		dest = { screen_height / 2 - 225, screen_height / 2 - 150, 450, 300 };
		if (showSpawn) SDL_RenderCopy(renderer, spawnCountDisplay, NULL, &dest);
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	
	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}

void Game::reset()
{
	sceneObjects.clear();
	enemyObjects.clear();
	player->reset();
	lifeDisplay = TextureManager::loadText(std::to_string(int(player->getLife())).c_str(), font);

	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map->grid[i][j] == 1) {
				Game::sceneObjects.push_back(new GameObject("assets/volume_ellipse.png", 128, 128, 128 * i, 128 * j, 128, 128));
			}
			if (map->grid[i][j] == 2) {
				Game::enemyObjects.push_back(new Enemy("assets/tank.png", 128 * i, 128 * j, 128, 128, player));
			}
			if (map->grid[i][j] == 3) {
				player->setPos(i * 128, j * 128);
			}
		}
	}
	isPlaying = true;
}

void Game::spawnBullet(GameObject* obj)
{
	
	bulletObjects.push_back(obj);
}
void Game::spawnWave() {
	spawnCount++;
	spawnCountDisplay = TextureManager::loadText(("Wave " + std::to_string(spawnCount)).c_str(), font);
	int i = rand() % 10;
	int j = rand() % 10;
	int count = 0;
	while (count < 4) {
		i++;
		if (i > 10) i = 0;
		j++;
		if (j > 10) j = 0;

		if (map->grid[i][j] == 0) {
			SDL_Point point = { i * 128, j * 128 };
			if (General::pointDistance(player->getPos(), &point) > 200) {
				Game::enemyObjects.push_back(new Enemy("assets/tank.png", 128 * i, 128 * j, 128, 128, player));
				count++;
			}
			
		}
		
	}
		
		

}
	
