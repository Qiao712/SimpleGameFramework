#include "Game.h"
#include "Window.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "InputHandler.h"
#include "Player.h"
#include "Layer.h"
#include "Sprite.h"
#include "TileFactory.h"
#include "TileMapManager.h"
#include "TileMap.h"
#include <iostream>
#include <memory>
using std::cout;
using std::make_shared;

Game* Game::_instance = nullptr;
Game::Game()
{
	//创建窗口
	Window::init("Dome", 900,1500);

	//初始化纹理资源管理器
	TextureManager::init();

	TileFactory::init();

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
	//创建层
	auto root = make_shared<Layer>();
	root->setBackground("background_forest");

	//创建TileMap对象
	auto tile_map = make_shared<TileMap>(100, 100, 50, 50);
	root->insert(tile_map);

	//创建玩家对象
	auto player = make_shared<Player>();
	root->insert(player);
	
	//绑定地图管理器
	TileMapManager::instance()->bindTileMap(*tile_map);
	TileMapManager::instance()->genMap();

	//设置相机的焦点
	Camera::instance()->setTarget(player);

	//将创建的层作为根节点（状态），开始执行
	insertState("play",root);
	changeState("play");
}


void Game::mainloop()
{
	InputHandler* inputHandler = InputHandler::instance();
	Camera* camera = Camera::instance();
	unsigned int frame = 0, start_time;
	while (_root) {
		if (frame == 0) start_time = inputHandler->getTime();
		
		inputHandler->update();
		update();
		camera->update();
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

void Game::insertState(string state_name, GameObjectPtr state)
{
	states.insert({ state_name, state });
}

void Game::update()
{
	_root->_update();
}

void Game::draw()
{
	static Window* win = Window::instance();
	win->clear();
	_root->_draw();
	win->present();
}