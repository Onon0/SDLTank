#pragma once
#include "Player.h"
class Enemy :public Player
{
public:
	Enemy(const char* texture, int x, int y, int width, int height);
	void Update() override;
	void handleMovement();
};

