#include "Transform.h"

#include "Gameobject.h"

Transform::Transform(Gameobject* gameobject)
	: gameobject(gameobject), m_Parent(this), m_Root(this)
	, position(0, 0), scale(1, 1), rotation(0) { }

Transform::~Transform()
{
	for (Transform* child : m_Children)
	{
		delete child;
	}

	m_Parent->RemoveChild(gameobject);
}

Vector2 Transform::RotateAround(const Vector2& pos, const Vector2& scale, const Vector2& offset, const float theta)
{
	return Vector2(pos.x * scale.x * cos(theta) - pos.y * scale.y * sin(theta),
		pos.x * scale.x * sin(theta) + pos.y * scale.y * cos(theta)) + offset;
}

Vector2 Transform::RotateAround(const Vector2& pos, const Transform& transform)
{
	return Vector2(pos.x * transform.scale.x * cos(transform.rotation) - pos.y * transform.scale.y * sin(transform.rotation),
		pos.x * transform.scale.x * sin(transform.rotation) + pos.y * transform.scale.y * cos(transform.rotation)) + transform.position;
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
	gameobject->transform.m_Parent = this; 
	gameobject->transform.Refresh(); 

	m_Children.push_back(&gameobject->transform); 
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
	const size_t index = std::find(m_Children.begin(), m_Children.end(), &gameobject->transform) - m_Children.begin();

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