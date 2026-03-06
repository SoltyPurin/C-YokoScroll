#pragma once
#include "Character.h"
#include "Vector2.h"
#include "Rect.h"
class Rect;
class Jump;
class Stage;
class Axe;
class Player : public Character {
public:
    Player();
    virtual ~Player();
    virtual void Update() override;
    virtual void Draw() override;
    virtual void CheckHitMap(Rect& chipRect) override;
    virtual void ResetPosition() override;
    void Move(float moveValue,bool isRight);
    void SetVY(float vy);
    float ReturnVY();
    Vector2 GetPos();
    void JumpProtocol(Jump& jump);
    void CheckFall();
    Axe* CreateAxe();
private:
    Vector2 _move;
    Jump* jump;
};