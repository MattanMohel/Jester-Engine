#pragma once

#include <vector>
#include "Vector2.h"

class Object;

class Transform 
{

	friend class Object;

public:
	Transform(Object*);
	~Transform();

	void SetChild(Object*);

	void RemoveChild(const size_t);
	void RemoveChild(const Object*);
	Object* GetChild(const size_t);
	Object* GetParent();
	Object* GetRoot();

	Object* object;

	Vector2 scale;
	Vector2 position;
	float rotation;

	void Translate(float x, float y) { position += Vector2(x, y); }
	void Dilate(float x, float y) { scale += Vector2(x, y); }
	void Rotate(float angle) { rotation += angle; }

	//returns your position rotated by a specified angle around a given point
	static Vector2 RotateAround(const Vector2&, const Vector2&, const Vector2&, const float);
	static Vector2 RotateAround(const Vector2&, const Transform&);

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

