#include "TextureManager.h"
#include "Game.hpp"

SDL_Texture* TextureManager::loadTexture(const char* path)
{
	return IMG_LoadTexture(Game::renderer, path);
}

SDL_Texture* TextureManager::loadText(const char* text, TTF_Font *font)
{
	
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}
