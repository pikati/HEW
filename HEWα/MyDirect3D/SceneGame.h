#pragma once
#include "BaseScene.h"
#include "WakkaManager.h"
#include "XManager.h"
#include "Player.h"
#include "Stage.h"
#include "Obst.h"
#include "Goal.h"
#include "Cameran.h"
#include "ItemManager.h"

#define WAKKA 2
#define PLAYER 2
#define STAGE 10//37
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
	WakkaManager *m_wakka;
	Stage *m_stage;
	Stage *m_stageWall;
	Stage *m_stageCurve;
	Cameran *m_camera;
	ItemManager *m_itemManager;
	LPDIRECT3DDEVICE9 m_d3dDevice;
	/*�v���C���[1�p�̏�Q���̔z��*/
	Obst*	m_pObstacle1[OBSTACLE_NUM];
	/*�v���C���[2�p�̏�Q���̔z��*/
	Obst*	m_pObstacle2[OBSTACLE_NUM];
	/*�v���C���[1�p�̐V�������������Q���p�̔z��*/
	CreatedObst m_1;
	/*�v���C���[2�p�̐V�������������Q���p�̔z��*/
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
	void WakkaUpdate();
	void WakkaFinalize();

	void StageInitialize();
	void StageUpdate();
	void StageDraw(D3DXVECTOR3 pos);
	void StageFinalize();

	void ObstacleInitialize();
	void ObstacleUpdate();
	void ObstacleDraw(int n);
	void ObstacleFinalize();

	void CameraInitialize();
	void CameraUpdate(int player);
	void CameraFinalize();

	void ItemInitialize();
	void ItemUpdate();
	void ItemDraw(int playerNum);
	void ItemFinalize();

	void Rendering(int a);

	void CollisionUpdate();
	//!�v���C���[�Ə�Q��
	void ColP2O();
	//!������Ə�Q��
	void ColW2O();
	//!�v���C���[�ƃA�C�e��
	void ColP2I();
	//!�v���C���[�ƃX�e�[�W
	void ColP2S();
	void CreatePitfalls(D3DXVECTOR3 pos, int n);
	void CreateSandStorm(D3DXVECTOR3 pos, int n);
public:
	~SceneGame();
	//�����x���W�A�����y���W�A�����A�c���A�e�N�X�`���i�w�i�j�̍���x���W�A�e�N�X�`���̍���y���W�A�e�N�X�`���̉����A�e�N�X�`���̏c���A�e�N�X�`��
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

