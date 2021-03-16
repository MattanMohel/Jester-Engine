#pragma once

#include "Jester.h"

#define DERIVES_FROM_COMPONENT_ASSERT static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must derive from Component")

typedef unsigned int COMP_ID;

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
	
	//initializes gameobject value
	virtual void Init(Gameobject* gameobject)
	{
		this->gameobject = gameobject;
	}

	Gameobject* gameobject;

protected:

	~Component()
	{
		std::cout << "Deleted Component\n";
	}

	//retrieves static data identifier
	static const COMP_ID& NewID()
	{
		static COMP_ID currID = 0; 
		currID++;

		return currID;
	}
};