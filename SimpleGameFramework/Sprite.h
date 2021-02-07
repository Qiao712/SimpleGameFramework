#pragma once
#include "GameObject.h"
#include "Vector.h"
#include "OBB.h"
#include <string>

using std::string;
/**
* @brief 精灵类
*/
class Sprite : public GameObject
{
public:
	Sprite()=default;
	/** 默认使用纹理的宽高作为其OBB包围盒的宽高*/
	Sprite(string name_texture, int x, int y, double angle = 0.0, Point center = Point(0,0));
	Sprite(string name_texture, int x, int y,int w, int h, double angle = 0.0, Point center = Point(0,0));
	
	virtual void draw();
	/**与另一个精灵进行碰撞检测*/
	bool collisionDetecting(const Sprite& rhs) const;
	
	void setHeight(unsigned int h) { _obb.h = _obb_abs.h = h; }
	void setWidth(unsigned int w) { _obb.w = _obb_abs.w = w; }
	unsigned int getWidth() const { return _obb_abs.w; }
	unsigned int getHeight() const { return  _obb_abs.h; }

	/**
	* @brief 设置相对于父节点的坐标、速度、角速度、加速度、角加速度等属性，
	* 相对于父节点的量
	* @{
	*/
	void setPosition(int x, int y) { setPosition(Point(x, y)); }
	void setPosition(const Point& pos);
	void setVelocity(const Vector& velocity);
	void setAcceleration(const Vector& velocity);
	void setAngle(double angle);
	void setAngularVelocity(double velocity);
	void setAngularAcceleration(double acceleration);
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
	Vector getVelocity() const { return _obb.velocity; }
	Vector getAcceleration() const { return _obb.acceleration; }
	double getAngle() const { return _obb.angle; }
	double getAngularVelocity() const { return _obb.angular_velocity; }
	double getAngularAcceleration() const { return _obb.angular_acceleration; }
	/**
	* @}
	*/
	
	//绝对的坐标，速度, rhs设为nullptr则相对于其父对象，若无父对象则设置为绝对坐标
	/*void setAbsolutePosition(int x, int y) { setAbsolutePosition(Point(x,y)); }
	void setAbsolutePosition(const Point& pos);
	void setAbsoluteVelocity(const Vector& velocity);
	void setAbsoluteAcceleration(const Vector& acceleration);
	void setAbsoluteAngle(double angle);
	void setAbsoluteAngularVelocity(double velocity);
	void setAbsoluteAngularAcceleration(double acceleration);*/

	/**
	* @brief 获取绝对的坐标、速度、角速度、加速度、角加速度， 即相对于世界坐标系
	* @{
	*/
	Point getAbsolutePosition() const { return _obb_abs.pos; };
	Vector getAbsoluteVelocity() const { return  _obb_abs.velocity; }
	Vector getAbsoluteAcceleration() const { return  _obb_abs.acceleration; };
	double getAbsoluteAngle() const { return  _obb_abs.angle; };
	double getAbsoluteAngularVelocity() const { return  _obb_abs.angular_velocity; };
	double getAbsoluteAngularAcceleration() const { return  _obb_abs.angular_acceleration; };
	/**
	* @}
	*/
private:
	virtual void _update();
	virtual void _draw();

	/** 在父节点坐标系下的 OBB包围盒，坐标、速度相对于父节点*/
	OBB _obb;
	/** 世界坐标系下的 OBB包围盒，绝对的坐标、速度，相对于世界坐标系原点*/
	OBB _obb_abs;

	/**纹理*/
	Texture _texture;
};