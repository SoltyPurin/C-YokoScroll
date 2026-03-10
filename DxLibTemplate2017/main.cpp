#include <DxLib.h>
#include <stdio.h>
#include "Player.h"
#include "Enemy.h"
#include "Jump.h"
#include "Obstacle.h"
#include "Stage.h"
#include "Pad.h"
#include "ThrowAxe.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(1920, 1080, 32);//画面サイズ指定
	SetBackgroundColor(0, 0, 0, 1);
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了

	char keyState[256];								// キー情報格納用変数
	GetHitKeyStateAll(keyState);					// キー入力情報取得
	float _minY = 900;
	bool _isJumping = false;
	bool _isRight = true;
	float _moveValue = 5;

	Player _player;
	Jump _jump;
	Stage _stage(&_player);
	_player.SetStagePointer(&_stage);
	while (ProcessMessage() == 0)
	{
		GetHitKeyStateAll(keyState);
		Pad::Update();
		if (Pad::IsPress(PAD_INPUT_RIGHT) || keyState[KEY_INPUT_RIGHT])
		{
			_isRight = true;
			_player.Move(_moveValue,_isRight);
			//_currentX += 2;
		}
		else if (Pad::IsPress(PAD_INPUT_LEFT) || keyState[KEY_INPUT_LEFT])
		{
			_isRight = false;
			_player.Move(-_moveValue,_isRight);
			//_currentX -= 2;
		}
		else {
			_player.Move(0,_isRight);
		}
		if (Pad::IsPress(PAD_INPUT_1) || keyState[KEY_INPUT_SPACE])
		{
			_player.JumpProtocol(_jump);
			_isJumping = true;
		}

		if (Pad::IsTrigger(PAD_INPUT_3)) {
			//武器の切り替え
			_player.ChangeWeapon();
		}
		
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
		ClearDrawScreen();//裏画面消す
		_stage.Update();
		_player.Update();
		//_obstacle.Update();
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}

