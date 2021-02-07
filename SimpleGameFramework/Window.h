#pragma once
#include<SDL.h>
#include<string>
using std::string;

class Texture;

/**
* @brief Window
* ������Ⱦ����clear��present
* �����ڵ������Ϣ
*/
class Window
{
	friend class TextureManager;
public: 
	Window(string winname, unsigned int height, unsigned int width);
	~Window();

	//����
	void clear();
	void present();

	unsigned getWidth() { return _width; }
	unsigned getHeight() { return _height; }
private:
	unsigned int _width;
	unsigned int _height;
	string _title;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	void init();
};

