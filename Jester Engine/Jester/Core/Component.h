#pragma once

#include "Vector2.h"
class Object;
class Collider;

#include <typeindex>
#define HASH_OF(comp) std::type_index(typeid(comp)).hash_code()

class Component
{
	friend class Object; 

public:
	// Resturns the component's name
	virtual const char* GetName() { return "Component"; }
	// Awake call - in app initiation
	virtual void OnAwake()        {}
	// Update call - once per frame
	virtual void OnUpdate()       {}
	// Editor call - called in play/edit mode
	virtual void OnEditorUpdate() {}
	// GUI call - once per frame
	virtual void OnGuiUpdate()    {}
	// Destructor - called on destroy
	virtual void OnDestroy()      {}

	// Called on frame of collision
	virtual void OnCollisionEnter(Collider& other, Vector2 indices) {}
	// Called on every frame of collision
	virtual void OnCollisionStay(Collider& other, Vector2 indices)  {}
	// Called on last frame of collision
	virtual void OnCollisionExit(Collider& other, Vector2 indices)  {}

	// The owning object of the component
	Object* object;
	// Whether to update the component or not
	bool isEnabled = true;

protected:
	~Component() { OnDestroy(); }

private:

	Component* Init(Object* obj)
	{
		this->object = obj;
		return this;
	}
};