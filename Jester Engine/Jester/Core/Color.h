#pragma once

struct Color
{
	Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{}

	float* GetValuePointer()
	{
		float* c[4] = { &r, &g, &b, &a };
		return *c;
	}

	float r, g, b, a;
};