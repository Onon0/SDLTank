#include "GameObject.h"
#include "Game.hpp"
#include "TextureManager.h"
#include "Camera.h"
#include <chrono>
GameObject::GameObject(const char* texturesheet, int src_w, int src_h, int x, int y, int width, int height)
{
	
	this->objTexture = TextureManager::loadTexture(texturesheet);
	id = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	xpos = x;
	ypos = y;
	srcRect.h = src_h;
	srcRect.w = src_w;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = width;
	destRect.h = height;
	destroyed = false;

	
}
void GameObject::Update() {

	
	
	destRect.x = xpos - origin_x;
	destRect.y = ypos - origin_y; 
	
	
	
}

SDL_Rect* GameObject::getDestRect()
{
	return &destRect;
}
SDL_Point* GameObject::getPos()
{
	SDL_Point point;
	point.x = xpos;
	point.y = ypos;
	return &point;
}
void GameObject::Render() {
	//SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	//SDL_RenderDrawRect(Game::renderer, &destRect);

	//SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}


