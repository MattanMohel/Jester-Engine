#include "CollMarker.h"

void CollMarker::OnAwake()
{
	for (Vector2 vert : gameobject->GetComponent<Collider>()->GetVertices())
	{
		Gameobject* obj = Gameobject::Instantiate("obj");
		obj->AddComponent<Sprite>()->SetTexture("resources/textures/block.png");
		obj->GetComponent<Sprite>()->Colors() = Color(1, 0, 1, 1);
		obj->transform->scale = Vector2(.1, .1);
		obj->transform->position = vert;
		points.push_back(obj);
	}
}

void CollMarker::OnUpdate(const Time* time)
{
	//gameobject->transform->Dilate(.1 * time->DeltaTime(), .2 * time->DeltaTime(), 0);
	gameobject->transform->Rotate(0, 0, .5 * time->DeltaTime());
	float rotation = gameobject->transform->rotation.z;

	if (Input::GetKey(KeySig::Space))
		gameobject->transform->Dilate(.2 * time->DeltaTime(), 0, 0);

	for (int i = 0; i < points.size(); i++) 
	{
		Vector2 vert(gameobject->GetComponent<Collider>()->GetVertices()[i]);
		Vector2 scale(gameobject->transform->scale);

		points[i]->transform->position = Transform::RotateAround(vert, *gameobject->transform);
	}
}
