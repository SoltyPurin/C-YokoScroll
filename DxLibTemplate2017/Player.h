#pragma once
#include "Vector2.h"
#include "Rect.h"
class Stage;
class Player {
public:
    Player();
    ~Player();
    void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
    void Move(float moveValue);
    void Update();
    void DrawPlayer();
    void SetVY(float vy);
    void Gravity();
    float ReturnVY();
    Vector2 GetPos();

private:
    Stage* _stagePointer;
    Rect _collisionRect;
};