#pragma once

class Time;
class Collider;
class Gameobject;

#define DERIVES_FROM_COMPONENT_ASSERT static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must derive from Component")

//Base Component
class Component
{

	friend class Gameobject; 

public:
	//called once on app initialization
	virtual void OnAwake() {}
	//called once every frame
	virtual void OnUpdate(const Time* Time) {}
	//called once every .2 seconds;
	virtual void OnFixedUpdate(const Time* Time) {}

	//collision calls, overridden in specialization
	virtual void OnCollisionEnter(Collider& other) {}
	virtual void  OnCollisionStay(Collider& other) {}
	virtual void  OnCollisionExit(Collider& other) {}

	Gameobject* gameobject;
	bool isEnabled = true;

protected:
	~Component()
	{}

private:
	//initializes gameobject value
	virtual void Init(Gameobject* gameobject)
	{
		this->gameobject = gameobject;
	}
};