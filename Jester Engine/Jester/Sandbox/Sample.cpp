#include "Sample.h"
#include "../Core/Input.h"
#include "../Core/Application.h"

class Time;

void SampleComponent::OnAwake()
{
	cam = Gameobject::FindComponent<Camera>(); 
}

void SampleComponent::OnUpdate()
{
	if (!move) return;

	if (Input::GetKey(KeySig::Escape)) 
		Window::Close(); 

	if (Input::GetKey(KeySig::LeftArrow))
	{
		gameobject->transform.Translate(2 * Time::DeltaTime(), 0);	
	}
	if (Input::GetKey(KeySig::RightArrow))
	{
		gameobject->transform.Translate(-2 * Time::DeltaTime(), 0);
	}
	if (Input::GetKey(KeySig::UpArrow))
		gameobject->transform.Translate(0, 2 * Time::DeltaTime());

	if (Input::GetKey(KeySig::DownArrow))
		gameobject->transform.Translate(0, -2 * Time::DeltaTime());
}

void SampleComponent::OnGuiUpdate()
{
	ImGui::Text((const char*)"Sample Component:");
	ImGui::Checkbox("Move", &move);
}


