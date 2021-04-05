#include "Application.h"

Application* Application::Get()
{
	static Application* s_Instance = new Application();

	return s_Instance;
}

void Application::Init()
{
	Logger::Print(LogFlag::Info, "Init");

	Time::Get()->Init();

	//On Awake Call
	for (Gameobject* gameobject : m_GameobjectRegistry)
	{
		if (!(gameobject->isEnabled)) continue;
		gameobject->OnAwake(); 
	}
}

void Application::Run()
{
	Logger::Print(LogFlag::Info, "Running");

	while (isRunning)
	{
		//Update Time Instance
		Time::Get()->OnUpdate();

		//Check for FixedUpdate
		static float FIXED_UPDATE_TIMER = 0;
		FIXED_UPDATE_TIMER += Time::Get()->DeltaTime();

		if (FIXED_UPDATE_TIMER > TIME_BETWEEN_FIXED_UPDATE)
		{
			FIXED_UPDATE_TIMER = 0;

			for (Gameobject* gameobject : m_GameobjectRegistry)
			{
				if (!(gameobject->isEnabled)) continue;
				gameobject->OnFixedUpdate(Time::Get());
			}
		}

		//Call Gameobject Updates
		for (Gameobject* gameobject : m_GameobjectRegistry)
		{
			if (!(gameobject->isEnabled)) continue;
			gameobject->OnUpdate(Time::Get());
		}
	}
}

bool Application::Close()
{
	isRunning = false;
	return false;
}

void Application::AddGameobject(Gameobject* gameobject)
{
	m_GameobjectRegistry.push_back(gameobject);
}

void Application::RemoveGameobject(Gameobject* gameobject)
{
	const auto& it = std::find(m_GameobjectRegistry.begin(), m_GameobjectRegistry.end(), gameobject);
	m_GameobjectRegistry.erase(it);
}

std::vector<Gameobject*> Application::GetGameobjects()
{
	return m_GameobjectRegistry;
}
