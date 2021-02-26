#pragma once
#include "Tile.h"
#include "TileMap.h"
#include <memory>
using std::shared_ptr;
class TileMap;
class Tile;

/**
* @breif ��ͼ��������Ϊ�������TileMap�ṩȫ�ֽӿ�
* Singleton
*/
class TileMapManager
{
public:
	static TileMapManager* instance();
	
	/**��TileMap*/
	void bindTileMap(TileMap& tile_map);

	/**�༭TileMap*/

	/**
	* @brief �ڵ�ͼ��ĳͼ���з���һ��Tile
	* @param id_tile Tile ID�� 0��ʾ�޷���
	* @param x_tile,y_tile ͼ������
	*/
	void setTile(int id_tile, unsigned int x_tile, unsigned int y_tile);
	/**
	* @brief �ڵ�ͼ��ĳͼ���з���һ��Tile
	* @param id_tile Tile���ƣ� 0��ʾ�޷���
	* @param x_tile,y_tile ͼ������
	*/
	void setTile(string name, unsigned int x_tile, unsigned int y_tile);
	/**
	* @brief �Ƴ�Tile���ȼ���setTile(0, x_tile, y_tile)
	* @param x_tile  y_tile ͼ������
	*/
	void removeTile(unsigned int x_tile, unsigned  int y_tile);
	/**
	* @brief ��ȡĳͼ���е�Tile����Flyweight)
	* @param x_tile  y_tile ͼ������
	*/
	TilePtr  getTile(unsigned int x_tile, unsigned int y_tile);
	/**
	* @brief ��ȡĳͼ���е�TileID
	* @param x_tile  y_tile ͼ������
	*/
	int		getTileID(unsigned int x_tile, unsigned int y_tile);

	/**
	* @brief ��ȡ��Ϣ��ͼ��Ϣ
	* @{
	*/
	int getTileWidth() { return _tile_map->_w_tile; }
	int getTileHeight() { return _tile_map->_h_tile; }
	int getMapWidth() { return _tile_map->_w_map; }
	int getMapHeight() { return _tile_map->_h_map; }
	/**
	* @}
	*/

	/**���ɵ�ͼ*/
	void genMap();
private:
	static TileMapManager* _instance;
	
	TileMapManager();
	
	/**�󶨵�ͼ*/
	TileMap* _tile_map;
};

