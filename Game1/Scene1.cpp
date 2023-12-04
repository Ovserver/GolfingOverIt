#include "stdafx.h"
#include "PhysicsCenter.h"
#include "Scene1.h"

Scene1::Scene1()
{
	grid = Grid::Create();

	cam_main = Camera::Create();
	cam_main->LoadFile("Cam.xml");

	Camera::main = cam_main;
	cam_minimap = Camera::Create();
	cam_minimap->LoadFile("Cam_minimap.xml");

	origin_cam_minimap_size.x = cam_minimap->viewport.x;
	origin_cam_minimap_size.y = cam_minimap->viewport.y;
	origin_cam_minimap_size.z = cam_minimap->viewport.width;
	origin_cam_minimap_size.w = cam_minimap->viewport.height;

	skybox = Sky::Create();
	skybox->LoadFile("sky.xml");

	player = Actor::Create();
	player->LoadFile("RunHuman.xml");
	player->Update();
	pos_player_init = player->GetWorldPos();

	ball = Actor::Create();
	ball->LoadFile("test_ball.xml");
	ball->Update();

	terrain = Actor::Create();
	terrain->LoadFile("grass.xml");
	terrain->Update();

	arrow_dir = Actor::Create();
	arrow_dir->LoadFile("arrow_dir_fixed.xml");

	objects = Actor::Create();
	objects->LoadFile("test_objects.xml");

	ui_ball_nav = Actor::Create();

	ui_pannel_minimap = UI::Create();
	ui_pannel_minimap->LoadFile("UI_pannel_minimap.xml");

	ui_pannel_hole_count = UI::Create();
	ui_pannel_hole_count->LoadFile("UI_pannel_holecount.xml");

	ui_pannel_power_gauge = UI::Create();
	ui_pannel_power_gauge->LoadFile("UI_pannel_gauge.xml");

	ui_power_gauge = UI::Create();
	ui_power_gauge->LoadFile("UI_gauge.xml");

	test_gauge_h = UI::Create();
	test_gauge_h->LoadFile("test_ui.xml");
	test_gauge_v = UI::Create();
	test_gauge_v->LoadFile("test_ui2.xml");

	PHYSICS->g_Ball = ball;
	PHYSICS->InitTerrainInfo(terrain);
	PHYSICS->InitObjectsInfo(terrain);
	player->SetWorldPos(pos_player_init + ball->GetWorldPos());
	player->Update();
	cam_main->SetWorldPos(ball->GetWorldPos() + Vector3(0, 10, -30));
	cam_main->Update();
	game_state = GameState::STANDBY;


}
Scene1::~Scene1()
{
	//new delete가 아닌 create release로 생성 해제
	grid->Release();
	cam_main->Release();
	cam_minimap->Release();
	skybox->Release();
	player->Release();
	ball->Release();
	terrain->Release();
	objects->Release();
	ui_ball_nav->Release();
	ui_pannel_minimap->Release();
	ui_pannel_hole_count->Release();
	ui_pannel_power_gauge->Release();
	ui_power_gauge->Release();
	test_gauge_h->Release();
	test_gauge_v->Release();
}

void Scene1::Init()
{

}

void Scene1::Release()
{
}

void Scene1::Update()
{
	// 디버그창에 출력
	LIGHT->RenderDetail();

	Camera::main->Update();
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	//하이어라이키창에 출력
	ImGui::Begin("Hierarchy");
	grid->RenderHierarchy();
	cam_main->RenderHierarchy();
	cam_minimap->RenderHierarchy();
	player->RenderHierarchy();
	ball->RenderHierarchy();
	terrain->RenderHierarchy();
	arrow_dir->RenderHierarchy();
	objects->RenderHierarchy();
	ui_ball_nav->RenderHierarchy();
	ui_pannel_minimap->RenderHierarchy();
	ui_pannel_hole_count->RenderHierarchy();
	ui_pannel_power_gauge->RenderHierarchy();
	ui_power_gauge->RenderHierarchy();
	test_gauge_h->RenderHierarchy();
	test_gauge_v->RenderHierarchy();
	ImGui::End();
	//gui출력끝


	//메인캠 컨트롤
	//Camera::main->ControlMainCam();

	if (INPUT->KeyDown('R'))
	{
		PHYSICS->InitSpherePhysics(Vector3(0, 2.5f, 0));
		game_state = GameState::STANDBY;
		InitToGameStandby();
	}
	if (game_state == GameState::STANDBY)
	{
		if (INPUT->KeyUp(VK_SPACE))
		{
			InitToGameStandby();
			game_state = GameState::CONTROL;
		}
	}
	else if (game_state == GameState::CONTROL)
	{
		if (INPUT->KeyPress(VK_SPACE))
		{
			if (ball_velocity <= MAX_POWER)
				ball_velocity += DELTA * 100;
			else
				ball_velocity = 0;
		}
		else
		{
			if (MIN_PLAYER_XPOS < player_horizontal_power && INPUT->KeyPress(VK_LEFT)) {
				player_horizontal_power -= DELTA * 50;
				player->MoveWorldPos(Vector3(1, 0, 0) * DELTA);
			}
			if (MAX_PLAYER_XPOS > player_horizontal_power && INPUT->KeyPress(VK_RIGHT)) {
				player_horizontal_power += DELTA * 50;
				player->MoveWorldPos(Vector3(-1, 0, 0) * DELTA);
			}
			if (MIN_PLAYER_ZPOS < player_vertical_power && INPUT->KeyPress(VK_DOWN)) {
				player_vertical_power -= DELTA * 50;
				player->MoveWorldPos(Vector3(0, 0, -1) * DELTA);
			}
			if (MAX_PLAYER_ZPOS > player_vertical_power && INPUT->KeyPress(VK_UP)) {
				player_vertical_power += DELTA * 50;
				player->MoveWorldPos(Vector3(0, 0, 1) * DELTA);
			}
			Vector3 arrow_vec = Vector3(player_horizontal_power, player_vertical_power, 0);
			arrow_vec += Vector3(0, 1, 1) * 100.0f;
			if (arrow_dir)
			{
				arrow_dir->rotation.x = atan2(arrow_vec.y, arrow_vec.z) - HALFPI;
				arrow_dir->rotation.y = atan2(arrow_vec.y, arrow_vec.x) - HALFPI;
			}
		}
		if (INPUT->KeyUp(VK_SPACE))
		{
			Vector3 powerVec;
			powerVec.x = player_horizontal_power;
			powerVec.y = player_vertical_power;
			powerVec += Vector3(0, 1, 1) * ball_velocity;
			PHYSICS->InitSpherePhysics(ball->GetWorldPos(), powerVec, ball_velocity);
			++stats_hole;
			game_state = GameState::ANIMTIME;
		}

		//test UI Update
		test_gauge_h->SetWorldPosX(player_horizontal_power / AbsSum(MIN_PLAYER_XPOS, MAX_PLAYER_XPOS) * 2);
		test_gauge_v->SetWorldPosX(player_vertical_power / AbsSum(MIN_PLAYER_ZPOS, MAX_PLAYER_ZPOS) * 2 - 1);
		ui_power_gauge->scale.y = ball_velocity / (MAX_POWER * 2);
	}
	else if (game_state == GameState::ANIMTIME)
	{
		if (!PHYSICS->g_SteadyState)
		{
			PHYSICS->UpdateSpherePhysics();
			cam_main->SetWorldPos(ball->GetWorldPos() + Vector3(0, 10, -30));
		}
		else
		{
			if (PHYSICS->g_GroundType == GroundType::HOLE)
				GameClear();
			else if (PHYSICS->g_GroundType == GroundType::WATER)
			{
				ball->SetWorldPos(pos_last_ball);
				ball->Update();
				player->SetWorldPos(pos_player_init + ball->GetWorldPos());
				cam_main->SetWorldPos(ball->GetWorldPos() + Vector3(0, 10, -30));
			}
			else
				player->SetWorldPos(pos_player_init + ball->GetWorldPos());
			game_state = GameState::STANDBY;
		}
	}


	//런타임에 객체는 반드시 업데이트 호출
	skybox->Update();
	//grid->Update();
	player->Update();
	ball->Update();
	terrain->Update();
	arrow_dir->Update();
	objects->Update();
	ui_ball_nav->Update();
	ui_pannel_minimap->Update();
	ui_pannel_hole_count->Update();
	ui_pannel_power_gauge->Update();
	ui_power_gauge->Update();
	cam_minimap->Update();
}

void Scene1::LateUpdate()
{

}

void Scene1::PreRender()
{

}

void Scene1::Render()
{
	//그리기시작
	Camera::main = cam_main;
	Camera::main->Set(); //카메라세팅
	LIGHT->Set();       //라이트세팅
	skybox->Render();
	//grid->Render();
	player->Render();
	ball->Render();
	terrain->Render();
	objects->Render();
	ui_pannel_minimap->Render();
	ui_pannel_hole_count->Render();
	if (game_state == GameState::CONTROL) {
		arrow_dir->Render();
		ui_pannel_power_gauge->Render();
		ui_power_gauge->Render();
	}
	Camera::main = cam_minimap;
	Camera::main->Set();
	LIGHT->Set();       //라이트세팅
	skybox->Render();
	ball->Render();
	terrain->Render();
	objects->Render();
	ui_ball_nav->Render();

	RECT rect;
	DWRITE->RenderText(L"HOLE\n\n" + to_wstring(stats_hole), RECT({ 156,57,500,500 }));

	Camera::main = cam_main;
	Camera::main->Set();
}

void Scene1::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();

	cam_minimap->viewport.x = origin_cam_minimap_size.x / 1280 * App.GetWidth();
	cam_minimap->viewport.y = origin_cam_minimap_size.y / 720 * App.GetHeight();
	cam_minimap->viewport.width = origin_cam_minimap_size.z / 1280 * App.GetWidth();
	cam_minimap->viewport.height = origin_cam_minimap_size.w / 720 * App.GetHeight();
	
}

void Scene1::InitToGameStandby()
{
	cam_main->SetWorldPos(ball->GetWorldPos() + Vector3(0, 10, -30));
	if (arrow_dir)
		arrow_dir->SetWorldPos(ball->GetWorldPos() + Vector3(0, 0, 2));
	pos_last_ball = ball->GetWorldPos();
	player_horizontal_power = 0;
	player_vertical_power = 0;
	ball_velocity = 0;
}

void Scene1::GameClear()
{
}
