#include "Sample.h"
#include "../Core/Input.h"
#include "../Core/Application.h"

class Time;

void SampleComponent::OnAwake()
{
	rb = object->GetComponent<Rigidbody>();
	cam = Object::FindComponent<Camera>(); 

	for (auto& index : object->GetComponent<Collider>()->GetVertices())
	{
		Object* obj = Object::Instantiate("follower");
		obj->AddComponent<Sprite>()->SetTexture("resources/textures/block.png");
		obj->GetComponent<Sprite>()->color = objectColor;
		obj->transform.position = index;
		obj->transform.scale = Vector2(.1f, .1f);
		objects.emplace_back(obj); 
	}
}

void SampleComponent::OnUpdate()
{
	if (!move) return;

	if (Input::GetKey(KeySig::Escape)) 
		Window::Close(); 

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->GetComponent<Sprite>()->color = objectColor;
		objects[i]->transform.position = Transform::RotateAround(object->GetComponent<Collider>()->GetIndex(i), object->transform);
	}

	Vector2 speed;
	if (Input::GetKey(KeySig::LeftArrow))
		speed -= Vector2::Right;
	if (Input::GetKey(KeySig::RightArrow))
		speed += Vector2::Right;
	if (Input::GetKey(KeySig::UpArrow))
		speed += Vector2::Up;
	if (Input::GetKey(KeySig::DownArrow))
		speed -= Vector2::Up;

	rb->velocity = speed;
}

void SampleComponent::OnGuiUpdate()
{
	Jester::UI::Serialize("Move", move, true); 
	Jester::UI::Serialize("Speed", speed);
}

void SampleComponent::OnCollisionStay(Collider& other, Vector2)
{
	object->GetComponent<Sprite>()->color = Color(1, 0, 0, 1);
}

void SampleComponent::OnCollisionExit(Collider& other, Vector2)
{
	object->GetComponent<Sprite>()->color = Color(1, 1, 1, 1);
}


