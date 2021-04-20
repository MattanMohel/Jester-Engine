#include "Application.h"

#include "Time.h"
#include "Gameobject.h"
#include "Component.h"
#include "Renderer/Window.h"

Application* Application::Get()
{
	static Application* s_Instance = new Application();

	return s_Instance;
}

void Application::Init()
{
	Logger::Print(LogFlag::Info, "Init");
	Window::Get(); 

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

	while (!Window::shouldClose())
	{
		//Poll GLFW events
		Window::PollEvents();

		//Update Time Instance
		Time::Get()->OnUpdate();

		Window::Get()->GLClear();

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

		Window::Get()->SwapBuffers();
		Window::EndFrame();
	}

	delete Window::Get();
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

const std::vector<Gameobject*>& Application::GetGameobjects()
{
	return m_GameobjectRegistry;
}
