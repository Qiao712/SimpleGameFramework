#include "Vector.h"
#include <cmath>

void Vector::round()
{
	x = ::round(x);
	y = ::round(y);
}

Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(x + rhs.x, y + rhs.y);
}

Vector Vector::operator-(const Vector& rhs) const
{
	return Vector(x - rhs.x, y - rhs.y);
}

double Vector::operator*(const Vector& rhs) const
{
	return x*rhs.x + y*rhs.y;
}

Vector Vector::operator*(double scale) const
{
	return Vector(x*scale, y*scale);
}

Vector Vector::operator/(double scale) const
{
	return Vector(x/scale, y/scale);
}

Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector& Vector::operator*=(double scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

Vector& Vector::operator/=(double scale)
{
	x /= scale;
	y /= scale;
	return *this;
}

bool Vector::operator==(const Vector& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vector::operator!=(const Vector& rhs) const
{
	return x != rhs.x || y != rhs.y;
}

double Vector::length() const
{
	return sqrt(x*x + y*y);
}

double Vector::projection(const Vector& rhs) const
{
	return operator*(rhs) / rhs.length();
}

