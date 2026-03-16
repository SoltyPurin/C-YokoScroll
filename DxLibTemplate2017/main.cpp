#include <DxLib.h>
#include <stdio.h>
#include "Player.h"
#include "Enemy.h"
#include "Jump.h"
#include "Obstacle.h"
#include "Stage.h"
#include "Pad.h"
#include "ThrowAxe.h"

int _menuHandle;
typedef enum {
    eScene_Menu,    //メニュー画面
    eScene_Game,    //ゲーム画面
    eScene_Clear,
} eScene;

static int Scene = eScene_Menu;    //現在の画面(シーン)

//シーンを更新する
void UpdateScene() {
    // 常に操作説明を表示
    DrawString(0, 20, "Gキーでゲーム、Mキーでメニュー", GetColor(255, 255, 255));

    if (CheckHitKey(KEY_INPUT_G) != 0) {
        Scene = eScene_Game;
    }
    if (CheckHitKey(KEY_INPUT_M) != 0) {
        Scene = eScene_Menu;
    }
}

//メニュー画面
void Menu() {
    DrawGraph(0, 0, _menuHandle, TRUE);
    DrawString(960, 540, "メニュー画面です。", GetColor(255, 255, 255));
}

//ゲーム画面のUIなどがあればここ（今回はStage側で描画しているので空でも可）
void Game() {
    DrawString(960, 540, "ゲーム画面です。", GetColor(255, 255, 255));
}

void Clear() {
    DrawString(960, 540, "クリア画面です。", GetColor(255, 255, 255));
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetOutApplicationLogValidFlag(FALSE);

    // 【修正】FALSEは全画面です。非全画面（ウィンドウ）なら TRUE にします
    ChangeWindowMode(TRUE);

    SetGraphMode(1920, 1080, 32);
    SetBackgroundColor(0, 0, 0, 1);

    // 【修正】DxLib_Initのエラーは -1 が返ってきます
    if (DxLib_Init() == -1) { return -1; }

    // 【修正】裏画面設定はループの前に1回だけ行う
    SetDrawScreen(DX_SCREEN_BACK);

    char keyState[256];

    _menuHandle = LoadGraph("Image/Title.jpg");
    Player _player(320, 600);
    Jump _jump;
    Stage _stage(&_player);
    _player.SetJumpAddres(&_jump);

    bool _isRight = true;
    float _moveValue = 5;

    while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        GetHitKeyStateAll(keyState);
        Pad::Update();

        UpdateScene();

        switch (Scene) {
        case eScene_Menu:
            Menu();
            break;

        case eScene_Game:
            Game();

            // プレイヤーの移動処理
            if (Pad::IsPress(PAD_INPUT_RIGHT) || keyState[KEY_INPUT_RIGHT]) {
                _isRight = true;
                _player.Move(_moveValue, _isRight);
            }
            else if (Pad::IsPress(PAD_INPUT_LEFT) || keyState[KEY_INPUT_LEFT]) {
                _isRight = false;
                _player.Move(-_moveValue, _isRight);
            }
            else {
                _player.Move(0, _isRight);
            }

            // プレイヤーのジャンプ・攻撃処理
            if (Pad::IsPress(PAD_INPUT_1) || keyState[KEY_INPUT_SPACE]) {
                _player.JumpProtocol();
            }
            if (Pad::IsTrigger(PAD_INPUT_2)) {
                _player.ChangeWeapon();
            }

            // ステージ（と敵・プレイヤー）の更新と描画
            _stage.Update();

            break; // eScene_Game の処理終わり
        }

        // 【修正】ループの最後に1回だけ裏画面を表に反映する
        ScreenFlip();
    }

    // 【修正】ループを抜けたら（×ボタン等で終了したら）ライブラリを終了する
    DxLib_End();
    return 0;
}