#include "Application.h"

#include "Time.h"
#include "Gameobject.h"
#include "Component.h"
#include "Renderer/Window.h"

bool Application::isRunning = false;

Application* Application::Get()
{
	static Application* s_Instance = new Application();

	return s_Instance;
}

void Application::Init()
{
	Logger::Print(LogFlag::Info, "Init");
	Window::Get();
}

void Application::Run()
{
	//On Awake Call
	for (size_t i = 0; i < m_GameobjectRegistry.size(); i++)
	{
		if (!(m_GameobjectRegistry[i]->isEnabled)) continue;
		m_GameobjectRegistry[i]->OnAwake();
	}

	Logger::Print(LogFlag::Info, "Running");

	isRunning = true;
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

			for (size_t i = 0; i < m_GameobjectRegistry.size(); i++)
			{
				if (!(m_GameobjectRegistry[i]->isEnabled)) continue;
				m_GameobjectRegistry[i]->OnFixedUpdate(Time::Get());
			}
		}

		//Call Gameobject Updates
		for (size_t i = 0; i < m_GameobjectRegistry.size(); i++)
		{
			if (!(m_GameobjectRegistry[i]->isEnabled)) continue;
			m_GameobjectRegistry[i]->OnUpdate(Time::Get());
		}

		Window::Get()->SwapBuffers();
		Window::EndFrame();
	}

	isRunning = false;
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
