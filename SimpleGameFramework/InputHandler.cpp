#include "InputHandler.h"
#include<cctype>
#include<iostream>
using std::cout;

InputHandler* InputHandler::_instance = nullptr;

InputHandler* InputHandler::instance()
{
	if (_instance == nullptr) {
		_instance = new InputHandler;
	}
	return _instance;
}

void InputHandler::update()
{	
	//记录时间
	_time_last_updating = _time_curr_updating;
	_time_curr_updating = getTime();

	//获取键盘状态
	int numkeys;
	const Uint8* keystate = SDL_GetKeyboardState(&numkeys);
	_cur = !_cur;
	for (int i = 0; i < numkeys; i++) {
		_keystate[_cur][i] = keystate[i];
	}

	//清理鼠标状态
	_button_clicks[0] = _button_clicks[1] = _button_clicks[2] = 0;

	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_MOUSEMOTION: {
			_x_cursor = event.motion.x;
			_y_cursor = event.motion.y;
			break;
		}
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN: {
			_button_state[event.button.which] = event.button.state;
			_button_clicks[event.button.which] = event.button.clicks;
			break;
		}
		}
	}
}

int InputHandler::ASCIIToScancode(char c)
{
	const int dis_upper = SDL_SCANCODE_A - 'A';	//ASCII到键盘SDL_SCANCODE
	const int dis_lower = SDL_SCANCODE_A - 'a';

	if (isupper(c)) {
		return c + dis_upper;
	}

	if (islower(c)) {
		return c + dis_lower;
	}

	return -1;
}

unsigned int InputHandler::getTime()
{
	return SDL_GetTicks();
}

bool InputHandler::getKeyState(int key)
{
	int scancode = ASCIIToScancode(key);

	if (scancode == -1) return false;

	return _keystate[_cur][scancode];
}

int InputHandler::getKeyChange(int key)
{
	int scancode = ASCIIToScancode(key);

	if (scancode == -1) return false;

	if (_keystate[_cur][scancode]) {
		if (_keystate[!_cur][scancode]) {
			return UNCHANGE;
		}
		else {
			return DOWN;
		}
	}
	else {
		if (_keystate[!_cur][scancode]) {
			return UP;
		}
		else {
			return UNCHANGE;
		}
	}
}
