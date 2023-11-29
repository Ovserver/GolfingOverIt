#include "stdafx.h"
#include "Human.h"

Human::Human()
{
    player = Actor::Create();
    player->LoadFile("Human.xml");

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
        player->Find("Neck")->rotation.y += plus ? DELTA : -DELTA;
        if (player->Find("Neck")->rotation.y < -30.0f * ToRadian)
        {
            plus = true;
            player->Find("Neck")->rotation.y = -30.0f * ToRadian;
        }
        else if (player->Find("Neck")->rotation.y > 30.0f * ToRadian)
        {
            plus = false;
            player->Find("Neck")->rotation.y = 30.0f * ToRadian;
        }

        //idle -> walk
        if (INPUT->KeyPress('W') or INPUT->KeyPress('S'))
        {
            state = HumanState::WALK;
            player->Find("Neck")->rotation.y = 0.0f;
        }
    }
    else if (state == HumanState::WALK)
    {
        //LPelvic; RSholder;
        //RPelvic; LSholder;
        player->Find("LPelvic")->rotation.x += plus ? DELTA : -DELTA;
        player->Find("RSholder")->rotation.x += plus ? DELTA : -DELTA;

        player->Find("RPelvic")->rotation.x += plus ? -DELTA : DELTA;
        player->Find("LSholder")->rotation.x += plus ? -DELTA : DELTA;

        if (player->Find("LPelvic")->rotation.x < -30.0f * ToRadian)
        {
            plus = true;
        }
        else if (player->Find("LPelvic")->rotation.x > 30.0f * ToRadian)
        {
            plus = false;
        }



        //walk -> idle
        if (not (INPUT->KeyPress('W') or INPUT->KeyPress('S')))
        {
            state = HumanState::IDLE;
            player->Find("LPelvic")->rotation.x    =0.0f;
            player->Find("RSholder")->rotation.x   =0.0f;
            player->Find("RPelvic")->rotation.x    =0.0f;
            player->Find("LSholder")->rotation.x   =0.0f;
        }
    }

    if (INPUT->KeyPress('W'))
    {
        player->MoveWorldPos(player->GetForward() * 10.0f * DELTA);
    }
    if (INPUT->KeyPress('S'))
    {
        player->MoveWorldPos(-player->GetForward() * 10.0f * DELTA);
    }
    if (INPUT->KeyPress('A'))
    {
        player->rotation.y -= DELTA;
    }
    if (INPUT->KeyPress('D'))
    {
        player->rotation.y += DELTA;
    }

    player->Update();
}

void Human::Render()
{
    player->Render();
}

void Human::RenderHierarchy()
{
    player->RenderHierarchy();
}
