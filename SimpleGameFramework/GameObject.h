#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include "Vector.h"
using std::string;
using std::vector;

/**
* @brief ��Ϸ�����࣬��Ϸ������Ԫ�ص���Ļ���\n
* �����㡢�����.\n
* ����һ���ӽڵ���б����γ����Ľṹ.\n
* ���е���ϷҪ�������ṹ��֯.
*/
class GameObject
{
	friend class Game;
	friend class Sprite;		//Ϊ����Body��_update���Է���_sub��ָ��ָ��Ķ���
public:
	GameObject();
	~GameObject();

	/**ÿһ֡�ĸ��£��ڴν��иö�����߼�ҵ��*/
	virtual void update();
	/**��������*/
	virtual void draw();

	/** ��������Ϸ����*/
	void insert(GameObject* sub);
	/** �Ƴ�����Ϸ����*/
	void remove(GameObject* sub);
	/** ��ø���Ϸ����*/
	GameObject* getParent() const { return _parent; }
	/** ��ȡ���ڱ��������ӽڵ���׵������� Ϊ����������*/
	vector<GameObject*>::const_iterator begin() const { return _sub.cbegin(); }
	/** ��ȡ���ڱ��������ӽڵ��β��������� Ϊ����������*/
	vector<GameObject*>::const_iterator end() const { return _sub.cend(); }

	/**
	* @name ���ڻ�ȡ�������������ϵ������\n
	* GameObject��������Щ���ԣ���Sprite�ڼ�������ʱ��Ҫʹ���丸�ڵ�ľ�������\n
	* ʹ��Щ�麯������"0"����֤Sprite��GameObjectΪ���ڵ�ʱ�����������������ϵ��\n
	* @{
	*/
	virtual int getAbsoluteX() const { return 0;}
	virtual int getAbsoluteY() const { return 0;}
	virtual Point getAbsolutePosition() const { return Point(0,0); }
	virtual double getAbsoluteAngle() const { return 0; }
	virtual Vector getAbsoluteVelocity() const { return Vector(0, 0); }
	virtual double getAbsoluteAngularVelocity() const { return 0; }
	virtual Vector getAbsoluteAcceleration() const { return Vector(0, 0); }
	virtual double getAbsoluteAngularAcceleration() const { return 0; }
	/** @} */
protected:
	/**���øýڵ�update�������µݹ��ִ���ӽڵ��_update,�����������˳��������ϵ���Ϸ����*/
	virtual void _update();
	/**���øýڵ�draw�������µݹ��ִ���ӽڵ��_draw�������������˳��������ϵ���Ϸ����*/
	virtual void _draw();
	GameObject* _parent = nullptr;	//���ڵ�
	vector<GameObject*> _sub;		//����Ϸ����
};