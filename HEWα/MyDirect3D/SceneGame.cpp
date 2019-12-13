#define _CRT_SECURE_NO_WARNINGS
#include "SceneGame.h"
#include "Input.h"
#include "Joycon.h"
//#include "SceneManager.h"
#include "Enum.h"
#include "Wakka.h"
#include "camera.h"
#include "Player.h"
#include "Stage.h"
#include "main.h"
#include "Collision.h"
#include "Utility.h"
#include "DriftWood.h"
#include "SandStorm.h"
#include <time.h>
#include "COBBTree.h"
#include "Fire.h"
#include "Tree.h"
#include "PitFall.h"
#include "Cameran.h"
#include "ItemManager.h"

static int count = 0;
static bool a = false;
static int count2 = 0;
static bool b = false;

/*xファイルの拡縮するときに法線がおかしくなることがあるのでデバイスのSetRenderStateでD3DRS_NOMALIZENORMALSみたいなことをする*/
/*当たり判定おかしいんご位*/
SceneGame::~SceneGame() {
}

void SceneGame::Initialize() {
	srand((unsigned int)time(NULL));
	PlayerInitialize();
	WakkaInitialize();
	PlayerInitialize(0);
	PlayerInitialize(1);
	StageInitialize();
	ObstacleInitialize();
	CameraInitialize();
	ItemInitialize();
	m_d3dDevice = GetDevice();
	m_goal = new Goal;
	m_goal->Initialize(D3DXVECTOR3(0.0f, 0.0f, 370.0f));
}

void SceneGame::Update() {
	PlayerUpdate(0);
	PlayerUpdate(1);
	WakkaUpdate();
	ObstacleUpdate();
	CollisionUpdate();
	ItemUpdate();
	if (m_goal->IsGoal(m_player->GetPlayerPosition())) {
		MyOutputDebugString("ゴールシタヨ！\n");
	}
}

void SceneGame::Draw() {
	PlayerDraw(0);
	ObstacleDraw(0);
	ItemDraw(0);
	PlayerDraw(1);
	ObstacleDraw(1);
	ItemDraw(1);
}

void SceneGame::Finalize() {
	m_goal->Finalize();
	delete m_goal;
	ItemFinalize();
	CameraFinalize();
	ObstacleFinalize();
	StageFinalize();
	PlayerFinalize(1);
	PlayerFinalize(0);
	WakkaFinalize();
	PlayerFinalize();
}

void SceneGame::PlayerInitialize() {
	m_player = new Player[PLAYER];
}

void SceneGame::PlayerInitialize(int j) {
	m_player[j].Initialize(j);
}

void SceneGame::PlayerUpdate(int j) {
	m_player[j].Update();
	if (a) {
		count++;
		if (count > 20) {
			a = false;
			count = 0;
		}
	}
	if (b) {
		count2++;
		if (count2 > 20) {
			b = false;
			count2 = 0;
		}
	}
	if (j == 0) {
		if (Input::TriggerKey(DIK_Q)|| g_diJoyState2[1] & BUTTON_M) {
			if (!a) {
				m_wakka[j].Change(1);
				a = true;
			}
			
		}
		if (Input::TriggerKey(DIK_E)|| g_diJoyState2[1] & BUTTON_R) {
			if (!a)
			{
				m_wakka[j].Change(0);
				a = true;
			}
		}
		if (Input::TriggerKey(DIK_W)|| g_diJoyState2[1] & BUTTON_START) {
			m_wakka[j].Shoot();
		}
	}
	else {
		if (Input::TriggerKey(DIK_U)||g_diJoyState2[3] & BUTTON_M) {
			if (!b)
			{
				m_wakka[j].Change(1);
				b = true;
			}	
		}
		if (Input::TriggerKey(DIK_O)|| g_diJoyState2[3] & BUTTON_R) {
			if (!b)
			{
				m_wakka[j].Change(1);
				b = true;
			}
		}
		if (Input::TriggerKey(DIK_I)|| g_diJoyState2[3] & BUTTON_START) {
			m_wakka[j].Shoot();
		}
	}
	
	
	/*if (Input::TriggerKey(DIK_C)) {
		m_wakka[j].Hit();
	}*/
}

void SceneGame::PlayerDraw(int j) {
	Rendering(j);
	
	m_player[j].Draw();
	
	m_wakka[j].Draw();
	StageDraw(m_player[j].GetPlayerPosition());
	m_goal->Update();
	m_goal->Draw();
}

void SceneGame::PlayerFinalize(int j) {
	m_player[j].Finalize();
}

void SceneGame::PlayerFinalize() {
	delete[] m_player;
}

void SceneGame::WakkaInitialize() {
	m_wakka = new WakkaManager[2];
	m_wakka[0].Initialize();
	m_wakka[1].Initialize();
	
}

void SceneGame::WakkaUpdate() {
	for (int i = 0; i < WAKKA; i++) 
	{
		m_wakka[i].SetPlayerPosition(m_player[i].GetPlayerPosition());
		m_wakka[i].SetPlayerAngle(m_player[i].GetPlayerAngle());
		m_wakka[i].Update();
	}
}

void SceneGame::WakkaFinalize() {
	m_wakka[1].Finalize();
	m_wakka[0].Finalize();
	delete[] m_wakka;
}

void SceneGame::ObstacleInitialize() {
	m_obstacleManager = new ObstacleManager[2];
	m_obstacleManager[0].Initialize();
	m_obstacleManager[1].Initialize();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) {
			m_obstacleManager[0].CreateObstacle(D3DXVECTOR3(rand() % 5 - 2.0f, 0.0f, 25.0f * i + 5.0f * j + 5.0f), (OBST_TYPE)i);
			//m_obstacleManager[1].CreateObstacle(D3DXVECTOR3(rand() % 5 - 2.0f, 0.0f, 9.0f * i + 3.0f * j + 10.0f), (OBST_TYPE)i);
		}
	}
}

void SceneGame::ObstacleUpdate() {
	m_obstacleManager[0].Update();
	m_obstacleManager[1].Update();
	m_obstacleManager[0].SetPlayerPosition(m_player[0].GetPlayerPosition());
	m_obstacleManager[1].SetPlayerPosition(m_player[1].GetPlayerPosition());
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

	for (int i = 0; i < STAGE; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(0.0f, -0.4f, i * 10.0f), STAGE_NORMAL);
	}
	for (int i = 0; i < STAGE * 2; i++)
	{
		m_stageManager->CreateStage(D3DXVECTOR3(1.25f, -0.4f, i * 5.0f), STAGE_WALL);
		m_stageManager->CreateStage(D3DXVECTOR3(-1.25f, -0.4f, i * 5.0f), STAGE_WALL);
	}
}

void SceneGame::StageDraw(D3DXVECTOR3 pos) {
	for (int i = 0; i < STAGE; i++) {
		StageInfo* info = m_stageManager->GetStageInfo(i);
		if (fabs(pos.y - info->pos.y) < 50.0f && fabs(pos.z - info->pos.z) < 50.0f && fabs(pos.x - info->pos.x) < 50.0f)
		{
			m_stageManager->Draw();
		}
	}
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
	m_camera[player].SetPlayerPos(m_player[player].GetPlayerPosition());
	m_camera[player].SetPlayerAngle(m_player[player].GetPlayerAngle());
	m_camera[player].Update();
	m_camera[player].SetCamera();
}

void SceneGame::CameraFinalize() {
	delete[] m_camera;
}

void SceneGame::ItemInitialize() {
	m_itemManager = new ItemManager[2];
	m_itemManager[0].Initialize();
	m_itemManager[1].Initialize();
	m_itemManager[0].CreateItem(D3DXVECTOR3(0.0f, 0.0f, 40.0f), TAIYAKI);
	m_itemManager[1].CreateItem(D3DXVECTOR3(0.0f, 0.0f, 40.0f), MERONPAN);
}

void SceneGame::ItemUpdate() {
	m_itemManager[0].Update();
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
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 225, 35), 1.0f, 0);
	// プロジェクショントランスフォーム（射影変換）
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	CameraUpdate(a);
	
	// ライトをあてる 白色で鏡面反射ありに設定
	D3DXVECTOR3 vecDirection(1, -1, -1);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	light.Range = 200.0f;
	m_d3dDevice->SetLight(0, &light);
	m_d3dDevice->LightEnable(0, TRUE);

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
		int obstacleNum = m_obstacleManager[idx].GetObstacleNum();
		for (int i = 0; i < obstacleNum; i++)
		{
			ObstacleInfo* info = m_obstacleManager[idx].GetObstacleInfo(i);
			D3DXMATRIX mat;
			D3DXMATRIXA16 matTranslation, matRotation, matScale;
			GetMatrix(info, mat);
			if (Collision::CheckCollision(m_player[idx].GetOBB(), *m_player[idx].GetMatrix(), m_obstacleManager[idx].GetOBB(info->type), mat))
			{
				m_obstacleManager[idx].Hit(i);
				m_player[idx].Hit();
				obstacleNum--;
			}
		}
	}
}

void SceneGame::ColW2O() {
	for (int idx = 0; idx < 2; idx++)
	{
		int obstacleNum = m_obstacleManager[idx].GetObstacleNum();
		for (int i = 0; i < obstacleNum; i++)
		{
			for (int wakka = 0; wakka < 5; wakka++)
			{
				if (m_wakka[idx].IsShoot(wakka))
				{
					ObstacleInfo* info = m_obstacleManager[idx].GetObstacleInfo(i);
					D3DXMATRIX mat;
					GetMatrix(info, mat);
					if (Collision::CheckCollision(m_wakka[idx].GetOBB(wakka), *m_wakka[idx].GetMatrix(wakka), m_obstacleManager[idx].GetOBB(info->type), mat))
					{
						m_wakka[0].Hit(wakka);
						/*アイテム生成処理*/
						if (m_wakka[idx].GetDestroyObstacleNum() % 3 == 0)
						{
							m_itemManager[idx].CreateItem(info->pos, (ITEM_TYPE)(rand() % 2));
						}

						/*障害物削除処理*/
						if (info->type == DRIFTWOOD && m_wakka[idx].GetElem(wakka) == FIRE)
						{
							m_obstacleManager[idx].Hit(i);
						}
						else if (info->type == FIREDRIFTWOOD && m_wakka[idx].GetElem(wakka) == WATER)
						{
							m_obstacleManager[idx].Hit(i);
						}
						else if (info->type == TREE && m_wakka[idx].GetElem(wakka) == FIRE)
						{
							m_obstacleManager[idx].Hit(i);
						}
						else if (info->type == SANDSTORM && m_wakka[idx].GetElem(wakka) == WATER)
						{
							m_obstacleManager[idx].Hit(i);
						}
						else if (info->type == PITFALL && m_wakka[idx].GetElem(wakka) == SOIL)
						{
							m_obstacleManager[idx].Hit(i);
						}
						if (!m_player[idx].GetCoolTime().bCoolTime)
						{
							if (m_wakka[idx].GetElem(wakka) == SAND)
							{
								D3DXVECTOR3 pos = m_wakka[idx].GetPosition(wakka);
								D3DXVECTOR3 pos1;
								D3DXVECTOR3 pos2;
								if (idx == 0)
								{
									pos1 = m_player[0].GetPlayerPosition();
									pos2 = m_player[1].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									m_obstacleManager[1].CreateObstacle(pos, SANDSTORM);
								}
								else
								{
									pos1 = m_player[1].GetPlayerPosition();
									pos2 = m_player[0].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									m_obstacleManager[0].CreateObstacle(pos, SANDSTORM);
								}

							}
							else if (m_wakka[idx].GetElem(wakka) == SOIL)
							{
								D3DXVECTOR3 pos = m_wakka[idx].GetPosition(wakka);
								D3DXVECTOR3 pos1;
								D3DXVECTOR3 pos2;
								if (idx == 0)
								{
									pos1 = m_player[1].GetPlayerPosition();
									pos2 = m_player[0].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									m_obstacleManager[1].CreateObstacle(pos, PITFALL);
								}
								else
								{
									pos1 = m_player[0].GetPlayerPosition();
									pos2 = m_player[1].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									m_obstacleManager[0].CreateObstacle(pos, PITFALL);
								}
							}
							m_player[idx].StartCoolTime();
						}
						obstacleNum--;
					}
				}
				
			}
		}
	}
	
}

void SceneGame::ColP2S() {
	//D3DXVECTOR3 pos = m_player[0].GetPlayerPosition();
	///*当たり判定必要なステージオブジェクトの数だけ繰り返すのだ*/
	//for (int i = 0; i < STAGE * 2; i++) {
	//	/*当たり判定とる範囲はできる限り小さくしてみた！ キラッとプリ☆チャンはいいぞ*/
	//	/*if (fabs(pos.y - m_stageInfo[i][0].y) < 2.0f && fabs(pos.z - m_stageInfo[i][0].z) < 2.0f && fabs(pos.x - m_stageInfo[i][0].x) < 2.0f)
	//	{*/
	//		D3DXMATRIX mat;
	//		D3DXMATRIXA16 matTranslation, matRotation, matScale;
	//		D3DXMatrixIdentity(&mat);
	//		D3DXMatrixIdentity(&matTranslation);
	//		D3DXMatrixIdentity(&matRotation);
	//		D3DXMatrixIdentity(&matScale);
	//		D3DXMatrixTranslation(&matTranslation, m_stageWallInfo[i][0].x, m_stageWallInfo[i][0].y, m_stageWallInfo[i][0].z);
	//		D3DXMatrixRotationYawPitchRoll(&matRotation, m_stageWallInfo[i][1].y, m_stageWallInfo[i][1].x, m_stageWallInfo[i][1].z);
	//		D3DXMatrixScaling(&matScale, m_stageWallInfo[i][2].x, m_stageWallInfo[i][2].y, m_stageWallInfo[i][2].z);
	//		mat = matScale * matRotation * matTranslation;
	//		if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_stageWall->GetOBB(), mat))
	//		{
	//			MyOutputDebugString("ｱﾀｯﾀﾖ!\n");
	//			m_player[0].Hit();
	//			m_player[0].HitWall();
	//		}
	//	/*}*/
	//	
	//}
}

void SceneGame::ColP2I() {
	int itemNum = m_itemManager[0].GetItemNum();
	for (int i = 0; i < itemNum; i++)
	{
		ItemInfo* info = m_itemManager[0].GetItemInfo(i);
		D3DXMATRIX mat;
		D3DXMATRIXA16 matTranslation, matRotation, matScale;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matTranslation);
		D3DXMatrixIdentity(&matRotation);
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixTranslation(&matTranslation, info->pos.x, info->pos.y, info->pos.z);
		D3DXMatrixRotationYawPitchRoll(&matRotation, info->rot.y, info->rot.x, info->rot.z);
		D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);
		mat = matScale * matRotation * matTranslation;
		if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_itemManager[0].GetOBB(info->type), mat))
		{
			if (info->type == TAIYAKI)
			{
				m_player[0].GetItemEffect(TAIYAKI);
			}
			else
			{
				m_player[1].GetItemEffect(MERONPAN);
			}
			itemNum--;
			m_itemManager[0].Hit(i);
		}
	}

	itemNum = m_itemManager[1].GetItemNum();
	for (int i = 0; i < itemNum; i++)
	{
		ItemInfo* info = m_itemManager[1].GetItemInfo(i);
		D3DXMATRIX mat;
		D3DXMATRIXA16 matTranslation, matRotation, matScale;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matTranslation);
		D3DXMatrixIdentity(&matRotation);
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixTranslation(&matTranslation, info->pos.x, info->pos.y, info->pos.z);
		D3DXMatrixRotationYawPitchRoll(&matRotation, info->rot.y, info->rot.x, info->rot.z);
		D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);
		mat = matScale * matRotation * matTranslation;
		if (Collision::CheckCollision(m_player[1].GetOBB(), *m_player[1].GetMatrix(), m_itemManager[1].GetOBB(info->type), mat))
		{
			if (info->type == TAIYAKI)
			{
				m_player[1].GetItemEffect(TAIYAKI);
			}
			else
			{
				m_player[0].GetItemEffect(MERONPAN);
			}
			m_itemManager[1].Hit(i);
			itemNum--;
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
	D3DXMatrixScaling(&matScale, info->scale.x, info->scale.y, info->scale.z);
	mat = matScale * matRotation * matTranslation;
	return &mat;
}