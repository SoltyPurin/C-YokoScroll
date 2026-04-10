#pragma once
#include "Character.h"
#include "Vector2.h"
#include "Rect.h"
#include "ShareClass.h"
class Rect;
class Jump;
class Stage;
class Axe;
class ThrowKnife;
enum class PlayerState {
    Idle,
    Move,
    Jump,
    Throw,
};

class Player : public Character {
public:
    Player(float x,float y,NormalPlayerImages images);
    virtual ~Player() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void CheckHitMap(Rect& chipRect) override;
    void CheckSpringHitMap(Rect& springRect);
    void CheckMoveFloorHitMap(Rect& moveFloorRect, VerticalMoveFloor* floor);
    virtual void ResetPosition() override;
    virtual void Move(float moveValue,bool isRight);
    void SetVY(float vy);
    float ReturnVY();
    Vector2 GetPos();
    void JumpProtocol();
    void SetJumpAddres(Jump* jump) { _jumpAddres = jump; }
    void ChangeWeapon();
    Axe* CreateAxe();
    ThrowKnife* CreateKnife();
    int ReturnCurrentWeaponIndex();
    virtual void ChangeHandle();

protected:
    enum class WeaponKinds {
        UseAxe,
        UseKnife,
        Max
    };
    PlayerState _currentState = PlayerState::Idle;
    Vector2 _move;
    Jump* _jumpAddres;
    int _weaponIndex;
    int _weaponCount = 0;
    //接地中か
    bool _isGround = false;
    //右向きか
    bool _isRight = true;
    //移動中か
    bool _isMoveing = false;
    //武器を投げてる最中かどうか
    bool _isThrowing = false;
    //表示に使うハンドル
    int _useHandle;
    //待機状態のハンドルを保存
    int _idleHandle;
    //移動1のハンドルを保存
    int _moveOneHandle;
    //移動2のハンドルを保存
    int _moveTwoHandle;
    //ジャンプのハンドルを保存
    int _jumpHandle;
    //武器を投げるハンドルを保存
    int _throwHandle;
    //投げるモーションの再生時間
    float _throwStateTime = 0.5f;
    float _currentThrowingTime = 0;
};