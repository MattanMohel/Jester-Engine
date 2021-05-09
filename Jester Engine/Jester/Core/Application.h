#pragma once

#include <vector>
#include "Log.h"

class Object;

#define TIME_BETWEEN_FIXED_UPDATE 0.02f

class Application
{
	friend class Object;

public:
	static Application* Get();

	void Init();
	void Run();

	inline const std::vector<Object*>& GetGameobjects() { return m_GameobjectRegistry; }

private:
	Application() {};

	~Application() { delete Get(); Logger::Print(LogFlag::Info, "Application Terminated"); }

	//adds gameobject from overall Gameobject vector
	void AddGameobject(Object* gameobject);
	
	//removes gameobject from overall Gameobject vector
	void RemoveGameobject(Object* gameobject);
	
	static bool isRunning;

private:
	std::vector<Object*> m_GameobjectRegistry;
};