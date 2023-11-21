#include "Button.h"
#include "General.h"
#include "Game.hpp"
#include "SDL.h"
#include <iostream>

Button::Button(const char* texture, int x, int y, int w, int h) :GameObject(texture, x, y, w, h)
{
	destRect.x = x;
	destRect.y = y;
}

void Button::handleInput()
{
	SDL_GetMouseState(&xMouse, &yMouse);
	SDL_Point point;
	point.x = xMouse;
	point.y = yMouse;
	
	
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (SDL_PointInRect(&point, &destRect)) {
			onClick_();
		}
		break;
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}


