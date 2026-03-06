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

void Character::Gravity() {
	_verticalY -= _gravity;
}

void Character::TakeDamage() {

}
