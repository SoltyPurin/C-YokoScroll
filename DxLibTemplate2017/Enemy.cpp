#include "Enemy.h"
#include <DxLib.h>
#include "Rect.h"
#include "ShareClass.h"


Enemy::Enemy(Stage* stage,float x,float y):
_stagePointer(stage),
_initPos(x,y),
_currentPos(x, y){
	_imageHandle = LoadGraph("Image/RedEnemy.png");
    _scale = 99;
    ResetPosition();
}


Enemy::~Enemy() {
	DeleteGraph(_imageHandle);
}
void Enemy::ResetPosition() {
    _currentPos.x = _initPos.x;
    _currentPos.y = _initPos.y;
    _verticalY = 0;
}


void Enemy::Update() {

	Gravity(ShareClass::DeltaTime);
	_currentPos.y -= _verticalY * _oneMinuteMovePixel * ShareClass::DeltaTime;
    float colX = _currentPos.x - _stagePointer->GetScrollX() - _scale * 0.5f;
    float colY = _currentPos.y - _stagePointer->GetScrollY() - _scale * 0.5f;

    //_collisionRect.SetCenter(colX  ,colY , _scale, _scale);
    _collisionRect.SetCenter(colX + _scale, colY + _scale, _scale, _scale);

}

void Enemy::Draw(float scrollX,float scrollY) {
    int drawX = static_cast<int>(_currentPos.x - scrollX);
    int drawY = static_cast<int>(_currentPos.y - scrollY);
    int sizeX = drawX + _scale;
    int sizeY = drawY + _scale;

    DrawExtendGraph(drawX, drawY, sizeX,sizeY, _imageHandle, TRUE);

#ifdef _DEBUG
	//// 当たり判定を表示
	_collisionRect.Draw(0x0000ff, false);
#endif

}

void Enemy::CheckHitMap(Rect& chipRect) {

    //今までは画面座標を使用していたが計算がズレ、バグの原因になっていたため、
    //仮のワールド座標を生成してそれで計算を行う。
    Rect worldRect;
    worldRect.SetCenter(_currentPos.x + _scale * 0.5f, _currentPos.y + _scale * 0.5f, _scale, _scale);
    // めり込み量（左右・上下）
    float overlapL = worldRect.GetRight() - chipRect.GetLeft();   // 左へ押す量
    float overlapR = chipRect.GetRight() - worldRect.GetLeft(); // 右へ押す量
    float overlapT = worldRect.GetBottom() - chipRect.GetTop();    // 上へ押す量
    float overlapB = chipRect.GetBottom() - worldRect.GetTop();  // 下へ押す量

    // X/Yそれぞれ最小の押し戻し量
    float pushX = (overlapL < overlapR) ? overlapL : overlapR;
    float pushY = (overlapT < overlapB) ? overlapT : overlapB;

    // 中心でどっち側にいるか判定
    float rcx = (worldRect.GetLeft() + worldRect.GetRight()) * 0.5f;
    float rcy = (worldRect.GetTop() + worldRect.GetBottom()) * 0.5f;
    float ccx = (chipRect.GetLeft() + chipRect.GetRight()) * 0.5f;
    float ccy = (chipRect.GetTop() + chipRect.GetBottom()) * 0.5f;

    // 重要：小さい軸だけ解決（壁に当たったのに縦へ押し戻す…を防ぐ）
    if (pushX < pushY)
    {
        // 横解決
        if (rcx < ccx)
            _currentPos.x -= pushX; // チップの左側にいる → 左へ
        else
            _currentPos.x += pushX; // チップの右側にいる → 右へ

        // 横衝突だけでは地面判定は変えない（降りられない原因になりやすい）
    }
    else
    {
        // 縦解決
        if (rcy < ccy)
        {
            // 上から乗った（着地）
            _currentPos.y -= pushY;
            if (_verticalY <= 0) {
                _verticalY = 0.0f;
            }
        }
    }

}

void Enemy::Gravity(float deltaTime) {
    _verticalY -= _gravity * deltaTime;
}



