#include "Application.h"

#include "UI.h"

#include "Time.h"
#include "Gameobject.h"
#include "Component.h"
#include "Window.h"

bool Application::isRunning = false;

Application* Application::Get()
{
	static Application* s_Instance = new Application();

	return s_Instance;
}

void Application::Init()
{
	Logger::Print(LogFlag::Info, "Init");
	UIContext::Init(); 
	Window::Get();
	Time::Init();
}

void Application::Run()
{
	/*Gameobject OnAwake Call*/
	for (size_t i = 0; i < m_GameobjectRegistry.size(); i++)
	{
		if (!(m_GameobjectRegistry[i]->isEnabled)) continue;
		m_GameobjectRegistry[i]->OnAwake();
	}

	Logger::Print(LogFlag::Info, "Running");

	isRunning = true;
	while (!Window::shouldClose())
	{
		UIContext::NewFrame();
		Window::PollEvents();
		Time::OnUpdate();

		Window::Get()->GLClear();

		/*Gameobject OnFixedUpdate Call*/
		static float FIXED_UPDATE_TIMER = 0;
		FIXED_UPDATE_TIMER += Time::DeltaTime();

		if (FIXED_UPDATE_TIMER > TIME_BETWEEN_FIXED_UPDATE)
		{
			FIXED_UPDATE_TIMER = 0;

			for (size_t i = 0; i < m_GameobjectRegistry.size(); i++)
			{
				if (!(m_GameobjectRegistry[i]->isEnabled)) continue;
				m_GameobjectRegistry[i]->OnFixedUpdate();
			}
		}

		/*Gameobject OnUpdate Call*/
		for (size_t i = 0; i < m_GameobjectRegistry.size(); i++)
		{
			if (!(m_GameobjectRegistry[i]->isEnabled)) continue;
			m_GameobjectRegistry[i]->OnUpdate(); 
		}

		UIContext::RenderHierarchy(); 

		// Rendering
		UIContext::RenderFrame(); 
		int display_w, display_h;
		glfwGetFramebufferSize(Window::Get()->window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		Window::Get()->SwapBuffers();
		Window::EndFrame();
	}

	//Clean-up
	UIContext::ShutDown(); 
	delete Window::Get();
	isRunning = false;
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


