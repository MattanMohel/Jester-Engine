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

bool Gameobject::hasComponent(unsigned int hash)
{
	for (auto& component : m_Components)
	{
		if (hash == HASH_OF(*component))
			return true;
	}

	return false;
}

size_t Gameobject::getComponentIndex(unsigned int hash)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		if (hash == HASH_OF(*m_Components[i]))
			return i;
	}

	return 0;
}

Gameobject::Gameobject(std::string& name)
	:name(name), m_ID(0), transform(new Transform(this))
{
	Application::Get()->AddGameobject(this);
}

Gameobject::~Gameobject()
{
	Logger::Print("Deleting ", name);

	delete transform;

	Application::Get()->RemoveGameobject(this);

	for (auto& component : m_Components)
		delete component;
}

void Gameobject::OnAwake()
{
	for (auto& component : m_Components)
		component->OnAwake();
}

void Gameobject::OnUpdate()
{
	for (auto& component : m_Components)
	{
		if (!(component->isEnabled)) continue;
			component->OnUpdate();
	}
}

void Gameobject::OnFixedUpdate()
{
	for (auto& component : m_Components)
		component->OnFixedUpdate();
}

void Gameobject::OnCollisionEnter(Collider& other)
{
	for (auto& component : m_Components)
		component->OnCollisionEnter(other);

	for (auto& child : transform->m_Children)
		child->gameobject->OnCollisionEnter(other);
}

void Gameobject::OnCollisionStay(Collider& other)
{
	for (auto& component : m_Components)
		component->OnCollisionStay(other);

	for (auto& child : transform->m_Children)
		child->gameobject->OnCollisionStay(other);
}

void Gameobject::OnCollisionExit(Collider& other)
{
	for (auto& component : m_Components)
		component->OnCollisionExit(other);

	for (auto& child : transform->m_Children)
		child->gameobject->OnCollisionExit(other);
}
