#include "../Sandbox/CollMarker.h"
#include "ComponentTracker.h"

#include "../Core/Log.h"

#include <string>

#include "Gameobject.h"

#include "Collider.h"
#include "../Renderer/Camera.h"
#include "../Renderer/Line.h"
#include "../Renderer/Shape.h"

const std::string LAST_COMPONENT = "CollMarker";

const std::string GetLastComponent() { return LAST_COMPONENT; }

void RetrieveComponent(Gameobject* gameobject, const std::string& componentName)
{
	Component* component = nullptr;
	if (componentName == "Collider")
		component = gameobject->AddComponent<Collider>();
	else if (componentName == "Camera")
		component = gameobject->AddComponent<Camera>();
	else if (componentName == "Line")
		component = gameobject->AddComponent<Line>();
	else if (componentName == "Shape")
		component = gameobject->AddComponent<Shape>();
	else if (componentName == "Sprite")
		component = gameobject->AddComponent<Line>();
    else if (componentName == "CollMarker")
        component = gameobject->AddComponent<CollMarker>();

	else
		Logger::Print(LogFlag::Warning, "Component ", componentName, " doesn't exist");

	if (component != nullptr)
		component->OnAwake(); 
}
//Test