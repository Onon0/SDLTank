#include "Bullet.h"


Bullet::Bullet(GameObject* owner, const char* texture, double start_x, double start_y, double deg,  int x, int y, int width, int height) :GameObject(texture, 64 ,320, x, y, width, height)
{
	this->owner = owner;
	this->start_x = start_x;
	this->start_y = start_y;
	end_x = cos(deg) + start_x;
	end_y = sin(deg) + start_y;
	distance = 20;
	vector_x = end_x - start_x;
	vector_y = end_y - start_y;
	damage = 10;
	hitTarget = false;
}

void Bullet::Update()
{
	if (!hitTarget) {

		distance = distance + deltaTime * 0.5;
	
		xpos = start_x + vector_x * distance;
	
		ypos = start_y + vector_y * distance;

		destRect.x = xpos - origin_x;
		destRect.y = ypos - origin_y;
	}
	else {
		if (destRect.w > 50) destroyed = true;
		destRect.x = xpos - origin_x;
		destRect.y = ypos - origin_y;
		destRect.w += deltaTime * 5;
		destRect.h += deltaTime * 5;

		if (destRect.w == 25) srcRect.x = 64;
		if (destRect.w == 30) srcRect.x = 64 * 2;
		if (destRect.w == 35) srcRect.x = 64 * 3;
		if (destRect.w == 45) srcRect.x = 64 * 4;
	}
}
