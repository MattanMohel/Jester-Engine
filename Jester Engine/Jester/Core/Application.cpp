#include "Application.h"

#include "Time.h"
#include "Window.h"
#include "Gameobject.h"
#include "Rigidbody.h"

#include "../Renderer/Renderer.h"
#include "../User Interface/ImGuiContext.h"
#include "../User Interface/UI.h"

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
	Renderer::Init();
	Window::Get();
	Time::Init();
}

void Application::Run()
{
	// Object OnAwake Call
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

		// Object OnUpdate Call
		for (size_t i = 0; i < m_GameobjectRegistry.size(); i++)
		{
			if (!(m_GameobjectRegistry[i]->isEnabled)) continue;
			m_GameobjectRegistry[i]->OnUpdate(); 
		}

		// Rigidbody update - position
		for (auto& rb : Rigidbody::GetRigidbodies())
			rb->object->transform.position += rb->velocity * rb->GetVelocityMultiplier() * Time::DeltaTime();

		Jester::UI::RenderHierarchy(); 

		// Rendering
		Renderer::Render();
		UIContext::RenderFrame();  
		int display_w, display_h;
		glfwGetFramebufferSize(Window::Get()->window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		Window::Get()->SwapBuffers();
		Window::EndFrame();
	}

	// Clean-up
	Renderer::Shutdown(); 
	UIContext::ShutDown(); 
	delete Window::Get();
	isRunning = false;
}

Object* Application::AddGameobject(const std::string& name, const ID& id)
{
	return m_GameobjectRegistry.emplace_back(new Object(name, id));
}

void Application::RemoveGameobject(Object* gameobject)
{
	const auto& it = std::find(m_GameobjectRegistry.begin(), m_GameobjectRegistry.end(), gameobject);
	m_GameobjectRegistry.erase(it);
}


