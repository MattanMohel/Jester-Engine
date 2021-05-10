#include "Collider.h"

#include "../User Interface/UI.h"

std::vector<Collider*> Collider::colliderRegistery;
size_t Collider::callIndex = 0;
bool Collider::checked = false;

void Collider::OnAwake()
{
	colliderRegistery.push_back(this);

	m_FurthestVertexDistance = 0;
	m_LineVisual.object = object;
	m_LineVisual.color() = Color(COLLIDER_COLOR);
}

void Collider::OnDestroy()
{
	colliderRegistery.erase(find(m_Collisions.begin(), m_Collisions.end(), this));
}

void Collider::OnUpdate()
{
	m_LineVisual.OnUpdate();

	if (!checked)
		CheckCollisions();
}

void Collider::OnGuiUpdate()
{
	using namespace Jester::UI;
	if (SerializeVec("Vertices", m_Vertices))
		RefreshVertices();
}

void Collider::SetVertices(const std::vector<Vector2>& verts)
{
	m_Vertices = verts;

	float maxDistance = 0;
	for (const auto& vert : m_Vertices)
	{
		float distance = Vector2::SquaredDistance(vert, Vector2::Zero);
		maxDistance = distance > maxDistance ? distance : maxDistance;
	}

	m_FurthestVertexDistance = maxDistance;

	m_LineVisual.SetVertices(m_Vertices);
}

void Collider::SetVertex(Vector2& newVertex, size_t index)
{
	m_Vertices[index] = newVertex;

	float dis = Vector2::SquaredDistance(Vector2::Zero, newVertex);
	m_FurthestVertexDistance < dis ? dis : m_FurthestVertexDistance;

	m_LineVisual.SetVertex(newVertex, index);
}

void Collider::RemoveVertex(size_t index)
{
	if (m_Vertices.size() == 0)
		return;

	m_Vertices.erase(m_Vertices.begin() + index);

	float maxDistance = 0;
	for (const auto& vert : m_Vertices)
	{
		float distance = Vector2::SquaredDistance(vert, Vector2::Zero);
		maxDistance = distance > maxDistance ? distance : maxDistance;
	}

	m_FurthestVertexDistance = maxDistance;

	m_LineVisual.RemoveVertex(index);
}

void Collider::AddVertex(size_t index)
{
	if (m_Vertices.size() == 0)
		m_Vertices.emplace_back(Vector2::Zero);
	else
		m_Vertices.insert(m_Vertices.begin() + index, Vector2::Zero);

	m_LineVisual.AddVertex(index);
}

Vector2 Collider::GetSegmentNormal(size_t a, size_t b) const
{
	return (m_Vertices[a] - m_Vertices[b]).Normalized();
}

const std::vector<Vector2>& Collider::GetVertices() const
{
	return m_Vertices;
}

Vector2 Collider::GetIndex(int index) const
{
	return m_Vertices[index];
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
	return find(m_Collisions.begin(), m_Collisions.end(), a) != m_Collisions.end();
}

void Collider::RefreshVertices()
{
	float maxDistance = 0;
	for (const auto& vert : m_Vertices)
	{
		float distance = Vector2::SquaredDistance(vert, Vector2::Zero);
		maxDistance = distance > maxDistance ? distance : maxDistance;
	}

	m_FurthestVertexDistance = maxDistance;

	m_LineVisual.SetVertices(m_Vertices);
}

void Collider::CheckCollisions()
{
	checked = true;
	
	callIndex++;

	for (int i = 0; i < colliderRegistery.size() - 1; i++)
	{
		for (int j = i + 1; j < colliderRegistery.size(); j++)
		{
			Collider* coll_i = colliderRegistery[i];
			Collider* coll_j = colliderRegistery[j];

			if (!coll_i->isEnabled || !coll_j->isEnabled) return;

			// If either shape is intersecting
			/*Collision indices for i and j*/ Vector2 i_coll, j_coll;
			bool colliding = isColliding(coll_i, coll_j, i_coll, j_coll) || isColliding(coll_j, coll_i, j_coll, i_coll);

			if (colliding)
			{
				if (coll_i->isInCollisionArray(coll_j)) // If already colliding
				{
					coll_i->object->transform.GetRoot()->OnCollisionStay(*coll_j, i_coll);
					coll_j->object->transform.GetRoot()->OnCollisionStay(*coll_i, j_coll);
				}
				else // If started colliding
				{
					coll_i->m_Collisions.push_back(coll_j);
					coll_j->m_Collisions.push_back(coll_i);

					coll_i->object->transform.GetRoot()->OnCollisionEnter(*coll_j, i_coll);
					coll_j->object->transform.GetRoot()->OnCollisionEnter(*coll_i, j_coll);

					coll_i->object->transform.GetRoot()->OnCollisionStay(*coll_j, i_coll);
					coll_j->object->transform.GetRoot()->OnCollisionStay(*coll_i, j_coll);
				}	
			}
			else if (coll_i->isInCollisionArray(coll_j)) // if stopped colliding
			{
				coll_i->object->transform.GetRoot()->OnCollisionExit(*coll_j, i_coll);
				coll_j->object->transform.GetRoot()->OnCollisionExit(*coll_i, j_coll);

				coll_i->m_Collisions.erase(find(coll_i->m_Collisions.begin(), coll_i->m_Collisions.end(), coll_j));
				coll_j->m_Collisions.erase(find(coll_j->m_Collisions.begin(), coll_j->m_Collisions.end(), coll_i));
			}
		}
	}

	if (callIndex == colliderRegistery.size() - 1)
	{
		checked = false;
		callIndex = 0;
	}
}

bool Collider::isColliding(const Collider* a, const Collider* b, Vector2& a_Indices, Vector2& b_Indices)
{
	bool colliding = false;
	bool collisionSide[2] = { false, false };

	/*if the distance between the shape if greater than the furthest lying vertices for both combined, its impossible for them
	to intersect - to be implemented*/
		/*float dis = Vector2::SquaredDistance(a->gameobject->transform->position, b->gameobject->transform->position);
		if (Vector2::SquaredDistance(a->gameobject->transform->position, b->gameobject->transform->position) - (a->m_FurthestVertexDistance / 2 + b->m_FurthestVertexDistance/2)
			> a->m_FurthestVertexDistance + b->m_FurthestVertexDistance)
			return false;*/

	for (size_t i = 0; i < a->m_Vertices.size(); i++)  
	{
		for (size_t j = 0; j < b->m_Vertices.size(); j++) 
		{
			// The refrenced vertices, transformed to match the object
			Vector2 segmentOffset((Transform::RotateAround(b->m_Vertices[j], b->object->transform))); 
			Vector2 segmentSlope(Transform::RotateAround(b->m_Vertices[(j + 1) % b->m_Vertices.size()], b->object->transform) - segmentOffset); 
			Vector2 transformedVert(Transform::RotateAround(a->m_Vertices[i], a->object->transform)); 

			// Collison check uses a [1 0] vector, so if line is below there's no way to reach it
			// as the Y slope is 0
			if (segmentSlope.y == 0 && abs(transformedVert.y - segmentOffset.y) > CALC_PRECISION)  
				continue;

			// The difference between the two constant vectors
			Vector2 constDiff = transformedVert - segmentOffset;
			// The x-position where the segment intersects with the vertex
			float segmentVar = constDiff.y / segmentSlope.y; 

			// If the intersction is not within the confines of the shape
			// where the shape is confined between 1 and 0
			if (!(segmentVar >= 0 && segmentVar <= 1))
				continue;
			
			// The x position where the vertex intersects with the segment
			float vertexVar = constDiff.x - segmentSlope.x * segmentVar;

			// Check if collison was on left or right side
			if (vertexVar < 0) collisionSide[0] = true; 
			else collisionSide[1] = true; 

			// If the vertex collides with shape on both left and right ||
			// the x distance between vertex x and segment x is close enough to zero == collision
			if ((collisionSide[0] && collisionSide[1]) || abs(vertexVar) <= CALC_PRECISION)
			{
				a_Indices = Vector2(j, (j + 1) % b->m_Vertices.size());
				b_Indices = Vector2(i, (i + 1) % a->m_Vertices.size());

				colliding = true;
				break;
			}
		}

		if (colliding)
			break;
	}

	return colliding;
}
