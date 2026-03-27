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
    Player(float x,float y);
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
    //表示に使うハンドル
    int _useHandle;
    //待機状態のハンドルを保存
    int _idleHandle;
    //移動のハンドルを保存
    int _moveHandle;

};