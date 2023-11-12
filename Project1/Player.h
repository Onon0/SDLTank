#pragma once

#include "TextureManager.h"
#include "GameObject.h"
class Player:public GameObject
{
public:
	
	Game* game;

	Player(const char* texture, int x, int y, int width, int height);
	void Update() override;
	void Render() override;
	
	void stop();
	
	SDL_Rect* GetCollisionBox();

	
	void handleEvents();
	
	void setHeadRot(int rot) { head_rot = rot; };

	void fire();
private:
	double v_speed;
	double h_speed;

	double speed;

	int xMouse, yMouse;
	int head_rot;
	SDL_Texture* head;
	SDL_Rect colRect;
	SDL_Rect srcHeadRect, destHeadRect;
};

