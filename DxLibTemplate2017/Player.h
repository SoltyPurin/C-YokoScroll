#pragma once
#include "Character.h"
#include "Vector2.h"
#include "Rect.h"
class Rect;
class Jump;
class Stage;
class Axe;
class ThrowKnife;
class Player : public Character {
public:
    Player();
    virtual ~Player();
    virtual void Update() override;
    virtual void Draw() override;
    virtual void CheckHitMap(Rect& chipRect) override;
    void CheckObstacleHitMap(Rect& obstacleRect,bool isSpring);
    virtual void ResetPosition() override;
    void Move(float moveValue,bool isRight);
    void SetVY(float vy);
    float ReturnVY();
    Vector2 GetPos();
    void JumpProtocol();
    void SetJumpAddres(Jump* jump) { _jumpAddres = jump; }
    void ChangeWeapon();
    Axe* CreateAxe();
    ThrowKnife* CreateKnife();
    int ReturnCurrentWeaponIndex();
private:
    enum class WeaponKinds {
        UseAxe,
        UseKnife,
        Max
    };
    Vector2 _move;
    Jump* _jumpAddres;
    int _weaponIndex;
    int _weaponCount = 0;
    bool _isGround = false;
    bool _isRight = true;
};