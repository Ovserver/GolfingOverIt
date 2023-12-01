#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	

	//투명 이미지출력
}

Main::~Main()
{
	
}
void Main::Init()
{
	grid = Grid::Create();

	cam_main = Camera::Create();
	cam_main->LoadFile("Cam.xml");
	Camera::main = cam_main;


}

void Main::Release()
{
}

void Main::Update()

{
	ImGui::Begin("Hierarchy");
	grid->RenderHierarchy();
	ImGui::End();

	cam_main->ControlMainCam();

	cam_main->Update();
	grid->Update();
}

void Main::LateUpdate()
{
	

}
void Main::PreRender()
{
}

void Main::Render()
{
	cam_main->Set();
	LIGHT->Set();
	
	grid->Render();
	
}

void Main::ResizeScreen()
{
	cam_main->viewport.x = 0.0f;
	cam_main->viewport.y = 0.0f;
	cam_main->viewport.width = App.GetWidth();
	cam_main->viewport.height = App.GetHeight();
	cam_main->width = App.GetWidth();
	cam_main->height = App.GetHeight();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game2");
	App.SetInstance(instance);
	WIN->Create();
	D3D->Create();
	Main* main = new Main();
	main->Init();

	int wParam = (int)WIN->Run(main);


	main->Release();
	SafeDelete(main);
	D3D->DeleteSingleton();
	WIN->DeleteSingleton();

	return wParam;
}