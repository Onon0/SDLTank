#pragma once

#include "TextureManager.h"
#include "GameObject.h"
class Player:public GameObject
{
public:
	Player(const char* texture, int x, int y, int width, int height);
	void Update() override;
	void Render() override;
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void stop();
	SDL_Rect* GetCollisionBox();
	void handleEvents();
	void setHeadRot(int rot) { head_rot = rot; };
private:
	double v_speed;
	double h_speed;
	int xMouse, yMouse;
	int head_rot;
	SDL_Texture* head;
	SDL_Rect colRect;
	SDL_Rect srcHeadRect, destHeadRect;
};

