#include "OBB.h"
#include <cmath>

OBB::OBB(int x_, int y_, int w_, int h_, double angle_, Point center_):
	pos(x_,y_), w(w_), h(h_), angle(angle_), center(center_)
{
}

bool OBB::collisionDetecting(const OBB& rhs) const
{   
	//OBB碰撞检测算法
	double radian_a = degree2radian(angle);
	double radian_b = degree2radian(rhs.angle);
	double sin_a = sin(radian_a), cos_a = cos(radian_a);
	double sin_b = sin(radian_b), cos_b = cos(radian_b);
	//该OBB碰撞盒的两个轴
	Vector axis1(-sin_a, cos_a);
	Vector axis2(cos_a, sin_a);
	//两碰撞盒 矩形中心 点连线向量
	double x1 = cos_a * (w / 2.0 - center.x) - sin_a * (h / 2.0 - center.y) + pos.x;		//相当于getRectCenter
	double y1 = cos_a * (h / 2.0 - center.y) + sin_a * (w / 2.0 - center.x) + pos.y;
	double x2 = cos_b * (rhs.w / 2.0 - rhs.center.x) - sin_b * (rhs.h / 2.0 - rhs.center.y) + rhs.pos.x;
	double y2 = cos_b * (rhs.h / 2.0 - rhs.center.y) + sin_b * (rhs.w / 2.0 - rhs.center.x) + rhs.pos.y;
	Vector c2c(x1 - x2, y1 - y2);
	//代表rhs的碰撞盒的两条边的向量
	Vector edge1(-(rhs.h * sin(radian_b)), rhs.h * cos(radian_b));
	Vector edge2(rhs.w * cos(radian_b), rhs.w * sin(radian_b));

	double project1 = abs(axis1 * edge1) + abs(axis1 * edge2); //rhs在axis1轴上的投影的绝对值
	double project2 = abs(axis2 * edge1) + abs(axis2 * edge2); //rhs在axis2轴上的投影的绝对值
	double project1_c2c = abs(axis1 * c2c);						//中心点连线在axis1轴上的投影的绝对值
	double project2_c2c = abs(axis2 * c2c);						//中心点连线在axis2轴上的投影的绝对值

	//rhs在一条轴上的投影 与 该矩形在这条轴上的投影 的和的二分之一 是否 大于其中点连线在该轴上的投影
	if ((project1 + h) / 2 < project1_c2c) return false;
	if ((project2 + w) / 2 < project2_c2c) return false;

	return true;
}

Point OBB::getLeftTopPoint() const
{
	double radian_a = degree2radian(angle);
	double cos_a = cos(radian_a);
	double sin_a = sin(radian_a);
	return Point(cos_a * (0 - center.x) - sin_a * (0 - center.y) + pos.x,
		cos_a * (0 - center.y) + sin_a * (0 - center.x) + pos.y);
}

Point OBB::getLeftBottomPoint() const
{
	double radian_a = degree2radian(angle);
	double cos_a = cos(radian_a);
	double sin_a = sin(radian_a);
	return Point(cos_a * (0 - center.x) - sin_a * (h - center.y) + pos.x,
		cos_a * (h - center.y) + sin_a * (0 - center.x) + pos.y);
}

Point OBB::getRightTopPoint() const
{
	double radian_a = degree2radian(angle);
	double cos_a = cos(radian_a);
	double sin_a = sin(radian_a);
	return Point(cos_a * (w - center.x) - sin_a * (0 - center.y) + pos.x,
		cos_a * (0 - center.y) + sin_a * (w - center.x) + pos.y);
}

Point OBB::getRightBottomPoint() const
{
	double radian_a = degree2radian(angle);
	double cos_a = cos(radian_a);
	double sin_a = sin(radian_a);
	return Point(cos_a * (w - center.x) - sin_a * (h - center.y) + pos.x,
		cos_a * (h - center.y) + sin_a * (w - center.x) + pos.y);
}

Vector OBB::getEdge1() const
{
	double radian_a = degree2radian(angle);
	return Vector(-(h * sin(radian_a)), h * cos(radian_a));
}

Vector OBB::getEdge2() const
{
	double radian_a = degree2radian(angle);
	return Vector(w * cos(radian_a), w * sin(radian_a));
}

Vector OBB::getAxisY() const
{
	double radian_a = degree2radian(angle);
	return Vector(-sin(radian_a), cos(radian_a));
}

Vector OBB::getAxisX() const
{
	double radian_a = degree2radian(angle);
	return Vector(cos(radian_a), sin(radian_a));
}

Point OBB::getRectCenter() const
{
	double radian_a = degree2radian(angle);
	double cos_a = cos(radian_a);
	double sin_a = sin(radian_a);
	return Point(cos_a * (w / 2.0 - center.x) - sin_a * (h / 2.0 - center.y) + pos.x,
		cos_a * (h / 2.0 - center.y) + sin_a * (w / 2.0 - center.x) + pos.y);
}