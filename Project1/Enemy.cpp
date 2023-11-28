#include "Enemy.h"
#include "Game.hpp"
#include "General.h"
#include <stdlib.h>
Enemy::Enemy(const char* texture, int x, int y, int width, int height, Player* player) : Player(texture, x, y, width, height, false)
{
	this->player = player;
}



void Enemy::Update()
{
	if (isCollided) stop();
	xpos = xpos + h_speed * deltaTime;
	ypos = ypos + v_speed * deltaTime;

	destRect.x = xpos - origin_x;
	destRect.y = ypos - origin_y;

	destHeadRect.x = destRect.x + 50;
	destHeadRect.y = destRect.y + 50;

	destHeadRect.x = destRect.x;
	destHeadRect.y = destRect.y;

	if(isAlive) aim();
	else {
		frame += deltaTime;
		if (frame > 95) destroyed = true;
		if (frame >= 10) srcRect.x = 64;
		if (frame >= 30) srcRect.x = 64 * 2;
		if (frame >= 50) srcRect.x = 64 * 3;
		if (frame >= 75) srcRect.x = 64 * 4;
	}

}

void Enemy::handleMovement()
{
	if (!isAlive) {
		stop();
		return;
	}
	double random = rand() % 2 ? 1 : 0;
	double x_direction, y_direction;
	if (player != nullptr) {
		x_direction = player->getDestRect()->x > destRect.x ? 0.1 : -0.1;
		y_direction = player->getDestRect()->y > destRect.y ? 0.1 : -0.1;
	}
	else {
		x_direction = rand() % 2 ? 0.1 : -0.1;
		y_direction = rand() % 2 ? 0.1 : -0.1;
	}

	h_speed = random * x_direction;
	v_speed = (1 - random) * y_direction;
	
	if(rand() % 3 == 0) fire();

}

void Enemy::aim()
{
	if (player == nullptr) {
		return;
	}
	int rot = General::calculateRotation(player->getDestRect()->x, player->getDestRect()->y, destRect.x, destRect.y);
	setHeadRot(rot + 90);
	
}
