#include "Sample.h"
#include "../Core/Input.h"
#include "../Core/Application.h"

class Time;

void SampleComponent::OnAwake()
{
	Logger::Print("Sample: Awake");
}

void SampleComponent::OnUpdate(const Time* time)
{
	m_Int++;
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
