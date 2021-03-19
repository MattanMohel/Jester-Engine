#include "Gameobject.h"

Gameobject* Gameobject::Instantiate(std::string&& name)
{
	auto* gameobject = new Gameobject(name);

	return gameobject;
}

void Gameobject::Destroy(Gameobject* gameobject)
{
	delete gameobject;
}

Gameobject::Gameobject(std::string& name)
	:name(name), transform(new Transform(this))
{
	Application::Get()->AddGameobject(this);
}

Gameobject::~Gameobject()
{
	Logger::Print("Deleting Object");

	delete transform;

	Application::Get()->RemoveGameobject(this);

	for (auto& component : m_Components)
	{
		delete component.second;
	}
}

void Gameobject::OnAwake()
{
	for (auto& component : m_Components)
	{
		component.second->OnAwake();
	}
}

void Gameobject::OnUpdate(const Time* Time)
{
	for (auto& component : m_Components)
	{
		if (!(component.second->isEnabled)) continue;
		component.second->OnUpdate(Time);
	}
}

void Gameobject::OnFixedUpdate(const Time* Time)
{
	for (auto& component : m_Components)
	{
		component.second->OnFixedUpdate(Time);
	}
}