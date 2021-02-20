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
* @brief ����TileMap��Tile�Ĵ�����  Singleton\n
* �������������Tile����
* Flyweightģʽ
*/
class TileFactory
{
public:
	static TileFactory* instance();
	static void init();

	/**ͨ��ID��ȡ�����Tile����*/
	TilePtr  getTile(int id);
	/**ͨ�����ƻ�ù����Tile����*/
	TilePtr  getTile(string name);
	/**ͨ�����ƻ�ȡID*/
	int		 getTileID(string name) { return _name2id[name]; }

private:
	static TileFactory* _instance;

	TileFactory();

	/**���ļ���������Tile����Ϣ*/
	void loadTileInform();
	
	/**����Tile�����ָ��*/
	vector<TilePtr> _tiles;
	
	/**���Ƶ�id��ӳ��*/
	map<string, int> _name2id;
};

