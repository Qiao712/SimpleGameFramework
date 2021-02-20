#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Texture.h"
#include "Vector.h"
using std::string;
using std::vector;

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectPtr;

/**
* @brief 游戏对象类，游戏内所有元素的类的基类\n
* 包括层、精灵等.\n
* 包含一个子节点的列表，以形成树的结构.\n
* 所有的游戏要素以树结构组织.
*/
class GameObject
{
	friend class Game;
	friend class Sprite;		//为了让Body的_update可以访问_sub中指针指向的对象
public:
	GameObject();
	~GameObject();

	/**每一帧的更新，在次进行该对象的逻辑业务*/
	virtual void update();
	/**绘制自身*/
	virtual void draw();

	/** 插入子游戏对象*/
	void insert(GameObjectPtr sub);
	/** 移除子游戏对象*/
	void remove(GameObjectPtr sub);
	/** 获得父游戏对象*/
	GameObjectPtr getParent() const { return _parent; }
	/** 获取用于遍历所有子节点的首迭代器， 为常量迭代器*/
	vector<GameObjectPtr>::const_iterator begin() const { return _sub.cbegin(); }
	/** 获取用于遍历所有子节点的尾后迭代器， 为常量迭代器*/
	vector<GameObjectPtr>::const_iterator end() const { return _sub.cend(); }

	/**
	* @name 用于获取相对于世界坐标系的属性\n
	* GameObject不储存这些属性，但Sprite在计算坐标时需要使用其父节点的绝对坐标\n
	* 使这些虚函数返回"0"，保证Sprite以GameObject为父节点时其是相对于世界坐标系的\n
	* @{
	*/
	virtual int getAbsoluteX() const { return 0;}
	virtual int getAbsoluteY() const { return 0;}
	virtual Point getAbsolutePosition() const { return Point(0,0); }
	virtual double getAbsoluteAngle() const { return 0; }
	virtual Vector getAbsoluteVelocity() const { return Vector(0, 0); }
	virtual double getAbsoluteAngularVelocity() const { return 0; }
	virtual Vector getAbsoluteAcceleration() const { return Vector(0, 0); }
	virtual double getAbsoluteAngularAcceleration() const { return 0; }
	virtual FLIP getAbsoluteFlipState() const { return FLIP_NONE; }
	/** @} */
protected:
	/**调用该节点update，并向下递归地执行子节点地_update,以先序遍历的顺序更新树上的游戏对象*/
	virtual void _update();
	/**调用该节点draw，并向下递归地执行子节点地_draw，以先序遍历的顺序绘制树上的游戏对象*/
	virtual void _draw();
	GameObjectPtr _parent = nullptr;	//父节点
	vector<GameObjectPtr> _sub;		//子游戏对象
};