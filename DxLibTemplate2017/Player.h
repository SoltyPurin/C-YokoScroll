#pragma once
#include "Vector2.h"
class Player {
public:
    Player();
    ~Player();
    void Move(float moveValue);
    void Update();
    void DrawPlayer();
    void SetVY(float vy);
    void Gravity();
    float ReturnVY();
    Vector2 GetPos();
};