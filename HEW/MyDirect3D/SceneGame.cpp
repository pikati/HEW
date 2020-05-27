/*wakka振りとわっかto障害物、プレイやto壁の音完了*/

#define _CRT_SECURE_NO_WARNINGS
#include "SceneGame.h"
#include "Input.h"
#include "Joycon.h"

#include "Wakka.h"
#include "camera.h"
#include "Stage.h"
#include "main.h"
#include "Collision.h"
#include "Utility.h"
#include "DriftWood.h"
#include "SandStorm.h"

#include "Fire.h"
#include "Tree.h"
#include "PitFall.h"
#include "Cameran.h"
#include "ItemManager.h"
#include "PlayerManager.h"
#include "Fade.h"
#include "SceneManager.h"
#include "Sound.h"
#include "Judge.h"

static int count = 0;
static bool a = false;
static int count2 = 0;
static bool b = false;
static bool isStart = false;

SceneGame::~SceneGame() {
}

void SceneGame::Initialize() {
	PlaySound(SOUND_BGM_GAME);

	Fade::FadeOut();
	PlayerInitialize();
	WakkaInitialize();
	PlayerInitialize();
	StageInitialize();
	EmitterInitialize();
	ObstacleInitialize();
	CameraInitialize();
	ItemInitialize();
	m_time = new Time;
	m_time->Initialize();
	m_startCount = new StartCount;
	m_startCount->Initialize();
	ScoreInitialize();
	m_winLose = new WinLose;
	m_winLose->Initialize();
	m_disp = new DispResult[2];
	m_d3dDevice = GetDevice();
	m_changeScene = false;
	m_goal1 = false;
	m_goal2 = false;
	m_fever1 = false;
	m_fever2 = false;
	m_feverIdx1 = -1;
	m_feverIdx2 = -1;
	m_resultInit = false;
	m_win = 0;
	SkyInitialize();
	//InitializeFog();
}

void SceneGame::Update() {
	if (!Fade::IsFadeOut())
	{
		if (!m_changeScene)
		{
			if (!m_goal1 || !m_goal2)
			{
				if (m_startCount->IsStart())
				{
					if (!isStart)
					{
						PlaySound(SOUND_SE_START);
						isStart = true;
					}
					PlayerUpdate();
					WakkaUpdate();
					ObstacleUpdate();
					CollisionUpdate();
					ItemUpdate();
					EmitterUpdate();
					m_time->Update();
				}
				m_startCount->Update();
			}
			else
			{
				if (!m_resultInit)
				{
					StopSound(SOUND_BGM_GAME);
					ResultInitialize();
					m_resultInit = true;
				}
				ResultUpdate();
			}
		}
	}
	if (m_changeScene)
	{
		if (!Fade::IsFadeIn())
		{
			SceneManager::ChangeSceneState();
		}
	}
	SkyUpdate();
}

void SceneGame::Draw() {
	
	if (!m_goal1)
	{
		Rendering(0);
		SkyDraw();
		ObstacleDraw(0);
		ItemDraw(0);
		PlayerDraw(0);
		EmitterDraw(0);
		ScoreDraw(0);
	}
	
	if (!m_goal2)
	{
		Rendering(1);
		SkyDraw();
		ObstacleDraw(1);
		ItemDraw(1);
		PlayerDraw(1);
		EmitterDraw(1);
		ScoreDraw(1);
	}
	
	if (!m_goal1 || !m_goal2)
	{
		m_time->Draw();

		m_startCount->Draw();
	}
	else
	{
		ResultDraw();
	}

	Fade::Fading();
}

void SceneGame::Finalize() {
	//SkyFinalize();
	ResultFinalize();
	ScoreFinalize();
	m_startCount->Finalize();
	delete m_startCount;
	m_time->Finalize();
	delete m_time;
	ItemFinalize();
	CameraFinalize();
	ObstacleFinalize();
	EmitterFinalize();
	StageFinalize();
	WakkaFinalize();
	PlayerFinalize();
}

void SceneGame::PlayerInitialize() {
	m_playerManager = new PlayerManager;
	m_playerManager->Initialize();
}

void SceneGame::PlayerUpdate() {
	m_playerManager->Update(m_goal1, m_goal2);
	if (a) {
		count++;
		if (count > 7) {
			a = false;
			count = 0;
		}
	}
	if (b) {
		count2++;
		if (count2 > 7) {
			b = false;
			count2 = 0;
		}
	}
	//Player1の処理
	//左に振った時
	if (!m_goal1)
	{
		if (Input::TriggerKey(DIK_Q) || g_diJoyState2[1] & BUTTON_M) {
			if (!a) {
				PlaySound(SOUND_SE_WCHANGE);
				m_wakkaManager[0].Change(1);
				a = true;
			}
		}
		//右に振ったとき
		if (Input::TriggerKey(DIK_E) || g_diJoyState2[1] & BUTTON_R) {
			if (!a)
			{
				PlaySound(SOUND_SE_WCHANGE);
				m_wakkaManager[0].Change(0);
				a = true;
			}
		}
		//縦に振った時
		if (Input::TriggerKey(DIK_W) || g_diJoyState2[1] & BUTTON_START) {
			PlaySound(SOUND_SE_SHOOT);
			m_wakkaManager[0].Shoot();
		}
		if (Input::TriggerKey(DIK_5))
		{
			m_score[0].AddScore((200 - m_time->GetTime()) * 20);
			m_goal1 = true;
		}

		

		if (m_wakkaManager[0].GetIsFever())
		{
			if (!m_fever1)
			{
				m_feverIdx1 = m_emitter[0].CreateEmitter(PARTICLE_FEVER, m_playerManager->GetPlayerPosition(0));
			}
			MyOutputDebugString("FeverNow\n");
			m_fever1 = true;
		}
		if (!m_wakkaManager[0].GetIsFever())
		{
			if (m_fever1)
			{
				//m_emitter[0].DestroyEmitter(m_feverIdx1);
				m_fever1 = false;
			}
		}
	}

	//Player2の処理
	if (!m_goal2)
	{
		if (Input::TriggerKey(DIK_U) || g_diJoyState2[3] & BUTTON_M) {
			if (!b)
			{
				PlaySound(SOUND_SE_WCHANGE);
				m_wakkaManager[1].Change(1);
				b = true;
			}
		}
		if (Input::TriggerKey(DIK_O) || g_diJoyState2[3] & BUTTON_R) {
			if (!b)
			{
				PlaySound(SOUND_SE_WCHANGE);
				m_wakkaManager[1].Change(0);
				b = true;
			}
		}
		if (Input::TriggerKey(DIK_I) || g_diJoyState2[3] & BUTTON_START) {
			PlaySound(SOUND_SE_SHOOT);
			m_wakkaManager[1].Shoot();
		}
		if (Input::TriggerKey(DIK_0))
		{
			m_score[1].AddScore((200 - m_time->GetTime()) * 20);
			m_goal2 = true;
		}
		if (Input::TriggerKey(DIK_M))
		{
			m_emitter[1].CreateEmitter(PARTICLE_SPEED, m_playerManager->GetPlayerPosition(1));
		}
		if (m_wakkaManager[1].GetIsFever())
		{
			if (!m_fever2)
			{
				m_feverIdx2 = m_emitter[1].CreateEmitter(PARTICLE_FEVER, m_playerManager->GetPlayerPosition(1));
			}
			m_fever2 = true;
		}
		if (!m_wakkaManager[1].GetIsFever())
		{
			if (m_fever2)
			{
				//m_emitter[1].DestroyEmitter(m_feverIdx2);
				m_fever2 = false;
			}
		}
	}
}

void SceneGame::PlayerDraw(int j) {
	StageDraw(m_playerManager->GetPlayerPosition(j));
	m_wakkaManager[j].Draw();
	m_playerManager->Draw(j);	
}

void SceneGame::PlayerFinalize() {
	m_playerManager->Finalize();
	delete m_playerManager;

}

void SceneGame::WakkaInitialize() {
	m_wakkaManager = new WakkaManager[2];
	m_wakkaManager[0].Initialize(0);
	m_wakkaManager[1].Initialize(1);
	
}

void SceneGame::WakkaUpdate() {
	for (int i = 0; i < WAKKA; i++) 
	{
		m_wakkaManager[i].SetPlayerPosition(m_playerManager->GetPlayerPosition(i));
		m_wakkaManager[i].SetPlayerAngle(m_playerManager->GetPlayerAngle(i));
		m_wakkaManager[i].SetPlayerFlow(m_playerManager->GetPlayerFlow(i));
		m_wakkaManager[i].Update();
	}
}

void SceneGame::WakkaFinalize() {
	m_wakkaManager[1].Finalize();
	m_wakkaManager[0].Finalize();
	delete[] m_wakkaManager;
}

void SceneGame::ObstacleInitialize() {
	m_obstacleManager = new ObstacleManager[2];
	m_obstacleManager[0].Initialize();
	m_obstacleManager[1].Initialize();

	//最初
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++) {
			D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 10 * 0.15f, 0.0f, 90.0f * i + 15.0f * j + 15.0f);
			OBST_TYPE type = OBST_TYPE(rand() % 5);
			m_obstacleManager[0].CreateObstacle(pos, type);
			m_obstacleManager[1].CreateObstacle(pos, type);
			if (type == SANDSTORM)
			{
				m_obstacleManager[0].SetParticleIndex(m_emitter[0].CreateEmitter(PARTICLE_SAND_STORM, pos));
				m_obstacleManager[1].SetParticleIndex(m_emitter[1].CreateEmitter(PARTICLE_SAND_STORM, pos));
			}
		}
	}

	//2
	for (int i = 0; i < 10; i++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(-15.0f * i - 0.15f, 0.0f, rand() % 10 * 0.2f - 1.0f + 300.0f);
		OBST_TYPE type = OBST_TYPE(rand() % 5);
		m_obstacleManager[0].CreateObstacle(pos, type);
		m_obstacleManager[1].CreateObstacle(pos, type);
		if (type == SANDSTORM)
		{
			m_obstacleManager[0].SetParticleIndex(m_emitter[0].CreateEmitter(PARTICLE_SAND_STORM, pos));
			m_obstacleManager[1].SetParticleIndex(m_emitter[1].CreateEmitter(PARTICLE_SAND_STORM, pos));
		}
	}

	//3
	for (int i = 0; i < 10; i++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 10 * 0.2f - 100.0f, 0.0f, 300.0f + 15.0f * i);
		OBST_TYPE type = OBST_TYPE(rand() % 5);
		m_obstacleManager[0].CreateObstacle(pos, type);
		m_obstacleManager[1].CreateObstacle(pos, type);
		if (type == SANDSTORM)
		{
			m_obstacleManager[0].SetParticleIndex(m_emitter[0].CreateEmitter(PARTICLE_SAND_STORM, pos));
			m_obstacleManager[1].SetParticleIndex(m_emitter[1].CreateEmitter(PARTICLE_SAND_STORM, pos));
		}
	}

	//4
	for (int i = 0; i < 10; i++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(-15.0f * i - 0.15f, 0.0f, rand() % 10 * 0.2f - 1.0f + 400.0f);
		OBST_TYPE type = OBST_TYPE(rand() % 5);
		m_obstacleManager[0].CreateObstacle(pos, type);
		m_obstacleManager[1].CreateObstacle(pos, type);
		if (type == SANDSTORM)
		{
			m_obstacleManager[0].SetParticleIndex(m_emitter[0].CreateEmitter(PARTICLE_SAND_STORM, pos));
			m_obstacleManager[1].SetParticleIndex(m_emitter[1].CreateEmitter(PARTICLE_SAND_STORM, pos));
		}
	}


}

void SceneGame::ObstacleUpdate() {
	m_obstacleManager[0].SetPlayerPosition(m_playerManager->GetPlayerPosition(0));
	m_obstacleManager[1].SetPlayerPosition(m_playerManager->GetPlayerPosition(1));
	m_obstacleManager[0].Update();
	m_obstacleManager[1].Update();
}

void SceneGame::ObstacleDraw(int playerIdx) {
	m_obstacleManager[playerIdx].Draw();
}

void SceneGame::ObstacleFinalize() {
	m_obstacleManager[1].Finalize();
	m_obstacleManager[0].Finalize();
	delete[] m_obstacleManager;
}

void SceneGame::StageInitialize() {
	m_stageManager = new StageManager;
	m_stageManager->Initialize();
	int count = 0;

	//直線の森ステージ
	for (int i = 0; i < FIRST_STAGE; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(0.0f, -1.0f, i * 10.0f), STAGE_ROAD, UP);
		count++;
	}
	for (int i = 0; i < FIRST_STAGE * 2 - 1; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(3.0f, -1.0f, i * 5.0f), 1.5f, STAGE_TREE, LEFT);
		m_stageManager->CreateStage(D3DXVECTOR3(-3.0f, -1.0f, i * 5.0f), 1.5f, STAGE_TREE, RIGHT);
	}
	/*for (int i = 0; i < FIRST_STAGE * 2 - 2; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(5.0f, -1.0f, i * 5.0f + 2.5f), 1.5f, STAGE_TREE, LEFT);
		m_stageManager->CreateStage(D3DXVECTOR3(-5.0f, -1.0f, i * 5.0f + 2.5f), 1.5f, STAGE_TREE, RIGHT);
	}*/
	for (int i = FIRST_STAGE * 2 - 1; i < FIRST_STAGE * 2 + 2; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(3.0f, -1.0f, i * 5.0f), 1.5f, STAGE_TREE, LEFT);
	}

	//グネグネ市街地ステージ
	//1曲がり目
	for (int i = count; i < FIRST_STAGE + 10; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (i - count), -1.0f, 300.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), STAGE_ROAD, UP);
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (i - count), -1.0f, 305.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), STAGE_ROAD, UP);
	}

	
	m_stageManager->CreateStage(D3DXVECTOR3(0.0f, -1.0f, 313.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, DOWN);

	for (int i = count + 1; i < FIRST_STAGE + 10; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (i - count), 0.0f, 292.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, UP);
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (i - count), 0.0f, 313.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, DOWN);
	}

	m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (FIRST_STAGE + 10 - count), 0.0f, 292.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, UP);
	m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (FIRST_STAGE + 11 - count), 0.0f, 292.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, UP);

	count += 10;

	//2曲がり目
	for (int i = count; i < FIRST_STAGE + 20; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10, -1.0f, 300.0f + 10.0f * (i - count)), STAGE_ROAD, UP);
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10 - 5.0f, -1.0f, 300.0f + 10.0f * (i - count)), STAGE_ROAD, UP);
	}

	m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10 - 13.0f, -1.0f, 300.0f), 1.5f, STAGE_HOUSE3, RIGHT);

	for (int i = count + 1; i < FIRST_STAGE + 20; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10 + 8.0f, -1.0f, 300.0f + 10.0f * (i - count)), 1.5f, STAGE_HOUSE3, LEFT);
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10 - 12.0f, -1.0f, 300.0f + 10.0f * (i - count)), 1.5f, STAGE_HOUSE3, RIGHT);
	}

	m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10 - 12.0f, -1.0f, 300.0f + 10.0f * (FIRST_STAGE + 20 - count)), 1.5f, STAGE_HOUSE3, RIGHT);
	m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10 - 12.0f, -1.0f, 300.0f + 10.0f * (FIRST_STAGE + 21 - count)), 1.5f, STAGE_HOUSE3, RIGHT);

	count += 10;

	//3曲がり目道1つに縮小
	for (int i = count - 1; i < FIRST_STAGE + 30; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (i - count) - 12.0f, -1.0f, 400.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), STAGE_ROAD, UP);
	}

	m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * 10, -1.0f, 408.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, DOWN);

	for (int i = count + 1; i < FIRST_STAGE + 30; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (i - count), 0.0f, 392.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, UP);
		m_stageManager->CreateStage(D3DXVECTOR3(-10.0f * (i - count), 0.0f, 408.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, DOWN);
	}

	m_stageManager->CreateStage(D3DXVECTOR3(0.0f, 0.0f, 392.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, UP);
	m_stageManager->CreateStage(D3DXVECTOR3(-10.0f, 0.0f, 392.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, UP);

	count -= 10;

	//4曲目最後の直線
	for (int i = count; i < FIRST_STAGE + 30; i++) 
	{
		m_stageManager->CreateStage(D3DXVECTOR3(0.0f, -1.0f, i * 10.0f), STAGE_ROAD, UP);
	}

	m_stageManager->CreateStage(D3DXVECTOR3(8.0f, 0.0f, count * 10.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, LEFT);

	for (int i = count + 1; i < FIRST_STAGE + 30; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(8.0f, 0.0f, i * 10.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, LEFT);
		m_stageManager->CreateStage(D3DXVECTOR3(-8.0f, 0.0f, i * 10.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_HOUSE1, RIGHT);
	}

	for (int i = FIRST_STAGE + 30; i < FIRST_STAGE + 40; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(8.0f, -1.0f, i * 10.0f), D3DXVECTOR3(90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_CHURCH, LEFT);
		m_stageManager->CreateStage(D3DXVECTOR3(-8.0f, -1.0f, i * 10.0f), D3DXVECTOR3(-90.0f * RADIAN, 0.0f, 0.0f), 3.5f, STAGE_CHURCH, RIGHT);
	}

	count += 10;
	m_stageManager->CreateStage(D3DXVECTOR3(0.0f, -1.0f, 700.0f), STAGE_TEMPLE, UP);

}

void SceneGame::StageDraw(D3DXVECTOR3 pos) {
	m_stageManager->SetPlayerPos(pos);
	m_stageManager->Update();
	m_stageManager->Draw();
}

void SceneGame::StageFinalize() {
	m_stageManager->Finalize();
	delete m_stageManager;
}

void SceneGame::CameraInitialize() {
	m_camera = new Cameran[2];
	m_camera[0].Initialize();
	m_camera[1].Initialize();
}

void SceneGame::CameraUpdate(int player) {
	m_camera[player].SetPlayerPos(m_playerManager->GetPlayerPosition(player));
	m_camera[player].SetPlayerAngle(m_playerManager->GetPlayerAngle(player));
	m_camera[player].Update();
	m_camera[player].SetCamera();
	m_camera[player].SetMat();
}

void SceneGame::CameraFinalize() {
	delete[] m_camera;
}

void SceneGame::ItemInitialize() {
	m_itemManager = new ItemManager[2];
	m_itemManager[0].Initialize();
	m_itemManager[1].Initialize();
}

void SceneGame::ItemUpdate() {
	m_itemManager[0].SetPlayerPosition(m_playerManager->GetPlayerPosition(0));
	m_itemManager[0].Update();
	m_itemManager[1].SetPlayerPosition(m_playerManager->GetPlayerPosition(1));
	m_itemManager[1].Update();
}

void SceneGame::ItemDraw(int playerIdx) {
	m_itemManager[playerIdx].Draw();
}

void SceneGame::ItemFinalize() {
	m_itemManager[1].Finalize();
	m_itemManager[0].Finalize();
	delete[] m_itemManager;
}

void SceneGame::EmitterInitialize() {
	m_emitter = new EmitterManager[2];
	m_emitter[0].Initialize();
	m_emitter[1].Initialize();
}

void SceneGame::EmitterUpdate() {
	m_emitter[0].SetPlayerAngle(m_playerManager->GetPlayerAngle(0));
	m_emitter[0].Update(m_playerManager->GetPlayerPosition(0));
	m_emitter[1].SetPlayerAngle(m_playerManager->GetPlayerAngle(1));
	m_emitter[1].Update(m_playerManager->GetPlayerPosition(1));
}

void SceneGame::EmitterDraw(int playerIdx) {
	m_emitter[playerIdx].Draw();
}

void SceneGame::EmitterFinalize() {
	m_emitter[1].Finalize();
	m_emitter[0].Finalize();
	delete[] m_emitter;
}

void SceneGame::ScoreInitialize() {
	m_score = new Score[2];
	m_score[0].Initialize();
	m_score[1].Initialize();
	D3DXVECTOR2 pos = D3DXVECTOR2(580.0f, 600.0f);
	m_score[0].SetPosition(pos);
	pos = D3DXVECTOR2(1220.0f, 600.0f);
	m_score[1].SetPosition(pos);
	
}

void SceneGame::ScoreDraw(int idx) {
	m_score[idx].Draw();
}

void SceneGame::ScoreFinalize() {
	m_score[1].Finalize();
	m_score[0].Finalize();
	delete[] m_score;
}

void SceneGame::Rendering(int a) {
	D3DVIEWPORT9 viwePort;
	if (a == 0) {
		viwePort.X = 0;
		viwePort.Y = 0;
		viwePort.Width = 640;
		viwePort.Height = 720;
		viwePort.MaxZ = 1.0f;
		viwePort.MinZ = 0.0f;
		m_d3dDevice->SetViewport(&viwePort);
	}
	else {
		viwePort.X = 640;
		viwePort.Y = 0;
		viwePort.Width = 640;
		viwePort.Height = 720;
		viwePort.MaxZ = 1.0f;
		viwePort.MinZ = 0.0f;
		m_d3dDevice->SetViewport(&viwePort);
	}
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(160, 216, 239), 1.0f, 0);
	// プロジェクショントランスフォーム（射影変換）
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	CameraUpdate(a);
	
	if (m_goal1 && m_goal2)
	{
		//m_d3dDevice->LightEnable(0, FALSE);
		D3DXVECTOR3 vecDirection(1, -1, -1);
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Diffuse.r = 1.0f;
		light.Diffuse.g = 1.0f;
		light.Diffuse.b = 1.0f;
		light.Specular.r = 0.0f;
		light.Specular.g = 0.0f;
		light.Specular.b = 0.0f;
		D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
		light.Range = 200.0f;
		m_d3dDevice->SetLight(0, &light);
		m_d3dDevice->LightEnable(0, TRUE);
	}
	else
	{
		// ライトをあてる 白色で鏡面反射ありに設定
		D3DXVECTOR3 vecDirection(1, -1, -1);
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Diffuse.r = 1.0f;
		light.Diffuse.g = 1.0f;
		light.Diffuse.b = 1.0f;
		light.Specular.r = 0.0f;
		light.Specular.g = 0.0f;
		light.Specular.b = 0.0f;
		D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
		light.Range = 200.0f;
		m_d3dDevice->SetLight(0, &light);
		m_d3dDevice->LightEnable(0, TRUE);
	}
}

void SceneGame::CollisionUpdate() {
	ColP2O();
	ColW2O();
	ColP2I();
	ColP2S();
}

void SceneGame::ColP2O() {
	for (int idx = 0; idx < 2; idx++) 
	{
		if (m_goal1 && idx == 0 || m_goal2 && idx == 1)
		{
			continue;
		}
		int obstacleNum = m_obstacleManager[idx].GetObstacleNum();
		for (int i = 0; i < obstacleNum; i++)
		{
			ObstacleInfo* info = m_obstacleManager[idx].GetObstacleInfo(i);
			D3DXVECTOR3 pos = info->pos;
			if (info->enable)
			{
				if (Collision::CheckCollision(m_playerManager->GetAABB(idx), m_obstacleManager[idx].GetAABB(i)))
				{
					m_playerManager->SetObstacleEffect(idx, info->type);
					m_obstacleManager[idx].Hit(i);
					m_playerManager->Hit(idx, NON);
					obstacleNum--;
					if (info->type == SANDSTORM)
					{
						m_emitter[idx].DestroyEmitter(m_obstacleManager[idx].GetParticleIndex(i));
					}
					m_emitter[idx].CreateEmitter(PARTICLE_HIT_PLAYER, pos);
				}
			}
		}
	}
}

void SceneGame::ColW2O() {
	for (int idx = 0; idx < 2; idx++)
	{
		if (m_goal1 && idx == 0 || m_goal2 && idx == 1)
		{
			continue;
		}
		int obstacleNum = m_obstacleManager[idx].GetObstacleNum();
		for (int i = 0; i < obstacleNum; i++)
		{
			for (int wakka = 0; wakka < 5; wakka++)
			{
				if (m_wakkaManager[idx].IsShoot(wakka))
				{
					ObstacleInfo* info = m_obstacleManager[idx].GetObstacleInfo(i);
					D3DXVECTOR3 pos = info->pos;
					if (info->enable)
					{
						if (Collision::CheckCollision(m_wakkaManager[idx].GetAABB(wakka), m_obstacleManager[idx].GetAABB(i)))
						{
							switch ((ELEM)wakka)
							{
							case WATER:
								PlaySound(SOUND_SE_WATER);
								break;
							case FIRE:
								PlaySound(SOUND_SE_FIRE);
								break;
							case SOIL:
								PlaySound(SOUND_SE_HOLE);
								break;
							case SAND:
								PlaySound(SOUND_SE_SAND);
								break;
							case WOOD:
								PlaySound(SOUND_SE_HITTREE);
								break;
							default:
								break;
							}
							m_wakkaManager[idx].Hit(wakka);
							m_score[idx].AddScore(100 + (m_wakkaManager[idx].GetComboCount() + 1) * 10);
							/*障害物削除処理*/
							if (IsObstacleDestroy(info->type, m_wakkaManager[idx].GetElem(wakka)) || m_wakkaManager[idx].GetIsFever())
							{
								m_obstacleManager[idx].Hit(i);
								m_wakkaManager[idx].DestroyObstacleCountUp();

								if (info->type == SANDSTORM)
								{
									m_emitter[idx].DestroyEmitter(m_obstacleManager[idx].GetParticleIndex(i));
								}
								
								/*アイテム生成処理*/
								if (m_wakkaManager[idx].GetDestroyObstacleNum() % 3 == 0)
								{
									m_itemManager[idx].CreateItem(m_wakkaManager[idx].GetPosition(wakka), (ITEM_TYPE)(rand() % 2));
								}
								obstacleNum--;
							}
							/*if (!m_playerManager->GetCoolTime(idx).bCoolTime)
							{
								if (m_wakkaManager[idx].GetElem(wakka) == SAND)
								{
									D3DXVECTOR3 pos = m_wakkaManager[idx].GetPosition(wakka);
									if (idx == 0)
									{
										m_obstacleManager[1].CreateObstacle(pos, SANDSTORM);
									}
									else
									{
										m_obstacleManager[0].CreateObstacle(pos, SANDSTORM);
									}

								}
								else if (m_wakkaManager[idx].GetElem(wakka) == SOIL)
								{
									D3DXVECTOR3 pos = m_wakkaManager[idx].GetPosition(wakka);
									if (idx == 0)
									{
										m_obstacleManager[1].CreateObstacle(pos, PITFALL);
									}
									else
									{
										m_obstacleManager[0].CreateObstacle(pos, PITFALL);
									}
								}
								m_playerManager->StartCoolTime(idx);
							}*/
							m_emitter[idx].CreateEmitter(PARTICLE_NORMAL, pos);
						}
					}
				}
			}
		}
	}
}

void SceneGame::ColP2S() {
	for (int idx = 0; idx < 2; idx++)
	{
		if (m_goal1 && idx == 0 || m_goal2 && idx == 1)
		{
			continue;
		}
		D3DXVECTOR3 playerPos = m_playerManager->GetPlayerPosition(idx);
		m_stageManager->SetPlayerPos(playerPos);
		m_stageManager->Update();
		int stageNum = STAGE_NUM;
		for (int i = 0; i < stageNum; i++)
		{
			StageInfo* info = m_stageManager->GetStageInfo(i);
				if (info->enable)
				{
					if (info->type != STAGE_ROAD)
					{
						if (Collision::CheckCollision(m_playerManager->GetAABB(idx), m_stageManager->GetAABB(i)))
						{
							PlaySound(SOUND_SE_PWALL);
							m_playerManager->Hit(idx, info->dir);
							m_emitter[idx].CreateEmitter(PARTICLE_HIT_PLAYER, m_playerManager->GetPlayerPosition(idx));
							stageNum--;
						
							if (info->type == STAGE_TEMPLE)
							{
								if (idx == 0)
								{
									m_goal1 = true;
									if (!m_goal2)
									{
										m_win = 0;
									}
								}
								else
								{
									m_goal2 = true;
									if (!m_goal1)
									{
										m_win = 1;
									}
								}
								m_playerManager->GetGoalTime(m_time->GetTime(), idx);
								m_score[idx].AddScore((200 - m_time->GetTime()) * 20);
							}
					}
				}
			}

		}
	}
}

void SceneGame::ColP2I() {
	int itemNum = ITEM_NUM;

	//プレイヤー１がアイテムをとった時の処理
	for (int i = 0; i < itemNum; i++)
	{
		if (m_goal1)
		{
			break;
		}
		ItemInfo* info = m_itemManager[0].GetItemInfo(i);
		if (info->enable)
		{
			if (Collision::CheckCollision(m_playerManager->GetAABB(0), m_itemManager[0].GetAABB(i)))
			{
				if (info->type == TAIYAKI)
				{
					m_playerManager->SetItemEffect(0, TAIYAKI);
					m_emitter[0].CreateEmitter(PARTICLE_POWERUP, m_playerManager->GetPlayerPosition(0));
					D3DXVECTOR3 position = m_playerManager->GetPlayerPosition(0);
					float angle = m_playerManager->GetPlayerAngle(0);
					m_emitter[0].CreateEmitter(PARTICLE_SPEED, m_playerManager->GetPlayerPosition(0));
				}
				else
				{
					m_playerManager->SetItemEffect(1, MERONPAN);
					m_emitter[1].CreateEmitter(PARTICLE_POWERDOWN, m_playerManager->GetPlayerPosition(1));
				}
				itemNum--;
				m_itemManager[0].Hit(i);
			}
		}
	}

	//プレイヤー２がアイテムを取った時の処理
	for (int i = 0; i < itemNum; i++)
	{
		if (m_goal2)
		{
			break;
		}
		ItemInfo* info = m_itemManager[1].GetItemInfo(i);
		if (info->enable)
		{
			if (Collision::CheckCollision(m_playerManager->GetAABB(1), m_itemManager[1].GetAABB(i)))
			{
				if (info->type == TAIYAKI)
				{
					m_playerManager->SetItemEffect(1, TAIYAKI);
					m_emitter[1].CreateEmitter(PARTICLE_POWERUP, m_playerManager->GetPlayerPosition(1));
					m_emitter[1].CreateEmitter(PARTICLE_SPEED, m_playerManager->GetPlayerPosition(1));
				}
				else
				{
					m_playerManager->SetItemEffect(0, MERONPAN);
					m_emitter[0].CreateEmitter(PARTICLE_POWERDOWN, m_playerManager->GetPlayerPosition(0));
				}
				m_itemManager[1].Hit(i);
				itemNum--;
				MyOutputDebugString("HIT ITEM TO PLAYER player%d to Obst%d\n", 1, info->type);
			}
		}
	}
}

template <class T>
D3DXMATRIX* SceneGame::GetMatrix(T& info, D3DXMATRIX& mat) {
	D3DXMATRIXA16 matTranslation, matRotation, matScale;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixTranslation(&matTranslation, info->pos.x, info->pos.y, info->pos.z);
	D3DXMatrixRotationYawPitchRoll(&matRotation, info->rot.y, info->rot.x, info->rot.z);
	D3DXMatrixScaling(&matScale, info->scale.x + 1.0f, info->scale.y + 1.0f, info->scale.z + 1.0f);
	mat = matScale * matRotation * matTranslation;
	return &mat;
}

bool SceneGame::IsObstacleDestroy(OBST_TYPE type, ELEM elem) {
	if (type == FIREWOOD && elem == FIRE)
	{
		return true;
	}
	else if (type == FIREWOOD && elem == WATER)
	{
		return true;
	}
	else if (type == SANDSTORM && elem == SAND)
	{
		return true;
	}
	else if (type == PITFALL && elem == SOIL)
	{
		return true;
	}
	else if (type == DRIFTWOOD && elem == WOOD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SceneGame::ResultInitialize() {
	PlaySound(SOUND_BGM_RESULT);
	int score1 = m_score[0].GetScore();
	int score2 = m_score[1].GetScore();
	m_win = Judge::JudgeRace(score1, score2);
	m_winLose->Win(m_win);
	
	//player1win
	if (m_win == 0)
	{
		m_disp[0].Initialize(0);
		m_disp[1].Initialize(1);
		m_disp[0].SetScore(score1);
		m_disp[1].SetScore(score2);
		m_winLose->SetPosition(m_playerManager->GetPlayerPosition(0), 0);
		m_winLose->SetPosition(m_playerManager->GetPlayerPosition(1), 1);
	}
	//player2win
	else
	{
		m_disp[0].Initialize(0);
		m_disp[1].Initialize(1);
		m_disp[0].SetScore(score2);
		m_disp[1].SetScore(score1);
		m_winLose->SetPosition(m_playerManager->GetPlayerPosition(0), 1);
		m_winLose->SetPosition(m_playerManager->GetPlayerPosition(1), 0);
	}
	
	
	/*スコア十勝*/
}

void SceneGame::ResultUpdate() {
	m_winLose->Update();
		/*スコア十勝*/
}

void SceneGame::ResultDraw() {
	if (m_resultInit)
	{
		Rendering(0);
		m_winLose->Draw(0);
		if (m_win == 0)
		{
			m_disp[0].Draw(0);
		}
		else
		{
			m_disp[1].Draw(0);
		}
		Rendering(1);
		m_winLose->Draw(1);
		if (m_win == 0)
		{
			m_disp[1].Draw(1);
		}
		else
		{
			m_disp[0].Draw(1);
		}
	}

}

void SceneGame::ResultFinalize() {
	m_disp[1].Finalize();
	m_disp[0].Finalize();
	delete[] m_disp;
	m_winLose->Finalize();
	delete m_winLose;
}


void SceneGame::InitializeFog() {
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));    //初期化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->GetDeviceCaps(&caps);

	//ピクセルフォグが使えるかどうか確認
	if ((caps.RasterCaps & D3DPRASTERCAPS_FOGRANGE) == 0)
	{
		MessageBox(NULL, "ピクセルフォグ対応してないとかザッコwww", NULL, MB_OK);
	}

	//フォグの設定
	FLOAT StartPos = 50;  //開始位置
	FLOAT EndPos = 100; //終了位置
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); //フォグ：ON
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); //白色で不透明
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);      //頂点モード
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);     //テーブルモード
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&StartPos)); //開始位置
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&EndPos));     //終了位置
}

void SceneGame::SkyInitialize() {
	m_sky = new Sky;
	m_sky->Initialize();
}

void SceneGame::SkyUpdate() {
	m_sky->Update();
}

void SceneGame::SkyDraw() {
	m_sky->Draw();
}

void SceneGame::SkyFinalize() {
	m_sky->Finalize();
}