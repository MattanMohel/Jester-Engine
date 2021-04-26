#include "CollMarker.h"

#include "../Core/CoreBase.h"
#include "../Core/Log.h"

void CollMarker::OnUpdate()
{
	Logger::Print("hi");
	gameobject->transform->Rotate(0, 0, rotSpeed * Time::DeltaTime());  
}

void CollMarker::OnGuiUpdate()
{
	ImGui::Text("Collider Marker");
	ImGui::SliderFloat("rotation speed", &rotSpeed, -10, 10, "", 1);
	if (ImGui::Button("Construct"))
		AddComponentToFile("CollMarker");
}

void CollMarker::OnCollisionEnter(Collider& other)
{
	gameobject->GetComponent<Shape>()->color() = Color(1, 0, 0, .3);
}

void CollMarker::OnCollisionExit(Collider& other)
{
	gameobject->GetComponent<Shape>()->color() = Color(1, 1, 1, .3); 
}