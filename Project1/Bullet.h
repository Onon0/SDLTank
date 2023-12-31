#pragma once
#include "GameObject.h"
#include "Game.hpp"
class Bullet: public GameObject
{
public:
	Bullet(GameObject* owner, const char* texture, double start_x, double start_y, double deg, int x, int y, int width, int height);
	void Update() override;
	double getDistance() { return distance; };
	double getDamage() { return damage; };
	bool hitTarget;
	GameObject* owner;
private:
	double start_x;
	double start_y;
	double end_x;
	double end_y;
	double vector_x;
	double vector_y;
	double distance;
	double damage;
};

