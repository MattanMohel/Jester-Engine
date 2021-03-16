#include "Application.h"

Application* Application::Get()
{
	static Application* s_Instance = new Application();

	return s_Instance;
}

void Application::Init()
{
	std::cout << "Init\n";

	Time::Get()->Init();

	//On Awake Call
	for (Gameobject* gameobject : m_Gameobjects)
	{
		gameobject->OnAwake();
	}
}

void Application::Run()
{
	std::cout << "Running\n";

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

			for (Gameobject* gameobject : m_Gameobjects)
			{
				gameobject->OnFixedUpdate(Time::Get());
			}
		}

		//Call Gameobject Updates
		for (Gameobject* gameobject : m_Gameobjects)
		{
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
	m_Gameobjects.push_back(gameobject);
}

void Application::RemoveGameobject(Gameobject* gameobject)
{
	const auto& it = std::find(m_Gameobjects.begin(), m_Gameobjects.end(), gameobject);
	m_Gameobjects.erase(it);
}

std::vector<Gameobject*> Application::GetGameobjects()
{
	return m_Gameobjects;
}
