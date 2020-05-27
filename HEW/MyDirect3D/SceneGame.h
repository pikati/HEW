#pragma once
//���󃂃f���̏������ɑ����̎��Ԃ������邽�߃��U���g���Q�[���V�[���ɂ܂Ƃ߂ēǂݍ��݂�1��ōς܂���
#include "BaseScene.h"
#include "WakkaManager.h"
#include "XManager.h"
#include "PlayerManager.h"
#include "StageManager.h"
#include "Obst.h"
#include "Cameran.h"
#include "ItemManager.h"
#include "ObstacleManager.h"
#include "EmitterManager.h"
#include "Time.h"
#include "StartCount.h"
#include "Score.h"
#include "WinLose.h"
#include "DispResult.h"
#include "Sky.h"

#define WAKKA 2
#define PLAYER 2
#define FIRST_STAGE 30

class SceneGame : public BaseScene
{
private:
	PlayerManager* m_playerManager;
	WakkaManager* m_wakkaManager;
	ObstacleManager* m_obstacleManager;
	StageManager* m_stageManager;
	Cameran* m_camera;
	ItemManager* m_itemManager;
	EmitterManager* m_emitter;
	Time* m_time;
	StartCount* m_startCount;
	Score*		m_score;
	WinLose*	m_winLose;
	//0�ɏ����̏��A1�ɕ����̏��
	DispResult* m_disp;
	LPDIRECT3DDEVICE9 m_d3dDevice;
	Sky* m_sky;

	bool m_changeScene;
	bool m_goal1;
	bool m_goal2;
	bool m_resultInit;
	bool m_fever1;
	bool m_fever2;
	int	 m_feverIdx1;
	int	 m_feverIdx2;
	int  m_win;

	void PlayerInitialize();
	void PlayerUpdate();
	void PlayerDraw(int j);
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

	void EmitterInitialize();
	void EmitterUpdate();
	void EmitterDraw(int playerIdx);
	void EmitterFinalize();

	void ScoreInitialize();
	void ScoreDraw(int idx);
	void ScoreFinalize();

	void ResultInitialize();
	void ResultUpdate();
	void ResultDraw();
	void ResultFinalize();

	void SkyInitialize();
	void SkyUpdate();
	void SkyDraw();
	void SkyFinalize();

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

	bool IsObstacleDestroy(OBST_TYPE type, ELEM elem);

	void InitializeFog();

	template <class T>
	D3DXMATRIX* GetMatrix(T& info, D3DXMATRIX& mat);
public:
	~SceneGame();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

