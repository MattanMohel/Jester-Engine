#include "Internal.h"

int main()
{
	/*Declare Gameobjects here for now
	Init location will change once you can create Gameobejcts in app*/

	Gameobject* obj_0 = Gameobject::Instantiate("obj_0");
	Gameobject* obj_1 = Gameobject::Instantiate("obj_1");
	Gameobject* obj_2 = Gameobject::Instantiate("obj_2");
	Gameobject* obj_3 = Gameobject::Instantiate("obj_3");
	Gameobject* obj_4 = Gameobject::Instantiate("obj_4");

	//creates this node tree
	/*   obj_0
	     /   \
	  obj_1  obj_2
	  /   \  
   obj_3  ob_4   */

	//Set Child-Parent Tree pictured above
	obj_1->transform->SetChild(obj_3);
	obj_1->transform->SetChild(obj_4);

	obj_0->transform->SetChild(obj_1);
	obj_0->transform->SetChild(obj_2);

	//print out Child-Parent dependencies 
	Logger::Print("obj_0's child[0] is ", obj_0->transform->GetChild(0)->name);
	Logger::Print("obj_0's child[1] is ", obj_0->transform->GetChild(1)->name);

	Logger::Print("obj_1's child[0] is ", obj_1->transform->GetChild(0)->name);
	Logger::Print("obj_1's child[1] is ", obj_1->transform->GetChild(1)->name);
	
	Logger::Print("obj_1's root is ", obj_1->transform->GetRoot()->name);
	Logger::Print("obj_2's root is ", obj_2->transform->GetRoot()->name);
	Logger::Print("obj_3's root is ", obj_3->transform->GetRoot()->name);
	Logger::Print("obj_4's root is ", obj_4->transform->GetRoot()->name);

	//Read/Write components to gameobject
	obj_0->AddComponent<SampleComponent>();
	obj_0->GetComponent<SampleComponent>()->SetInt(5);
	Logger::Print("obj_0's Sample Returned: ", obj_0->GetComponent<SampleComponent>()->GetInt());

	obj_1->AddComponent<SampleComponent>();

	//cached reference to SampleComponent 
	SampleComponent* sample = obj_1->GetComponent<SampleComponent>();
	sample->SetInt(10);
	Logger::Print("obj_1's cached reference to Sample component printed: ", sample->GetInt());

	//Destroy obj_1 so it isn't called on OnUpdate
	Gameobject::Destroy(obj_1);

	Application::Get()->Init(); 
	Application::Get()->Run();
} 