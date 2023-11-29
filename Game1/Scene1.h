#pragma once
class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
private:
	Camera* cam1;
	Grid* grid;

	Actor* player;
	Actor* ball;
	Actor* terrain;
	Actor* objects;
};