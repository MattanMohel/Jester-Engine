#include "Gameobject.h"

Gameobject* Gameobject::Instantiate(std::string&& name)
{
	auto* gameobject = new Gameobject(name);
	
	static unsigned long curr_ID = 0;
	gameobject->m_ID = curr_ID;
	curr_ID++;

	return gameobject;
}

void Gameobject::Destroy(Gameobject* gameobject)
{
	delete gameobject;
}

Gameobject::Gameobject(std::string& name)
	:name(name), m_ID(0), transform(new Transform(this)), position({0, 0})
{
	Application::Get()->AddGameobject(this);
}

Gameobject::~Gameobject()
{
	Logger::Print("Deleting ", name);

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

void Gameobject::OnCollisionEnter(Collider& other)
{
	for (auto& component : m_Components)
		component.second->OnCollisionEnter(other);

	for (auto& child : transform->m_Children)
		child->gameobject->OnCollisionEnter(other);
}

void Gameobject::OnCollisionStay(Collider& other)
{
	for (auto& component : m_Components)
		component.second->OnCollisionStay(other);

	for (auto& child : transform->m_Children)
		child->gameobject->OnCollisionStay(other);
}

void Gameobject::OnCollisionExit(Collider& other)
{
	for (auto& component : m_Components)
		component.second->OnCollisionExit(other);

	for (auto& child : transform->m_Children)
		child->gameobject->OnCollisionExit(other);
}
