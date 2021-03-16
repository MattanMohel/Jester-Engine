#include "../Core/Jester.h"
#include "../Sandbox/Components.h"

template<typename T>
int Get(int a, bool&& assign)
{
	static int b = a;
	std::cout << b << "\n";
	return a;
}

int main()
{
	/*Declare Gameobjects here for now
	Init location will change once you can create Gamoebjcts in app*/

	//new component system - rather than have the ID's in the component, it'll be in gameobject
	//template methods will have static variables inside of them assigned by typename of TCompoent 
	Get<int>(5, true); 
	Get<int>(88, true);
	Get<double>(8, false);
	//above, two templates, two different static variables -> store static variables by assigned TComponent and store
	//then retrieve that data by setting the assign bool to false

	Gameobject* obj = Gameobject::Instantiate("obj");
	obj->AddComponent<Sample>();

	Gameobject::Destroy(obj);
	
	Application::Get()->Init();
	Application::Get()->Run();
} 