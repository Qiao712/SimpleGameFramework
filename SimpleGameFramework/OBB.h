#pragma once
#include "Vector.h"
#define double_pi 6.2831853
#define degree2radian(A) A/360*double_pi
/**
* OrientedBoundingBox OBB包围盒类
* 描述一个有倾斜角的矩形，并储存速度、加速度、角速度、角加速度 \n
* 实现碰撞检测
*/
class OBB
{
public:
	OBB(int x = 0, int y = 0, int w = 0, int h = 0, double angle = 0, Point center = Point(0,0));

	/**
	* @brief 碰撞检测
	* @param 另一个包围盒
	* @return 0: 未碰撞 1:碰撞
	*/
	bool collisionDetecting(const OBB& rhs) const;

	//以下函数，实际未调用
	//获取4个顶点坐标
	Point getLeftTopPoint()			const;
	Point getLeftBottomPoint()		const;
	Point getRightTopPoint()			const;
	Point getRightBottomPoint()		const;
	//获取矩形两边的向量
	Vector getEdge1()				const;
	Vector getEdge2()				const;
	//获取矩形两边方向的单位向量
	Vector getAxisY()				const;
	Vector getAxisX()				const;
	//获取中心点
	Point getRectCenter()				const;

	/**该包围盒的坐标，即center在坐标系内的坐标*/
	Point pos;

	unsigned int w = 0;		//! 宽
	unsigned int h = 0;		//! 高

	double angle = 0;					//! 旋转角度，以center为旋转中心,单位:度, 正数:顺时针
	Point center = Vector(0, 0);			//! 中心点，即旋转的轴和定位精灵所用的点，相对于自身左上角的坐标(左上角(0,0))

	Vector velocity = Vector();			//! 速度
	Vector acceleration = Vector();		//! 加速度
	double angular_velocity = 0;			//! 角速度
	double angular_acceleration = 0;		//! 角加速度
};

