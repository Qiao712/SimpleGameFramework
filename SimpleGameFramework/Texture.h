#pragma once
#include<SDL.h>
#include"Vector.h"
/**
* @brief Texture
* 封装的纹理，仅仅是SDL_Texture的外壳
* 共享统一的SDL_Texture，由TextureManager对象创建
*/
class Texture
{
	friend class TextureManager;
public:
	Texture(SDL_Texture* texture = nullptr, SDL_Renderer* renderer = nullptr);

	//绘制
	void draw(int x, int y, int h, int w);
	void draw(int x, int y);
	void draw(int x, int y, double angle, Vector center = Vector(0,0));

	//get
	int getHeight() { return _height; }
	int getWidth() { return _width; }
private:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	int _height = 0;
	int _width = 0;
};