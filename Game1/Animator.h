#pragma once
#define ANIMSPEED 5
class Animator
{
public:
	static void Human_move(Actor* human);
	static void Human_idle(Actor* human);
private:
	static float animTime;
};

