#include "Player.h"
#include "General.h"
#include "Bullet.h"
#include <stdlib.h>

double temp = 0;
int speed_up = 300;
Player::Player(const char* texture, int x, int y, int width, int height, bool followCamera) :GameObject(texture, 128, 128, x, y, width, height)
{
	h_speed = v_speed = 0;
	head_rot = 0;
	body_rot = 0;
	speed = 0.2;
	
	life = 100;
	srcHeadRect.h = 64;
	srcHeadRect.w = 64;
	srcHeadRect.x = 0;
	srcHeadRect.y = 0;

	destHeadRect.w = width;
	destHeadRect.h = height;

	colRect.x = destRect.x;
	colRect.y = destRect.y;
	colRect.w = destRect.w;
	colRect.h = destRect.h;
	
	this->followCamera = followCamera;
	if (followCamera) {
		origin_x = x - static_cast<double>(screen_width / 2) + destRect.w * 0.5;
		origin_y = y - static_cast<double>(screen_height / 2) + destRect.h * 0.5;
	}
	
	isCollided = false;

	head = IMG_LoadTexture(Game::renderer, "assets/tank_top.png");
	
}



void Player::Update()
{
	temp += deltaTime;
	if (isCollided) return;
	origin_x = origin_x + h_speed * deltaTime;
	origin_y = origin_y + v_speed * deltaTime;
	
	xpos =  xpos + h_speed * deltaTime;
	ypos =  ypos + v_speed * deltaTime;

	destRect.x = xpos - origin_x;
	destRect.y = ypos - origin_y;

	destHeadRect.x = destRect.x;
	destHeadRect.y = destRect.y;

	
	
}

void Player::Render()
{
	//SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	//SDL_RenderDrawRect(Game::renderer, &destRect);
	//SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect(Game::renderer, &colRect);
	//SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	if(!(h_speed == 0 && v_speed == 0))
		body_rot = h_speed == 0 ? 0 : 90;

	SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, body_rot ,NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(Game::renderer, head, &srcHeadRect, &destHeadRect, head_rot, NULL, SDL_FLIP_NONE);
}


void Player::stop()
{
	h_speed = v_speed = 0;
}

SDL_Rect* Player::GetCollisionBox()
{
	if (&destRect == nullptr) return nullptr;
	
	colRect.x = xpos + h_speed * 10 -origin_x;
	colRect.y = ypos + v_speed * 10 -origin_y;
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
	case SDL_MOUSEBUTTONDOWN:
		if (temp > 500) {
			temp =0;
			fire();
		}
		
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
		case SDLK_a:
			h_speed = -speed;
			v_speed = 0;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			h_speed = speed;
			v_speed = 0;
			break;

		case SDLK_UP:
		case SDLK_w:
			v_speed = -speed;
			h_speed = 0;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			v_speed = speed;
			h_speed = 0;
			break;
		case SDLK_LSHIFT:
		
			if (speed_up > 0) {
				speed_up--;
				speed = 0.4;
			}
			else {
				speed = 0.2;
			}
			
			break;
		}
	

		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
		case SDLK_a:
			h_speed = 0;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			h_speed = 0;
			break;

		case SDLK_UP:
		case SDLK_w:
			v_speed = 0;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			v_speed = 0;
			break;
		case SDLK_LSHIFT:
			speed = 0.2;
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

void Player::fire()
{
//spawn bullet
	double rad = General::deg2rad(head_rot - 90);
	double b_x = origin_x + screen_width/2 + cosf(rad)  * 100;
	double b_y = origin_y + screen_height / 2 + sinf(rad) * 100;
	
	Bullet* bullet = new Bullet(this, "assets/bullet.png", xpos + destRect.w/2, ypos + destRect.h / 2, rad, b_x, b_y, 20, 20);
	
	Game::spawnBullet(bullet);
}

void Player::getHit(double damage)
{
	life -= damage;
	if (life <= 0) destroyed = true;
}

void Player::setPos(double x, double y)
{
	xpos = x;
	ypos = y;
	if (followCamera) {
		origin_x = x - static_cast<double>(screen_width / 2) + destRect.w * 0.5;
		origin_y = y - static_cast<double>(screen_height / 2) + destRect.h * 0.5;
	}

}




