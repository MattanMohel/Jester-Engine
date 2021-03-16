#pragma once

#include "Jester.h"

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

	void AddGameobject(Gameobject* gameobject);

	void RemoveGameobject(Gameobject* gameobject);
	
	std::vector<Gameobject*> GetGameobjects();

private:

	bool isRunning = true;

	std::vector<Gameobject*> m_Gameobjects;

	static constexpr float TIME_BETWEEN_FIXED_UPDATE = 0.2f;
};