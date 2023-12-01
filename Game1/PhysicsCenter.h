#pragma once
enum class GroundType
{
	GRASS, OB_GRASS, SAND, WATER, HOLE
};
class PhysicsCenter : public Singleton<PhysicsCenter>
{
public:
	PhysicsCenter();
	void InitTerrainInfo(Actor* _terrain);
	void InitObjectsInfo(Actor* _objects);
	void InitSpherePhysics(Vector3 ballPos, Vector3 dir = Vector3(0, 0, 0), float _velocity = 10.0f);	//물리 초기값 설정
	void UpdateSpherePhysics();	//매 프레임 호출하여 공의 물리적 상태 구현

	Actor* g_Ball;			//공
	Actor* g_Terrain;		//지형
	Actor* g_Objects;		//장애물
	Vector3	g_Direction;	//공의 운동 방향
	float	g_Velocity;		//공의 운동 가중치
	float	g_Gravity;		//중력 가속도
	bool		g_SteadyState;	//안정 상태 판별
	GroundType g_GroundType;
private:
	void UpdatePhysicsCoord(GroundType groundType, bool terrain_col = true);
	void SetPhysicsValue(float& _velocity, float& _gravity, bool terrain_col = true);
	Vector3 m_direction;
	Vector3 m_gravity;
	vector<GameObject*> m_GrassList;
	vector<GameObject*> m_OBGrassList;
	vector<GameObject*> m_SandList;
	vector<GameObject*> m_WaterList;
	vector<GameObject*> m_HoleList;
	vector<GameObject*> m_ObjList;
};

