#include "Precompile.h"
#include "Player.h"
#include "SkatePlayer.h"
#include "Enemy.h"
#include "Jump.h"
#include "Obstacle.h"
#include "Stage.h"
#include "ThrowAxe.h"
#include "SoundPlayer.h"
#include "Button.h"
#include "OutGameInputManager.h"

int _menuHandle;
int _clearHandle;
int counter = 0, FpsTime[2] = { 0, }, FpsTime_i = 0;
int color_white;
double Fps = 0.0;
typedef enum {
    eScene_Title,    //メニュー画面
    eScene_Game,    //ゲーム画面
    eScene_Clear,
} eScene;


static int Scene = eScene_Title;    //現在の画面(シーン)

//シーンを更新する
void UpdateScene(SoundPlayer& sound) {
    // 常に操作説明を表示

    if (CheckHitKey(KEY_INPUT_G) != 0) {
        sound.PlayGameBGM(1);
        Scene = eScene_Game;
    }
    if (CheckHitKey(KEY_INPUT_M) != 0) {
        sound.PlayGameBGM(0);
        Scene = eScene_Title;
    }
    if (CheckHitKey(KEY_INPUT_T) != 0) {
        sound.PlayGameBGM(2);
        Scene = eScene_Clear;
    }
}

//メニュー画面
void Menu(Button* loadGameButton,Button* gameExitButton,Vector2 mousePos,SoundPlayer& sound) {
    DrawGraph(0, 0, _menuHandle, TRUE);
    loadGameButton->DrawButton();
    gameExitButton->DrawButton();
    if (loadGameButton->IsTouch(mousePos)) {
        Scene = eScene_Game;
        loadGameButton->Reset();
        sound.PlayGameBGM(1);
    }
    if (gameExitButton->IsTouch(mousePos)) {
        DxLib_End();
    }
}

//ゲーム画面のUIなどがあればここ（今回はStage側で描画しているので空でも可）
void Game() {
    DrawString(960, 540, "ゲーム画面です。", GetColor(255, 255, 255));
}

void Clear(Button* returnTitleButton,Button* gameExitButton,Vector2 mousePos,SoundPlayer& sound) {
    DrawGraph(0, 0, _clearHandle, TRUE);
    returnTitleButton->DrawButton();
    gameExitButton->DrawButton();
    if (returnTitleButton->IsTouch(mousePos)) {
        Scene = eScene_Title;
        returnTitleButton->Reset();
        sound.PlayGameBGM(0);
    }
    if (gameExitButton->IsTouch(mousePos)) {
        DxLib_End();
    }
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
    SetOutApplicationLogValidFlag(TRUE);

    // 【修正】FALSEは全画面です。非全画面（ウィンドウ）なら TRUE にします
    ChangeWindowMode(TRUE);

    SetGraphMode(1920, 1080, 32);
    SetBackgroundColor(0, 0, 0, 1);

    // 【修正】DxLib_Initのエラーは -1 が返ってきます
    if (DxLib_Init() == -1) { return -1; }
    SetWaitVSyncFlag(TRUE);

    // 【修正】裏画面設定はループの前に1回だけ行う
    SetDrawScreen(DX_SCREEN_BACK);

    ShareClass share;
    share.GetImages();

    int x, y;
    int _buttonHandle = LoadGraph("Image/Button.png");
    int _seletButtonHandle = LoadGraph("Image/ButtonSelect.png");
 
    Vector2 _gameStartButtonPos = Vector2(500, 300);
    Vector2 _gameExitButtonPos = Vector2(500, 600);
    Vector2 _returnTitleButtonPos = Vector2(500, 400);

    Button _gameStartButton(ButtonJob::LoadGameScene, _buttonHandle,_seletButtonHandle, "ゲームスタート", _gameStartButtonPos);
    Button _gameExitButton(ButtonJob::GameExit, _buttonHandle, _seletButtonHandle, "　ゲーム終了", _gameExitButtonPos);
    Button _returnTitleButton(ButtonJob::ReturnTitle, _buttonHandle, _seletButtonHandle, "タイトルに戻る", _returnTitleButtonPos);

    share.SetButtons(&_gameStartButton, &_gameExitButton, &_returnTitleButton);
    _menuHandle = LoadGraph("Image/Title.jpg");
    _clearHandle = LoadGraph("Image/Clear.png");

    OutGameInputManager _outGame(share._buttons);

    SoundPlayer _soundPlay;
    Stage _stage(&_soundPlay);


    int frameStartTime;

    _soundPlay.PlayGameBGM(0);


    while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        RefreshTime = GetNowCount();
        frameStartTime = GetNowCount();
        GetMousePoint(&x, &y);
        UpdateScene(_soundPlay);

        switch (Scene) {
        case eScene_Title:
            Menu(&_gameStartButton,&_gameExitButton,Vector2((float)x,(float)y),_soundPlay);
            _outGame.TitleInput();
            break;

        case eScene_Game:
            Game();

            _stage.Draw();
            // ステージの更新と描画
            if (_stage.Update()) {
                Scene = eScene_Clear;
                _soundPlay.PlayGameBGM(2);
            }

            break; // eScene_Game の処理終わり

        case eScene_Clear:
            Clear(&_returnTitleButton,&_gameExitButton,Vector2((float)x, (float)y),_soundPlay);
            _outGame.ResultInput();
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
    DeleteGraph(_menuHandle);
    DeleteGraph(_clearHandle);
    DeleteGraph(_buttonHandle);
    share.ReleaseImages();
    // ループを抜けたら（×ボタン等で終了したら）ライブラリを終了する
    DxLib_End();
    return 0;
}