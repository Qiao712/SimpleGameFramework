#pragma once
#include "Tile.h"
#include "TileMap.h"
#include <memory>
using std::shared_ptr;
class TileMap;
class Tile;

/**
* @breif 地图管理器，为管理控制TileMap提供全局接口
* Singleton
*/
class TileMapManager
{
public:
	static TileMapManager* instance();
	
	/**绑定TileMap*/
	void bindTileMap(TileMap& tile_map);

	/**编辑TileMap*/

	/**
	* @brief 在地图的某图格中放置一个Tile
	* @param id_tile Tile ID， 0表示无方块
	* @param x_tile,y_tile 图格坐标
	*/
	void setTile(int id_tile, unsigned int x_tile, unsigned int y_tile);
	/**
	* @brief 在地图的某图格中放置一个Tile
	* @param id_tile Tile名称， 0表示无方块
	* @param x_tile,y_tile 图格坐标
	*/
	void setTile(string name, unsigned int x_tile, unsigned int y_tile);
	/**
	* @brief 移除Tile，等价于setTile(0, x_tile, y_tile)
	* @param x_tile  y_tile 图格坐标
	*/
	void removeTile(unsigned int x_tile, unsigned  int y_tile);
	/**
	* @brief 获取某图格中的Tile对象（Flyweight)
	* @param x_tile  y_tile 图格坐标
	*/
	TilePtr  getTile(unsigned int x_tile, unsigned int y_tile);
	/**
	* @brief 获取某图格中的TileID
	* @param x_tile  y_tile 图格坐标
	*/
	int		getTileID(unsigned int x_tile, unsigned int y_tile);

	/**
	* @brief 获取信息地图信息
	* @{
	*/
	int getTileWidth() { return _tile_map->_w_tile; }
	int getTileHeight() { return _tile_map->_h_tile; }
	int getMapWidth() { return _tile_map->_w_map; }
	int getMapHeight() { return _tile_map->_h_map; }
	/**
	* @}
	*/

	/**生成地图*/
	void genMap();
private:
	static TileMapManager* _instance;
	
	TileMapManager();
	
	/**绑定地图*/
	TileMap* _tile_map;
};

