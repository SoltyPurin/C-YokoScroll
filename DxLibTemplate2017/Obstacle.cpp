#include "Obstacle.h"
#include <DxLib.h>
#include "Vector2.h"
#include "Stage.h"

int _obstacleGraph = 0;
Vector2 _position;
float _obstacleScale = 159;
int _xPos = 320;
int _yPos = 320;

float _obstacleDrawX;
float _obstacleDrawY;
Obstacle::Obstacle():
_stagePointer(nullptr){
	_obstacleGraph = LoadGraph("Image/Obstacle.png");
	_position.x = _xPos;
	_position.y = _yPos;
}

Obstacle::~Obstacle() {
	DeleteGraph(_obstacleGraph);
}
void Obstacle::DrawObstacle() {
	_obstacleDrawX = _position.x - _stagePointer->GetScrollX() - _obstacleScale * 0.5f;
	_obstacleDrawY = _position.y - _stagePointer->GetScrollY() - _obstacleScale * 0.5f;
	DrawExtendGraph(_obstacleDrawX, _obstacleDrawY, 
		_obstacleDrawX +_obstacleScale, _obstacleDrawY + _obstacleScale, _obstacleGraph, TRUE);
#ifdef _DEBUG
	// “–‚½‚è”»’è‚ð•\Ž¦
	_collisionRect.Draw(0xFF0000, false);
#endif

	//DrawGraph(0, 0, _obstacleGraph, TRUE);
}
void Obstacle::Update() {
	DrawObstacle();
	_collisionRect.SetCenter(_obstacleDrawX + _obstacleScale * 0.5f,
		_obstacleDrawY + _obstacleScale * 0.5f, _obstacleScale, _obstacleScale);
}

Vector2 Obstacle::ReturnPos() {
	return _position;
}

float Obstacle::ReturnScale() {
	return _obstacleScale;
}
