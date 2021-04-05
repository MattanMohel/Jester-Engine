#pragma once

class Gameobject;
#include "Gameobject.h"
#include "Vector2.h"

class Transform 
{

	friend class Gameobject;

public:
	Transform(Gameobject* gameobject);
	~Transform();

	void SetChild(Gameobject* transform);

	void RemoveChild(const size_t index);
	void RemoveChild(const Gameobject* gameobject);
	Gameobject* GetChild(const size_t index);
	Gameobject* GetParent();
	Gameobject* GetRoot();

	Gameobject* gameobject;

	Vector2 position;
	Vector2 scale;

	float rotation;

private:
	void Refresh();

	Transform* m_Root;
	Transform* m_Parent;

	std::vector<Transform*> m_Children;
};

