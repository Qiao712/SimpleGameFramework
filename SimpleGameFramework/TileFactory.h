#pragma once
#include "Texture.h"
#include "TileMap.h"
#include "Tile.h"
#include <memory>
#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::map;

/**
* @brief 管理TileMap中Tile的创建，  Singleton\n
* 持有所有种类的Tile对象
* Flyweight模式
*/
class TileFactory
{
public:
	static TileFactory* instance();
	static void init();

	/**通过ID获取共享的Tile对象*/
	TilePtr  getTile(int id);
	/**通过名称获得共享的Tile对象*/
	TilePtr  getTile(string name);
	/**通过名称获取ID*/
	int		 getTileID(string name) { return _name2id[name]; }

private:
	static TileFactory* _instance;

	TileFactory();

	/**从文件加载所有Tile的信息*/
	void loadTileInform();
	
	/**储存Tile对象的指针*/
	vector<TilePtr> _tiles;
	
	/**名称到id的映射*/
	map<string, int> _name2id;
};

