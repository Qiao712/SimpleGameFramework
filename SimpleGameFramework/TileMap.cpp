#include "TileMap.h"
#include "TileFactory.h"
#include "TileMapManager.h"
#include <iostream>

TileMap::TileMap(unsigned int w_map, unsigned int h_map, unsigned int w_tile, unsigned int h_tile) :
	_w_map(w_map), _h_map(h_map), _w_tile(w_tile),_h_tile(h_tile)
{
	/**初始化tiles数组,初始时全为空*/
	//_tiles.resize((unsigned long long)_w_map * _h_map, nullptr);
	
	//构建二维数组
	_data_map = new int*[w_map];
	for (int i = 0; i < w_map; i++) {
		_data_map[i] = new int[h_map];
		for (int j = 0; j < h_map; j++) _data_map[i][j] = 0;
	}
}

void TileMap::setTile(int id_tile, unsigned int x_tile, unsigned int y_tile)
{
	_data_map[x_tile][y_tile] = id_tile;
}

void TileMap::removeTile(unsigned int x_tile, unsigned int y_tile)
{
	setTile(0, x_tile, y_tile);
}

int TileMap::getTileID(unsigned int x_tile, unsigned int y_tile)
{
	return _data_map[x_tile][y_tile];
}

void TileMap::draw()
{
	static TileMapManager* tile_map_manager = TileMapManager::instance();

	for (int x = 0; x < _w_map; x++) {
		for (int y = 0; y < _h_map; y++) {
			TilePtr tile = tile_map_manager->getTile(x, y);	//获取tile对象
			if (tile == nullptr) continue;
			tile->draw(x * _w_tile, y * _h_tile, _h_tile, _w_tile);
		}
	}
}
