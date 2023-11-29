#include "stdafx.h"
#include "PhysicsCenter.h"

Actor* PhysicsCenter::g_Ball = nullptr;
Actor* PhysicsCenter::g_Terrain = nullptr;
Vector3 PhysicsCenter::g_Direction = Vector3(0, 1, 0);
float PhysicsCenter::g_Velocity = 10;
float PhysicsCenter::g_Gravity = 1;

void PhysicsCenter::UpdateSpherePhysics()
{
	if (g_Velocity >= 0.01f)
	{
		if (g_Gravity < 50.0f)
			g_Gravity += DELTA * 5;
		//if (g_Velocity > 0)
		//	g_Velocity -= DELTA;
		//else
		//	g_Velocity = 0;
		g_Direction.Normalize();
		Vector3 gravity = Vector3(0, -1, 0) * g_Gravity * DELTA;
		g_Ball->MoveWorldPos(Vector3(0, -1, 0) * g_Gravity * DELTA);
		Vector3 direction = g_Direction * g_Velocity * DELTA;
		g_Ball->MoveWorldPos(g_Direction * g_Velocity * DELTA);
		size_t end = g_Terrain->children.size();
		for (size_t i = 0; i < end; i++)
		{
			GameObject* child = g_Terrain->Find("grass" + to_string(i));
			if (child && child->collider && g_Ball->Intersect(child))
			{
				Vector3 dir;
				Vector3::Reflect(direction + gravity, child->GetUp(), dir);
				g_Direction = dir;
				while (g_Ball->Intersect(child))
				{
					g_Ball->MoveWorldPos(child->GetUp() * 0.1f);
					g_Ball->Update();
				}
				g_Velocity *= 0.6f;
				g_Gravity = 0;
				i = end;
			}
		}
	}
	else
	{
	}
}
