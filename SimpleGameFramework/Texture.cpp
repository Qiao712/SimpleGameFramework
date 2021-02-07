#include "Texture.h"
#include "TextureManager.h"
#include<iostream>
using std::cout;

Texture::Texture(SDL_Texture* texture, SDL_Renderer* renderer) : _texture(texture), _renderer(renderer)
{
	if (texture == nullptr) {
		_height = 0;
		_width = 0;
		return;
	}
	int height, width;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	_height = height;
	_width = width;
}

void Texture::draw(int x, int y, int h, int w)
{
	static SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = h;
	dst.w = w;

	SDL_RenderCopy(_renderer, _texture, nullptr, &dst);
}

void Texture::draw(int x, int y)
{
	static SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = _height;
	dst.w = _width;

	//cout << "Draw texture:" << _texture << " h: "<<_height<<" w:"<<_width<<" at"<<_renderer<<std::endl;
	SDL_RenderCopy(_renderer, _texture, nullptr, &dst);
}

void Texture::draw(int x, int y, double angle, Vector center)
{
	static SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.h = _height;
	dst.w = _width;

	SDL_Point sdl_center;
	sdl_center.x = center.x;
	sdl_center.y = center.y;

	SDL_RenderCopyEx(_renderer, _texture, nullptr, &dst, angle,  &sdl_center, SDL_FLIP_NONE);
}