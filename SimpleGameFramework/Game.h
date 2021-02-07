#pragma once
#include <map>
#include <string>
using std::map;
using std::string;
class Window;
class GameObject;

/**
* @brief ��ʾ������Ϸ������������Դ \n
* ΪSingleton \n
* �����ʼ����Ϸ���ݡ���Ϸ������ѭ����
* �л���Ϸ״̬������Ϸ�������ĸ��ڵ㣩\n
*/
class Game
{
public:
	static Game* instance();

	/**
	* @brief ��Ϸ���ݳ�ʼ��
	*/
	void initGame();	
	/**
	*@brief ��Ϸ������ѭ��(��ȡ�û����룬��Ϸ������߼�����Ⱦ)
	*/
	void mainloop();	
	/**
	* @brief �л���Ϸ״̬
	* @param state_name ״̬��
	*/
	void changeState(string state_name);	
	/**
	* @brief ����һ����״̬���������ʾ����
	* @param state_name Ҫ�����״̬��
	* @Param state ״̬������Ϸ�������ĸ��ڵ�
	*/
	void insertState(string state_name, GameObject* state); //������״̬����������Ϸ�������ĸ��ڵ�
protected:
	static Game* _instance;

	Game();

	/**
	* @brief һ֡����Ҫ�����ĸ��£�ִ����Ϸ�߼�
	*/
	void update();
	/**
	* @brief ������Ϸ����
	*/
	void draw();

	
	Window* _win;

	GameObject* _root;					//! ��Ϸ��ǰ״̬������һ����Ϸ�������ĸ��ڵ�
	
	map<string, GameObject*> states;		//! ״̬����״̬������Ϸ�������ĸ��ڵ㣩��ӳ��
};

