#pragma once
#include "DxLib.h"
#include "Vector2.h"
enum class ButtonJob {
	LoadGameScene,
	GameExit,
	ReturnTitle,
};

class Button
{
public:
	Button(ButtonJob job, int buttonImageHandle, int selectButtonHandle, CHAR* message, Vector2 pos);
	~Button();
	/// <summary>
	/// ボタンをクリックしたかどうかを返す
	/// </summary>
	/// <param name="mousePos">マウスの画面座標</param>
	/// <returns>クリックしたかどうか</returns>
	bool IsTouch(Vector2 mousePos);
	/// <summary>
	/// ボタンを描画する
	/// </summary>
	void DrawButton() const;
	/// <summary>
	/// コントローラーの選択判定
	/// </summary>
	void ControllTap();
	/// <summary>
	/// ボタンの色を切り替える
	/// </summary>
	/// <param name="isSelecting">ボタンが選択されてるか否か</param>
	void SwitchButtonColor(bool isSelecting);
	/// <summary>
	/// ボタンの状態をリセットする。これが走らないとボタンがおしっぱになる
	/// </summary>
	void Reset();
private:
	ButtonJob _job;
	int _buttonHandle;
	int _selectButtonHandle;
	int _useButtonHandle;
	CHAR* _message;
	Vector2 _startPos;
	Vector2 _endPos;
	int _xScale = 500;
	int _yScale = 100;
	int _fontHandle;
	Vector2 _textPos;
	bool _isControllSelecting = false;
	enum ButtonState {
		None,
		Selected,
	};

	ButtonState _curState = ButtonState::None;
};

