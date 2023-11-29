#pragma once
class PhysicsCenter
{
public:
	static void UpdateSpherePhysics();
	static Actor*	g_Ball;
	static Actor*	g_Terrain;
	static Vector3	g_Direction;
	static float	g_Velocity;
	static float	g_Gravity;
};

