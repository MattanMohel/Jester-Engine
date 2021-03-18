#include "../Core/Jester.h"
#include "../Sandbox/Components.h"

int main()
{
	/*Declare Gameobjects here for now
	Init location will change once you can create Gameobejcts in app*/

	Gameobject* obj = Gameobject::Instantiate<Transform, Sample, Sample>("obj");
	Application::Get()->Init(); 
	Application::Get()->Run();
} 