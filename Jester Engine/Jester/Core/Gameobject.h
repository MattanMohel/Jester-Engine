#pragma once

#include <vector>
#include <typeindex>
#include <unordered_map>

#include "Log.h"
#include "Application.h"
#include "ECS.h"
class Timer; 

class Transform;
#include "Transform.h"

class Gameobject  
{

	friend class Application;

public:
	//Instances a new Gameobject, returns a pointer
	static Gameobject* Instantiate(std::string&& name);
	//Destroys Gameobject pointer
	static void Destroy(Gameobject* gameobject);

	std::string name;
	bool isEnabled = true;
	Transform* transform;

	//Adds component of type TComponent
	template<typename TComponent>
	void AddComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (m_Components.find(std::type_index(typeid(TComponent))) != m_Components.end())
		{
			Logger::Print(LogFlag::Warning, "Tried to add duplicate component to ", name);
			return;
		}

		auto* component = new TComponent();
		component->Init(this);

		m_Components.insert({ std::type_index(typeid(TComponent)), component });
	}	
	
	//Removes component of type TComponent
	template<typename TComponent>
	void RemoveComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (m_Components.find(std::type_index(typeid(TComponent))) == m_Components.end())
		{
			Logger::Print(LogFlag::Warning, "Tried to remove non-existing component from ", name);
			return;
		}

		delete m_Components[std::type_index(typeid(TComponent))];
		m_Components.erase (std::type_index(typeid(TComponent)));
	}

	//Accesses type TComponent of gameobject
	template<typename TComponent>
	TComponent* GetComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		return (TComponent*)m_Components[std::type_index(typeid(TComponent))];
	}

	//Finds first instance of type TComponent
	template<typename TComponent>
	static TComponent* FindComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		for (Gameobject* gameobject : Application::Get()->GetGameobjects())
		{
			if (gameobject->m_Components.find(std::type_index(typeid(TComponent))) != gameobject->m_Components.end())
			{
				return (TComponent*)(gameobject->m_Components[std::type_index(typeid(TComponent))]);
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
			if (gameobject->m_Components.find(std::type_index(typeid(TComponent))) != gameobject->m_Components.end())
			{
				components.push_back((TComponent*)gameobject->m_Components[std::type_index(typeid(TComponent))]);
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

private:

	std::unordered_map<std::type_index, Component*> m_Components;
};

