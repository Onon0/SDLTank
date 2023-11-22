#include "Bullet.h"


Bullet::Bullet(GameObject* owner, const char* texture, double start_x, double start_y, double deg,  int x, int y, int width, int height) :GameObject(texture, x, y, width, height)
{
	this->owner = owner;
	this->start_x = start_x;
	this->start_y = start_y;
	end_x = cos(deg) + start_x;
	end_y = sin(deg) + start_y;
	distance = 0;
	vector_x = end_x - start_x;
	vector_y = end_y - start_y;
	damage = 10;
}

void Bullet::Update()
{
	
	
	
	distance = distance + deltaTime * 0.5;
	
	xpos = start_x + vector_x * distance;
	
	ypos = start_y + vector_y * distance;

	destRect.x = xpos - origin_x;
	destRect.y = ypos - origin_y;
}
