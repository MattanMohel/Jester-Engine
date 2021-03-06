#include "Transform.h"
#include "Gameobject.h"
#include "../Renderer/RendererBase.h"

Transform::Transform(Object* object)
	: object(object), m_Parent(this), m_Root(this)
	, position(0, 0), scale(1, 1), rotation(0) { }

Transform::~Transform()
{
	for (Transform* child : m_Children)
	{
		delete child;
	}

	m_Parent->RemoveChild(object);
}

Vector2 Transform::RotateAround(const Vector2& pos, const Vector2& scale, const Vector2& offset, const float theta)
{
	return Vector2(pos.x * scale.x * cos(-theta * Deg2Rad) - pos.y * scale.y * sin(-theta * Deg2Rad),
		pos.x * scale.x * sin(-theta * Deg2Rad) + pos.y * scale.y * cos(-theta * Deg2Rad)) + offset;
}

Vector2 Transform::RotateAround(const Vector2& pos, const Transform& transform)
{
	return Vector2(pos.x * transform.scale.x * cos(-transform.rotation * Deg2Rad) - pos.y * transform.scale.y * sin(-transform.rotation * Deg2Rad),
		pos.x * transform.scale.x * sin(-transform.rotation * Deg2Rad) + pos.y * transform.scale.y * cos(-transform.rotation * Deg2Rad)) + transform.position;
}

void Transform::Refresh()
{
	m_Root = m_Parent->m_Root;
	for (Transform* child : m_Children)
	{
		child->Refresh();
	}
}

void Transform::SetChild(Object* gameobject)
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

void Transform::RemoveChild(const Object* gameobject)
{
	const size_t index = std::find(m_Children.begin(), m_Children.end(), &gameobject->transform) - m_Children.begin();

	m_Children[index]->m_Parent = m_Children[index];
	m_Children[index]->m_Root = m_Children[index];
	m_Children[index]->Refresh();

	m_Children.erase(m_Children.begin() + index);
}

Object* Transform::GetChild(const size_t index)
{
	return m_Children[index]->object;
}

Object* Transform::GetParent()
{
	return m_Parent->object;
}

Object* Transform::GetRoot()
{
	return m_Root->object;
}