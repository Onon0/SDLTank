#pragma once
#include "SDL.h"

enum Direction { up,down, right, left };
class General
{
public:
	static float calculateRotation(int mouseX, int mouseY, int centerX, int centerY);
	static bool collisionCheck(SDL_Rect* A, SDL_Rect* B);
	static float deg2rad(float deg);
	static float calculateDistance(int x1, int y1, int x2, int y2);
	static float pointDistance(SDL_Point* A, SDL_Point* B);
};

