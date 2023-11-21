#pragma once
#include "General.h"
#include "SDL_ttf.h"
class TextureManager
{
public:
	static SDL_Texture* loadTexture(const char* path);
	static SDL_Texture* loadText(const char* text, TTF_Font* font);
};

