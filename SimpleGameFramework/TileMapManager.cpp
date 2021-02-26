#include "TileMapManager.h"
#include "TileFactory.h"
#include "TileMap.h"
#include <random>
using std::random_device;
using std::uniform_int_distribution;

TileMapManager* TileMapManager::_instance = nullptr;

TileMapManager* TileMapManager::instance()
{
	if (_instance == nullptr) {
		_instance = new TileMapManager;
	}
	return _instance;
}

void TileMapManager::bindTileMap(TileMap& tile_map)
{
	_tile_map = &tile_map;
}

void TileMapManager::setTile(int id_tile, unsigned int x_tile, unsigned int y_tile)
{
	_tile_map->setTile(id_tile, x_tile, y_tile);
}

void TileMapManager::setTile(string name, unsigned int x_tile, unsigned int y_tile)
{
	static TileFactory* tile_factory = TileFactory::instance();
	setTile(tile_factory->getTileID(name), x_tile, y_tile);
}

void TileMapManager::removeTile(unsigned int x_tile, unsigned int y_tile)
{
	_tile_map->removeTile(x_tile, y_tile);
}

TilePtr TileMapManager::getTile(unsigned int x_tile, unsigned int y_tile)
{
	if (x_tile >= 0 && x_tile < _tile_map->_w_map && y_tile >= 0 && y_tile < _tile_map->_h_map) {
		static TileFactory* tile_factory = TileFactory::instance();
		TilePtr tile = tile_factory->getTile(_tile_map->getTileID(x_tile, y_tile));

		return tile;
	}
	else {
		return nullptr;
	}

	
}

int TileMapManager::getTileID(unsigned int x_tile, unsigned int y_tile)
{
	if (x_tile >= 0 && x_tile < _tile_map->_w_map && y_tile >= 0 && y_tile < _tile_map->_h_map)
		return _tile_map->getTileID(x_tile, y_tile);
	else
		return 0;
}

void TileMapManager::genMap()
{
	static TileFactory* tile_factory = TileFactory::instance();
	//随机数生成器
	random_device rd;
	uniform_int_distribution<int> uid(0,1);
	uniform_int_distribution<int> uid2;

	for (int i = 0; i < _tile_map->_w_map; i++) {
		for (int j = 20 - uid(rd); j < 30; j++) {
			setTile("soil", i, j);
		}
	}

	//铺设草方块
	for (int i = 0; i < _tile_map->_w_map; i++) {
		for (int j = 0; j < 30; j++) {
			if (getTileID(i, j) == 0 && getTileID(i, j + 1) == tile_factory->getTileID("soil")) {
				setTile("grass", i, j);
				//随机种植物
				switch (uid2(rd) % 5) {
				case 0: setTile("flower", i, j - 1); break;
				case 1: setTile("bush", i, j - 1); break;
				}
			}
		}
	}

	for (int i = 0; i < _tile_map->_w_map; i++) {
		for (int j = 30; j < 50; j++) {
			setTile("stone", i, j);
		}
	}
}

TileMapManager::TileMapManager()
{

}