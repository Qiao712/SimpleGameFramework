#include "Player.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include <iostream>
using std::cout;

Player::Player()
{
	setPosition(Point(150, 150));
	setWidth(200);
	setHeight(200);
	_texture_head = TextureManager::create("head_player");
	_texture_body = TextureManager::create("body_player");
	_texture_hand = TextureManager::create("hand_player");
}

void Player::update()
{
	setVelocity(Vector(0,0));
	if (InputHandler::instance()->getKeyState('A')) {
		setVelocity(getVelocity() + Vector(-0.3, 0));
	}
	if (InputHandler::instance()->getKeyState('D')) {
		setVelocity(getVelocity() + Vector(0.3, 0));
	}
	if (InputHandler::instance()->getKeyState('W')) {
		setVelocity(getVelocity() + Vector(0, -0.3));
	}
	if (InputHandler::instance()->getKeyState('S')) {
		setVelocity(getVelocity() + Vector(0, 0.3));
	}

	if(InputHandler::instance()->getButtonClicks(LEFT_BUTTON) >= 2)
		setPosition(InputHandler::instance()->getCursorPos());

	if (InputHandler::instance()->getKeyChange('R') == DOWN)
		setAngle(getAngle() + 30);
}

//void Player::draw()
//{
//	_texture_head.draw(getX(), getY());
//	const int x_body = getX() + (_texture_head.getWidth() - _texture_body.getWidth()) / 2;
//	const int y_body = getY() + _texture_head.getHeight();
//	_texture_body.draw(x_body, y_body);
//	const int x_hand = getX() + (_texture_head.getWidth() - _texture_hand.getWidth()) / 2;
//	const int y_hand = getY() + _texture_head.getHeight() + 10;
//	_texture_hand.draw(x_hand, y_hand);
//}