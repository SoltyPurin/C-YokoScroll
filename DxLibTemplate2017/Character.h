#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Stage.h"
class Rect;

class Character
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	Character(float x,float y);
	/// <summary>
	/// 終了時の処理
	/// </summary>
	~Character();
	/// <summary>
	/// 最初に呼び出す
	/// </summary>
	virtual void Start();
	/// <summary>
	/// 常に行う処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// 被弾時の処理
	/// </summary>
	virtual void TakeDamage();
	/// <summary>
	/// ステージクラスのポインターをセット
	/// </summary>
	/// <param name="pStage">ステージのポインター</param>
	virtual void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	/// <summary>
	/// 当たり判定の処理
	/// </summary>
	/// <param name="chipRect">ステージのチップセットの当たり判定(Rect)</param>
	virtual void CheckHitMap(Rect& chipRect);
	/// <summary>
	/// 自分の当たり判定を返す
	/// </summary>
	/// <returns>自分のRect</returns>
	Rect GetColRect() const { return _collisionRect; }
	/// <summary>
	/// 座標をリセットする
	/// </summary>
	virtual void ResetPosition();
	/// <summary>
	/// 重力
	/// </summary>
	virtual void  Gravity(float deltaTime);
protected:
	//写真のハンドルを保存
	int _imageHandle;
	//垂直方向の力
	float _verticalY;
	//ステージのポインター
	Stage* _stagePointer;
	//現在の座標
	Vector2 _pos;
	//描画する座標
	Vector2 _draw;
	//当たり判定
	Rect _collisionRect;
	//大きさ
	float _scale = 99;
	//重力
	float _gravity = 10.5f;
	//最初のX座標
	float _initX;
	//最初のy座標
	float _initY;
	//1秒あたりなんピクセル進むか
	float _oneMinuteMovePixel = 100.0f; 
	//時間
	float _deltaTime = 0;
	//最初の時間
	float _prevTime = 0;
};


