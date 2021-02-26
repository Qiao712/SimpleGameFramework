#pragma once
#include "GameObject.h"
#include "Vector.h"
#include "OBB.h"
#include <string>
//#define _SHOW_BOX_
using std::string;
/**
* @brief 精灵类\n
* 具有速度、加速度、位置、大小的游戏对象的父类\n
* 支持相对坐标系（相对于其父节点),对其速度、加速度的设置为相对于其父节点的量。
* 支持旋转，可设置角速度与角加速度（相对的）。\n
* 其位置、大小、速度、加速度、旋转角度、角速度、角加速度集中与OBB对象种。
* 储存两个OBB对象，分别标识在世界坐标系种的量，和相对于其父节点的量。
*/
class Sprite : public GameObject
{
	friend class CollisionManager;
public:
	Sprite()=default;
	/** 默认使用纹理的宽高作为其OBB包围盒的宽高*/
	Sprite(string name_texture, int x, int y, double angle = 0.0, Point center = Point(0,0));
	Sprite(string name_texture, int x, int y,int w, int h, double angle = 0.0, Point center = Point(0,0));
	~Sprite();

	virtual void draw();
	virtual void update();
	
	void setHeight(unsigned int h) { _obb.h = _obb_abs.h = h; }
	void setWidth(unsigned int w) { _obb.w = _obb_abs.w = w; }
	unsigned int getWidth() const { return _obb_abs.w; }
	unsigned int getHeight() const { return  _obb_abs.h; }

	/**获取对该对象绑定的纹理/动画*/
	Texture& getTexture() { return *_texture; }

	/**
	* @brief 设置相对于父节点的坐标、速度、角速度、加速度、角加速度等属性，
	* 相对于父节点的量
	* @{
	*/
	void setPosition(int x, int y) { setPosition(Point(x, y)); }
	void setPosition(const Point& pos);
	void setCenter(const Point& center);
	void setVelocity(const Vector& velocity);
	void setAcceleration(const Vector& acceleration);
	void setAngle(double angle);
	void setAngularVelocity(double velocity);
	void setAngularAcceleration(double acceleration);
	void setFlipState(FLIP flip);
	/**
	* @}
	*/

	/**
	* @brief 获取相对于父节点的坐标、速度、角速度、加速度、角加速度
	* @{
	*/
	int getX() const { return _obb.pos.x; }
	int getY() const { return _obb.pos.y; }
	Point getPosition() const { return _obb.pos; }
	Point getCenter() const { return _obb.center;  }
	Vector getVelocity() const { return _obb.velocity; }
	Vector getAcceleration() const { return _obb.acceleration; }
	double getAngle() const { return _obb.angle; }
	double getAngularVelocity() const { return _obb.angular_velocity; }
	double getAngularAcceleration() const { return _obb.angular_acceleration; }
	FLIP getFlipState() const;
	/**
	* @}
	*/

	/**
	* @brief 获取绝对的坐标、速度、角速度、加速度、角加速度， 即相对于世界坐标系
	* @{
	*/
	Point getAbsolutePosition() const { return _obb_abs.pos; }
	Vector getAbsoluteVelocity() const { return  _obb_abs.velocity; }
	Vector getAbsoluteAcceleration() const { return  _obb_abs.acceleration; }
	double getAbsoluteAngle() const { return  _obb_abs.angle; };
	double getAbsoluteAngularVelocity() const { return  _obb_abs.angular_velocity; }
	double getAbsoluteAngularAcceleration() const { return  _obb_abs.angular_acceleration; }
	FLIP getAbsoluteFlipState() const;
	/**
	* @}
	*/
protected:
	virtual void _update();
	virtual void _draw();

	/**根据速度、角速度、加速度、角加速度移动，计算坐标*/
	void move();
	/**
	* @brief 检测与地图的碰撞并阻止其穿透地图
	* @param offset Vector的指针，用于返回偏移向量，传nullptr则不返回
	*/
	bool detectCollisionsOnTileMap(Vector* offset = nullptr);

	/** 在父节点坐标系下的 OBB包围盒，坐标、速度相对于父节点*/
	OBB _obb;
	/** 世界坐标系下的 OBB包围盒，绝对的坐标、速度，相对于世界坐标系原点*/
	OBB _obb_abs;

	/**纹理*/
	Texture* _texture = nullptr;
};