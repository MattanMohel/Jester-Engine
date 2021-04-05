#pragma once

#include <cmath>
#include <iostream>
#include "Vector2.h"

struct  Vector3
{
public:
	 Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}	 
	 
	 Vector3(Vector2 xy, float z)
		: x(xy.x), y(xy.y), z(z)
	 {}	 
	 
	 Vector3(float x, Vector2 yz)
		 : x(x), y(yz.x), z(yz.y)
	 {}

	//returns a vector with x-y components ranging from 0 to 1
	 Vector3 Normalized() const
	 {
		if (x > y)
		{
			if (x > z)
			{
				return  Vector3(1, y / x, z / x);
			}
		}
		if (y > z)
		{
			return  Vector3(x / y, 1, z / y);
		}
		else
		{
			return Vector3(x / z, y / z, 1);
		}
	}

	//returns absolute value of length, squared
	static float SquaredDistance(const  Vector3& a, const  Vector3& b)
	{
		return abs((a.x - b.x) * (a.x - b.x)
			+ (a.y - b.y) * (a.y - b.y)
			+ (a.z - b.z) * (a.z - b.z));
	}
	//returns absolute value of length
	static float Distance(const  Vector3& a, const  Vector3& b)
	{
		return 	sqrt(abs((a.x - b.x) * (a.x - b.x)
			+ (a.y - b.y) * (a.y - b.y)
			+ (a.z - b.z) * (a.z - b.z)));
	}
	//returns length, squared
	static float SquaredLength(const  Vector3& a, const  Vector3& b)
	{
		return (a.x - b.x) * (a.x - b.x)
			+ (a.y - b.y) * (a.y - b.y)
			+ (a.z - b.z) * (a.z - b.z);
	}
	//returns length
	static float Length(const  Vector3& a, const  Vector3& b)
	{
		return 	sqrt((a.x - b.x) * (a.x - b.x)
			+ (a.y - b.y) * (a.y - b.y)
			+ (a.z - b.z) * (a.z - b.z));
	}

	void operator+= (const  Vector3& vec3)
	{
		x += vec3.x;
		y += vec3.y;
		z += vec3.z;
	}
	void operator-= (const  Vector3& vec3)
	{
		x -= vec3.x;
		y -= vec3.y;
		z -= vec3.z;
	}
	void operator*= (const float& multiplier)
	{
		x *= multiplier;
		y *= multiplier;
		z *= multiplier;
	}
	void operator/= (const float& divider)
	{
		x /= divider;
		y /= divider;
		z /= divider;
	}

	 Vector3 operator+ (const  Vector3& vec3)
	{
		return  Vector3(x + vec3.x, y + vec3.y, z + vec3.z);
	}
	 Vector3 operator- (const  Vector3& vec3)
	{
		return  Vector3(x - vec3.x, y - vec3.y, z - vec3.z);
	}
	 Vector3 operator* (const float& num)
	{
		return  Vector3(x * num, y * num, z * num);
	}
	 Vector3 operator/ (const float& num)
	{
		return  Vector3(x / num, y / num, z / num);
	}

	static friend std::ostream& operator<< (std::ostream& os, const  Vector3& vec3)
	{
		os << "x: " << vec3.x << " y: " << vec3.y << " z: " << vec3.z;
		return os;
	}

public:
	float x = 0, y = 0, z = 0;
};
