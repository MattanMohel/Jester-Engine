#include "Sample.h"
#include "../Core/Input.h"
#include "../Core/Application.h"

class Time;

void SampleComponent::OnAwake()
{
}

void SampleComponent::OnUpdate(const Time* time)
{
	if (!move) return;

	if (Input::GetKey(KeySig::Escape))
		Window::Close();

	if (Input::GetKey(KeySig::LeftArrow))
	{
		gameobject->transform->Translate(2 * time->DeltaTime(), 0);	
	}
	if (Input::GetKey(KeySig::RightArrow))
	{
		gameobject->transform->Translate(-2 * time->DeltaTime(), 0);	
	}
	if (Input::GetKey(KeySig::UpArrow))
		gameobject->transform->Translate(0, 2 * time->DeltaTime());

	if (Input::GetKey(KeySig::DownArrow))
		gameobject->transform->Translate(0, -2 * time->DeltaTime());
}

void SampleComponent::OnCollisionEnter(Collider& other)
{
	if (gameobject->GetComponent<Collider>() != nullptr && gameobject->GetComponent<Sprite>() != nullptr)
	{
		gameobject->GetComponent<Sprite>()->Colors() = Color(1, 0, 0, .2);
	}
}

void SampleComponent::OnCollisionExit(Collider& other)
{
	if (gameobject->GetComponent<Collider>() != nullptr && gameobject->GetComponent<Sprite>() != nullptr)
	{
		gameobject->GetComponent<Sprite>()->Colors() = Color(1, 1, 1, .2);
	}
}
