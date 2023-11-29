#include "stdafx.h"
#include "Animator.h"
#include "Scene1.h"



void Scene1::GameInit()
{
	for (size_t i = 0; i < BLOON_MAX; i++)
	{
		bloons->Find("bloon" + to_string(i))->SetWorldPos(Vector3(0, RANDOM->Float(20.0f, 120.0f), i * 3 + 20));
	}
	//Camera::main = (Camera*)actor->Find("humanCam");
	Camera::main = cam1;
	Animator::Human_idle(actor);
	actor->SetWorldPos(Vector3(0, 9, 0));
	actor->Update();
	spear->SetWorldPos(actor->Find("handPos")->GetWorldPos());
	spearObj->rotation.x = 0;
	spear->Update();

	GameObject* gauger = actor->Find("gauge");
	gauger->scale.z = 0;
	gauger->SetWorldPosZ(-5);
	foward_val = 1;
	up_val = 1;
	isShooting = false;
	gameStart = false;
	scorePrint = false;
	score = 0;
	TextOuter();
}

void Scene1::TextOuter()
{
	system("cls");
	cout << "          ※ 창던지기 ※ " << endl << endl;
	cout << " - Space를 눌러 게임을 시작합니다. " << endl;
	cout << " - Space를 길게 눌러 창을 던지세요 " << endl;
	cout << " - 다시 시작하려면 R키를 누르세요 " << endl << endl;
	cout << " * 현재 최고 기록 [ " << maxScore << "m ]" << endl << endl;
}

Scene1::Scene1()
{
	grid = Grid::Create();

	cam1 = Camera::Create();
	cam1->LoadFile("Cam.xml");

	Camera::main = cam1;

	spearDir.x = 0;
	spearDir.y = 1;
	spearDir.z = 1;
	//액터의 생성은 Create 함수로 생성
	actor = Actor::Create();
	actor->LoadFile("RunHuman.xml");

	spear = Actor::Create();
	spear->LoadFile("Spear.xml");
	spearObj = spear->Find("object");

	line = Actor::Create();
	line->LoadFile("Line.xml");

	bloons = Actor::Create();
	for (size_t i = 0; i < BLOON_MAX; i++)
	{
		Actor* temp = Actor::Create();
		temp->LoadFile("bloon.xml");
		temp->name = "bloon" + to_string(i);
		bloons->AddChild(temp);
	}

	GameInit();
}
Scene1::~Scene1()
{
	//new delete가 아닌 create release로 생성 해제
	grid->Release();
	cam1->Release();
	actor->Release();
	spear->Release();
	line->Release();
	bloons->Release();
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
	cam1->RenderHierarchy();
	actor->RenderHierarchy();
	spear->RenderHierarchy();
	line->RenderHierarchy();
	bloons->RenderHierarchy();
	ImGui::End();
	//gui출력끝


	//메인캠 컨트롤
	Camera::main->ControlMainCam();
	if (INPUT->KeyDown('R'))
	{
		GameInit();
	}
	if (gameStart)
	{
		if (!isShooting)
		{
			if (INPUT->KeyPress(VK_SPACE))
			{
				spear->SetWorldPos(actor->Find("handPos")->GetWorldPos());
				spearObj->rotation.x = actor->Find("Rarm")->rotation.x;
				Animator::Human_move(actor);

				GameObject* gauger = actor->Find("gauge");
				if (gauger->scale.z >= 5.0f)
				{
					gauger->scale.z = 0;
					gauger->SetWorldPosZ(-5);
					up_val = 1;
					foward_val = 1;
				}
				else
				{
					gauger->scale.z += DELTA * 4;
					gauger->SetWorldPosZ(gauger->GetWorldPos().z + DELTA * 4);
					up_val += DELTA * 60.0f;
					foward_val += DELTA * 120.0f;
				}
			}
			if (INPUT->KeyUp(VK_SPACE))
			{
				isShooting = true;
				spear->SetWorldPos(actor->GetWorldPos() + Vector3(0, 5, 0));
				spearObj->rotation.x = 0;
				Animator::Human_idle(actor);
			}
		}
		else
		{
			Camera::main = (Camera*)spear->Find("spearCam");
			for (size_t i = 0; i < BLOON_MAX; i++)
			{
				GameObject* temp = bloons->Find("bloon" + to_string(i));
				if (temp->Intersect(spear->children["object"]))
				{
					temp->SetWorldPosZ(-200.0f);
					++score;
				}
			}
			if (spear->GetWorldPos().y > 0)
			{
				up_val -= DELTA * 20.0f;
				spearDir.Normalize();
				Vector3 velocity = Vector3(0, spearDir.y * up_val, spearDir.z * foward_val);
				spear->MoveWorldPos(velocity * DELTA);
				velocity.Normalize();
				spearObj->rotation.x = -atan2(velocity.y, velocity.z);
			}
			else
			{
				if (!scorePrint)
				{
					//float score = (spear->GetWorldPos().z - 150.0f) * 0.05f;
					scorePrint = true;
					cout << "  기록 : ";
					cout << score << "점" << endl;
					if (score > maxScore)
					{
						cout << " * 신기록 달성 *" << endl;
						maxScore = score;
					}
				}
				if (INPUT->KeyUp(VK_SPACE))
				{
					GameInit();
				}
			}
		}
	}
	else
	{
		if (INPUT->KeyUp(VK_SPACE))
		{
			gameStart = true;
		}
	}
	//런타임에 객체는 반드시 업데이트 호출
	grid->Update();
	actor->Update();
	spear->Update();
	line->Update();
	bloons->Update();
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
	Camera::main->Set(); //카메라세팅
	LIGHT->Set();       //라이트세팅
	grid->Render();
	actor->Render();
	spear->Render();
	line->Render();
	bloons->Render();
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
