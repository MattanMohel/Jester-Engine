#pragma once

#include "Internal.h"
#include "../Core/Application.h"
#include "../Core/Input.h"

class TimeKeeper : public Component
{
	void OnUpdate(const Time* Time)
	{
		if (Input::GetKey(KeySig::Escape))
		Logger::Print(Time->DeltaTime());
	}
};

