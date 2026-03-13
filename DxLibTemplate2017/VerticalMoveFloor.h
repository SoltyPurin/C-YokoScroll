#pragma once
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
class Stage;
class Rect;
class VerticalMoveFloor
{
public:
	VerticalMoveFloor(Stage* stage);
	~VerticalMoveFloor();
	void Update();
	void DrawFloor(float scrrolX, float scrrolY);
	void SetPosition(float x, float y);
	virtual void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }

private:
	int _floorHandle;

	int _scale = 99;
	//現在の座標
	Vector2 _currentPos;
	//描画する座標
	Vector2 _currentDraw;

	Stage* _stagePointer;

	Rect _collisionRect;

	//上昇のフラグ、1が上昇、-1が下降
	int _upperFlagValue;

	//一秒間に動くピクセル数
	float _oneMinuteMovePixel = 100;

	//速度
	float _floorMoveSpeed = 1;

	//最初の地点からどれだけ移動するか
	float _moveRange =100;

	float _upperLimit;

	float _downerLimit;

	//時間
	float _deltaTime = 0;
	//最初の時間
	float _prevTime = 0;

};

