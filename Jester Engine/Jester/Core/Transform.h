#pragma once

#include <vector>
#include "Vector2.h"
class Gameobject;

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
	float rotation;

	void Translate(float x, float y) { position += Vector2(x, y); }
	void Dilate(float x, float y) { scale += Vector2(x, y); }
	void Rotate(float angle) { rotation += angle; }

	//returns your position rotated by a specified angle around a given point
	static Vector2 RotateAround(const Vector2& pos, const Vector2& scale, const Vector2& offset, const float theta);
	static Vector2 RotateAround(const Vector2& pos, const Transform& transform);

	inline bool operator== (Transform& transform) const
	{
		return position == transform.position &&
			scale == transform.scale && rotation == transform.rotation;
	}	
	
	inline bool operator!= (Transform& transform) const
	{
		return position != transform.position &&
			scale != transform.scale && rotation != transform.rotation;
	}

private:
	void Refresh();

	Transform* m_Root;
	Transform* m_Parent;

	std::vector<Transform*> m_Children;
};

