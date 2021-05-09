#include "../Jester.h"
#include "Sample.h"

int main()
{
	Application::Get()->Init(); 

	Object* obj = Object::Instantiate("Camera");	 
  	obj->AddComponent<Camera>();

	Object* player = Object::Instantiate("player1");
	player->AddComponent<SampleComponent>()->move = true;
	player->AddComponent<Sprite>()->SetTexture("resources/textures/spitoon.png");	
	
	Object* player2 = Object::Instantiate("player");
	player2->AddComponent<SampleComponent>()->move = true;
	player2->AddComponent<Sprite>()->SetTexture("resources/textures/spitoon.png");	
	
	Object* player3 = Object::Instantiate("player");
	player3->AddComponent<SampleComponent>()->move = true;
	player3->AddComponent<Sprite>()->SetTexture("resources/textures/spitoon.png");

	Object* target = Object::Instantiate("target");
	target->AddComponent<Collider>()->SetVertices(Vector2(-1, -1), Vector2(-1, 1), Vector2(1, 1), Vector2(1, -1));

	Application::Get()->Run(); 
}  