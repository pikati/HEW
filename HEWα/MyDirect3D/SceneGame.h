#pragma once
#include "BaseScene.h"
#include "WakkaManager.h"
#include "XManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Obst.h"
#include "Goal.h"
#include "Cameran.h"
#include "ItemManager.h"
#include "ObstacleManager.h"

#define WAKKA 2
#define PLAYER 2
#define STAGE 10//37

class SceneGame : public BaseScene
{
private:
	Player* m_player;
	WakkaManager* m_wakka;
	ObstacleManager* m_obstacleManager;
	StageManager* m_stageManager;
	Cameran* m_camera;
	ItemManager* m_itemManager;
	LPDIRECT3DDEVICE9 m_d3dDevice;
	Goal*	m_goal;

	void PlayerInitialize(int j);
	void PlayerUpdate(int j);
	void PlayerDraw(int j);
	void PlayerFinalize(int j);
	void PlayerInitialize();
	void PlayerFinalize();

	void WakkaInitialize();
	void WakkaUpdate();
	void WakkaFinalize();

	void StageInitialize();
	void StageUpdate();
	void StageDraw(D3DXVECTOR3 pos);
	void StageFinalize();

	void ObstacleInitialize();
	void ObstacleUpdate();
	void ObstacleDraw(int playerIdx);
	void ObstacleFinalize();

	void CameraInitialize();
	void CameraUpdate(int player);
	void CameraFinalize();

	void ItemInitialize();
	void ItemUpdate();
	void ItemDraw(int playerIdx);
	void ItemFinalize();

	void Rendering(int a);

	void CollisionUpdate();
	//!プレイヤーと障害物
	void ColP2O();
	//!わっかと障害物
	void ColW2O();
	//!プレイヤーとアイテム
	void ColP2I();
	//!プレイヤーとステージ
	void ColP2S();

	template <class T>
	D3DXMATRIX* GetMatrix(T& info, D3DXMATRIX& mat);
public:
	~SceneGame();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

