#include "Weapons.h"
#include "DxLib.h"

Weapons::Weapons():
	_weaponPosition({ 0,0 }),
	_move({ 0,0 })
{

}

Weapons::~Weapons() {

}

void Weapons::Update() {

}
void Weapons::DrawWeapon() {
	float drawX = _weaponPosition.x - _weaponScale * 0.5f;
	float drawY = _weaponPosition.y - _weaponScale * 0.5f;

	float plusPosx = drawX + _weaponScale;
	float plusPosy = drawY + _weaponScale;
	DrawExtendGraph(drawX, drawY, plusPosx, plusPosy, _weaponHandle, TRUE);
#ifdef _DEBUG
	// “–‚½‚è”»’è‚ð•\Ž¦
	_weaponCollision.Draw(0x00ff00, false);
#endif


}
void Weapons::SetInfo(const Vector2& playerPos, bool isRight) {

}
Vector2 Weapons::GetPos() {
	return _weaponPosition;
}
