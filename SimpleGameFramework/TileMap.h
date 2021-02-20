#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <vector>
using std::vector;

/**
* @brief 游戏的瓦片地图类，持有地图的数据。
*/
class TileMap : public GameObject
{
	friend class TileMapManager;
public:
	TileMap(unsigned int w_map, unsigned int h_map, unsigned int w_tile, unsigned int h_tile);

	/**
	* @brief 在地图的某图格中放置一个Tile
	* @param id_tile Tile ID， 0表示无方块
	* @param x_tile 图格坐标
	* @param y_tile 图格坐标
	*/
	void setTile(int id_tile, unsigned int x_tile, unsigned int y_tile);
	
	/**
	* @brief 移除Tile，等价于setTile(0, x_tile, y_tile)
	* @param x_tile  y_tile 图格坐标
	*/
	void removeTile(unsigned int x_tile, unsigned  int y_tile);

	/**
	* @brief 获取某图格中的Tile的ID
	* @param x_tile  y_tile 图格坐标
	*/
	int  getTileID(unsigned int x_tile, unsigned int y_tile);

	/**绘制*/
	void draw();
private:
	/**地图宽（图格数）*/
	unsigned int _w_map;
	/**地图高（图格数）*/
	unsigned int _h_map;
	/**一个图格的宽度（像素）*/
	unsigned int _w_tile;
	/**一个图格的高度（像素）*/
	unsigned int _h_tile;

	/**地图数据, 二维数组*/
	int **_data_map;
};

