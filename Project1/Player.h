#pragma once

#include "TextureManager.h"
#include "GameObject.h"
#include "SDL_mixer.h"
class Player:public GameObject
{
public:
	


	Player(const char* texture, int x, int y, int width, int height, bool followCamera);
	void Update() override;
	void Render() override;
	
	void stop();
	
	SDL_Rect* GetCollisionBox();
	bool getCollided() { return isCollided; };
	void setCollided(bool b) { isCollided = b; };
	
	void handleEvents();
	
	void setHeadRot(int rot) { head_rot = rot; };
	void setLife(double life) { this->life = life; };
	double getLife() { return life; };
	void fire();
	void getHit(double damage);
	void reset();
	virtual void setPos(double x, double y);
	bool isAlive;
protected:
	double v_speed;
	double h_speed;

	double speed;
	double life;
	double frame;
	int xMouse, yMouse;
	int body_rot;
	int head_rot;

	bool isCollided;
	bool followCamera;
	Mix_Chunk* shotSound;
	Mix_Chunk* deadSound;
	SDL_Texture* head;
	SDL_Texture* deadAnimation;
	SDL_Rect colRect;
	SDL_Rect srcHeadRect, destHeadRect;
};

