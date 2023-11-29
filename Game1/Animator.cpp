#include "stdafx.h"
#include "Animator.h"

float Animator::animTime = 0.1f;

void Animator::Human_move(Actor* human)
{
	if (animTime > 0.5f)
		animTime = 0;
	animTime += DELTA;

	GameObject* Larm = human->Find("Larm");
	GameObject* Rarm = human->Find("Rarm");
	GameObject* Lleg = human->Find("Lleg");
	GameObject* Rleg = human->Find("Rleg");

	Rarm->rotation.x = 150.0f * ToRadian;

	//if (animTime > 0.25f)
	//{
	//	if (Larm->rotation.x < QUATERPI)
	//		Larm->rotation.x += DELTA * ANIMSPEED;
	//	//if (Rarm->rotation.x > -QUATERPI)
	//	//	Rarm->rotation.x -= DELTA * ANIMSPEED;
	//	if (Lleg->rotation.x > -QUATERPI)
	//		Lleg->rotation.x -= DELTA * ANIMSPEED;
	//	if (Rleg->rotation.x < QUATERPI)
	//		Rleg->rotation.x += DELTA * ANIMSPEED;
	//}
	//else
	//{
	//	if (Larm->rotation.x > -QUATERPI)
	//		Larm->rotation.x -= DELTA * ANIMSPEED;
	//	//if (Rarm->rotation.x < QUATERPI)
	//	//	Rarm->rotation.x += DELTA * ANIMSPEED;
	//	if (Lleg->rotation.x < QUATERPI)
	//		Lleg->rotation.x += DELTA * ANIMSPEED;
	//	if (Rleg->rotation.x > -QUATERPI)
	//		Rleg->rotation.x -= DELTA * ANIMSPEED;
	//}
}

void Animator::Human_idle(Actor* human)
{
	GameObject* Larm = human->Find("Larm");
	GameObject* Rarm = human->Find("Rarm");
	GameObject* Lleg = human->Find("Lleg");
	GameObject* Rleg = human->Find("Rleg");

	Larm->rotation.x = 0;
	Rarm->rotation.x = 0;
	Lleg->rotation.x = 0;
	Rleg->rotation.x = 0;
}
