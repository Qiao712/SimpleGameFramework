#include "Sprite.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "OBB.h"
#include <cmath>
#include <iostream>
#include <algorithm>
using std::cout;
using std::sort;
Sprite::Sprite(string name_texture, int x, int y, double angle, Point center)
{
	_texture = TextureManager::create(name_texture);
	_obb.w = _obb_abs.w = _texture->getWidth();
	_obb.w = _obb_abs.h = _texture->getHeight();
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

Sprite::~Sprite()
{
	if (_texture) delete _texture;
}

void Sprite::draw()
{
	static Point _position_lefttop;

	if (_texture == nullptr) return;
	//纹理绘制应传入无偏转时该矩形的左上角
	//而精灵的所储存的坐标是原点到中心点的坐标

	_position_lefttop = _obb_abs.pos - _obb_abs.center;

	_texture->draw(_position_lefttop,														//定位
					_obb_abs.w, _obb_abs.h,													//大小
				  _obb_abs.angle, _obb_abs.center,											//旋转中心
		          getAbsoluteFlipState());													//翻转
}

void Sprite::update()
{
	move();
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

	//整数化，防止绘制时因小数的误差而出现抖动
	_obb.pos.round();
	_obb_abs.pos.round();
}

void Sprite::setCenter(const Point& center)
{	
	Vector off = center - _obb.center;
	_obb.center = _obb_abs.center = center;
	//重新设置中心点位置需要修正精灵的坐标
	_obb.pos += off;
	_obb_abs.pos += off;
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

void Sprite::setFlipState(FLIP flip)
{
	if (flip == FLIP_BOTH || flip == FLIP_HORIZONTAL)
		_obb._flip_horizontal = true;
	if (flip == FLIP_BOTH || flip == FLIP_VERTICAL)
		_obb._flip_vertical = true;
	if(flip == FLIP_NONE) 
		_obb._flip_vertical = _obb._flip_horizontal = false;

	//同步更新绝对状态
	if (_parent == nullptr) {
		_obb_abs._flip_horizontal = _obb._flip_horizontal;
		_obb_abs._flip_vertical = _obb._flip_vertical;
	}
	else {
		_obb_abs._flip_vertical = _obb._flip_vertical;
		_obb_abs._flip_horizontal = _obb._flip_horizontal;
		FLIP parent_flip_state = _parent->getAbsoluteFlipState();

		if (parent_flip_state == FLIP_BOTH || parent_flip_state == FLIP_HORIZONTAL)
			_obb_abs._flip_horizontal = !_obb_abs._flip_horizontal;
		if (parent_flip_state == FLIP_BOTH || parent_flip_state == FLIP_VERTICAL)
			_obb_abs._flip_vertical = !_obb_abs._flip_vertical;
	}
}

FLIP Sprite::getFlipState() const
{
	if (_obb._flip_horizontal) {
		if (_obb._flip_vertical) {
			return FLIP_BOTH;
		}
		else {
			return FLIP_HORIZONTAL;
		}
	}
	else {
		if (_obb._flip_vertical) {
			return FLIP_VERTICAL;
		}
		else {
			return FLIP_NONE;
		}
	}
}

FLIP Sprite::getAbsoluteFlipState() const
{
	if (_obb_abs._flip_horizontal) {
		if (_obb_abs._flip_vertical) {
			return FLIP_BOTH;
		}
		else {
			return FLIP_HORIZONTAL;
		}
	}
	else {
		if (_obb_abs._flip_vertical) {
			return FLIP_VERTICAL;
		}
		else {
			return FLIP_NONE;
		}
	}
}

void Sprite::_update()
{
	update();

	//同步更新绝对翻转状态
	if (_parent == nullptr) {
		_obb_abs._flip_horizontal = _obb._flip_horizontal;
		_obb_abs._flip_vertical = _obb._flip_vertical;
	}
	else {
		_obb_abs._flip_vertical = _obb._flip_vertical;
		_obb_abs._flip_horizontal = _obb._flip_horizontal;
		FLIP parent_flip_state = _parent->getAbsoluteFlipState();

		if (parent_flip_state == FLIP_BOTH || parent_flip_state == FLIP_HORIZONTAL)
			_obb_abs._flip_horizontal = !_obb_abs._flip_horizontal;
		if (parent_flip_state == FLIP_BOTH || parent_flip_state == FLIP_VERTICAL)
			_obb_abs._flip_vertical = !_obb_abs._flip_vertical;
	}

	//递归更新子节点
	for (auto& i : GameObject::_sub) {
		i->_update();
	}
}

void Sprite::_draw()
{
	GameObject::_draw();

#ifdef _SHOW_BOX_
	//绘制包围盒
	Vector lt1 = _obb_abs.getLeftTopPoint();
	Vector lb1 = _obb_abs.getLeftBottomPoint();
	Vector rt1 = _obb_abs.getRightTopPoint();
	Vector rb1 = _obb_abs.getRightBottomPoint();
	TextureManager::drawLine(lt1, lb1);
	TextureManager::drawLine(lb1, rb1);
	TextureManager::drawLine(rb1, rt1);
	TextureManager::drawLine(rt1, lt1);
	TextureManager::drawLine(rt1, lb1);
	TextureManager::drawLine(lt1, rb1);
#endif
	TextureManager::drawLine(Point(0,0), Point(0,10000),0,255,0);
	TextureManager::drawLine(Point(0, 0), Point(10000, 0), 0, 0, 255);
}

void Sprite::move()
{
	//处理速度与加速度，与父节点同步
	unsigned int d = InputHandler::instance()->getIntervalTime();
	Vector new_velocity = _obb.velocity + _obb.acceleration * d;
	setVelocity(_obb.velocity + _obb.acceleration * d);		//同步由set完成
	setPosition(_obb.pos + _obb.velocity * d);

	//处理角速度与角加速度，与父节点同步
	setAngularVelocity(_obb.angular_velocity + _obb.angular_acceleration * d);
	setAngle(_obb.angle + _obb.angular_velocity * d);
}

bool Sprite::detectCollisionsOnTileMap(Vector* offset_)
{
	static CollisionManager* collision_manager = CollisionManager::instance();
	Vector offset;		//偏移，指出如何移动时的精灵与地图的Tile分离
	bool flag;
	if (flag = collision_manager->isCollisedWithTile(*this, offset)) {
		setPosition(getPosition() + offset);
	}

	if (offset_ != nullptr) {
		*offset_ = offset;
	}

	return flag;
}
