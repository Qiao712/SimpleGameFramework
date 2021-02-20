#include "Window.h"
#include "TextureManager.h"
#include "Texture.h"
#include<iostream>
using std::cout;

Window* Window::_instance = nullptr;

Window::Window(string winname, unsigned int height, unsigned int width) : _width(width), _height(height), _title(winname)
{
	//SDL初始化
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	//创建窗口
	_window = SDL_CreateWindow(_title.c_str(), 100, 100, _width, _height, SDL_WINDOW_SHOWN);
	if (_window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	//创建渲染器
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr) {
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}


void Window::clear()
{
	SDL_RenderClear(_renderer);
}

void Window::present()
{
	SDL_RenderPresent(_renderer);
}

Window* Window::instance()
{
	return _instance;
}

void Window::init(string winname, unsigned int height, unsigned int width)
{
	_instance = new Window(winname, height, width);
}
