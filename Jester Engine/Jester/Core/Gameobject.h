#pragma once

#include <unordered_map>

#include "Jester.h"

class Gameobject  
{
	friend class Application;

public:

	static Gameobject* Instantiate(std::string&& name);
	static void Destroy(Gameobject* gameobject);

	std::string name;

#pragma region Component Templated Methods

	/*statically instances unique pointers for different
	TComponents - each with their own templated instance*/
	template<typename TComponent>
	static const COMP_ID& GetTComponentID()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		static COMP_ID ID = Component::NewID();
		
		return ID;
	}	

	//adds component of type TComponent
	template<typename TComponent>
	void AddComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (m_Components.find(GetTComponentID<TComponent>()) != m_Components.end())
		{
			std::cerr << "tried to add a duplicate component to " << name << "\n";
			return;
		}
		
		TComponent* component = new TComponent();
		component->Init(this);

		m_Components.insert({ GetTComponentID<TComponent>(), component });
	}	
	
	//removes component of type TComponent
	template<typename TComponent>
	void RemoveComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		if (m_Components.find(GetTComponentID<TComponent>()) == m_Components.end())
		{
			std::cerr << "tried to remove a non-existent component from " << name << "\n";
			return;
		}

		delete m_Components[GetTComponentID<TComponent>()];
		m_Components.erase (GetTComponentID<TComponent>());
	}

	//Accesses type TComponent of gameobject
	template<typename TComponent>
	TComponent* GetComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		return (TComponent*)m_Components[GetTComponentID<TComponent>()];
	}

	//Finds first component of type TComponent in all Gameobjects
	template<typename TComponent>
	static TComponent* FindComponent()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		for (Gameobject* gameobject : Application::Get()->GetGameobjects())
		{
			if (gameobject->m_Components.find(GetTComponentID<TComponent>()) != gameobject->m_Components.end())
			{
				return (TComponent*)(gameobject->m_Components[GetTComponentID<TComponent>()]);
			}
		}

		return nullptr;
	}	
	
	//Finds all components of type TComponent in all Gameobjects
	template<typename TComponent>
	static std::vector<TComponent*> FindComponents()
	{
		DERIVES_FROM_COMPONENT_ASSERT;

		std::vector<TComponent*> components; 

		for (Gameobject* gameobject : Application::Get()->GetGameobjects()) 
		{
			if (gameobject->m_Components.find(GetTComponentID<TComponent>()) != gameobject->m_Components.end())
			{
				components.push_back((TComponent*)gameobject->m_Components[GetTComponentID<TComponent>()]);
			}
		}

		return components;
	}

#pragma endregion

private:

	Gameobject(std::string& name);
	~Gameobject();

	void OnAwake();
	void OnUpdate(const Time* Time);
	void OnFixedUpdate(const Time* Time);

private:

	std::unordered_map<COMP_ID, Component*> m_Components;
};

