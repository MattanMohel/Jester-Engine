#pragma once

#include <cmath>

struct Vector2
{
	Vector2()
		: x(0), y(0)
	{}

	Vector2(float x, float y)
		: x(x), y(y)
	{}

	float* GetValuePointer() 
	{ 
		float* v[2] { &x, &y };
		return *v; 
	}

	float* GetValue() const
	{
		float v[2] { x, y };
		return v;
	}

	//returns the magnitude of a vector
	float Magnitude() const
	{
		return sqrt(x * x + y * y);
	}
	//returns a magnitude of a vector without taking the root
	float SquaredMagnitude() const
	{
		return x * x + y * y;
	}

	//returns a vector with x-y components ranging from 0 to 1
	Vector2 Normalized() const
	{
		float mag = Magnitude();
		return { x / mag, y / mag };
	}

	static float DotProduct(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	//returns absolute value of length, squared
	static float SquaredDistance(const Vector2& a, const Vector2& b)
	{
		return abs((a.x - b.x) * (a.x - b.x)
			+ (a.y - b.y) * (a.y - b.y));
	}
	//returns absolute value of length
	static float Distance(const Vector2& a, const Vector2& b)
	{
		return 	sqrt(abs((a.x - b.x) * (a.x - b.x)
			+ (a.y - b.y) * (a.y - b.y)));
	}
	//returns length, squared
	static float SquaredLength(const Vector2& a, const Vector2& b)
	{
		return (a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y);
	}
	//returns length
	static float Length(const Vector2& a, const Vector2& b)
	{
		return 	sqrt((a.x - b.x) * (a.x - b.x)
			+ (a.y - b.y) * (a.y - b.y));
	}

	void operator+= (const Vector2& vec2)
	{
		x += vec2.x;
		y += vec2.y;
	}
	void operator-= (const Vector2& vec2)
	{
		x -= vec2.x;
		y -= vec2.y;
	}
	void operator*= (const float& multiplier)
	{
		x *= multiplier;
		y *= multiplier;
	}	
	void operator*= (const Vector2& multiplier)
	{
		x *= multiplier.x;
		y *= multiplier.y;
	}
	void operator/= (const float& divider)
	{
		x /= divider;
		y /= divider;
	}		
	void operator/= (const Vector2& divider)
	{
		x /= divider.x;
		y /= divider.y;
	}	

	Vector2 operator+ (const Vector2& vec2) const
	{
		return Vector2(x + vec2.x, y + vec2.y);
	}
	Vector2 operator- (const Vector2& vec2) const
	{
		return Vector2(x - vec2.x, y - vec2.y);
	}	
	Vector2 operator* (const float& num) const
	{
		return Vector2(x * num, y * num);
	}	
	Vector2 operator* (const Vector2& num) const
	{
		return Vector2(x * num.x, y * num.y);
	}
	Vector2 operator/ (const float& num) const
	{
		return Vector2(x / num, y / num);
	}	
	Vector2 operator/ (const Vector2& num) const
	{
		return Vector2(x / num.x, y / num.y);
	}

	bool operator== (const Vector2 vec2) const
	{
		return vec2.x == x && vec2.y == y;
	}	
	
	bool operator!= (const Vector2 vec2) const
	{
		return !(vec2.x == x && vec2.y == y);
	}

	//static friend std::ostream& operator<< (std::ostream& os, const Vector2& vec2)
	//{
	//	os << "x: " << vec2.x << " y: " << vec2.y;
	//	return os;
	//}

	float x = 0, y = 0; 

	static const Vector2 Right;
	static const Vector2 Zero;
	static const Vector2 One; 
	static const Vector2 Up;
};
