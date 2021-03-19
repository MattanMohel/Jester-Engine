#pragma once

#include "Internal.h"

class Sample : public Component
{
public:
	void OnAwake() override;
	void OnFixedUpdate(const Time* Time) override;

	void SetInt(int a)
	{
		m_Int = a;
	}
	int GetInt()
	{
		return m_Int;
	}

	int m_Int = 5;
};

