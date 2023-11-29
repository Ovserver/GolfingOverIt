#include "stdafx.h"
#include "PhysicsCenter.h"
#include "Scene1.h"

Scene1::Scene1()
{
	grid = Grid::Create();

	cam1 = Camera::Create();
	cam1->LoadFile("Cam.xml");

	Camera::main = cam1;

	player = Actor::Create();
	ball = Actor::Create();
	ball->LoadFile("test_ball.xml");
	terrain = Actor::Create();
	terrain->LoadFile("grass.xml");
	objects = Actor::Create();

	terrain->Update();

	PhysicsCenter::g_Ball = ball;
	PhysicsCenter::g_Terrain = terrain;
}
Scene1::~Scene1()
{
	//new delete�� �ƴ� create release�� ���� ����
	grid->Release();
	cam1->Release();
	player->Release();
	ball->Release();
	terrain->Release();
	objects->Release();
}

void Scene1::Init()
{

}

void Scene1::Release()
{
}

void Scene1::Update()
{
	// �����â�� ���
	LIGHT->RenderDetail();

	Camera::main->Update();
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	//���̾����Űâ�� ���
	ImGui::Begin("Hierarchy");
	grid->RenderHierarchy();
	cam1->RenderHierarchy();
	player->RenderHierarchy();
	ball->RenderHierarchy();
	terrain->RenderHierarchy();
	ImGui::End();
	//gui��³�


	//����ķ ��Ʈ��
	Camera::main->ControlMainCam();

	if (INPUT->KeyDown('R')) {
		PhysicsCenter::InitSpherePhysics();
		ball->SetWorldPos(Vector3(0, 50, 0));
	}
	if (INPUT->KeyDown(VK_SPACE)) {
		PhysicsCenter::InitSpherePhysics();
		ball->SetWorldPos(Vector3(0, 5, 0));
		PhysicsCenter::g_Direction = Vector3(0, 1, 1);
		PhysicsCenter::g_Velocity = 50;
	}

	if(!PhysicsCenter::g_SteadyState)
		PhysicsCenter::UpdateSpherePhysics();

	//��Ÿ�ӿ� ��ü�� �ݵ�� ������Ʈ ȣ��
	grid->Update();
	player->Update();
	ball->Update();
	terrain->Update();
}

void Scene1::LateUpdate()
{

}

void Scene1::PreRender()
{

}

void Scene1::Render()
{
	//�׸������
	Camera::main->Set(); //ī�޶���
	LIGHT->Set();       //����Ʈ����
	grid->Render();
	player->Render();
	ball->Render();
	terrain->Render();
}

void Scene1::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
