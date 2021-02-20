#include "Animation.h"
#include "InputHandler.h"
#include "Camera.h"
#include<iostream>

Animation::Animation(int width_frame, int interval, SDL_Texture* texture, SDL_Renderer* renderer):
	Texture(texture, renderer), _width_frame(width_frame), _interval(interval)
{
	if (_width_frame != 0)
		_num_frame = _width / _width_frame;
	else
		_num_frame = 0;
}

void Animation::draw(Point position, int w, int h, CROOD crood)
{
	_refresh();

	static Camera* camera = Camera::instance();
	if (crood == WORLD_CROOD) position = camera->transform2win(position);	//如果给入的是，世界坐标系，则转到屏幕坐标系

	static SDL_Rect dst;
	dst.x = round(position.x);
	dst.y = round(position.y);
	dst.h = h;
	dst.w = w;

	SDL_RenderCopy(_renderer, _texture, &_getSrcRect(), &dst);
}

void Animation::draw(Point position, CROOD crood)
{
	draw(position, _height, _width_frame, crood);
}

void Animation::draw(Point position, int w, int h, double angle, Vector center, int flip, CROOD crood)
{
	static Camera* camera = Camera::instance();
	if (crood == WORLD_CROOD) position = camera->transform2win(position);	//如果给入的是，世界坐标系，则转到屏幕坐标系

	_refresh();

	static SDL_Rect dst;
	dst.x = round(position.x);
	dst.y = round(position.y);
	dst.h = h;
	dst.w = w;

	SDL_Point sdl_center;
	sdl_center.x = center.x;
	sdl_center.y = center.y;

	SDL_Rect srcrect = _getSrcRect();

	switch (flip) {
	case FLIP_NONE:
		SDL_RenderCopyEx(_renderer, _texture, &srcrect, &dst, angle, &sdl_center, SDL_FLIP_NONE);
		break;
	case FLIP_HORIZONTAL:
		SDL_RenderCopyEx(_renderer, _texture, &srcrect, &dst, angle, &sdl_center, SDL_FLIP_HORIZONTAL);
		break;
	case FLIP_VERTICAL:
		SDL_RenderCopyEx(_renderer, _texture, &srcrect, &dst, angle, &sdl_center, SDL_FLIP_VERTICAL);
		break;
	case FLIP_BOTH:
		SDL_RenderCopyEx(_renderer, _texture, &srcrect, &dst, angle, &sdl_center, (SDL_RendererFlip)(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL));
	}
}

void Animation::draw(Point position, double angle, Vector center, int flip, CROOD crood)
{
	draw(position, _width_frame, _height, angle, center, flip, crood);
}

SDL_Rect Animation::_getSrcRect()
{
	SDL_Rect rect;
	rect.x = _width_frame * _current_frame;
	rect.y = 0;
	rect.h = _height;
	rect.w = _width_frame;
	return rect;
}

void Animation::_refresh()
{
	if (!_play) return;
	unsigned int time_now = InputHandler::instance()->getTime();
	if (time_now - _time_last >= _interval) {
		_current_frame++;
		_current_frame %= _num_frame;
		_time_last = time_now;
	}
}