#pragma once
#include "Player.h"
class Enemy :public Player
{
public:
	Enemy(const char* texture, int x, int y, int width, int height, Player *player);
	void Update() override;
	void handleMovement();

	void aim();
	Player* player;
};

