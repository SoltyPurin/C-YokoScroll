#include "Enemy.h"
#include <DxLib.h>
#include "Rect.h"



Enemy::Enemy(){
    _prevTime = GetNowCount();
	_imageHandle = LoadGraph("Image/RedEnemy.png");
    _initX = _enInitX;
    _initY = _enInitY;
    ResetPosition();
}

Enemy::~Enemy() {
	DeleteGraph(_imageHandle);
}

void Enemy::Update() {
    int currentTime = GetNowCount();
    _deltaTime = (currentTime - _prevTime) / 1000.0f;
    _prevTime = currentTime;

	Gravity(_deltaTime);
	_pos.y -= _verticalY * _oneMinuteMovePixel * _deltaTime;
    _collisionRect.SetCenter(
        _pos.x + _scale * 0.5f,
        _pos.y + _scale * 0.5f,
        _scale,
        _scale
    );
    //_centerX = _pos.x  + _scale * 0.5f;
    //_centerY = _pos.y +  _scale * 0.5f;
    //_collisionRect.SetCenter(_centerX , _centerY , _scale, _scale);
}

void Enemy::Draw() {
    int scrollX = _stagePointer->GetScrollX();
    int scrollY = _stagePointer->GetScrollY();
    int drawX = static_cast<int>(_pos.x - _stagePointer->GetScrollX());
    int drawY = static_cast<int>(_pos.y - _stagePointer->GetScrollY());
    int sizeX = drawX + _scale;
    int sizeY = drawY + _scale;
    DrawExtendGraph(drawX, drawY, sizeX, sizeY, _imageHandle, TRUE);

#ifdef _DEBUG
    DrawBoxAA(
        _collisionRect.GetLeft() - scrollX,
        _collisionRect.GetTop() - scrollY,
        _collisionRect.GetRight() - scrollX,
        _collisionRect.GetBottom() - scrollY,
        0x0000ff,
        false
    );
	//// 当たり判定を表示
	//_collisionRect.Draw(0x0000ff, false);
#endif

}

void Enemy::SetPosition(float x, float y) {
    _initX = x;
    _initY = y;
    _verticalY = 0;
    ResetPosition();
}

void Enemy::CheckHitMap(Rect& chipRect) {

    _collisionRect.SetCenter(
        _pos.x + _scale * 0.5f,
        _pos.y + _scale * 0.5f,
        _scale,
        _scale
    );
  /*  _collisionRect.SetCenter(_centerX, _centerY, _scale, _scale);*/

    // めり込み量（左右・上下）
    float overlapL = _collisionRect.GetRight() - chipRect.GetLeft();   // 左へ押す量
    float overlapR = chipRect.GetRight() - _collisionRect.GetLeft(); // 右へ押す量
    float overlapT = _collisionRect.GetBottom() - chipRect.GetTop();    // 上へ押す量
    float overlapB = chipRect.GetBottom() - _collisionRect.GetTop();  // 下へ押す量

    // X/Yそれぞれ最小の押し戻し量
    float pushX = (overlapL < overlapR) ? overlapL : overlapR;
    float pushY = (overlapT < overlapB) ? overlapT : overlapB;

    // 中心でどっち側にいるか判定
    float rcx = (_collisionRect.GetLeft() + _collisionRect.GetRight()) * 0.5f;
    float rcy = (_collisionRect.GetTop() + _collisionRect.GetBottom()) * 0.5f;
    float ccx = (chipRect.GetLeft() + chipRect.GetRight()) * 0.5f;
    float ccy = (chipRect.GetTop() + chipRect.GetBottom()) * 0.5f;

    // 重要：小さい軸だけ解決（壁に当たったのに縦へ押し戻す…を防ぐ）
    if (pushX < pushY)
    {
        // 横解決
        if (rcx < ccx)
            _pos.x -= pushX; // チップの左側にいる → 左へ
        else
            _pos.x += pushX; // チップの右側にいる → 右へ

        // 横衝突だけでは地面判定は変えない（降りられない原因になりやすい）
    }
    else
    {
        // 縦解決
        if (rcy < ccy)
        {
            // 上から乗った（着地）
            _pos.y -= pushY;
            if (_verticalY <= 0) {
                _verticalY = 0.0f;
            }
        }
    }
    _collisionRect.SetCenter(
        _pos.x + _scale * 0.5f,
        _pos.y + _scale * 0.5f,
        _scale,
        _scale
    );
    //_collisionRect.SetCenter(_centerX, _centerY, _scale, _scale);

    //_collisionRect.SetCenter(_pos.x + _scale * 0.5f, _pos.y + _scale * 0.5f, _scale, _scale);

    //_collisionRect.SetCenter(_pos.x - _stagePointer->GetScrollX() - _scale * 0.5f, _pos.y - _stagePointer->GetScrollY() - _scale * 0.5f, _scale, _scale);

}
