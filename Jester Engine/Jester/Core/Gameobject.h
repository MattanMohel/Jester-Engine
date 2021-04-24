#pragma once

#include <vector>
#include <typeindex>
#include <unordered_map>

#include "Log.h"
#include "Application.h"
#include "Component.h"
#include "Transform.h"

class Timer; 
class Collider;
class Transform;

#define HASH_OF(TComponent) std::type_index(typeid(TComponent)).hash_code()

class Gameobject  
{

	friend class Application;
	friend class Collider;

public:
	/*Instances a new Gameobject, returns a pointer
	Adds the gameobject to the gameobject registry only at
	the end of the frame to avoid confusion in the application*/
	static Gameobject* Instantiate(std::string&& name);
	//Destroys Gameobject pointer
	static void Destroy(Gameobject* gameobject);

	std::string name;
	bool isEnabled = true;
	Transform* transform;

	//Adds component of type TComponent
	template<typename TComponent>
	TComponent* AddComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (hasComponent(HASH_OF(TComponent)))
		{
			Logger::Print(LogFlag::Warning, "Tried to add duplicate component to ", name);
			return nullptr;
		}

		auto* component = new TComponent();
		component->Init(this);

		m_Components.push_back(component);
		return component; 
	}	
	
	//Removes component of type TComponent
	template<typename TComponent>
	void RemoveComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (!(hasComponent(HASH_OF(TComponent))))
		{
			Logger::Print(LogFlag::Warning, "Tried to remove non-existing component from ", name);
			return;
		}

		size_t index = getComponentIndex(HASH_OF(TComponent));
		delete m_Components[index];
		m_Components.erase(m_Components.begin() + index);
	}

	//Accesses type TComponent of gameobject
	template<typename TComponent>
	TComponent* GetComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		return (TComponent*)m_Components[getComponentIndex(HASH_OF(TComponent))]; 
	}

	//Finds first instance of type TComponent
	template<typename TComponent>
	static TComponent* FindComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		for (Gameobject* gameobject : Application::Get()->GetGameobjects())
			if (gameobject->hasComponent(HASH_OF(TComponent))) 
				return (TComponent*)(gameobject->m_Components[gameobject->getComponentIndex(HASH_OF(TComponent))]); 

		return nullptr;
	}	
	
	//Finds all instances of type TComponent 
	template<typename TComponent>
	static std::vector<TComponent*> FindComponents()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		std::vector<TComponent*> components; 

		for (Gameobject* gameobject : Application::Get()->GetGameobjects()) 
			if (gameobject->hasComponent(HASH_OF(TComponent))) 
				components.push_back((TComponent*)gameobject->m_Components[gameobject->getComponentIndex(HASH_OF(TComponent))]);

		return components;
	}

private:
	bool hasComponent(unsigned int hash);
	size_t getComponentIndex(unsigned int hash);

	Gameobject(std::string& name);
	~Gameobject();

	void OnAwake();
	void OnUpdate();
	void OnFixedUpdate();

	void OnCollisionEnter(Collider& other);
	void  OnCollisionStay(Collider& other);
	void  OnCollisionExit(Collider& other);

private:

	std::vector<Component*> m_Components;
	unsigned long m_ID;
};

