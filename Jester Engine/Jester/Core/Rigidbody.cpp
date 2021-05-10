#include "Rigidbody.h"
#include "Gameobject.h"
#include "Collider.h"

#include "Input.h"
#include "Log.h"

#include "../User Interface/UI.h"

std::vector<Rigidbody*> Rigidbody::rigidbodyRegistery;

void Rigidbody::OnAwake()
{
	object->hasRigidbody = true;
	rigidbodyRegistery.emplace_back(this);
}

void Rigidbody::OnDestroy()
{
	object->hasRigidbody = false;
	rigidbodyRegistery.erase(std::find(rigidbodyRegistery.begin(), rigidbodyRegistery.end(), this));
}

void Rigidbody::OnGuiUpdate()
{
	using namespace Jester::UI;
	Serialize("Velocity", velocity);
	Serialize("Friction", friction);
}

void Rigidbody::OnCollisionStay(Collider& other, Vector2 indices)
{
	if (other.isTrigger() || !other.object->hasRigidbody)
		return;

	if (Input::GetKey(KeySig::Space))
		Logger::Print("c");

	velocity *= other.GetSegmentNormal(indices.x, indices.y) * other.object->GetComponent<Rigidbody>()->friction;
}
