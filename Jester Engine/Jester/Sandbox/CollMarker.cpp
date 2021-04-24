#include "CollMarker.h"

void CollMarker::OnUpdate()
{
	//gameobject->transform->Dilate(.1 * time->DeltaTime(), .2 * time->DeltaTime(), 0);
	gameobject->transform->Rotate(0, 0, .5 * Time::DeltaTime());
	float rotation = gameobject->transform->rotation.z;

	if (Input::GetKey(KeySig::W))
		gameobject->transform->Dilate(.2 * Time::DeltaTime(), 0, 0);
	if (Input::GetKey(KeySig::S))
		gameobject->transform->Dilate(-.2 * Time::DeltaTime(), 0, 0);
}

void CollMarker::OnCollisionEnter(Collider& other)
{
	gameobject->GetComponent<Shape>()->color() = Color(1, 0, 0, .3);
}

void CollMarker::OnCollisionExit(Collider& other)
{
	gameobject->GetComponent<Shape>()->color() = Color(1, 1, 1, .3); 
}