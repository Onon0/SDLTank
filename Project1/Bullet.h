#pragma once
#include "GameObject.h"
#include "Game.hpp"
class Bullet: public GameObject
{
public:
	Bullet(const char* texture, double start_x, double start_y, double deg, int x, int y, int width, int height);
	void Update() override;
private:
	double start_x;
	double start_y;
	double end_x;
	double end_y;
	double vector_x;
	double vector_y;
	double distance;
};

