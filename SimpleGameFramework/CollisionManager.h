#pragma once
class Sprite;
class Vector;
/**
* @brief 管理各游戏对象间的碰撞检测
* 各对象向其询问是否碰撞。
*/
class CollisionManager
{
public:
	static CollisionManager* instance();

	/**
	* @brief 两个精灵间的碰撞检测
	* @param 两个精灵对象引用
	*/
	bool isCollised(const Sprite& a, const Sprite& b);
	/**
	* @brief 精灵对象与Tile之间的碰撞检测
	* @param a 精灵对象引用
	* @param offset 偏离量，指出如何移动才能分离精灵与地图的碰撞,其方向取决于碰撞时a的几何中心的位置
	*/
	bool isCollisedWithTile(Sprite& a, Vector& offset);
private:
	static CollisionManager* _instance;
	
	CollisionManager();
};

