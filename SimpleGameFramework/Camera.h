#pragma once
#include "Vector.h"
#include "GameObject.h"
class GameObject;
/**
* @brief 相机类\n
* Singletion\n
* 控制屏幕所显示的游戏场景的范围。\n
* 通过坐标的变换来完成。
*/
class Camera
{
public:
	static Camera* instance();

	/**设置位置，左上角绝对坐标位置*/
	void setPosition(Point position);
	Point getPosition() { return _position; }
	
	/**设置位置，矩形中心绝对坐标位置*/
	void setCenterPosition(Point position) { setPosition(position - Vector(_w / 2, _h / 2));}
	Point getCenterPosition() { return _position + Vector(_w / 2, _h / 2); }

	/**转换到窗口坐标*/
	Point transform2win(const Point& pos_abs);
	/**转换到绝对坐标*/
	Point transform2abs(const Point& pos_win);

	/**设置相机跟随的焦点*/
	void setTarget(GameObjectPtr target) { _target = target; }

	/**更新位置，跟随焦点*/
	void update();
private:
	static Camera* _instance;

	Camera();

	/**相机拍摄矩形区域 左上角 在绝对坐标系中的位置*/
	Point _position;
	int _w;
	int _h;

	/**跟随的目标*/
	GameObjectPtr _target;
};