#include "Gameobject.h"

#include "Application.h"

Object* Object::Instantiate(std::string&& name)
{
	static ID id = 0; id++;
	auto* gameobject = new Object(name, id);

	return gameobject;
}

void Object::Destroy(Object* gameobject)
{
	delete gameobject;
}

Info Object::hasComponent(unsigned int hash)
{
	for (size_t i = 0; i < m_Components.size(); i++)
		if (hash == HASH_OF(*m_Components[i])) return { true, i };

	return { false, 0 };
}

Object::Object(const std::string& name, const ID& id)
	: name(name), m_ID(id), transform(this)
{
	Application::Get()->AddGameobject(this);
}

Object::~Object()
{
	Application::Get()->RemoveGameobject(this);

	for (auto& component : m_Components)
		delete component;
}

void Object::OnAwake()
{
	for (auto& component : m_Components)
		component->OnAwake();
}

void Object::OnUpdate()
{
	for (auto& component : m_Components)
	{
		if (!(component->isEnabled)) continue;
			component->OnUpdate();
	}
}

void Object::OnCollisionEnter(Collider& other)
{
	for (auto& component : m_Components)
		component->OnCollisionEnter(other);

	for (auto& child : transform.m_Children)
		child->gameobject->OnCollisionEnter(other);
}

void Object::OnCollisionStay(Collider& other)
{
	for (auto& component : m_Components)
		component->OnCollisionStay(other);

	for (auto& child : transform.m_Children)
		child->gameobject->OnCollisionStay(other);
}

void Object::OnCollisionExit(Collider& other)
{
	for (auto& component : m_Components)
		component->OnCollisionExit(other);

	for (auto& child : transform.m_Children)
		child->gameobject->OnCollisionExit(other);
}
