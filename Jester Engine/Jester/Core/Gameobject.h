#pragma once

#include <vector>
#include <string>
#include <concepts>

#include "Component.h"
#include "Transform.h"

class Rigidbody;

template<typename T> concept TComponent = std::is_base_of<Component, T>::value;
using ID = long long unsigned int;
using Info = std::pair<bool, size_t>;

class Object  
{
	friend class Application;
	friend class Rigidbody;
	friend class Collider;

public:
	// Instances a new Object, returns a pointer
	static Object* Instantiate(std::string&& name);
	// Destroys a given Object instance
	static void Destroy(Object* gameobject);
	// Retrieves a vector of all binded components
	inline const std::vector<Component*>& GetComponents() { return m_Components; }
	// Retrieves the Object's ID
	inline const ID& GetID() { return m_ID; }
	// Retrieves whether the Object is a physics object
	inline bool IsRigidbody() { return hasRigidbody; }

	std::string name;
	bool isEnabled = true;
	Transform transform;

	// Binds a new component of a specified type
	template<TComponent comp>
	comp* AddComponent()
	{
		return (comp*)m_Components.emplace_back(new comp())->Init(this);
	}	
	// Removes a component of a specified type
	template<TComponent comp>
	void RemoveComponent()
	{
		size_t index = hasComponent(HASH_OF(comp)).second;
		delete m_Components[index]; m_Components.erase(m_Components.begin() + index);
	}
	// Returns pointer to binded component of a specified type
	template<TComponent comp>
	comp* GetComponent()
	{
		return (comp*)m_Components[hasComponent(HASH_OF(comp)).second];
	}
	// Returns first found instance of a specified type
	template<TComponent comp>
	static comp* FindComponent()
	{
		for (Object* object : Application::Get()->GetGameobjects())
		{
			auto [present, index] = object->hasComponent(HASH_OF(comp));
			if (present) return (comp*)(object->m_Components[index]);
		}

		return nullptr;
	}		
	//Finds all instances of type TComponent 
	template<TComponent comp>
	static std::vector<comp*> FindComponents()
	{
		std::vector<comp*> components;

		for (Object* object : Application::Get()->GetGameobjects())
		{
			auto [present, index] = object->hasComponent(HASH_OF(comp));
			if (present) components.push_back((comp*)object->m_Components[index]);
		}

		return components;
	}

	bool operator== (const Object* obj) const { return m_ID == obj->m_ID; }	
	bool operator!= (const Object* obj) const { return m_ID != obj->m_ID; }

private:
	Info hasComponent(unsigned int hash);

	Object(const std::string&, const ID&);
	~Object();

	void OnAwake();
	void OnUpdate();

	void OnCollisionEnter(Collider&, Vector2);
	void OnCollisionStay(Collider&, Vector2);
	void OnCollisionExit(Collider&, Vector2);

	ID m_ID;
	bool hasRigidbody = false;
	std::vector<Component*> m_Components;
};

