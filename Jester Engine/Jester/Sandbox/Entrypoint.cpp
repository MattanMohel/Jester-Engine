#include "../Core/Jester.h"
#include "../Sandbox/Components.h"

int main()
{
	/*Declare Gameobjects here for now
	Init location will change once you can create Gamoebjcts in app*/

	Gameobject* obj = Gameobject::Instantiate("obj");
	obj->AddComponent<Sample>();
	obj->AddComponent<Transform>();

	Gameobject::FindComponents<Transform>()[0]->gameobject->RemoveComponent<Transform>();

	Application::Get()->Init(); 
	Application::Get()->Run();
} 