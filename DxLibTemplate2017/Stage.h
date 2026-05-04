#pragma once
#include <vector>
#include <memory>
#include "Vector2.h"
#include "Rect.h"
class Player;
class Jump;
class Enemy;
class AxeEnemy;
class Axe;
class ThrowKnife;
class VerticalMoveFloor;
class Spring;
class Goal;
class Skate;
class SoundPlayer;
class PlayerInputManager;
class Stone;
class Stage
{
public:
	Stage(SoundPlayer* sound);
	~Stage();
	void LoadMap();
	bool Update();
	void Draw();
	void DrawBackGround();
	void DrawMapChip();
	/// <summary>
	/// 描画範囲内のプレイヤーの現在のX座標を返す
	/// </summary>
	/// <returns>プレイヤーのX座標</returns>
	int GetScrollX();
	/// <summary>
    /// 描画範囲内のプレイヤーの現在のY座標を返す
	/// </summary>
	/// <returns>プレイヤーのY座標</returns>
	int GetScrollY();
	/// <summary>
	/// 渡された当たり判定の持ち主がマップチップと接触したかどうかを返す
	/// </summary>
	/// <param name="rect">接触を判定したいものの当たり判定</param>
	/// <param name="chipRect">マップチップの当たり判定</param>
	/// <returns></returns>
	bool IsCollision(Rect rect, Rect& chipRect);
	void DrawAxe();
	void UpdateAxe();
	void DeleteAxe(int index);
	void DrawEnemyAxe();
	void UpdateEnemyAxe();
	void DeleteEnemyAxe(int index);
	void DrawKnife();
	void UpdateKnife();
	void DeleteKnife(int index);
	void DetectPlayerToEnemyCollision();
	void DetectPlayerToObstacleCollision();
	bool DetectPlayerToSkateCollision();
	bool DetectPlayerToGoalCollision();
	/// <summary>
	/// 全てをリセットする
	/// </summary>
	void ResetGame();
	void PlayerFallCheck();
	/// <summary>
	/// プレイヤーが現在選択している武器を表示する
	/// </summary>
	void DrawCurrentWeapon();
	void SpawnEnemy(int enIndex, float x, float y);
	void SetMoveFloor(float x, float y);
	void SetSpring(float x, float y);
	void SetSkate(float x, float y);
	void SetFellStone(float x, float y);
	/// <summary>
	/// プレイヤーの状態を切り替える
	/// </summary>
	/// <param name="isSkatePlayer">スケボー状態にするかどうか</param>
	/// <param name="pos">状態を変える時の座標</param>
	void SwitchPlayerState(bool isSkatePlayer,Vector2 pos);
	static constexpr float MAP_WIDTH = 30000.0f;	 // マップ全体の幅
	static constexpr float MAP_HEIGHT = 2080.0f;	 // マップ全体の高さ
	static constexpr float SCREEN_WIDTH = 1920.0f;	 // スクリーンの幅
	static constexpr float SCREEN_HEIGHT = 1080.0f; // スクリーンの高さ
	static constexpr float CHIP_SIZE = 64;


	static constexpr float kChipScale = 1.5f; 	// マップチップ拡大率

	// チップを置く数
	static constexpr int CHIP_NUM_X = MAP_WIDTH / CHIP_SIZE;
	static constexpr int CHIP_NUM_Y = MAP_HEIGHT / CHIP_SIZE;

private:
	const int WEAPON_MAX = 2;

	// マップチップの配列情報
	int CHIP_DATA[CHIP_NUM_Y][CHIP_NUM_X];

	int _bgWidth = static_cast<int>(SCREEN_WIDTH) - 1;
	int _bgHeight = static_cast<int>(SCREEN_HEIGHT) - 1;

	int _backGroundHandler = 0;

	Vector2 pos;
	Vector2 size;
	Vector2 _playerInitPos = Vector2(320, 600);
	Player* _player;
	Jump* _jump;
	SoundPlayer* _soundPlayer;
	PlayerInputManager* _inputManager;
	std::vector<std::unique_ptr<Enemy>> _enemys;
	std::vector<std::unique_ptr<VerticalMoveFloor>> _moveFloors;
	std::vector<std::unique_ptr <Spring>> _springs;
	std::vector<std::unique_ptr<Skate>> _skates;
	std::vector<std::unique_ptr<Stone>> _stones;
	std::unique_ptr<Goal> _goal;
	std::unique_ptr<Axe> _axe[3];
	std::unique_ptr<Axe> _enemyAxe[16];
	std::unique_ptr<ThrowKnife> _knife[3];
	float _groundY = 900;
	int _mapData;
	int _mapChipHandle;
	int _graphChipNumX;
	int _graphChipNumY;
	int _axeHandle;
	int _knifeHandle;
	int _skateHandle;
	int _colChipIndex;
	int _rideSkateIndex;
	int _brakeSkateIndex;
	int _stoneHandle;
	bool _isResetting = false;
	bool _isSkateing = false;
};
