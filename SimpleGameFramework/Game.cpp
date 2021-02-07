#include "Game.h"
#include "Window.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Player.h"
#include "Layer.h"
#include "Sprite.h"
#include <iostream>
using std::cout;

Game* Game::_instance = nullptr;
Game::Game()
{
	//创建窗口
	_win = new Window("Demo", 900, 1500);

	//初始化纹理资源管理器
	TextureManager::init(*_win);

	//将游戏程序退出状态设为nullptr
	insertState("over", nullptr);
	changeState("over");

	initGame();
}

Game* Game::instance()
{
	if (_instance == nullptr) {
		_instance = new Game;
	}
	return _instance;
}

void Game::initGame()
{
	//游戏内容初始化
	auto root = new Layer;
	auto ball = new Sprite("ball", 100, 100, 0, Point(50, 50));
	ball->setAngularAcceleration(0.000001);
	root->insert(ball);

	auto player = new Player;
	root->insert(player);

	auto rect1 = new Sprite("rect1", 200, 200, 20, Point(50, 100));
	rect1->setAngularVelocity(0.01);
	rect1->setAcceleration(Vector(0.00002, 0.00003));
	root->insert(rect1);

	auto rect2 = new Sprite("rect2", 300, 200, 0, Point(-50, -50));
	rect2->setAngularAcceleration(0.000003);
	root->insert(rect2);

	auto sun = new Sprite("sun", 700, 400, 0.0, Point(25,25));
	sun->setAngularVelocity(0.03);
	root->insert(sun);

	auto earth = new Sprite("earth", 0, 200, 0.0, Point(15,15));
	earth->setAngularVelocity(0.03);
	sun->insert(earth);

	auto moon = new Sprite("moon", 0, 50, 0.0, Point(12,12));
	moon->setAngularVelocity(0.03);
	earth->insert(moon);

	insertState("play",root);
	changeState("play");
}


void Game::mainloop()
{
	InputHandler* inputHandler = InputHandler::instance();
	unsigned int frame = 0, start_time;
	while (_root) {
		if (frame == 0) start_time = inputHandler->getTime();

		inputHandler->update();
		update();
		draw();
		
		//帧率测试
		if (++frame == 100) {
			cout << "fps:" << frame*1000 / (inputHandler->getTime() - start_time)<<'\n';
			frame = 0;
		}
	}
}

void Game::changeState(string state_name)
{
	_root = states[state_name];
}

void Game::insertState(string state_name, GameObject* root)
{
	states.insert({ state_name, root });
}

void Game::update()
{
	_root->_update();
}

void Game::draw()
{
	_win->clear();
	_root->_draw();
	_win->present();
}