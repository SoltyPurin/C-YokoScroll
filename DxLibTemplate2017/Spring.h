#pragma once
#include "Vector2.h"
#include "Stage.h"
#include "Rect.h"
class Stage;
class Rect;
class Spring
{
public:
	Spring(Stage* stagePointer,float x,float y);
	~Spring();
	void Update();
	void DrawSpring(float scrrolX, float scrrolY);
	/// <summary>
	/// バネを発動状態に切り替える
	/// </summary>
	void ActiveSpring();
	virtual void SetStagePointer(Stage* pStage) { _stagePointer = pStage; }
	Rect GetColRect() const { return _collisionRect; }
	Vector2 GetPos() const { return _currentPos; }

private:
	int _springDeActiveHandle;

	int _springActiveHandle;

	int _viewSpringHandle;

	int _scale = 99;
	//現在の座標
	Vector2 _currentPos;
	//描画する座標
	Vector2 _currentDraw;

	Stage* _stagePointer;

	Rect _collisionRect;

	//時間
	float _deltaTime = 0;
	//最初の時間
	float _prevTime = 0;

	bool _isSpringActive;

	float _springActiveTime = 1.5f;

	float _currentActiveTime =0;

};

