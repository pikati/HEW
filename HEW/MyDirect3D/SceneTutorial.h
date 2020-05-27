#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "WakkaManager.h"
#include "XManager.h"
#include "Player.h"
#include "Stage.h"
#include "Obst.h"
#include "Cameran.h"
#include "TextBack.h"
#include "Text.h"
#include "Obst.h"
#include "SceneGame.h"

#define TEXT 17

#define TCAMERA_X -10.0f
#define TCAMERA_Y 1.5f
#define TCAMERA_Z 3.0f

struct CreateObst {
	Obst*	createdObst[20];
	int		sandStormCounter;
	int		pitFallCounter;
};


class SceneTutorial : public BaseScene
{
private:
	Player *m_player;
	WakkaManager *m_wakka;
	Stage *m_stage;
	Stage *m_stageWall;
	Cameran *m_camera;
	TextBack *m_textback;
	Text *m_text;
	Text *m_next;

	SceneManager *smanager;
	LPDIRECT3DDEVICE9 m_d3dDevice;
	XManager *xmanager;

	/*プレイヤー1用の障害物の配列*/
	Obst*	m_pObstacle1[OBSTACLE_NUM];
	/*プレイヤー2用の障害物の配列*/
	Obst*	m_pObstacle2[OBSTACLE_NUM];
	/*プレイヤー1用の新しく生成する障害物用の配列*/
	CreateObst m_1;
	/*プレイヤー2用の新しく生成する障害物用の配列*/
	CreateObst m_2;

	D3DXVECTOR3 m_stageInfo[STAGE][3];
	D3DXVECTOR3 m_stageWallInfo[STAGE * 2][3];
	D3DXVECTOR3 tCameraPos;
	bool clear1 = false;
	bool clear2 = false;
	bool once = false;
	
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
	//void StageUpdate();
	void StageDraw(D3DXVECTOR3 pos);
	void StageFinalize();
	void ObstacleInitialize();
	void ObstacleUpdate();
	void ObstacleDraw(int n);
	void ObstacleFinalize();
	void CreatePitfalls(D3DXVECTOR3 pos, int n);
	void CreateSandStorm(D3DXVECTOR3 pos, int n);
	void CameraInitialize();
	void CameraUpdate(int player);
	void CameraFinalize();
	void TextInitialize();
	void TextInitialize(int j);
	void TextUpdate();
	void TextDraw();
	void TextFinalize(int j);
	void TextFinalize();
	void Rendering(int a);
	void SceneManagerInitialize();
	void SceneManagerFinalize();
	void ClearFlag();
	void ClearInit();
	void CollisionUpdate();
	void ColP2O();
	void ColW2O();
	void ColP2S();

public:
	~SceneTutorial();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};