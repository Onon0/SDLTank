#include "Enemy.h"
#include "Game.hpp"
#include <stdlib.h>
Enemy::Enemy(const char* texture, int x, int y, int width, int height) : Player(texture, x, y, width, height, false)
{
	colRect.x = destRect.x;
	colRect.y = destRect.y;
	colRect.w = destRect.w;
	colRect.h = destRect.h;
}

void Enemy::Update()
{

	xpos = xpos + h_speed * deltaTime;
	ypos = ypos + v_speed * deltaTime;

	destRect.x = xpos - origin_x;
	destRect.y = ypos - origin_y;

	destHeadRect.x = destRect.x + 50;
	destHeadRect.y = destRect.y + 50;



}

void Enemy::handleMovement()
{
	h_speed = rand()%2 ? 1: -1;
	h_speed = h_speed * deltaTime;

}
