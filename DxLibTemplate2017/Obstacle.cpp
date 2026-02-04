#include "Obstacle.h"
#include <DxLib.h>

int _obstacleGraph = 0;
void Obstacle::Start() {
	_obstacleGraph = LoadGraph("Image/Obstacle.png");
}
void Obstacle::DrawObstacle() {
	DrawGraph(0, 0, _obstacleGraph, TRUE);
}