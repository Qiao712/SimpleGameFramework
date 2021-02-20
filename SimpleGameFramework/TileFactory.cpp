#include "TileFactory.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
using std::ifstream;
TileFactory* TileFactory::_instance = nullptr;

TileFactory* TileFactory::instance()
{
	return _instance;
}

void TileFactory::init()
{
	_instance = new TileFactory;
}

TilePtr TileFactory::getTile(int id)
{
	return _tiles[id];
}

TilePtr TileFactory::getTile(string name)
{
	return getTile(_name2id[name]);
}

void TileFactory::loadTileInform()
{
	ifstream file("res\\Tiles.txt", std::ios::in);
	
	int id = 0;	//! 0表示无Tile,从1开始
	_tiles.push_back(nullptr);

	string name, name_texture;
	TilePtr tile;

	while (file >> name && file >> name_texture) {
		std::cout <<"Load tile: "<<name << ' ' << name_texture << '\n';

		id++;
		tile = make_shared<Tile>(name_texture);
		tile->_hardness = 1;
		tile->_name = name;

		_tiles.push_back(tile);
		_name2id.insert({ name, id });
	}
}

TileFactory::TileFactory() {
	loadTileInform();
}