#pragma once
#include "GameObject.h"
#include "Vector.h"
#include "OBB.h"
#include <string>
//#define _SHOW_BOX_
using std::string;
/**
* @brief ������
*/
class Sprite : public GameObject
{
	friend class CollisionManager;
public:
	Sprite()=default;
	/** Ĭ��ʹ������Ŀ����Ϊ��OBB��Χ�еĿ��*/
	Sprite(string name_texture, int x, int y, double angle = 0.0, Point center = Point(0,0));
	Sprite(string name_texture, int x, int y,int w, int h, double angle = 0.0, Point center = Point(0,0));
	~Sprite();

	virtual void draw();
	virtual void update();
	
	void setHeight(unsigned int h) { _obb.h = _obb_abs.h = h; }
	void setWidth(unsigned int w) { _obb.w = _obb_abs.w = w; }
	unsigned int getWidth() const { return _obb_abs.w; }
	unsigned int getHeight() const { return  _obb_abs.h; }

	/**��ȡ�Ըö���󶨵�����/����*/
	Texture& getTexture() { return *_texture; }

	/**
	* @brief ��������ڸ��ڵ�����ꡢ�ٶȡ����ٶȡ����ٶȡ��Ǽ��ٶȵ����ԣ�
	* ����ڸ��ڵ����
	* @{
	*/
	void setPosition(int x, int y) { setPosition(Point(x, y)); }
	void setPosition(const Point& pos);
	void setCenter(const Point& center);
	void setVelocity(const Vector& velocity);
	void setAcceleration(const Vector& acceleration);
	void setAngle(double angle);
	void setAngularVelocity(double velocity);
	void setAngularAcceleration(double acceleration);
	void setFlipState(FLIP flip);
	/**
	* @}
	*/

	/**
	* @brief ��ȡ����ڸ��ڵ�����ꡢ�ٶȡ����ٶȡ����ٶȡ��Ǽ��ٶ�
	* @{
	*/
	int getX() const { return _obb.pos.x; }
	int getY() const { return _obb.pos.y; }
	Point getPosition() const { return _obb.pos; }
	Point getCenter() const { return _obb.center;  }
	Vector getVelocity() const { return _obb.velocity; }
	Vector getAcceleration() const { return _obb.acceleration; }
	double getAngle() const { return _obb.angle; }
	double getAngularVelocity() const { return _obb.angular_velocity; }
	double getAngularAcceleration() const { return _obb.angular_acceleration; }
	FLIP getFlipState() const;
	/**
	* @}
	*/
	
	//���Ե����꣬�ٶ�, rhs��Ϊnullptr��������丸�������޸�����������Ϊ��������
	/*void setAbsolutePosition(int x, int y) { setAbsolutePosition(Point(x,y)); }
	void setAbsolutePosition(const Point& pos);
	void setAbsoluteVelocity(const Vector& velocity);
	void setAbsoluteAcceleration(const Vector& acceleration);
	void setAbsoluteAngle(double angle);
	void setAbsoluteAngularVelocity(double velocity);
	void setAbsoluteAngularAcceleration(double acceleration);*/

	/**
	* @brief ��ȡ���Ե����ꡢ�ٶȡ����ٶȡ����ٶȡ��Ǽ��ٶȣ� ���������������ϵ
	* @{
	*/
	Point getAbsolutePosition() const { return _obb_abs.pos; }
	Vector getAbsoluteVelocity() const { return  _obb_abs.velocity; }
	Vector getAbsoluteAcceleration() const { return  _obb_abs.acceleration; }
	double getAbsoluteAngle() const { return  _obb_abs.angle; };
	double getAbsoluteAngularVelocity() const { return  _obb_abs.angular_velocity; }
	double getAbsoluteAngularAcceleration() const { return  _obb_abs.angular_acceleration; }
	FLIP getAbsoluteFlipState() const;
	/**
	* @}
	*/
protected:
	virtual void _update();
	virtual void _draw();

	/**�����ٶȡ����ٶȡ����ٶȡ��Ǽ��ٶ��ƶ�����������*/
	void move();
	/**
	* @brief ������ͼ����ײ����ֹ�䴩͸��ͼ
	* @param offset Vector��ָ�룬���ڷ���ƫ����������nullptr�򲻷���
	*/
	bool detectCollisionsOnTileMap(Vector* offset = nullptr);

	/** �ڸ��ڵ�����ϵ�µ� OBB��Χ�У����ꡢ�ٶ�����ڸ��ڵ�*/
	OBB _obb;
	/** ��������ϵ�µ� OBB��Χ�У����Ե����ꡢ�ٶȣ��������������ϵԭ��*/
	OBB _obb_abs;

	/**����*/
	Texture* _texture = nullptr;
};