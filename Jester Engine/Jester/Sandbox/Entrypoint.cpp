#include "../Core/Jester.h"
#include "../Sandbox/Components.h"

int main()
{
	/*Declare Gameobjects here for now
	Init location will change once you can create Gamoebjcts in app*/

	Gameobject* obj = Gameobject::Instantiate("obj");
	obj->AddComponent<Sample>();

	Gameobject* obj_1 = Gameobject::Instantiate("obj_1");
	obj_1->AddComponent<Sample>();

	Gameobject::Destroy(obj_1);

	Application::Get()->Init(); 
	Application::Get()->Run();
} 