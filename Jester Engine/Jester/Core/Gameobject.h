#pragma once

#include <vector>
#include <typeindex>
#include <unordered_map>

#include "Vector2.h"

#include "Log.h"
#include "Application.h"
#include "Component.h"
class Timer; 

class Collider;
class Transform;
#include "Transform.h"

#define HASH_OF(TComponent) std::type_index(typeid(TComponent)).hash_code()

class Gameobject  
{

	friend class Application;
	friend class Collider;

public:
	//Instances a new Gameobject, returns a pointer
	static Gameobject* Instantiate(std::string&& name);
	//Destroys Gameobject pointer
	static void Destroy(Gameobject* gameobject);

	std::string name;
	bool isEnabled = true;
	Vector2 position;
	Transform* transform;

	//Adds component of type TComponent
	template<typename TComponent>
	void AddComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (m_Components.find(HASH_OF(TComponent)) != m_Components.end())
		{
			Logger::Print(LogFlag::Warning, "Tried to add duplicate component to ", name);
			return;
		}

		auto* component = new TComponent();
		component->Init(this);

		m_Components.insert({ HASH_OF(TComponent), component });
	}	
	
	//Removes component of type TComponent
	template<typename TComponent>
	void RemoveComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (m_Components.find(HASH_OF(TComponent)) == m_Components.end())
		{
			Logger::Print(LogFlag::Warning, "Tried to remove non-existing component from ", name);
			return;
		}

		delete m_Components[HASH_OF(TComponent)];
		m_Components.erase (HASH_OF(TComponent));
	}

	//Accesses type TComponent of gameobject
	template<typename TComponent>
	TComponent* GetComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		return (TComponent*)m_Components[HASH_OF(TComponent)];
	}

	//Finds first instance of type TComponent
	template<typename TComponent>
	static TComponent* FindComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		for (Gameobject* gameobject : Application::Get()->GetGameobjects())
		{
			if (gameobject->m_Components.find(HASH_OF(TComponent)) != gameobject->m_Components.end())
			{
				return (TComponent*)(gameobject->m_Components[HASH_OF(TComponent)]);
			}
		}

		return nullptr;
	}	
	
	//Finds all instances of type TComponent 
	template<typename TComponent>
	static std::vector<TComponent*> FindComponents()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		std::vector<TComponent*> components; 

		for (Gameobject* gameobject : Application::Get()->GetGameobjects()) 
		{
			if (gameobject->m_Components.find(HASH_OF(TComponent)) != gameobject->m_Components.end())
			{
				components.push_back((TComponent*)gameobject->m_Components[HASH_OF(TComponent)]);
			}
		}

		return components;
	}

private:

	Gameobject(std::string& name);
	~Gameobject();

	void OnAwake();
	void OnUpdate(const Time* Time);
	void OnFixedUpdate(const Time* Time);

	void OnCollisionEnter(Collider& other);
	void  OnCollisionStay(Collider& other);
	void  OnCollisionExit(Collider& other);

private:

	std::unordered_map<unsigned short, Component*> m_Components;
	unsigned long m_ID;
};

