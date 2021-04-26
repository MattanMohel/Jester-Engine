#pragma once

#include <vector>
#include "Log.h"
#include "Vector2.h"

class Gameobject; 

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#define TIME_BETWEEN_FIXED_UPDATE 0.02f

class Application
{
	friend class Gameobject;

public:
	static Application* Get();

	void Init();
	void Run();

	inline const std::vector<Gameobject*>& GetGameobjects() { return m_GameobjectRegistry; }

private:
	Application() {};

	~Application() { delete Get(); Logger::Print(LogFlag::Info, "Application Terminated"); }

	//adds gameobject from overall Gameobject vector
	void AddGameobject(Gameobject* gameobject);
	
	//removes gameobject from overall Gameobject vector
	void RemoveGameobject(Gameobject* gameobject);
	
	static bool isRunning;

private:
	std::vector<Gameobject*> m_GameobjectRegistry;
};