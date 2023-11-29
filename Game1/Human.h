#pragma once

enum class HumanState
{
    IDLE,
    WALK
};


class Human
{
private:
    Actor* actor;
    HumanState state;
    bool plus = true;

public:
    Human();
    void Update();
    void Render();
    void RenderHierarchy();

};

