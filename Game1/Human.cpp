#include "stdafx.h"
#include "Human.h"

Human::Human()
{
    actor = Actor::Create();
    actor->LoadFile("Human.xml");

    //Actor* Hand = Actor::Create();
    //Hand->LoadFile("Paper.xml");
    //Hand->name = "handRoot";
    //
    //actor->Find("RHand")->AddChild(Hand);


    //메인카메라 등록

    //카메라 출력할 창 위치 크기
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    //종횡비
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();

    state = HumanState::IDLE;
}

void Human::Update()
{
    if (state == HumanState::IDLE)
    {
        //아이들상태에서는 Neck 을 회전
        //-30~ 30
        actor->Find("Neck")->rotation.y += plus ? DELTA : -DELTA;
        if (actor->Find("Neck")->rotation.y < -30.0f * ToRadian)
        {
            plus = true;
            actor->Find("Neck")->rotation.y = -30.0f * ToRadian;
        }
        else if (actor->Find("Neck")->rotation.y > 30.0f * ToRadian)
        {
            plus = false;
            actor->Find("Neck")->rotation.y = 30.0f * ToRadian;
        }

        //idle -> walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('S'))
        {
            state = HumanState::WALK;
            actor->Find("Neck")->rotation.y = 0.0f;
        }
    }
    else if (state == HumanState::WALK)
    {
        //LPelvic; RSholder;
        //RPelvic; LSholder;
        actor->Find("LPelvic")->rotation.x += plus ? DELTA : -DELTA;
        actor->Find("RSholder")->rotation.x += plus ? DELTA : -DELTA;

        actor->Find("RPelvic")->rotation.x += plus ? -DELTA : DELTA;
        actor->Find("LSholder")->rotation.x += plus ? -DELTA : DELTA;

        if (actor->Find("LPelvic")->rotation.x < -30.0f * ToRadian)
        {
            plus = true;
        }
        else if (actor->Find("LPelvic")->rotation.x > 30.0f * ToRadian)
        {
            plus = false;
        }



        //walk -> idle
        if (not (INPUT->KeyPress('W') or INPUT->KeyPress('S')))
        {
            state = HumanState::IDLE;
            actor->Find("LPelvic")->rotation.x    =0.0f;
            actor->Find("RSholder")->rotation.x   =0.0f;
            actor->Find("RPelvic")->rotation.x    =0.0f;
            actor->Find("LSholder")->rotation.x   =0.0f;
        }
    }

    if (INPUT->KeyPress('W'))
    {
        actor->MoveWorldPos(actor->GetForward() * 10.0f * DELTA);
    }
    if (INPUT->KeyPress('S'))
    {
        actor->MoveWorldPos(-actor->GetForward() * 10.0f * DELTA);
    }
    if (INPUT->KeyPress('A'))
    {
        actor->rotation.y -= DELTA;
    }
    if (INPUT->KeyPress('D'))
    {
        actor->rotation.y += DELTA;
    }

    actor->Update();
}

void Human::Render()
{
    actor->Render();
}

void Human::RenderHierarchy()
{
    actor->RenderHierarchy();
}
