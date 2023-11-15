#include "TextureManager.h"
#include "Game.hpp"
SDL_Texture* TextureManager::loadTexture(const char* path)
{
	return IMG_LoadTexture(Game::renderer, path);
}
