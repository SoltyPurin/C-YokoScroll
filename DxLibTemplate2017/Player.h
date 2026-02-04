#pragma once
class Player {
public:
    void SetUp();
    void Move(int moveValue);
    void Update();
    void DrawPlayer();
    void SetVY(int vy);
    void Gravity();
    int ReturnY();
    int ReturnVY();
};