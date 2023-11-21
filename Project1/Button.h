#pragma once
#include "GameObject.h"
#include "Game.hpp"
#include <functional>

class Button:public GameObject
{
public:
	Button(const char* texture, int x, int y, int w, int h);
	
	void handleInput();
	void Register(const std::function<void()>& onClick) {
		onClick_ = onClick;
	}
private:
	int xMouse, yMouse;
	std::function<void()> onClick_;
};

