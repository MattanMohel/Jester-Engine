#include "../Jester.h"
#include "Sample.h"

int main()
{
	Application::Get()->Init(); 

	Object* obj = Object::Instantiate("Camera");	 
  	obj->AddComponent<Camera>();

	Object* player = Object::Instantiate("player");
	player->AddComponent<SampleComponent>()->move = true;
	player->AddComponent<Collider>()->SetVertices(Vector2(-1, -1), Vector2(-1, 1), Vector2(1, 1), Vector2(1, -1));
	player->AddComponent<Rigidbody>()->isEnabled = false;
	player->AddComponent<Sprite>()->SetTexture("resources/textures/block.png");	
	
	Object* player3 = Object::Instantiate("target");
	player3->AddComponent<SampleComponent>();
	player3->AddComponent<Collider>()->SetVertices(Vector2(-1, -1), Vector2(-1, 1), Vector2(1, 1), Vector2(1, -1));
	player3->AddComponent<Rigidbody>();
	player3->AddComponent<Sprite>()->SetTexture("resources/textures/block.png");

	Application::Get()->Run(); 
}  