#pragma once
#include "Sprite.h"
#include <memory>
#include <string>
using std::string;

class Tile;
typedef std::shared_ptr<Tile> TilePtr;
class Texture;

/**
* @brief 瓦片地图中的一种方块
* 储存方块纹理、id、名称等属性
* 使用Flyweight模式共享
*/
class Tile
{
	friend class TileFactory;
public:
	Tile();
	Tile(string name_texture);

	/**
	* @brief 绘制在世界坐标系中
	*/
	void draw(int x, int y, int h, int w);
protected:
	/**标识方块种类的id*/
	int _id_tile;

	/**各种属性*/
	Texture* _texture;
	string _name;
	int _hardness = 1;
};