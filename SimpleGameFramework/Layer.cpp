#include "Layer.h"
#include "TextureManager.h"
#include "Window.h"

Layer::Layer()
{
	_w = Window::instance()->getWidth();
	_h = Window::instance()->getHeight();
}

void Layer::draw()
{
	if(_background)
		_background->draw(Point(0, 0), _w, _h, SCREEN_CROOD);
}

void Layer::setBackground(string name_texture)
{
	_background = TextureManager::create(name_texture);
}
