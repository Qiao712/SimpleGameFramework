#include "TileMapManager.h"
#include "TileFactory.h"
#include "TileMap.h"

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

void TileMapManager::genMap()
{
	for (int i = 0; i < _tile_map->_w_map; i++) {
			setTile("grass", i, 19);
	}

	for (int i = 0; i < _tile_map->_w_map; i++) {
		for (int j = 20; j < 30; j++) {
			setTile("soil", i, j);
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