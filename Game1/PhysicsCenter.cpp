#include "stdafx.h"
#include "PhysicsCenter.h"

PhysicsCenter::PhysicsCenter()
{
	g_Ball = nullptr;
	g_Terrain = nullptr;
	g_Objects = nullptr;
	g_Direction = Vector3(0, 0, 0);
	g_Velocity = 10;
	g_Gravity = 1;
	g_SteadyState = false;
	g_GroundType = GroundType::GRASS;
}
void PhysicsCenter::InitTerrainInfo(Actor* _terrain)
{
	g_Terrain = _terrain;
	int end = g_Terrain->children.size();
	for (size_t i = 0; i < end; i++)
	{
		GameObject* temp = nullptr;
		if ((temp = g_Terrain->Find("grass" + to_string(i))) && temp->collider)
			m_GrassList.push_back(temp);
		if ((temp = g_Terrain->Find("obstacle grass" + to_string(i))) && temp->collider)
			m_OBGrassList.push_back(temp);
		if ((temp = g_Terrain->Find("sand" + to_string(i))) && temp->collider)
			m_SandList.push_back(temp);
		if ((temp = g_Terrain->Find("water" + to_string(i))) && temp->collider)
			m_WaterList.push_back(temp);
		if ((temp = g_Terrain->Find("hole" + to_string(i))) && temp->collider)
			m_HoleList.push_back(temp);
	}
}

void PhysicsCenter::InitObjectsInfo(Actor* _objects)
{
	g_Objects = _objects;
	int end = g_Objects->children.size();
	for (size_t i = 0; i < end; i++)
	{
		GameObject* temp = nullptr;
		if ((temp = g_Objects->Find("object" + to_string(i))) && temp->collider)
			m_ObjList.push_back(temp);
	}
}

void PhysicsCenter::InitSpherePhysics(Vector3 ballPos, Vector3 dir, float _velocity)
{
	g_Ball->SetWorldPos(ballPos);
	g_Ball->Update();
	g_Direction = dir;
	g_Velocity = _velocity;
	g_Gravity = 1;
	g_SteadyState = false;
}

void PhysicsCenter::UpdateSpherePhysics()
{
	if (g_GroundType == GroundType::HOLE) {
		g_SteadyState = true;
		return;
	}

	bool velocityDamp = false;
	bool gravityDamp = false;

	if (g_Gravity < 500.0f)
		g_Gravity += DELTA * 30;
	//if (g_Velocity > 0)
	//	g_Velocity -= DELTA * 0.001f;
	else
		g_Velocity = 0;
	g_Direction.Normalize();

	m_direction = g_Direction * g_Velocity * DELTA;
	m_gravity = Vector3(0, -1, 0) * g_Gravity * DELTA;

	if (g_Velocity >= 0.02f)
		g_Ball->MoveWorldPos(g_Direction * g_Velocity * DELTA);
	else
		velocityDamp = true;
	if (g_Velocity >= 0.02f && g_Gravity >= DELTA * 5)
		g_Ball->MoveWorldPos(Vector3(0, -1, 0) * g_Gravity * DELTA);
	else
		gravityDamp = true;

	if (velocityDamp && gravityDamp) {
		g_SteadyState = true;
		return;
	}

	UINT end;
	end = m_ObjList.size();
	for (size_t i = 0; i < end; i++)
	{
		GameObject* child = m_ObjList[i];
		if (g_Ball->Intersect(child))
		{
			Vector3 dir, norm; 
			norm = g_Ball->GetWorldPos() - child->GetWorldPos(); norm.Normalize();
			Vector3::Reflect(m_direction + m_gravity, norm, dir);
			g_Direction = dir;
			while (g_Ball->Intersect(child))
			{
				g_Ball->MoveWorldPos(norm * 0.01f);
				g_Ball->Update();
			}
			SetPhysicsValue(g_Velocity, g_Gravity);
			return;
			i = end;
		}
	}
	UpdatePhysicsCoord(GroundType::GRASS);
	UpdatePhysicsCoord(GroundType::OB_GRASS);
	UpdatePhysicsCoord(GroundType::SAND);
	UpdatePhysicsCoord(GroundType::WATER);
	UpdatePhysicsCoord(GroundType::HOLE);
}
void PhysicsCenter::UpdatePhysicsCoord(GroundType groundType, bool terrain_col)
{
	UINT end;
	vector<GameObject*>* tempList = &m_GrassList;
	switch (groundType)
	{
	case GroundType::GRASS:
		tempList = &m_GrassList;
		end = m_GrassList.size();
		break;
	case GroundType::OB_GRASS:
		tempList = &m_OBGrassList;
		end = m_OBGrassList.size();
		break;
	case GroundType::SAND:
		tempList = &m_SandList;
		end = m_SandList.size();
		break;
	case GroundType::WATER:
		tempList = &m_WaterList;
		end = m_WaterList.size();
		break;
	case GroundType::HOLE:
		tempList = &m_HoleList;
		end = m_HoleList.size();
		break;
	default:
		end = 0;
		break;
	}
	for (size_t i = 0; i < end; i++)
	{
		GameObject* child = (*tempList)[i];
		if (g_Ball->Intersect(child))
		{
			Vector3 dir;
			Vector3::Reflect(m_direction + m_gravity, child->GetUp(), dir);
			g_Direction = dir;
			while (g_Ball->Intersect(child))
			{
				g_Ball->MoveWorldPos(child->GetUp() * 0.01f);
				g_Ball->Update();
			}
			g_GroundType = groundType;
			SetPhysicsValue(g_Velocity, g_Gravity);
			return;
			i = end;
		}
	}
}
void PhysicsCenter::SetPhysicsValue(float& _velocity, float& _gravity, bool terrain_col)
{
	if (terrain_col)
	{
		switch (g_GroundType)
		{
		case GroundType::GRASS:
			_velocity *= 0.6f;
			_gravity = 0;
			break;
		case GroundType::OB_GRASS:
			_velocity *= 0.6f;
			_gravity *= 0.2f;
			break;
		case GroundType::SAND:
			_velocity = 0;
			_gravity = 0;
			break;
		case GroundType::WATER:
			_velocity = 0;
			_gravity = 0;
			break;
		case GroundType::HOLE:
			_velocity = 0;
			_gravity = 0;
			break;
		default:
			break;
		}
	}
	else
	{
		_velocity *= 0.8f;
		_gravity = 0.1f;
	}
}


