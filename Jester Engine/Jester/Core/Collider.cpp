#include "Collider.h"

#include "../User Interface/UI.h"

std::vector<Collider*> Collider::colliderRegistery;
size_t Collider::callIndex = 0;
bool Collider::checked = false;

Collider::Collider()
	: m_FurthestVertexDistance(0)
{
	colliderRegistery.push_back(this);
}

Collider::~Collider()
{
	colliderRegistery.erase(find(m_Collisions.begin(), m_Collisions.end(), this));
}

void Collider::OnAwake()
{
	m_LineVisual.gameobject = gameobject;
	m_LineVisual.color() = Color(COLLIDER_COLOR);
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
		m_Vertices.push_back(Vector2::Zero);
	else
		m_Vertices.insert(m_Vertices.begin() + index, Vector2::Zero);

	m_LineVisual.AddVertex(index);
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

void Collider::CheckCollisions()
{
	checked = true;
	
	//declare out of method
	callIndex++;

	for (int i = 0; i < colliderRegistery.size() - 1; i++)
	{
		for (int j = i + 1; j < colliderRegistery.size(); j++)
		{
			Collider* coll_i = colliderRegistery[i];
			Collider* coll_j = colliderRegistery[j];

			/*checks if either of the shape's vertex lies within the other shape*/
			bool colliding = isColliding(coll_i, coll_j) || isColliding(coll_j, coll_i);

			if (colliding)
			{
				if (coll_i->isInCollisionArray(coll_j)) /*if already colliding*/
				{
					coll_i->gameobject->transform.GetRoot()->OnCollisionStay((Collider&)coll_j);
					coll_j->gameobject->transform.GetRoot()->OnCollisionStay((Collider&)coll_i);
				}
				else /*if wasn't colliding before*/
				{
					coll_i->m_Collisions.push_back(coll_j);
					coll_j->m_Collisions.push_back(coll_i);

					coll_i->gameobject->transform.GetRoot()->OnCollisionEnter((Collider&)coll_j); 
					coll_j->gameobject->transform.GetRoot()->OnCollisionEnter((Collider&)coll_i); 
				}	
			}
			else if (coll_i->isInCollisionArray(coll_j)) /*if stopped colliding*/
			{
				coll_i->gameobject->transform.GetRoot()->OnCollisionExit((Collider&)coll_j);
				coll_j->gameobject->transform.GetRoot()->OnCollisionExit((Collider&)coll_i);

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

bool Collider::isColliding(const Collider* a, const Collider* b)
{
	bool colliding = false;
	bool collisionSide[2] = { false, false };

	/*if the distance between the shape if greater than the furthest lying vertices for both combined, its impossible for them
	to intersect - to be implemented*/
		/*float dis = Vector2::SquaredDistance(a->gameobject->transform->position, b->gameobject->transform->position);
		if (Vector2::SquaredDistance(a->gameobject->transform->position, b->gameobject->transform->position) - (a->m_FurthestVertexDistance / 2 + b->m_FurthestVertexDistance/2)
			> a->m_FurthestVertexDistance + b->m_FurthestVertexDistance)
			return false;*/

	for (const auto& vert : a->m_Vertices)  
	{
		for (size_t i = 0; i < b->m_Vertices.size(); i++) 
		{
			/*the refrenced vertices, transformed to match the gameobject*/
			Vector2 segmentOffset((Transform::RotateAround(b->m_Vertices[i], b->gameobject->transform))); 
			Vector2 segmentSlope(Transform::RotateAround(b->m_Vertices[(i + 1) % b->m_Vertices.size()], b->gameobject->transform) - segmentOffset); 
			Vector2 transformedVert(Transform::RotateAround(vert, a->gameobject->transform)); 

			/*collison check uses a [1 0] vector, so if line is below there's no way to reach it*/
			if (segmentSlope.y == 0 && abs(transformedVert.y - segmentOffset.y) > CALC_PRECISION)  
				continue;

			/*the difference between the two constant vectors*/
			Vector2 constDiff = transformedVert - segmentOffset;
			/*the x-position where the segment intersects with the vertex*/
			float segmentVar = constDiff.y / segmentSlope.y; 

			/*if the intersction is not within the confines of the shape*/
			if (!(segmentVar >= 0 && segmentVar <= 1))
				continue;
			
			/*the x position where the vertex intersects with the segment*/
			float vertexVar = constDiff.x - segmentSlope.x * segmentVar;

			/*check if collison was on left or right side*/
			if (vertexVar < 0) 
				collisionSide[0] = true; 
			else
				collisionSide[1] = true; 

			/*if the vertex collides with shape on both left and right ||
			the x distance between vertex x and segment x is close enough to zero == collision*/
			if ((collisionSide[0] && collisionSide[1]) || abs(vertexVar) <= CALC_PRECISION)
			{
				colliding = true;
				break;
			}
		}

		if (colliding)
			break;
	}

	return colliding;
}
