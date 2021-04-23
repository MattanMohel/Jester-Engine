#pragma once

class Gameobject;
#include "Gameobject.h"
#include "Vector3.h"
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

	Vector2 scale;
	Vector2 position;
	Vector3 rotation;

	void Translate(float x, float y) { position += Vector2(x, y); }
	void Dilate(float x, float y, float z) { scale += Vector2(x, y); }
	void Rotate(float x, float y, float z) { rotation += Vector3(x, y, z); }

	//returns your position rotated by a specified angle around a given point
	static Vector2 RotateAround(const Vector2& pos, const Vector2& scale, const Vector2& offset, const float theta);
	static Vector2 RotateAround(const Vector2& pos, const Transform& transform);

private:
	void Refresh();

	Transform* m_Root;
	Transform* m_Parent;

	std::vector<Transform*> m_Children;
};

