#pragma once

#include <vector>
#include "Log.h"

class Object;

using ID = long long unsigned int;

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
	Object* AddGameobject(const std::string&, const ID&);
	//removes gameobject from overall Gameobject vector
	void RemoveGameobject(Object*);
	
	static bool isRunning;

private:
	std::vector<Object*> m_GameobjectRegistry;
};