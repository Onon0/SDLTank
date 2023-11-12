#pragma once
#include "SDL.h"

enum Direction { up,down, right, left };
class General
{
public:
	static float calculateRotation(int mouseX, int mouseY, int centerX, int centerY);
	static bool collisionCheck(SDL_Rect* A, SDL_Rect* B);
	static float deg2rad(float deg);
};

