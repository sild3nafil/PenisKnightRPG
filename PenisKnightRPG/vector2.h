#pragma once
#include <math.h>
#include <SDL.h>

class vector2
{
public:
	vector2();
	vector2(float, float);
	~vector2();

	float x;
	float y;
	int ix;
	int iy;

	void IndexXY() { ix = (int)(x / 32), iy = (int)(y / 32); }
	void setXY(float xx, float yy) { x = xx, y = yy; };
	void reset() { x = y = 0; }
	void multiply(int a, int b) { x *= a, y *= b; }
	void rotate(double rad) { x = x * cos(rad) - y * sin(rad), y = x * sin(rad) + y * cos(rad); }
	double getNorm();
	double getAngle();
	double getRad();
	vector2 unitvec();

	//operator overloading
	vector2 operator+(const vector2& v);
	vector2 operator-(const vector2& v);
	vector2 operator*(const float speed);
	vector2 operator<(const float xx);
	vector2 operator>(const float yy);
	void operator*=(double rad);
	void operator+=(const vector2& v);
	void operator-=(const vector2& v);
	void operator<<(const float xx);
	void operator>>(const float yy);
	friend vector2 operator<(float x, vector2& v);
	friend vector2 operator>(float y, vector2& v);
	friend vector2 operator*(double rad, vector2& v);
};

