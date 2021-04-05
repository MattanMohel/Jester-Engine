#pragma once

#include <vector>

#include "Log.h"
#include "Time.h"
#include "Gameobject.h"
#include "Component.h"

class Application
{
	friend class Gameobject;

public:
	static Application* Get();

	void Init();

	void Run();

	bool Close();

private:
	Application() {};

	~Application() { delete Get(); std::cout << "Application Terminated"; }

	//adds gameobject from overall Gameobject vector
	void AddGameobject(Gameobject* gameobject);
	
	//removes gameobject from overall Gameobject vector
	void RemoveGameobject(Gameobject* gameobject);
	
	std::vector<Gameobject*> GetGameobjects();

private:

	bool isRunning = true;

	std::vector<Gameobject*> m_GameobjectRegistry;

	static constexpr float TIME_BETWEEN_FIXED_UPDATE = 0.2f;
};