#include "CollisionManager.h"
#include "TileMapManager.h"
#include "Sprite.h"
#include "OBB.h"
#include "Vector.h"
#include<limits>
#include<cmath>
#include<iostream>

/**double���͵����ֵ*/
const double Max_Double = std::numeric_limits<double>::max();
/**double���͵���Сֵ*/
const double Min_Double = std::numeric_limits<double>::lowest();

CollisionManager* CollisionManager::_instance = nullptr;
CollisionManager* CollisionManager::instance()
{
	if (_instance == nullptr) {
		_instance = new CollisionManager;
	}
	return nullptr;
}

bool CollisionManager::isCollised(const Sprite& a, const Sprite& b)
{
	return a._obb_abs.collisionDetecting(b._obb_abs);
}

/**
* ���̫��д�ˡ�����
* ���������ַ��������ڿ�����
*/
bool CollisionManager::isCollisedWithTile(Sprite& sprite, Vector& offset)
{
	static TileMapManager* tile_map_manager = TileMapManager::instance();
	static OBB obb_tile(0,0, tile_map_manager->getTileWidth(), tile_map_manager->getTileHeight());	//����һ��Tile����ײ��

	//������ײ��
	OBB obb_sprite = sprite._obb_abs;

	/**TODO: �ɽ����Ż��������ظ�����*/
	//���������귶Χ���ҵ��������ǵ�����tile����������ײ���
	Point vertexes[4];
	vertexes[0] = sprite._obb_abs.getLeftTopPoint();
	vertexes[1] = sprite._obb_abs.getRightBottomPoint();
	vertexes[2] = sprite._obb_abs.getLeftBottomPoint();
	vertexes[3] = sprite._obb_abs.getRightTopPoint();
	double left = Max_Double, right = Min_Double, top = Max_Double, bottom = Min_Double; //����˵�x���ꡢ���Ҷ˵�x���ꡢ���϶˵�y���ꡢ���¶˵�y����
	for (auto& i : vertexes) {
		left = std::min(left, i.x);
		right = std::max(right, i.x);
		top = std::min(top, i.y);
		bottom = std::max(bottom, i.y);
	}
	
	//���㷶Χ����Ҫ����Щ���ӽ�����ײ���
	int left_tile = left / tile_map_manager->getTileWidth() - 1;
	left_tile = std::max(left_tile, 0);
	int right_tile = right / tile_map_manager->getTileWidth() + 1;
	right_tile = std::min(right_tile, tile_map_manager->getMapWidth());
	int top_tile = top / tile_map_manager->getTileHeight() - 1;
	top_tile = std::max(top_tile, 0);
	int bottom_tile = bottom / tile_map_manager->getTileHeight() + 1;
	bottom_tile = std::min(bottom_tile, tile_map_manager->getTileHeight());

	//�ֱ���ײ���
	offset = Vector(0,0);
	bool flag = false;
	for (int i = left_tile; i <= right_tile; i++) {
		for (int j = top_tile; j <= bottom_tile; j++) {
			if (tile_map_manager->getTile(i, j)) {
				obb_tile.pos.set(i * obb_tile.w, j * obb_tile.h);	//�ƶ������ײ�䵽��Ӧλ���Գ䵱��tile����ײ��
				if (obb_tile.collisionDetecting(obb_sprite)) {
					flag = true;

					//�ĸ������ϵ�ƫ����(���ʹ�þ��鲻���ڸ�tile��ײ��ƫ����)
					double offset_to_right = obb_tile.pos.x + obb_tile.w - left;			//x�������ƫ�Ʋ���ʹ�����������tile�����Ҳ�ǡ�ýӴ�
					double offset_to_left = obb_tile.pos.x - 1 - right;					//x�������ƫ�Ʋ���ʹ�������Ҳ���tile�������ǡ�ýӴ�
					double offset_to_bottom = obb_tile.pos.y + obb_tile.h - top;			//y�������ƫ�Ʋ���ʹ�������ϲ���tile�����²�ǡ�ýӴ�
					double offset_to_top = obb_tile.pos.y - 1 - bottom;					//y�������ƫ�Ʋ���ʹ�������²���tile�����ϲ�ǡ�ýӴ�
					

					/**
					* ���Tileĳһ���з��飬�򲻿���ò�ƫ�ƣ���Ϊ���ʹ���ں���Ĳ��ᱻѡ��
					* offset_to_... != 0 �Ǳ�Ҫ�ģ���ֹ��������Ĳ�����ƫ��
					*   OX
					*   OX             X:Tile O:����
					*   XX 
					* 
					*/
					if (tile_map_manager->getTile(i + 1, j) != 0 && offset_to_right != 0) {
						offset_to_right = Max_Double;
					}
					if (tile_map_manager->getTile(i - 1, j) != 0 && offset_to_left != 0) {
						offset_to_left = Max_Double;
					}
					if (tile_map_manager->getTile(i, j + 1) != 0 && offset_to_bottom != 0) {
						offset_to_bottom = Max_Double;
					}
					if (tile_map_manager->getTile(i, j - 1) != 0 && offset_to_top != 0) {
						offset_to_top = Max_Double;
					}

					//std::cout << offset_to_right << ' ' << offset_to_left << ' ' << offset_to_bottom << ' ' << offset_to_top << '\n';

					//ѡȡ�������ƫ�ƣ� X�᷽���ϵĴ� ���������ֵѡȡ�� Y�᷽���ϵġ�������
					double offset_x = abs(offset_to_left) < abs(offset_to_right) ? offset_to_left : offset_to_right;		//ȡ��С����x���ϵ�ƫ��
					double offset_y = abs(offset_to_bottom) < abs(offset_to_top) ? offset_to_bottom : offset_to_top;		//ȡ��С����y���ϵ�ƫ��

					//�������϶��޷�ƫ�� �Ͳ�Ҫƫ����
					if (offset_x == Max_Double && offset_y == Max_Double) continue;

					//�ڴ�X���Y�᷽����ѡ��һ������ѡ����С��ƫ�Ƶķ���
					if (abs(offset_x) > abs(offset_y)) {
						obb_sprite.pos.y += offset_y;
						top += offset_y;		//��Щ��Ҫ���Ŷ�/(��o��)/~~
						bottom += offset_y;
					}
					else {
						obb_sprite.pos.x += offset_x;
						left += offset_x;
						right += offset_x;
					}

				}
			}
		}
	}

	//��������ƫ����
	offset = obb_sprite.pos - sprite._obb_abs.pos;
	return flag;
}

CollisionManager::CollisionManager()
{
	
}