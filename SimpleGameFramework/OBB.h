#pragma once
#include "Vector.h"
#define double_pi 6.2831853
#define degree2radian(A) A/360*double_pi
/**
* OrientedBoundingBox OBB��Χ����
* ����һ������б�ǵľ��Σ��������ٶȡ����ٶȡ����ٶȡ��Ǽ��ٶ� \n
* ʵ����ײ���
*/
class OBB
{
public:
	OBB(int x = 0, int y = 0, int w = 0, int h = 0, double angle = 0, Point center = Point(0,0));

	/**
	* @brief ��ײ���
	* @param ��һ����Χ��
	* @return 0: δ��ײ 1:��ײ
	*/
	bool collisionDetecting(const OBB& rhs) const;

	//���º�����ʵ��δ����
	//��ȡ4����������
	Point getLeftTopPoint()			const;
	Point getLeftBottomPoint()		const;
	Point getRightTopPoint()			const;
	Point getRightBottomPoint()		const;
	//��ȡ�������ߵ�����
	Vector getEdge1()				const;
	Vector getEdge2()				const;
	//��ȡ�������߷���ĵ�λ����
	Vector getAxisY()				const;
	Vector getAxisX()				const;
	//��ȡ���ĵ�
	Point getRectCenter()				const;

	/**�ð�Χ�е����꣬��center������ϵ�ڵ�����*/
	Point pos;

	unsigned int w = 0;		//! ��
	unsigned int h = 0;		//! ��

	double angle = 0;					//! ��ת�Ƕȣ���centerΪ��ת����,��λ:��, ����:˳ʱ��
	Point center = Vector(0, 0);			//! ���ĵ㣬����ת����Ͷ�λ�������õĵ㣬������������Ͻǵ�����(���Ͻ�(0,0))

	Vector velocity = Vector();			//! �ٶ�
	Vector acceleration = Vector();		//! ���ٶ�
	double angular_velocity = 0;			//! ���ٶ�
	double angular_acceleration = 0;		//! �Ǽ��ٶ�
};

