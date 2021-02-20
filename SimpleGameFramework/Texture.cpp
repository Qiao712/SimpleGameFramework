#include "Texture.h"
#include "TextureManager.h"
#include "Camera.h"
#include<cmath>
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

void Texture::draw(Point position, int w, int h, double angle, Vector center, int flip, CROOD crood)
{
	static Camera* camera = Camera::instance();
	if (crood == WORLD_CROOD) position = camera->transform2win(position);	//如果给入的是，世界坐标系，则转到屏幕坐标系

	static SDL_Rect dst;
	dst.x = round(position.x);
	dst.y = round(position.y);
	dst.h = h;
	dst.w = w;

	SDL_Point sdl_center;
	sdl_center.x = round(center.x);
	sdl_center.y = round(center.y);

	switch (flip) {
	case FLIP_NONE:
		SDL_RenderCopyEx(_renderer, _texture, nullptr, &dst, angle, &sdl_center, SDL_FLIP_NONE);
		break;
	case FLIP_HORIZONTAL:
		SDL_RenderCopyEx(_renderer, _texture, nullptr, &dst, angle, &sdl_center, SDL_FLIP_HORIZONTAL);
		break;
	case FLIP_VERTICAL:
		SDL_RenderCopyEx(_renderer, _texture, nullptr, &dst, angle, &sdl_center, SDL_FLIP_VERTICAL);
		break;
	case FLIP_BOTH:
		SDL_RenderCopyEx(_renderer, _texture, nullptr, &dst, angle, &sdl_center, (SDL_RendererFlip)(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL));
	}
}

void Texture::draw(Point position, int w, int h, CROOD crood)
{
	static Camera* camera = Camera::instance();
	if (crood == WORLD_CROOD) position = camera->transform2win(position);	//如果给入的是，世界坐标系，则转到屏幕坐标系

	static SDL_Rect dst;
	dst.x = round(position.x);
	dst.y = round(position.y);
	dst.h = h;
	dst.w = w;

	SDL_RenderCopy(_renderer, _texture, nullptr, &dst);
}

void Texture::draw(Point position, double angle, Vector center, int flip, CROOD crood)
{
	draw(position, _width, _height, angle, center, flip, crood);
}

void Texture::draw(Point position, CROOD crood)
{
	draw(position, _width, _height, crood);
}