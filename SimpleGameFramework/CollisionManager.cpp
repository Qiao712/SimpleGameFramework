#include "CollisionManager.h"
#include "TileMapManager.h"
#include "Sprite.h"
#include "OBB.h"
#include "Vector.h"
#include<limits>
#include<cmath>
#include<iostream>

/**double类型的最大值*/
const double Max_Double = std::numeric_limits<double>::max();
/**double类型的最小值*/
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
* 这可太难写了。。。
* 试了无数种方案，终于靠谱了
*/
bool CollisionManager::isCollisedWithTile(Sprite& sprite, Vector& offset)
{
	static TileMapManager* tile_map_manager = TileMapManager::instance();
	static OBB obb_tile(0,0, tile_map_manager->getTileWidth(), tile_map_manager->getTileHeight());	//储存一个Tile的碰撞箱

	//拷贝碰撞盒
	OBB obb_sprite = sprite._obb_abs;

	/**TODO: 可进行优化，避免重复计算*/
	//计算其坐标范围，找到其所覆盖的所有tile，并进行碰撞检测
	Point vertexes[4];
	vertexes[0] = sprite._obb_abs.getLeftTopPoint();
	vertexes[1] = sprite._obb_abs.getRightBottomPoint();
	vertexes[2] = sprite._obb_abs.getLeftBottomPoint();
	vertexes[3] = sprite._obb_abs.getRightTopPoint();
	double left = Max_Double, right = Min_Double, top = Max_Double, bottom = Min_Double; //最左端的x坐标、最右端的x坐标、最上端的y坐标、最下端的y坐标
	for (auto& i : vertexes) {
		left = std::min(left, i.x);
		right = std::max(right, i.x);
		top = std::min(top, i.y);
		bottom = std::max(bottom, i.y);
	}
	
	//计算范围，需要与那些格子进行碰撞检测
	int left_tile = left / tile_map_manager->getTileWidth() - 1;
	left_tile = std::max(left_tile, 0);
	int right_tile = right / tile_map_manager->getTileWidth() + 1;
	right_tile = std::min(right_tile, tile_map_manager->getMapWidth());
	int top_tile = top / tile_map_manager->getTileHeight() - 1;
	top_tile = std::max(top_tile, 0);
	int bottom_tile = bottom / tile_map_manager->getTileHeight() + 1;
	bottom_tile = std::min(bottom_tile, tile_map_manager->getTileHeight());

	//分别碰撞检测
	offset = Vector(0,0);
	bool flag = false;
	for (int i = left_tile; i <= right_tile; i++) {
		for (int j = top_tile; j <= bottom_tile; j++) {
			if (tile_map_manager->getTile(i, j)) {
				obb_tile.pos.set(i * obb_tile.w, j * obb_tile.h);	//移动这个碰撞箱到相应位置以充当该tile的碰撞箱
				if (obb_tile.collisionDetecting(obb_sprite)) {
					flag = true;

					//四个方向上的偏移量(如何使该精灵不在于该tile碰撞的偏移量)
					double offset_to_right = obb_tile.pos.x + obb_tile.w - left;			//x轴上如何偏移才能使精灵最左侧于tile的最右侧恰好接触
					double offset_to_left = obb_tile.pos.x - 1 - right;					//x轴上如何偏移才能使精灵最右侧于tile的最左侧恰好接触
					double offset_to_bottom = obb_tile.pos.y + obb_tile.h - top;			//y轴上如何偏移才能使精灵最上侧于tile的最下侧恰好接触
					double offset_to_top = obb_tile.pos.y - 1 - bottom;					//y轴上如何偏移才能使精灵最下侧于tile的最上侧恰好接触
					

					/**
					* 如果Tile某一侧有方块，则不可向该侧偏移，记为最大，使其在后面的不会被选择
					* offset_to_... != 0 是必要的，防止这种情况的不正常偏移
					*   OX
					*   OX             X:Tile O:精灵
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

					//选取尽量向的偏移， X轴方向上的从 左右两侧的值选取， Y轴方向上的。。。。
					double offset_x = abs(offset_to_left) < abs(offset_to_right) ? offset_to_left : offset_to_right;		//取最小的做x轴上的偏移
					double offset_y = abs(offset_to_bottom) < abs(offset_to_top) ? offset_to_bottom : offset_to_top;		//取最小的做y轴上的偏移

					//两条轴上都无法偏移 就不要偏移了
					if (offset_x == Max_Double && offset_y == Max_Double) continue;

					//在从X轴和Y轴方向中选择一个方向，选尽量小的偏移的方向
					if (abs(offset_x) > abs(offset_y)) {
						obb_sprite.pos.y += offset_y;
						top += offset_y;		//这些点要跟着动/(ㄒoㄒ)/~~
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

	//返回最终偏移量
	offset = obb_sprite.pos - sprite._obb_abs.pos;
	return flag;
}

CollisionManager::CollisionManager()
{
	
}