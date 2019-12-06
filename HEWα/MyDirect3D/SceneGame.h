#pragma once
#include "BaseScene.h"
#include "Wakka.h"
#include "XManager.h"
#include "Player.h"
#include "Stage.h"
#include "Obst.h"
#include "Goal.h"

#define WAKKA 5
#define PLAYER 2
#define STAGE 37
static const int OBSTACLE_NUM = 100;
static const int CREATED_OBSTACLE_NUM = 20;

struct CreatedObst{
	Obst*	createdObst[20];
	int		sandStormCounter;
	int		pitFallCounter;
};

class SceneGame : public BaseScene
{
private:
	Player *m_player;
	Wakka **m_wakka;
	Stage *m_stage;
	Stage *m_stageWall;
	Stage *m_stageCurve;
	LPDIRECT3DDEVICE9 m_d3dDevice;
	XManager *xmanager;
	/*プレイヤー1用の障害物の配列*/
	Obst*	m_pObstacle1[OBSTACLE_NUM];
	/*プレイヤー2用の障害物の配列*/
	Obst*	m_pObstacle2[OBSTACLE_NUM];
	/*プレイヤー1用の新しく生成する障害物用の配列*/
	CreatedObst m_1;
	/*プレイヤー2用の新しく生成する障害物用の配列*/
	CreatedObst m_2;
	Goal*	m_goal;

	D3DXVECTOR3 m_stageInfo[STAGE][3];
	D3DXVECTOR3 m_stageWallInfo[STAGE * 2][3];
	D3DXVECTOR3 m_stageCurveInfo[STAGE][3];



	void PlayerInitialize(int j);
	void PlayerUpdate(int j);
	void PlayerDraw(int j);
	void PlayerFinalize(int j);
	void PlayerInitialize();
	void PlayerFinalize();
	void WakkaInitialize();
	void WakkaFinalize();
	void StageInitialize();
	void StageUpdate();
	void StageDraw(D3DXVECTOR3 pos);
	void StageFinalize();
	void ObstacleInitialize();
	void ObstacleUpdate();
	void ObstacleDraw(int n);
	void ObstacleFinalize();
	void Rendering(int a);

	void CollisionUpdate();
	void ColP2O();
	void ColW2O();
	//プレイヤーとステージ
	void ColP2S();
	void CreatePitfalls(D3DXVECTOR3 pos, int n);
	void CreateSandStorm(D3DXVECTOR3 pos, int n);
public:
	~SceneGame();
	//左上のx座標、左上のy座標、横幅、縦幅、テクスチャ（背景）の左上x座標、テクスチャの左上y座標、テクスチャの横幅、テクスチャの縦幅、テクスチャ
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

