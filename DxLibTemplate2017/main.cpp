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
char keyState[256];
int counter = 0, FpsTime[2] = { 0, }, FpsTime_i = 0;
int color_white;
double Fps = 0.0;
typedef enum {
    eScene_Menu,    //メニュー画面
    eScene_Game,    //ゲーム画面
    eScene_Clear,
} eScene;

static int Scene = eScene_Menu;    //現在の画面(シーン)

//シーンを更新する
void UpdateScene() {
    // 常に操作説明を表示

    if (CheckHitKey(KEY_INPUT_G) != 0) {
        Scene = eScene_Game;
    }
    if (CheckHitKey(KEY_INPUT_M) != 0) {
        Scene = eScene_Menu;
    }
    if (CheckHitKey(KEY_INPUT_T) != 0) {
        Scene = eScene_Clear;
    }
}

//メニュー画面
void Menu() {
    DrawString(960, 540, "メニュー画面です。", GetColor(255, 255, 255));
    DrawGraph(0, 0, _menuHandle, TRUE);
}

//ゲーム画面のUIなどがあればここ（今回はStage側で描画しているので空でも可）
void Game() {
    DrawString(960, 540, "ゲーム画面です。", GetColor(255, 255, 255));
}

void Clear() {
    DrawString(960, 540, "クリア画面です。", GetColor(255, 255, 255));
}

void SetColor() {
    color_white = GetColor(255, 255, 255);            //白色ハンドルを取得
    return;
}
void FpsTimeFanction() {
    if (FpsTime_i == 0)
        FpsTime[0] = GetNowCount();               //1周目の時間取得
    if (FpsTime_i == 49) {
        FpsTime[1] = GetNowCount();               //50周目の時間取得
        Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
        FpsTime_i = 0;//カウントを初期化
    }
    else
        FpsTime_i++;//現在何周目かカウント
    if (Fps != 0)
        DrawFormatString(0, 0, color_white, "FPS %.1f", Fps); //fpsを表示
    return;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int RefreshTime = 0;
    SetOutApplicationLogValidFlag(FALSE);

    // 【修正】FALSEは全画面です。非全画面（ウィンドウ）なら TRUE にします
    ChangeWindowMode(TRUE);

    SetGraphMode(1920, 1080, 32);
    SetBackgroundColor(0, 0, 0, 1);

    // 【修正】DxLib_Initのエラーは -1 が返ってきます
    if (DxLib_Init() == -1) { return -1; }
    SetWaitVSyncFlag(TRUE);

    // 【修正】裏画面設定はループの前に1回だけ行う
    SetDrawScreen(DX_SCREEN_BACK);

 

    _menuHandle = LoadGraph("Image/Title.jpg");
    Player _player(320, 600);
    Jump _jump;
    Stage _stage(&_player);
    _player.SetJumpAddres(&_jump);

    bool _isRight = true;
    float _moveValue = 5;

    int frameStartTime;

    while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        RefreshTime = GetNowCount();
        GetHitKeyStateAll(keyState);
        Pad::Update();
        frameStartTime = GetNowCount();

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
            _stage.Draw();

            // ステージ（と敵・プレイヤー）の更新と描画
            if (_stage.Update()) {
                Scene = eScene_Clear;
            }

            break; // eScene_Game の処理終わり

        case eScene_Clear:
            Clear();
            break;
        }
        DrawString(0, 20, "Gキーでゲーム画面、Mキーでメニュー画面,Tキーでクリア画面", GetColor(255, 255, 255));


        int frameProcessTime = GetNowCount() - frameStartTime; // 処理にかかった時間
        int waitTime = 16 - frameProcessTime;                  // 16ミリ秒(60FPS)まで何ミリ秒余っているか
        if (waitTime > 0) {
            WaitTimer(waitTime); // 余っている時間はなんもしない
        }
        FpsTimeFanction();

        // ループの最後に1回だけ裏画面を表に反映する
        ScreenFlip();

    }

    // ループを抜けたら（×ボタン等で終了したら）ライブラリを終了する
    DxLib_End();
    return 0;
}