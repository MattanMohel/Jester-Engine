#include "Gameobject.h"

#include "Application.h"

Object* Object::Instantiate(std::string&& name)
{
	static ID id = 0;
	return Application::Get()->AddGameobject(name, id++);
}

void Object::Destroy(Object* object)
{
	Application::Get()->RemoveGameobject(object);
	delete object;
}

Info Object::hasComponent(unsigned int hash)
{
	for (size_t i = 0; i < m_Components.size(); i++)
		if (hash == HASH_OF(*m_Components[i])) return { true, i };

	return { false, 0 };
}

Object::Object(const std::string& name, const ID& id)
	: name(name), m_ID(id), transform(this)
{}

Object::~Object()
{
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

void Object::OnCollisionEnter(Collider& other, Vector2 indices)
{
	for (auto& component : m_Components)
		component->OnCollisionEnter(other, indices);

	for (auto& child : transform.m_Children)
		child->object->OnCollisionEnter(other, indices);
}

void Object::OnCollisionStay(Collider& other, Vector2 indices)
{
	for (auto& component : m_Components)
		component->OnCollisionStay(other, indices);

	for (auto& child : transform.m_Children)
		child->object->OnCollisionStay(other, indices);
}

void Object::OnCollisionExit(Collider& other, Vector2 indices)
{
	for (auto& component : m_Components)
		component->OnCollisionExit(other, indices);

	for (auto& child : transform.m_Children)
		child->object->OnCollisionExit(other, indices);
}
