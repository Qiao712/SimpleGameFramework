#pragma once
#include <map>
#include <string>
#include "GameObject.h"
using std::map;
using std::string;
class Window;
class GameObject;

/**
* @brief 表示整个游戏，整合所有资源 \n
* 为Singleton \n
* 负责初始化游戏内容、游戏进程主循环、
* 切换游戏状态（即游戏对象树的根节点）\n
*/
class Game
{
public:
	static Game* instance();

	/**
	* @brief 游戏内容初始化
	*/
	void initGame();	
	/**
	*@brief 游戏进程主循环(获取用户输入，游戏对象的逻辑，渲染)
	*/
	void mainloop();	
	/**
	* @brief 切换游戏状态
	* @param state_name 状态名
	*/
	void changeState(string state_name);	
	/**
	* @brief 加入一个新状态，并赋予表示名称
	* @param state_name 要赋予的状态名
	* @Param state 状态，即游戏对象树的根节点
	*/
	void insertState(string state_name, GameObjectPtr state); //加入新状态，加入新游戏对象树的根节点
protected:
	static Game* _instance;

	Game();

	/**
	* @brief 一帧内所要做出的更新，执行游戏逻辑
	*/
	void update();
	/**
	* @brief 绘制游戏内容
	*/
	void draw();

	GameObjectPtr _root;					//! 游戏当前状态，即根一个游戏对象树的根节点
	
	map<string, GameObjectPtr> states;		//! 状态名到状态（即游戏对象树的根节点）的映射
};

