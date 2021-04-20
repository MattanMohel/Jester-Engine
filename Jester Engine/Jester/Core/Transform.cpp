#include "Transform.h"

Transform::Transform(Gameobject* gameobject)
	: gameobject(gameobject), m_Parent(this), m_Root(this)
	, position(0, 0), scale(1, 1), rotation(0, 0, 0) { }

Transform::~Transform()
{
	for (Transform* child : m_Children)
	{
		delete child;
	}

	m_Parent->RemoveChild(gameobject);
}

void Transform::Refresh()
{
	m_Root = m_Parent->m_Root;
	for (Transform* child : m_Children)
	{
		child->Refresh();
	}
}

void Transform::SetChild(Gameobject* gameobject)
{
	gameobject->transform->m_Parent = this;
	gameobject->transform->Refresh();

	m_Children.push_back(gameobject->transform);
}

void Transform::RemoveChild(const size_t index)
{
	m_Children[index]->m_Parent = m_Children[index];
	m_Children[index]->m_Root = m_Children[index];
	m_Children[index]->Refresh();

	m_Children.erase(m_Children.begin() + index);
}

void Transform::RemoveChild(const Gameobject* gameobject)
{
	const size_t index = std::find(m_Children.begin(), m_Children.end(), gameobject->transform) - m_Children.begin();

	m_Children[index]->m_Parent = m_Children[index];
	m_Children[index]->m_Root = m_Children[index];
	m_Children[index]->Refresh();

	m_Children.erase(m_Children.begin() + index);
}

Gameobject* Transform::GetChild(const size_t index)
{
	return m_Children[index]->gameobject;
}

Gameobject* Transform::GetParent()
{
	return m_Parent->gameobject;
}

Gameobject* Transform::GetRoot()
{
	return m_Root->gameobject;
}