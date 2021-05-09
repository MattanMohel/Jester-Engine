#include "Sample.h"
#include "../Core/Input.h"
#include "../Core/Application.h"

class Time;

void SampleComponent::OnAwake()
{
	cam = Object::FindComponent<Camera>(); 
}

void SampleComponent::OnUpdate()
{
	if (!move) return;

	if (Input::GetKey(KeySig::Escape)) 
		Window::Close(); 

	if (Input::GetKey(KeySig::LeftArrow))
	{
		object->transform.Translate(2 * Time::DeltaTime(), 0);	
	}
	if (Input::GetKey(KeySig::RightArrow))
	{
		object->transform.Translate(-2 * Time::DeltaTime(), 0);
	}
	if (Input::GetKey(KeySig::UpArrow))
		object->transform.Translate(0, 2 * Time::DeltaTime());

	if (Input::GetKey(KeySig::DownArrow))
		object->transform.Translate(0, -2 * Time::DeltaTime());
}

void SampleComponent::OnGuiUpdate()
{
	Jester::UI::Serialize("Move", move, true); 
}


