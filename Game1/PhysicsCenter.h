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
	void InitSpherePhysics(Vector3 ballPos, Vector3 dir = Vector3(0, 0, 0), float _velocity = 10.0f);	//���� �ʱⰪ ����
	void UpdateSpherePhysics();	//�� ������ ȣ���Ͽ� ���� ������ ���� ����

	Actor* g_Ball;			//��
	Actor* g_Terrain;		//����
	Actor* g_Objects;		//��ֹ�
	Vector3	g_Direction;	//���� � ����
	float	g_Velocity;		//���� � ����ġ
	float	g_Gravity;		//�߷� ���ӵ�
	bool		g_SteadyState;	//���� ���� �Ǻ�
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

