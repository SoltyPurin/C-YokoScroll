#pragma once
#include "Character.h"
#include "Vector2.h"
#include "Rect.h"
#include "ShareClass.h"
#include <memory>
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
    BlowAway,
};

class Player : public Character {
public:
    Player(float x,float y,PlayerImages images);
    virtual ~Player() override;
    virtual void Update() override;
    virtual void Draw() override;
    /// <summary>
    /// 通常の当たり判定検知
    /// </summary>
    /// <param name="chipRect">マップチップの当たり判定</param>
    virtual void CheckHitMap(Rect& chipRect) override;
    /// <summary>
    /// バネとの当たり判定検知
    /// </summary>
    /// <param name="springRect"></param>
    void CheckSpringHitMap(Rect& springRect);
    /// <summary>
    /// 移動床との当たり判定検知
    /// </summary>
    /// <param name="moveFloorRect"></param>
    /// <param name="floor"></param>
    void CheckMoveFloorHitMap(Rect& moveFloorRect, VerticalMoveFloor* floor);
    /// <summary>
    /// 座標をリセット
    /// </summary>
    virtual void ResetPosition() override;
    /// <summary>
    /// 移動
    /// </summary>
    /// <param name="moveValue">移動量</param>
    /// <param name="isRight">入力が右かどうか</param>
    virtual void Move(float moveValue,bool isRight);
    /// <summary>
    /// ジャンプの際に上に行く力を設定
    /// </summary>
    /// <param name="vy">上昇力をセット</param>
    void SetVY(float vy);
    /// <summary>
    /// 現在の上昇力を返す
    /// </summary>
    /// <returns>上昇力</returns>
    float ReturnVY();
    Vector2 GetPos();
    void JumpProtocol();
    void SetJumpAddres(Jump* jump) { _jumpAddres = jump; }
    void ChangeWeapon();
    std::unique_ptr<Axe> CreateAxe();
    std::unique_ptr<ThrowKnife> CreateKnife();
    int ReturnCurrentWeaponIndex()const;
    virtual void ChangeHandle();
    /// <summary>
    /// 転んだ時の吹き飛び処理
    /// </summary>
    void BlowAway();
    /// <summary>
    /// 転ぶ処理を呼び出す
    /// </summary>
    /// <param name="isRight">転ぶ際にどちらに転ばせるか</param>
    void CallBlowAway(bool isRight);
    bool IsPlayerRight()const { return _isRight; }

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
    //吹き飛ぶハンドル
    int _blowAwayHandle;
    //武器を投げるハンドルを保存
    int _throwHandle;
    //投げるモーションの再生時間
    float _throwStateTime = 0.5f;
    float _currentThrowingTime = 0;

    float _blowAwayPower = 1.0f;
    float _initBlowAwayPower;
    float _blowAwayMovePixel = 300.0f;
    bool _isBlowing = false;
    bool _isBlowRight;
    float _blowTime = 0;
};