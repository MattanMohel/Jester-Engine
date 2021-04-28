#pragma once

#include "Window.h"
#include <cmath>

class Application;

class Time
{

#define MIL 1000.0f

	friend class Application;

public:
	static void Init();
	static void OnUpdate();

	static inline float DeltaTime() { return deltaTime; }
	static inline float TimeSinceStartupInSeconds() { return timeSinceInit - glfwGetTime(); }
	static inline float TimeSinceStartupInMilliseconds() { return (timeSinceInit - glfwGetTime()) / MIL; }

	static inline double GetFPS() { return round(1 / deltaTime); }

private:
	static double deltaTime, previousTime;
	static long double timeSinceInit;
}; 