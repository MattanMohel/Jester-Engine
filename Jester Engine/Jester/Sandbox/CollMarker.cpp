#include "CollMarker.h"

#include "../Core/Log.h"

void CollMarker::OnUpdate()
{
	gameobject->transform.Rotate(rotSpeed * Time::DeltaTime());  
}

void CollMarker::OnGuiUpdate()
{

}

void CollMarker::OnCollisionEnter(Collider& other)
{
	gameobject->GetComponent<Shape>()->color() = Color(1, 0, 0, .3);
}

void CollMarker::OnCollisionExit(Collider& other)
{
	gameobject->GetComponent<Shape>()->color() = Color(1, 1, 1, .3); 
}