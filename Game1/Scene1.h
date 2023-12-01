#pragma once
#define MIN_PLAYER_XPOS -100
#define MAX_PLAYER_XPOS 100
#define MIN_PLAYER_ZPOS 0
#define MAX_PLAYER_ZPOS 100
#define MAX_POWER 200
#define AbsSum(a,b) (abs(a) + abs(b))
enum class GameState
{
	STANDBY, CONTROL, ANIMTIME, RESULT
};
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
	void InitToGameStandby();
	void GameClear();
	int stats_hole = 0;
	
	float player_horizontal_power = 0;
	float player_vertical_power = 0;
	float ball_velocity = 0.0f;

	GameState game_state;
	Vector3 pos_player_init;
	Vector3 pos_last_ball;
	Vector2 wind_dir;
	Camera* cam_main;
	Camera* cam_minimap;
	Grid* grid;
	Sky* skybox;
	Actor* player;
	Actor* ball;
	Actor* terrain;
	Actor* arrow_dir;
	Actor* objects;
	Actor* ui_ball_nav;
	UI* ui_pannel_minimap;
	UI* test_gauge_h;
	UI* test_gauge_v;
	UI* test_gauge_p;
};