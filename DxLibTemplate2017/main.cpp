#include <DxLib.h>
#include <stdio.h>
#include "Player.h"
#include "Jump.h"
#include "Obstacle.h"
#include "Stage.h"

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
	float _moveValue = 5;

	Player _player;
	Jump _jump;
	Obstacle _obstacle;
	Stage _stage(&_player);
	_player.SetStagePointer(&_stage);
	while (ProcessMessage() == 0)
	{
		GetHitKeyStateAll(keyState);

		if (keyState[KEY_INPUT_RIGHT]) 
		{
			_player.Move(_moveValue);
			//_currentX += 2;
		}
		else if (keyState[KEY_INPUT_LEFT])
		{
			_player.Move(-_moveValue);
			//_currentX -= 2;
		}

		if (keyState[KEY_INPUT_SPACE] && !_isJumping)
		{
			_jump.JumpProtocol(_player);
			_isJumping = true;
		}
		
		if (_player.GetPos().y < _minY) 
		{
			_player.Gravity();
		}
		else {
			_isJumping = false;
		}
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
		ClearDrawScreen();//裏画面消す
		_stage.Update();
		_player.DrawPlayer();
		_obstacle.DrawObstacle();
		_player.Update();
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}

