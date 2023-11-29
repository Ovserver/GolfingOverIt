#pragma once
#define BLOON_MAX 200
#define GAUGE_MAX 10
class Scene1 : public Scene
{
private:
	Camera* cam1;
	Grid* grid;

	//�⺻������ ������Ʈ�� ���ͷ� ����
	Actor* actor;
	Actor* spear;
	Actor* line;
	Actor* bloons;	
	GameObject* spearObj;
	bool    isShooting = false;
	bool	gameStart = false;
	bool	scorePrint = false;
	Vector3 spearDir;
	float   foward_val = 10;
	float   up_val = 10;
	float	score = 0;
	float	maxScore = 0;

	void GameInit();
	void TextOuter();
public:
	Scene1();
	~Scene1();

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

