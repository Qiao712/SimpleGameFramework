#include "Tile.h"
#include "TextureManager.h"
#include <iostream>
Tile::Tile() : _id_tile(0)
{
}
Tile::Tile(string name_texture){
	_texture = TextureManager::create(name_texture);
}

void Tile::draw(int x, int y, int h, int w)
{
	_texture->draw(Point(x, y), h, w);
}
