#include "GameObject.h"
#include "TextureManager.h"
#include "Camera.h"
GameObject::GameObject(const char* texturesheet, int x, int y, int width, int height)
{
	
	this->objTexture = TextureManager::loadTexture(texturesheet);
	xpos = x;
	ypos = y;
	srcRect.h = 153;
	srcRect.w = 153;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = width;
	destRect.h = height;
	
}
void GameObject::Update() {

	
	
	destRect.x = xpos - origin_x;
	destRect.y = ypos - origin_y; 
	
	
	
}

SDL_Rect* GameObject::getDestRect()
{
	return &destRect;
}
void GameObject::Render() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(Game::renderer, &destRect);

	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
