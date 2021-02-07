#include "Sprite.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "OBB.h"
#include <cmath>
#include <iostream>
#include <algorithm>
using std::cout;
using std::sort;
Sprite::Sprite(string name_texture, int x, int y, double angle, Point center)
{
	_texture = TextureManager::create(name_texture);
	_obb.w = _obb_abs.w = _texture.getWidth();
	_obb.w = _obb_abs.h = _texture.getHeight();
	_obb.center = _obb_abs.center = center;
	setPosition(Point(x,y));
	setAngle(angle);
}

Sprite::Sprite(string name_texture, int x, int y, int w, int h, double angle, Point center)
{
	_texture = TextureManager::create(name_texture);
	_obb.w = _obb_abs.w = w;
	_obb.w = _obb_abs.h = h;
	_obb.center = _obb_abs.center = center;
	setPosition(Point(x,y));
	setAngle(angle);
}

void Sprite::draw()
{
	//纹理绘制应传入无偏转时该矩形的左上角
	//而精灵的所储存的坐标是原点到中心点的坐标
	_texture.draw(_obb_abs.pos.x - _obb_abs.center.x, _obb_abs.pos.y - _obb_abs.center.y, _obb_abs.angle, _obb_abs.center);
}

bool Sprite::collisionDetecting(const Sprite& rhs) const
{
	return _obb_abs.collisionDetecting(rhs._obb_abs);
}

void Sprite::setPosition(const Point& pos)
{
	_obb.pos = pos;
	//同步绝对位置
	if (_parent == nullptr) _obb_abs.pos = pos;
	else {
		//相对位置到绝对位置的转换,要跟随父节点旋转
		double radian_a = degree2radian(_parent->getAbsoluteAngle());
		double cos_a = cos(radian_a);
		double sin_a = sin(radian_a);
		_obb_abs.pos = Point(cos_a * _obb.pos.x - sin_a * _obb.pos.y,
							 cos_a * _obb.pos.y + sin_a * _obb.pos.x)  + _parent->getAbsolutePosition();
	}
}

void Sprite::setVelocity(const Vector& velocity)
{
	_obb.velocity = velocity;

	if (_parent == nullptr) _obb_abs.velocity = velocity;
	else {
		//将速度转化到世界坐标系下,向量需变换到世界坐标系下
		double radian_a = degree2radian(_parent->getAbsoluteAngle());
		double cos_a = cos(radian_a);
		double sin_a = sin(radian_a);
		//相对速度向量的基
		Vector axisY(-sin_a, cos_a);	
		Vector axisX(cos_a, sin_a);
		_obb_abs.velocity = axisX * velocity.x + axisY * velocity.y;
	}
}

void Sprite::setAcceleration(const Vector& acceleration)
{
	_obb.acceleration = acceleration;

	if (_parent == nullptr) _obb_abs.acceleration = acceleration;
	else {
		//将加速度转化到世界坐标系下,向量需变换到世界坐标系下
		double radian_a = degree2radian(_parent->getAbsoluteAngle());
		double cos_a = cos(radian_a);
		double sin_a = sin(radian_a);
		//相对加速度向量的基
		Vector axisY(-sin_a, cos_a);
		Vector axisX(cos_a, sin_a);
		_obb_abs.acceleration = axisX * acceleration.x + axisY * acceleration.y;
	}
}

void Sprite::setAngle(double angle)
{
	_obb.angle = angle;

	if (_parent == nullptr) _obb_abs.angle = angle;
	else _obb_abs.angle = angle + _parent->getAbsoluteAngle();
}

void Sprite::setAngularVelocity(double velocity)
{
	_obb.angular_velocity = velocity;

	if (_parent == nullptr) _obb_abs.angular_velocity = velocity;
	else _obb_abs.angular_velocity = velocity + _parent->getAbsoluteAngularVelocity();
}

void Sprite::setAngularAcceleration(double acceleration)
{
	_obb.angular_acceleration = acceleration;

	if (_parent == nullptr) _obb_abs.angular_acceleration = acceleration;
	else _obb_abs.angular_acceleration = acceleration + _parent->getAbsoluteAngularAcceleration();
}

void Sprite::_update()
{
	update();
	
	//处理速度与加速度
	unsigned int d = InputHandler::instance()->getIntervalTime();
	Vector new_velocity = _obb.velocity + _obb.acceleration * d;
	setVelocity(_obb.velocity + _obb.acceleration * d);
	setPosition(_obb.pos + _obb.velocity * d);

	//处理角速度与角加速度
	setAngularVelocity(_obb.angular_velocity + _obb.angular_acceleration * d);
	setAngle(_obb.angle + _obb.angular_velocity * d);

	for (auto& i : GameObject::_sub) {
		i->_update();
	}
}

void Sprite::_draw()
{
	GameObject::_draw();

	//绘制包围盒
	Vector lt1 = _obb_abs.getLeftTopPoint();
	Vector lb1 = _obb_abs.getLeftBottomPoint();
	Vector rt1 = _obb_abs.getRightTopPoint();
	Vector rb1 = _obb_abs.getRightBottomPoint();
	TextureManager::drawLine(lt1.x, lt1.y, lb1.x, lb1.y);
	TextureManager::drawLine(lb1.x, lb1.y, rb1.x, rb1.y);
	TextureManager::drawLine(rb1.x, rb1.y, rt1.x, rt1.y);
	TextureManager::drawLine(rt1.x, rt1.y, lt1.x, lt1.y);
	TextureManager::drawLine(rt1.x, rt1.y, lb1.x, lb1.y);
	TextureManager::drawLine(lt1.x, lt1.y, rb1.x, rb1.y);
}

//void Sprite::setAbsolutePosition(const Point& pos)
//{
//	_obb_abs.pos = pos;
//	//同步相对位置
//	
//}
//
//void Sprite::setAbsoluteVelocity(const Vector& velocity)
//{
//	_obb_abs.velocity = velocity;
//
//	if (_parent == nullptr) _obb.velocity = velocity;
//	else _obb.velocity = velocity - _parent->getAbsoluteVelocity();
//}
//
//void Sprite::setAbsoluteAcceleration(const Vector& acceleration)
//{
//	_obb_abs.acceleration = acceleration;
//
//	if (_parent == nullptr) _obb.acceleration = acceleration;
//	else _obb.acceleration = acceleration - _parent->getAbsoluteAcceleration();
//}
//
//void Sprite::setAbsoluteAngle(double angle)
//{
//	_obb_abs.angle = angle;
//	
//	if (_parent == nullptr) _obb.angle = angle;
//	else _obb.angle = angle - _parent->getAbsoluteAngle();
//}
//
//void Sprite::setAbsoluteAngularVelocity(double velocity)
//{
//	_obb_abs.angular_velocity = velocity;
//
//	if (_parent == nullptr) _obb.angular_velocity = velocity;
//	else _obb.angular_velocity = velocity - _parent->getAbsoluteAngularVelocity();
//}
//
//void Sprite::setAbsoluteAngularAcceleration(double acceleration)
//{
//	_obb_abs.angular_acceleration = acceleration;
//
//	if (_parent == nullptr) _obb.angular_acceleration = acceleration;
//	else _obb.angular_acceleration = acceleration - _parent->getAbsoluteAngularAcceleration();
//}
