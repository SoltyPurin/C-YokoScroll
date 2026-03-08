#include "Character.h"
#include "Stage.h"

Character::Character() :
_stagePointer(nullptr){

}

Character::~Character() {

}

void Character::Start() {

}

void Character::Update() {
}

void Character::Draw() {
}

void Character::Gravity(float deltaTime) {
	_verticalY -= _gravity * deltaTime;
}

void Character::CheckHitMap(Rect& chipRect) {

}
void Character::TakeDamage() {

}


void Character::ResetPosition() {
	_pos.x = _initX;
	_pos.y = _initY;
	_verticalY = 0;
}
