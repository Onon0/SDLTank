#pragma once
#include "SDL.h"
#include "SDL_image.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y, int width, int height);
	~GameObject();
	virtual void Update();
	virtual void Render();	
	SDL_Rect* getDestRect();
	SDL_Point* getPos();
	int getID() { return id; };
	bool destroyed;
protected:
	int id;
	double xpos;
	double ypos;
	

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	
	
};

