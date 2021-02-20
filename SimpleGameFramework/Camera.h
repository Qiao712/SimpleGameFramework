#pragma once
#include "Vector.h"
#include "GameObject.h"
class GameObject;
/**
* @brief �����\n
* Singletion\n
* ������Ļ����ʾ����Ϸ�����ķ�Χ��\n
* ͨ������ı任����ɡ�
*/
class Camera
{
public:
	static Camera* instance();

	/**����λ�ã����ϽǾ�������λ��*/
	void setPosition(Point position);
	Point getPosition() { return _position; }
	
	/**����λ�ã��������ľ�������λ��*/
	void setCenterPosition(Point position) { setPosition(position - Vector(_w / 2, _h / 2));}
	Point getCenterPosition() { return _position + Vector(_w / 2, _h / 2); }

	/**ת������������*/
	Point transform2win(const Point& pos_abs);
	/**ת������������*/
	Point transform2abs(const Point& pos_win);

	/**�����������Ľ���*/
	void setTarget(GameObjectPtr target) { _target = target; }

	/**����λ�ã����潹��*/
	void update();
private:
	static Camera* _instance;

	Camera();

	/**�������������� ���Ͻ� �ھ�������ϵ�е�λ��*/
	Point _position;
	int _w;
	int _h;

	/**�����Ŀ��*/
	GameObjectPtr _target;
};