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
	//�������Ӧ������ƫתʱ�þ��ε����Ͻ�
	//��������������������ԭ�㵽���ĵ������

	_position_lefttop = _obb_abs.pos - _obb_abs.center;

	_texture->draw(_position_lefttop,														//��λ
					_obb_abs.w, _obb_abs.h,													//��С
				  _obb_abs.angle, _obb_abs.center,											//��ת����
		          getAbsoluteFlipState());													//��ת
}

void Sprite::update()
{
	move();
}

void Sprite::setPosition(const Point& pos)
{
	_obb.pos = pos;
	//ͬ������λ��
	if (_parent == nullptr) _obb_abs.pos = pos;
	else {
		//���λ�õ�����λ�õ�ת��,Ҫ���游�ڵ���ת
		double radian_a = degree2radian(_parent->getAbsoluteAngle());
		double cos_a = cos(radian_a);
		double sin_a = sin(radian_a);
		_obb_abs.pos = Point(cos_a * _obb.pos.x - sin_a * _obb.pos.y,
							 cos_a * _obb.pos.y + sin_a * _obb.pos.x)  + _parent->getAbsolutePosition();
	}

	//����������ֹ����ʱ��С�����������ֶ���
	_obb.pos.round();
	_obb_abs.pos.round();
}

void Sprite::setCenter(const Point& center)
{	
	Vector off = center - _obb.center;
	_obb.center = _obb_abs.center = center;
	//�����������ĵ�λ����Ҫ�������������
	_obb.pos += off;
	_obb_abs.pos += off;
}

void Sprite::setVelocity(const Vector& velocity)
{
	_obb.velocity = velocity;

	if (_parent == nullptr) _obb_abs.velocity = velocity;
	else {
		//���ٶ�ת������������ϵ��,������任����������ϵ��
		double radian_a = degree2radian(_parent->getAbsoluteAngle());
		double cos_a = cos(radian_a);
		double sin_a = sin(radian_a);
		//����ٶ������Ļ�
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
		//�����ٶ�ת������������ϵ��,������任����������ϵ��
		double radian_a = degree2radian(_parent->getAbsoluteAngle());
		double cos_a = cos(radian_a);
		double sin_a = sin(radian_a);
		//��Լ��ٶ������Ļ�
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

	//ͬ�����¾���״̬
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

	//ͬ�����¾��Է�ת״̬
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

	//�ݹ�����ӽڵ�
	for (auto& i : GameObject::_sub) {
		i->_update();
	}
}

void Sprite::_draw()
{
	GameObject::_draw();

#ifdef _SHOW_BOX_
	//���ư�Χ��
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
	//�����ٶ�����ٶȣ��븸�ڵ�ͬ��
	unsigned int d = InputHandler::instance()->getIntervalTime();
	Vector new_velocity = _obb.velocity + _obb.acceleration * d;
	setVelocity(_obb.velocity + _obb.acceleration * d);		//ͬ����set���
	setPosition(_obb.pos + _obb.velocity * d);

	//������ٶ���Ǽ��ٶȣ��븸�ڵ�ͬ��
	setAngularVelocity(_obb.angular_velocity + _obb.angular_acceleration * d);
	setAngle(_obb.angle + _obb.angular_velocity * d);
}

bool Sprite::detectCollisionsOnTileMap(Vector* offset_)
{
	static CollisionManager* collision_manager = CollisionManager::instance();
	Vector offset;		//ƫ�ƣ�ָ������ƶ�ʱ�ľ������ͼ��Tile����
	bool flag;
	if (flag = collision_manager->isCollisedWithTile(*this, offset)) {
		setPosition(getPosition() + offset);
	}

	if (offset_ != nullptr) {
		*offset_ = offset;
	}

	return flag;
}
