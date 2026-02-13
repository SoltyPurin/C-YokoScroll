#pragma once
#include "Vector2.h"
#include "Rect.h"
class Rect;
class Jump;
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
    void JumpProtocol(Jump& jump);
private:
    void CheckHitMap(Rect chipRect);
    Vector2 _move;
    Stage* _stagePointer;
    Rect _collisionRect;
    Jump* jump;
};