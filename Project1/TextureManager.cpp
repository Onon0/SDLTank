#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* path)
{
	return IMG_LoadTexture(Game::renderer, path);
}
