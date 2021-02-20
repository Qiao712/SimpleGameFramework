#pragma once
#include "Sprite.h"
#include <memory>
#include <string>
using std::string;

class Tile;
typedef std::shared_ptr<Tile> TilePtr;
class Texture;

/**
* @brief ��Ƭ��ͼ�е�һ�ַ���
* ���淽������id�����Ƶ�����
* ʹ��Flyweightģʽ����
*/
class Tile
{
	friend class TileFactory;
public:
	Tile();
	Tile(string name_texture);

	/**
	* @brief ��������������ϵ��
	*/
	void draw(int x, int y, int h, int w);
protected:
	/**��ʶ���������id*/
	int _id_tile;

	/**��������*/
	Texture* _texture;
	string _name;
	int _hardness = 1;
};