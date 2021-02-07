#pragma once
#include<SDL.h>
#include"Vector.h"
/**
* @brief Texture
* ��װ������������SDL_Texture�����
* ����ͳһ��SDL_Texture����TextureManager���󴴽�
*/
class Texture
{
	friend class TextureManager;
public:
	Texture(SDL_Texture* texture = nullptr, SDL_Renderer* renderer = nullptr);

	//����
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