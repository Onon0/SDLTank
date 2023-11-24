#pragma once
#include "SDL.h"
#include "SDL_image.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int src_w, int src_h, int x, int y, int width, int height);
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

