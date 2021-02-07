#pragma once
/**
* @brief 向量类
* 也作为点坐标
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
	double operator*(const Vector& rhs) const;	//内积
	Vector operator*(double scale) const;		//数乘
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

/**点坐标，即向量类*/
typedef Vector Point;