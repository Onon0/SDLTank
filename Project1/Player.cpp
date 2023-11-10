#include "Player.h"
#include "General.h"
#include <stdlib.h>

Player::Player(const char* texture, int x, int y, int width, int height) :GameObject(texture, x, y, width, height)
{
	h_speed = v_speed = 0;
	head_rot = 0;

	

	srcHeadRect.h = 64;
	srcHeadRect.w = 64;
	srcHeadRect.x = 0;
	srcHeadRect.y = 0;

	destHeadRect.w = 64;
	destHeadRect.h = 64;

	
	xpos = static_cast<double>(screen_width / 2) - static_cast<double>(srcRect.w / 2);
	ypos = static_cast<double>(screen_height / 2) - static_cast<double>(srcRect.h / 2);



	

	head = IMG_LoadTexture(Game::renderer, "assets/test.png");
	
}



void Player::Update()
{
	

	origin_x = origin_x + h_speed * deltaTime;
	origin_y = origin_y + v_speed * deltaTime;
	
	xpos =   xpos + h_speed * deltaTime;
	ypos =  ypos + v_speed * deltaTime;

	destRect.x = xpos - origin_x;
	destRect.y = ypos - origin_y;

	destHeadRect.x = destRect.x + 50;
	destHeadRect.y = destRect.y + 50;

	
	
}

void Player::Render()
{
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(Game::renderer, &destRect);
	SDL_RenderDrawRect(Game::renderer, &colRect);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	SDL_RenderCopyEx(Game::renderer, head, &srcHeadRect, &destHeadRect, head_rot, NULL, SDL_FLIP_NONE);
}

void Player::moveRight()
{
		
	h_speed = 1;

	
	
}

void Player::moveLeft()
{
	
	h_speed = -1;
}

void Player::moveUp()
{
	
	v_speed = -1;
}

void Player::moveDown()
{
	
	v_speed = 1;
}

void Player::stop()
{
	h_speed = v_speed = 0;
}

SDL_Rect* Player::GetCollisionBox()
{
	if (&destRect == nullptr) return nullptr;
	colRect.x = destRect.x;
	colRect.y = destRect.y;
	colRect.w = destRect.w;
	colRect.h = destRect.h;
	colRect.x = xpos + h_speed * deltaTime - origin_x;
	colRect.y = ypos + v_speed * deltaTime - origin_y;
	return &colRect;
}

void Player::handleEvents()
{
	SDL_GetMouseState(&xMouse, &yMouse);
	int rot = General::calculateRotation(xMouse, yMouse, screen_width / 2, screen_height / 2);
	setHeadRot(rot + 90);
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			moveLeft();
			break;
		case SDLK_RIGHT:
			moveRight();
			break;

		case SDLK_UP:
			moveUp();
			break;
		case SDLK_DOWN:
			moveDown();
			break;
		}
	

		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			h_speed = 0;
			break;
		case SDLK_RIGHT:
			h_speed = 0;
			break;

		case SDLK_UP:
			v_speed = 0;
			break;
		case SDLK_DOWN:
			v_speed = 0;
			break;
		}


		break;
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}




