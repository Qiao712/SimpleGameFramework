#pragma once
/**
* @brief ������
* Ҳ��Ϊ������
*/
class Vector
{
public:
	explicit Vector(double x = 0, double y = 0) : x(x), y(y) { };

	void setX(double x_) { x = x_; }
	void setY(double y_) { y = y_; }
	void set(double x_, double y_) { x = x_; y = y_; }

	Vector operator+(const Vector& rhs) const;
	Vector operator-(const Vector& rhs) const;
	double operator*(const Vector& rhs) const;	//�ڻ�
	Vector operator*(double scale) const;		//����
	Vector operator/(double scale) const;
	Vector& operator+=(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);
	Vector& operator*=(double scale);
	Vector& operator/=(double scale);
	bool   operator==(const Vector& rhs) const;
	bool   operator!=(const Vector& rhs) const;
	double length() const;
	double projection(const Vector& rhs) const;
	
	double x;
	double y;
};

/**�����꣬��������*/
typedef Vector Point;