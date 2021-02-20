#pragma once
#include<SDL.h>
#include<string>
using std::string;

class Texture;

/**
* @brief Window
* Singleton
* 管理渲染器的clear、present
* 管理窗口的相关信息
*/
class Window
{
	friend class TextureManager;
public:
	static Window* instance();
	static void init(string winname, unsigned int height, unsigned int width);

	~Window();

	//绘制
	void clear();
	void present();

	unsigned getWidth() { return _width; }
	unsigned getHeight() { return _height; }
	string getTitle() { return _title; }
private:
	static Window* _instance;

	Window(string winname, unsigned int height, unsigned int width);

	unsigned int _width;
	unsigned int _height;
	string _title;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};

