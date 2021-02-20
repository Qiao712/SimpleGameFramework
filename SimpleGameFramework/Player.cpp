#include "Player.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include <iostream>
#include <memory>
using std::cout;
using std::make_shared;

Player::Player()
{
	_head = make_shared<Sprite>("head_player", 0, 0);
	_head->setCenter(Point(_head->getWidth() / 2, _head->getHeight()));

	_hand_left = make_shared<Sprite>("hand_player", 0, 0);
	_hand_left->setCenter(Point(_hand_left->getWidth() / 2, 0));
	_hand_left->setPosition(_head->getPosition());

	_body = make_shared<Sprite>("body_player_animation", 0, 0);
	_body->setCenter(Point(_body->getWidth() / 2, 0));
	_body->setPosition(_head->getPosition());

	_hand_right = make_shared<Sprite>("hand_player", 0, 0);
	_hand_right->setCenter(Point(_hand_right->getWidth() / 2, 0));
	_hand_right->setPosition(_head->getPosition());

	setPosition(Point(0, 0));
	setHeight(_head->getHeight() + _body->getHeight());
	setWidth(_head->getWidth());

	insert(_hand_left);
	insert(_head);
	insert(_body);
	insert(_hand_right);
}

void Player::update()
{	
	control();
	
	move();

	bool flag = detectCollisionsOnTileMap();

	//根据是否与Tile碰撞，设置下落的速度
	if (flag) {
		Vector velocity = getVelocity();
		velocity.y = 0;
		setVelocity(velocity);
	}
	else {
		Vector velocity = getVelocity();
		velocity.y = 0.4;
		setVelocity(velocity);
	}

	//翻转
	if (getVelocity().x < 0) setFlipState(FLIP_HORIZONTAL);
	if (getVelocity().x > 0) setFlipState(FLIP_NONE);

	//行走时的动作处理
	walkingAction();
}

void Player::control()
{
	setVelocity(Vector(0, 0.5));
	if (InputHandler::instance()->getKeyState('A')) {
		setVelocity(getVelocity() + Vector(-0.3, 0));
	}
	if (InputHandler::instance()->getKeyState('D')) {
		setVelocity(getVelocity() + Vector(0.3, 0));
	}
	if (InputHandler::instance()->getButtonClicks(LEFT_BUTTON) >= 2) {
		Point p = Camera::instance()->transform2abs(InputHandler::instance()->getCursorPos());
		setPosition(p);
	}
	if (InputHandler::instance()->getKeyChange('R') == DOWN)
		setAngle(getAngle() + 30);
}

void Player::walkingAction()
{
	//行走动画
	if (getVelocity().x != 0)
		_body->getTexture().play();
	else {
		_body->getTexture().pause();
		_body->getTexture().setCurrentFrame(0);
	}

	//手在行走时的摆动
	if (getVelocity() == Vector(0, 0)) {
		_hand_left->setAngle(0);
		_hand_right->setAngle(0);
		_hand_left->setAngularVelocity(0);
		_hand_right->setAngularVelocity(0);
	}
	else {
		//左手
		if (_hand_left->getAngularVelocity() > 0) {
			if (_hand_left->getAngle() > 30) {
				_hand_left->setAngularVelocity(-0.1);
			}
		}
		else if (_hand_left->getAngularVelocity() < 0) {
			if (_hand_left->getAngle() < -30) {
				_hand_left->setAngularVelocity(0.1);
			}
		}
		else {
			_hand_left->setAngularVelocity(0.1);
		}

		//右手
		if (_hand_right->getAngularVelocity() > 0) {
			if (_hand_right->getAngle() > 30) {
				_hand_right->setAngularVelocity(-0.1);
			}
		}
		else if (_hand_right->getAngularVelocity() < 0) {
			if (_hand_right->getAngle() < -30) {
				_hand_right->setAngularVelocity(0.1);
			}
		}
		else {
			_hand_right->setAngularVelocity(-0.1);
		}
	}
}
