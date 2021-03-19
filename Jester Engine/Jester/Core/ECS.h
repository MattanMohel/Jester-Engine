#pragma once

class Timer;
class Gameobject;

#define DERIVES_FROM_COMPONENT_ASSERT static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must derive from Component")

//Base Component
class Component
{

	friend class Gameobject; 

public:

	//called in Application->Init
	virtual void OnAwake() {}
	//called in Application->Run every frame
	virtual void OnUpdate(const Time* Time) {}
	//called in Application->Run every .2 seconds;
	virtual void OnFixedUpdate(const Time* Time) {}
	

	Gameobject* gameobject;
	bool isEnabled = true;

protected:

	~Component()
	{
		std::cout << "Deleted Component\n";
	}

private:

	//initializes gameobject value
	virtual void Init(Gameobject* gameobject)
	{
		this->gameobject = gameobject;
	}
};