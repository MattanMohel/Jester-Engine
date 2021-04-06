#pragma once

#include "Internal.h"

class SampleComponent : public Component
{
public:
	void OnAwake() override;
	void OnUpdate(const Time* Time) override;

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

