#include "Obstacle.h"
#include <DxLib.h>
#include "Vector2.h"

int _obstacleGraph = 0;
Vector2 _position;
Vector2 _scale;
int _xPos = 320;
int _yPos = 320;
int _xScale = 159;
int _yScale = 159;
Obstacle::Obstacle() {
	_obstacleGraph = LoadGraph("Image/Obstacle.png");
	_position.x = _xPos;
	_position.y = _yPos;
	_scale.x = _xScale;
	_scale.y = _yScale;
}

Obstacle::~Obstacle() {
	DeleteGraph(_obstacleGraph);
}
void Obstacle::DrawObstacle() {
	DrawExtendGraph(_xPos, _yPos, _xPos+_xScale, _yPos + _yScale, _obstacleGraph, TRUE);
	//DrawGraph(0, 0, _obstacleGraph, TRUE);
}

Vector2 Obstacle::ReturnPos() {
	return _position;
}

Vector2 Obstacle::ReturnScale() {
	return _scale;
}
