#pragma once

#include <vector>
#include "Log.h"

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

private:
	Application() {};

	~Application() { delete Get(); Logger::Print(LogFlag::Info, "Application Terminated"); }

	//adds gameobject from overall Gameobject vector
	void AddGameobject(Gameobject* gameobject);
	
	//removes gameobject from overall Gameobject vector
	void RemoveGameobject(Gameobject* gameobject);
	
	const std::vector<Gameobject*>& GetGameobjects();

	static bool isRunning;
private:
	std::vector<Gameobject*> m_GameobjectRegistry;
};