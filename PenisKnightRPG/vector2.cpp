#include "vector2.h"
vector2::vector2()
{
	x = y = 0;
}
vector2::vector2(float xx,float yy)
{
	x = xx;
	y = yy;
}
vector2::~vector2()
{}

double vector2::getNorm()
{
	return sqrt(x * x + y * y);
}
double vector2::getAngle()
{
	return atan2(y, x) / M_PI * 180;
}
double vector2::getRad()
{
	return atan2(y, x);
}
vector2 vector2::unitvec()
{
	return vector2(cos(getRad()), sin(getRad()));
}

//operator overloading
vector2 vector2::operator+(const vector2& v)
{
	vector2 tmp;
	tmp.x = x + v.x;
	tmp.y = y + v.y;
	return tmp;
}
vector2 vector2::operator-(const vector2& v)
{
	vector2 tmp;
	tmp.x = x - v.x;
	tmp.y = y - v.y;
	return tmp;
}
vector2 vector2::operator*(const float speed)
{
	vector2 tmp;
	tmp.x = x * speed;
	tmp.y = y * speed;
	return tmp;
}
vector2 vector2::operator<(const float xx)
{
	vector2 tmp;
	tmp.x = x + xx;
	tmp.y = y;
	return tmp;
}
vector2 vector2::operator>(const float yy)
{
	vector2 tmp;
	tmp.x = x;
	tmp.y = y + yy;
	return tmp;
}
void vector2::operator*=(double rad)
{
	x = x * cos(rad);
	y = y * sin(rad);
}
void vector2::operator+=(const vector2& v)
{
	x += v.x;
	y += v.y;
}
void vector2::operator-=(const vector2& v)
{
	x -= v.x;
	y -= v.y;
}
void vector2::operator<<(const float xx)
{
	x += xx;
}
void vector2::operator>>(const float yy)
{
	y += yy;
}
vector2 operator<(float xx, vector2& v)
{
	vector2 tmp;
	tmp.x = xx + v.x;
	tmp.y = v.y;
	return tmp;
}
vector2 operator>(float yy, vector2& v)
{
	vector2 tmp;
	tmp.x = v.x;
	tmp.y = yy + v.y;
	return tmp;
}
vector2 operator*(double rad, vector2& v)
{
	vector2 tmp;
	tmp.x = v.x * cos(rad);
	tmp.y = v.y * sin(rad);
	return tmp;
}