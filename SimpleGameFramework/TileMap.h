#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <vector>
using std::vector;

/**
* @brief ��Ϸ����Ƭ��ͼ�࣬���е�ͼ�����ݡ�
*/
class TileMap : public GameObject
{
	friend class TileMapManager;
public:
	TileMap(unsigned int w_map, unsigned int h_map, unsigned int w_tile, unsigned int h_tile);

	/**
	* @brief �ڵ�ͼ��ĳͼ���з���һ��Tile
	* @param id_tile Tile ID�� 0��ʾ�޷���
	* @param x_tile ͼ������
	* @param y_tile ͼ������
	*/
	void setTile(int id_tile, unsigned int x_tile, unsigned int y_tile);
	
	/**
	* @brief �Ƴ�Tile���ȼ���setTile(0, x_tile, y_tile)
	* @param x_tile  y_tile ͼ������
	*/
	void removeTile(unsigned int x_tile, unsigned  int y_tile);

	/**
	* @brief ��ȡĳͼ���е�Tile��ID
	* @param x_tile  y_tile ͼ������
	*/
	int  getTileID(unsigned int x_tile, unsigned int y_tile);

	/**����*/
	void draw();
private:
	/**��ͼ��ͼ������*/
	unsigned int _w_map;
	/**��ͼ�ߣ�ͼ������*/
	unsigned int _h_map;
	/**һ��ͼ��Ŀ�ȣ����أ�*/
	unsigned int _w_tile;
	/**һ��ͼ��ĸ߶ȣ����أ�*/
	unsigned int _h_tile;

	/**��ͼ����, ��ά����*/
	int **_data_map;
};

