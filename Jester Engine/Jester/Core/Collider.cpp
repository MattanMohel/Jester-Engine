#include "Collider.h"

std::vector<Collider*> Collider::colliderRegistery;
bool Collider::checked = false;

Collider::Collider()
{
	colliderRegistery.push_back(this);
}

const std::vector<Vector2>& Collider::GetIndices() const
{
	return Indices;
}

Vector2 Collider::GetIndex(int index) const
{
	return Indices[index];
}

bool Collider::isTrigger() const
{
	return m_State == State::Trigger;
}

bool Collider::isPhysics() const
{
	return m_State == State::Physics;
}

Collider::Type Collider::GetType() const
{
	return m_Type;
}

inline bool Collider::isInCollisionArray(const Collider* a) const
{
	return find(Collisions.begin(), Collisions.end(), a) != Collisions.end();
}

auto&& Collider::collisionArrayIt(const Collider* a) const
{
	return find(Collisions.begin(), Collisions.end(), a);
}

void Collider::OnUpdate(const Time* Time)
{
	if (!checked)
		CheckCollisions();
}

void Collider::CheckCollisions()
{
	checked = true;
	
	static size_t callIndex = 0;
	callIndex++;

	for (int i = 0; i < colliderRegistery.size() - 1; i++)
	{
		for (int j = i + 1; j < colliderRegistery.size(); j++)
		{
			Collider* coll_i = colliderRegistery[i];
			Collider* coll_j = colliderRegistery[j];

			if (isColliding(coll_i, coll_j))
			{
				if (coll_i->isInCollisionArray(coll_j)) /*if already colliding*/
				{
					coll_i->gameobject->transform->GetRoot()->OnCollisionStay((Collider&)coll_j);
					coll_j->gameobject->transform->GetRoot()->OnCollisionStay((Collider&)coll_i);
				}
				else /*if wasn't colliding before*/
				{
					coll_i->Collisions.push_back(coll_j);
					coll_j->Collisions.push_back(coll_i);

					coll_i->gameobject->transform->GetRoot()->OnCollisionEnter((Collider&)coll_j);
					coll_j->gameobject->transform->GetRoot()->OnCollisionEnter((Collider&)coll_i);
				}	
			}
			else if (isColliding(coll_i, coll_j)) /*if stopped colliding*/
			{
				coll_i->Collisions.erase(coll_i->collisionArrayIt(coll_j));
				coll_j->Collisions.erase(coll_j->collisionArrayIt(coll_i));

				coll_i->gameobject->transform->GetRoot()->OnCollisionExit((Collider&)coll_j);
				coll_j->gameobject->transform->GetRoot()->OnCollisionExit((Collider&)coll_i);
			}
		}
	}

	if (callIndex == colliderRegistery.size() - 1)
	{
		checked = false;
		callIndex = 0;
	}
}

bool Collider::isColliding(const Collider* a, const Collider* b)
{
	return true;
}
