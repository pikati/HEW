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


static int count = 0;
static bool a = false;
static int count2 = 0;
static bool b = false;

/*xファイルの拡縮するときに法線がおかしくなることがあるのでデバイスのSetRenderStateでD3DRS_NOMALIZENORMALSみたいなことをする*/
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
	m_d3dDevice = GetDevice();
	m_goal = new Goal;
	m_goal->Initialize(D3DXVECTOR3(0.0f, 0.0f, 370.0f));
}

void SceneGame::Update() {
	PlayerUpdate(0);
	PlayerUpdate(1);
	ObstacleUpdate();
	CollisionUpdate();
	if (m_goal->IsGoal(m_player->GetPlayerPosition())) {
		MyOutputDebugString("ゴールシタヨ！\n");
	}
}

void SceneGame::Draw() {
	PlayerDraw(0);
	ObstacleDraw(0);
	PlayerDraw(1);
	ObstacleDraw(1);
}

void SceneGame::Finalize() {
	m_goal->Finalize();
	delete m_goal;
	ObstacleFinalize();
	StageFinalize();
	PlayerFinalize(1);
	PlayerFinalize(0);
	//WakkaFinalize();
	PlayerFinalize();
}

void SceneGame::PlayerInitialize() {
	m_player = new Player[PLAYER];
}

void SceneGame::PlayerInitialize(int j) {
	m_player[j].Initialize(j);
	for (int i = 0; i < WAKKA; i++) {
		m_wakka[j][i].Initialize((ELEM)i, j);
	}
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
				Wakka::Chenge(1, j);
				a = true;
			}
			
		}
		if (Input::TriggerKey(DIK_E)|| g_diJoyState2[1] & BUTTON_R) {
			if (!a)
			{
				Wakka::Chenge(0, j);
				a = true;
			}
		}
		if (Input::TriggerKey(DIK_W)|| g_diJoyState2[1] & BUTTON_START) {
			m_wakka[j][Wakka::GetCenter(j)].Shoot();
		}
	}
	else {
		
		if (Input::TriggerKey(DIK_U)||g_diJoyState2[3] & BUTTON_M) {
			if (!b)
			{
				Wakka::Chenge(1, j);
				b = true;
			}
			
		}
		if (Input::TriggerKey(DIK_O)|| g_diJoyState2[3] & BUTTON_R) {
			if (!b)
			{
				Wakka::Chenge(0, j);
				b = true;
			}
			
		}
		if (Input::TriggerKey(DIK_I)|| g_diJoyState2[3] & BUTTON_START) {
			m_wakka[j][Wakka::GetCenter(j)].Shoot();
		}
	}
	
	
	if (Input::TriggerKey(DIK_C)) {
		m_wakka[j][Wakka::GetCenter(j)].Hit();
	}
	for (int i = 0; i < WAKKA; i++) {
		m_wakka[j][i].SetPlayerPosition(m_player[j].GetPlayerPosition());
		m_wakka[j][i].Update(j);
	}
}

void SceneGame::PlayerDraw(int j) {
	Rendering(j);
	
	m_player[j].Draw();
	
	for (int i = 0; i < WAKKA; i++) {
		m_wakka[j][i].Draw();
	}
	StageDraw(m_player[j].GetPlayerPosition());
	m_goal->Update();
	m_goal->Draw();
}

void SceneGame::PlayerFinalize(int j) {
	for (int i = WAKKA - 1; i >= 0; i--) 
	{
		m_wakka[j][i].Finalize();
	}
	m_player[j].Finalize();
}

void SceneGame::PlayerFinalize() {
	delete[] m_player;
}

void SceneGame::WakkaInitialize() {
	m_wakka = new Wakka*[2];
	m_wakka[0] = new Wakka[WAKKA];
	m_wakka[1] = new Wakka[WAKKA];
	
}

void SceneGame::WakkaFinalize() {
	delete m_wakka[1];
	delete m_wakka[0];
	delete[] m_wakka;
}

void SceneGame::StageInitialize() {
	m_stage = new Stage;
	m_stageWall = new Stage;
	//m_stageCurve = new Stage;
	m_stage->Initialize(0);
	m_stageWall->Initialize(1);
	//m_stageCurve->Initialize(2);
	for (int i = 0; i < STAGE; i++)
	{
		m_stageInfo[i][0] = (D3DXVECTOR3(0.0f, -0.4f, i * 10.0f));
		m_stageInfo[i][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_stageInfo[i][2] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
	for (int i = 0; i < STAGE * 2; i += 2)
	{
		m_stageWallInfo[i][0] = D3DXVECTOR3(1.25f, -0.4f, i * 5.0f);
		m_stageWallInfo[i][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_stageWallInfo[i][2] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_stageWallInfo[i + 1][0] = D3DXVECTOR3(-1.25f, -0.4f, i * 5.0f);
		m_stageWallInfo[i + 1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_stageWallInfo[i + 1][2] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
}

void SceneGame::StageDraw(D3DXVECTOR3 pos) {
	for (int i = 0; i < STAGE; i++) {
		if (fabs(pos.y - m_stageInfo[i][0].y) < 50.0f || fabs(pos.z - m_stageInfo[i][0].z) < 50.0f || fabs(pos.x - m_stageInfo[i][0].x) < 50.0f)
		{
			m_stage->SetPosition(m_stageInfo[i][0]);
			m_stage->Update();
			m_stage->Draw();
		}
	}
	for (int i = 0; i < STAGE * 2; i++) {
		if (fabs(pos.y - m_stageWallInfo[i][0].y) < 50.0f || fabs(pos.z - m_stageWallInfo[i][0].z) < 50.0f || fabs(pos.x - m_stageWallInfo[i][0].x) < 50.0f)
		{
			m_stageWall->SetPosition(m_stageWallInfo[i][0]);
			m_stageWall->Update();
			m_stageWall->Draw();
		}
	}
}

void SceneGame::StageFinalize() {
	//m_stageCurve->Finalize();
	m_stageWall->Finalize();
	m_stage->Finalize();
	//delete m_stageCurve;
	delete m_stageWall;
	delete m_stage;
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
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	// プロジェクショントランスフォーム（射影変換）
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	
	SetPlayerPosZ(m_player[a].GetPlayerPosition().z);
	Camera_Update();
	SetCamera();

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
	ColP2S();
}

void SceneGame::ColP2O() {
	/*最初に設定してある障害物との当たり判定*/
	for (int i = 0; i < OBSTACLE_NUM; i++) 
	{
		if (m_pObstacle1[i] != nullptr) 
		{
			if (m_pObstacle1[i]->IsEnable()) 
			{
				if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_pObstacle1[i]->GetOBB(), *m_pObstacle1[i]->GetMatrix())) 
				{
					m_pObstacle1[i]->Hit();
					m_player[0].Hit();
					MyOutputDebugString("P1ブツカッタヨ！！\n");
				}
			}
		}
	}
	for (int i = 0; i < OBSTACLE_NUM; i++) 
	{
		if (m_pObstacle2[i] != nullptr) 
		{
			if (m_pObstacle2[i]->IsEnable()) 
			{
				if (Collision::CheckCollision(m_player[1].GetOBB(), *m_player[1].GetMatrix(), m_pObstacle2[i]->GetOBB(), *m_pObstacle2[i]->GetMatrix()))
				{
					m_pObstacle2[i]->Hit();
					m_player[1].Hit();
					MyOutputDebugString("P2ブツカッタヨ！！\n");
				}
			}
		}
	}

	/*後から生成された障害物の当たり判定*/
	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++) 
	{
		if (m_1.createdObst[i] != nullptr) 
		{
			if (m_1.createdObst[i]->IsEnable())
			{
				if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_1.createdObst[i]->GetOBB(), *m_1.createdObst[i]->GetMatrix()))
				{
					m_1.createdObst[i]->Hit();
					m_player[0].Hit();
					MyOutputDebugString("P1ブツカッタヨ！！\n");
				}
			}
		}
	}
	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
	{
		if (m_2.createdObst[i] != nullptr) 
		{
			if (m_2.createdObst[i]->IsEnable()) 
			{
				if (Collision::CheckCollision(m_player[1].GetOBB(), *m_player[1].GetMatrix(), m_2.createdObst[i]->GetOBB(), *m_2.createdObst[i]->GetMatrix()))
				{
					m_2.createdObst[i]->Hit();
					m_player[1].Hit();
					MyOutputDebugString("P2ブツカッタヨ！！\n");
				}
			}
		}
	}
}

void SceneGame::ColW2O() {
	/*わっかと初期障害物の当たり判定（絶対最適化できるゾ）*/
	for (int i = 0; i < OBSTACLE_NUM; i++) 
	{
		if (m_pObstacle1[i] != nullptr) 
		{
			if (m_pObstacle1[i]->IsEnable()) 
			{
				for (int j = 0; j < 5; j++) 
				{
					if (m_wakka[0][j].IsShoot()) 
					{
						if (Collision::CheckCollision(m_wakka[0][j].GetOBB(), *m_wakka[0][j].GetMatrix(), m_pObstacle1[i]->GetOBB(), *m_pObstacle1[i]->GetMatrix()))
						{
							m_wakka[0][j].Hit();
							if (m_pObstacle1[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
							{
								m_pObstacle1[i]->Hit();
							}
							else if (m_pObstacle1[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
							{
								m_pObstacle1[i]->Hit();
							}
							else if (m_pObstacle1[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
							{
								m_pObstacle1[i]->Hit();
							}
							else if (m_pObstacle1[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
							{
								m_pObstacle1[i]->Hit();
							}
							else if (m_pObstacle1[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
							{
								m_pObstacle1[i]->Hit();
							}
							if (!m_player[0].GetCoolTime().bCoolTime)
							{
								if (m_wakka[0][j].GetElem() == SAND)
								{
									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									CreateSandStorm(pos, 0);
								}
								else if (m_wakka[0][j].GetElem() == SOIL)
								{
									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									CreatePitfalls(pos, 0);
								}
								m_player[0].StartCoolTime();
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < OBSTACLE_NUM; i++) 
	{
		if (m_pObstacle2[i] != nullptr) 
		{
			if (m_pObstacle2[i]->IsEnable()) 
			{
				for (int j = 0; j < 5; j++) 
				{
					if (m_wakka[1][j].IsShoot()) 
					{
						if (Collision::CheckCollision(m_wakka[1][j].GetOBB(), *m_wakka[1][j].GetMatrix(), m_pObstacle2[i]->GetOBB(), *m_pObstacle2[i]->GetMatrix()))
						{
							m_wakka[1][j].Hit();
							if (m_pObstacle2[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
							{
								m_pObstacle2[i]->Hit();
							}
							else if (m_pObstacle2[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
							{
								m_pObstacle2[i]->Hit();
							}
							else if (m_pObstacle2[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
							{
								m_pObstacle2[i]->Hit();
							}
							else if (m_pObstacle2[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
							{
								m_pObstacle2[i]->Hit();
							}
							else if (m_pObstacle2[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
							{
								m_pObstacle2[i]->Hit();
							}
							if (!m_player[1].GetCoolTime().bCoolTime)
							{
								if (m_wakka[1][j].GetElem() == SAND)
								{
									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									CreateSandStorm(pos, 1);
								}
								else if (m_wakka[1][j].GetElem() == SOIL)
								{
									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									CreatePitfalls(pos, 1);
								}
								m_player[1].StartCoolTime();
							}
						}
					}
				}
			}
		}
	}

	/*わっかと生成された障害物の当たり判定（上に同じ）*/
	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
	{
		if (m_1.createdObst[i] != nullptr)
		{
			if (m_1.createdObst[i]->IsEnable())
			{
				for (int j = 0; j < 5; j++)
				{
					if (m_wakka[0][j].IsShoot())
					{
						if (Collision::CheckCollision(m_wakka[0][j].GetOBB(), *m_wakka[0][j].GetMatrix(), m_1.createdObst[i]->GetOBB(), *m_1.createdObst[i]->GetMatrix()))
						{
							m_wakka[0][j].Hit();
							if (m_1.createdObst[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
							{
								m_1.createdObst[i]->Hit();
							}
							else if (m_1.createdObst[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
							{
								m_1.createdObst[i]->Hit();
							}
							else if (m_1.createdObst[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
							{
								m_1.createdObst[i]->Hit();
							}
							else if (m_1.createdObst[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
							{
								m_1.createdObst[i]->Hit();
							}
							else if (m_1.createdObst[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
							{
								m_1.createdObst[i]->Hit();
							}
							if (!m_player[0].GetCoolTime().bCoolTime)
							{
								if (m_wakka[0][j].GetElem() == SAND)
								{
									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									CreateSandStorm(pos, 0);
								}
								else if (m_wakka[0][j].GetElem() == SOIL)
								{
									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									CreatePitfalls(pos, 0);
								}
								m_player[0].StartCoolTime();
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
	{
		if (m_2.createdObst[i] != nullptr)
		{
			if (m_2.createdObst[i]->IsEnable())
			{
				for (int j = 0; j < 5; j++)
				{
					if (m_wakka[1][j].IsShoot())
					{
						if (Collision::CheckCollision(m_wakka[1][j].GetOBB(), *m_wakka[1][j].GetMatrix(), m_2.createdObst[i]->GetOBB(), *m_2.createdObst[i]->GetMatrix()))
						{
							m_wakka[1][j].Hit();
							if (m_2.createdObst[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
							{
								m_2.createdObst[i]->Hit();
							}
							else if (m_2.createdObst[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
							{
								m_2.createdObst[i]->Hit();
							}
							else if (m_2.createdObst[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
							{
								m_2.createdObst[i]->Hit();
							}
							else if (m_2.createdObst[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
							{
								m_2.createdObst[i]->Hit();
							}
							else if (m_2.createdObst[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
							{
								m_2.createdObst[i]->Hit();
							}
							if (!m_player[1].GetCoolTime().bCoolTime)
							{
								if (m_wakka[1][j].GetElem() == SAND)
								{
									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									CreateSandStorm(pos, 1);
								}
								else if (m_wakka[1][j].GetElem() == SOIL)
								{
									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
									float pos3 = pos1.z - pos2.z;
									pos.z -= pos3;
									pos.z += 3.0f;
									pos.z -= m_player[1].GetPlayerPosition().z - m_player[0].GetPlayerPosition().z;
									CreatePitfalls(pos, 1);
								}
								m_player[1].StartCoolTime();
							}
						}
					}
				}
			}
		}
	}
}

void SceneGame::ColP2S() {
	D3DXVECTOR3 pos = m_player[0].GetPlayerPosition();
	/*当たり判定必要なステージオブジェクトの数だけ繰り返すのだ*/
	for (int i = 0; i < STAGE * 2; i++) {
		/*当たり判定とる範囲はできる限り小さくしてみた！ キラッとプリ☆チャンはいいぞ*/
		if (fabs(pos.y - m_stageInfo[i][0].y) < 3.0f || fabs(pos.z - m_stageInfo[i][0].z) < 3.0f || fabs(pos.x - m_stageInfo[i][0].x) < 3.0f)
		{
			D3DXMATRIX mat;
			D3DXMATRIXA16 matTranslation, matRotation, matScale;
			D3DXMatrixIdentity(&mat);
			D3DXMatrixIdentity(&matTranslation);
			D3DXMatrixIdentity(&matRotation);
			D3DXMatrixIdentity(&matScale);
			D3DXMatrixTranslation(&matTranslation, m_stageWallInfo[i][0].x, m_stageWallInfo[i][0].y, m_stageWallInfo[i][0].z);
			D3DXMatrixRotationYawPitchRoll(&matRotation, m_stageWallInfo[i][1].y, m_stageWallInfo[i][1].x, m_stageWallInfo[i][1].z);
			D3DXMatrixScaling(&matScale, m_stageWallInfo[i][2].x, m_stageWallInfo[i][2].y, m_stageWallInfo[i][2].z);
			mat = matScale * matRotation * matTranslation;
			if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_stageWall->GetOBB(), mat))
			{
				m_player[0].Hit();
				m_player[0].HitWall();
			}
		}
		
	}
}

void SceneGame::ObstacleInitialize() {
	for (int i = (OBSTACLE_NUM / 5) * 0; i < (OBSTACLE_NUM / 5) * 1; i++)
	{
		m_pObstacle1[i] = new Fire;
		m_pObstacle1[i]->Initialize();
		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 0; i < (OBSTACLE_NUM / 5) * 1; i++)
	{
		m_pObstacle2[i] = new Fire;
		m_pObstacle2[i]->Initialize();
		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 1; i < (OBSTACLE_NUM / 5) * 2; i++)
	{
		m_pObstacle1[i] = new Tree;
		m_pObstacle1[i]->Initialize();
		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 1; i < (OBSTACLE_NUM / 5) * 2; i++)
	{
		m_pObstacle2[i] = new Tree;
		m_pObstacle2[i]->Initialize();
		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 2; i < (OBSTACLE_NUM / 5) * 3; i++)
	{
		m_pObstacle1[i] = new DriftWood;
		m_pObstacle1[i]->Initialize();
		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 2; i < (OBSTACLE_NUM / 5) * 3; i++)
	{
		m_pObstacle2[i] = new DriftWood;
		m_pObstacle2[i]->Initialize();
		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 3; i < (OBSTACLE_NUM / 5) * 4; i++)
	{
		m_pObstacle1[i] = new SandStorm;
		m_pObstacle1[i]->Initialize();
		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 3; i < (OBSTACLE_NUM / 5) * 4; i++)
	{
		m_pObstacle2[i] = new SandStorm;
		m_pObstacle2[i]->Initialize();
		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 4; i < (OBSTACLE_NUM / 5) * 5; i++)
	{
		m_pObstacle1[i] = new PitFall;
		m_pObstacle1[i]->Initialize();
		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = (OBSTACLE_NUM / 5) * 4; i < (OBSTACLE_NUM / 5) * 5; i++)
	{
		m_pObstacle2[i] = new PitFall;
		m_pObstacle2[i]->Initialize();
		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
	}

	for (int i = 0; i < CREATED_OBSTACLE_NUM / 2; i++) 
	{
		m_1.createdObst[i] = new SandStorm;
		m_1.createdObst[i]->Initialize();
		m_1.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
	}

	for (int i = CREATED_OBSTACLE_NUM / 2; i < CREATED_OBSTACLE_NUM; i++)
	{
		m_1.createdObst[i] = new PitFall;
		m_1.createdObst[i]->Initialize();
		m_1.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
	}

	for (int i = 0; i < CREATED_OBSTACLE_NUM / 2; i++)
	{
		m_2.createdObst[i] = new SandStorm;
		m_2.createdObst[i]->Initialize();
		m_2.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
	}

	for (int i = CREATED_OBSTACLE_NUM / 2; i < CREATED_OBSTACLE_NUM; i++)
	{
		m_2.createdObst[i] = new PitFall;
		m_2.createdObst[i]->Initialize();
		m_2.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
	}

	m_1.pitFallCounter = 10;
	m_1.sandStormCounter = 0;
	m_2.pitFallCounter = 10;
	m_2.sandStormCounter = 0;
	/*for (int i = 5; i < 10; i++) {
		m_pObstacle1[i] = new SandStorm;
		m_pObstacle1[i]->Initialize();
	}

	for (int i = 15; i < OBSTACLE_NUM; i++) {
		m_pObstacle1[i] = new SandStorm;
		m_pObstacle1[i]->Initialize();
	}*/
}

void SceneGame::ObstacleUpdate() {
	D3DXVECTOR3 p1Pos = m_player[0].GetPlayerPosition();
	D3DXVECTOR3 p2Pos = m_player[1].GetPlayerPosition();
	for (int i = 0; i < OBSTACLE_NUM; i++) 
	{
		m_pObstacle1[i]->SetPlayerPos(p1Pos);
		m_pObstacle1[i]->Update();
		m_pObstacle2[i]->SetPlayerPos(p2Pos);
		m_pObstacle2[i]->Update();
	}
	for (int i = 0; i < CREATED_OBSTACLE_NUM ; i++)
	{
		m_1.createdObst[i]->SetPlayerPos(p1Pos);
		m_1.createdObst[i]->Update();
		m_2.createdObst[i]->SetPlayerPos(p2Pos);
		m_2.createdObst[i]->Update();
	}
}

void SceneGame::ObstacleDraw(int n) {
	if (n == 0) 
	{
		for (int i = 0; i < OBSTACLE_NUM; i++)
		{
			if (m_pObstacle1[i]->IsEnable())
			{
				m_pObstacle1[i]->Draw();
			}
		}
		for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
		{
			if (m_1.createdObst[i]->IsEnable())
			{
				m_1.createdObst[i]->Draw();
			}
		}
	}
	else 
	{
		for (int i = 0; i < OBSTACLE_NUM; i++)
		{
			if (m_pObstacle2[i]->IsEnable())
			{
				m_pObstacle2[i]->Draw();
			}
		}
		for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
		{
			if (m_2.createdObst[i]->IsEnable())
			{
				m_2.createdObst[i]->Draw();
			}
		}
	}
}

void SceneGame::ObstacleFinalize() {

	for (int i = CREATED_OBSTACLE_NUM - 1; i >= 0; i--) {
		m_2.createdObst[i]->Finalize();
		delete m_2.createdObst[i];
	}

	for (int i = CREATED_OBSTACLE_NUM - 1; i >= 0; i--) {
		m_1.createdObst[i]->Finalize();
		delete m_1.createdObst[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 5 - 1; i >= (OBSTACLE_NUM / 5) * 4; i--)
	{
		m_pObstacle2[i]->Finalize();
		delete m_pObstacle2[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 5 - 1; i >= (OBSTACLE_NUM / 5) * 4; i--)
	{
		m_pObstacle1[i]->Finalize();
		delete m_pObstacle1[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 4 - 1; i >= (OBSTACLE_NUM / 5) * 3; i--)
	{
		m_pObstacle2[i]->Finalize();
		delete m_pObstacle2[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 4 - 1; i >= (OBSTACLE_NUM / 5) * 3; i--)
	{
		m_pObstacle1[i]->Finalize();
		delete m_pObstacle1[i];
	}
	
	for (int i = (OBSTACLE_NUM / 5) * 3 - 1; i >= (OBSTACLE_NUM / 5) * 2; i--)
	{
		m_pObstacle2[i]->Finalize();
		delete m_pObstacle2[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 3 - 1; i >= (OBSTACLE_NUM / 5) * 2; i--)
	{
		m_pObstacle1[i]->Finalize();
		delete m_pObstacle1[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 2 - 1; i >= (OBSTACLE_NUM / 5) * 1; i--)
	{
		m_pObstacle2[i]->Finalize();
		delete m_pObstacle2[i];
	}
	
	for (int i = (OBSTACLE_NUM / 5) * 2 - 1; i >= (OBSTACLE_NUM / 5) * 1; i--)
	{
		m_pObstacle1[i]->Finalize();
		delete m_pObstacle1[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 1 - 1; i >= (OBSTACLE_NUM / 5) * 0; i--)
	{
		m_pObstacle2[i]->Finalize();
		delete m_pObstacle2[i];
	}

	for (int i = (OBSTACLE_NUM / 5) * 1 - 1; i >= (OBSTACLE_NUM / 5) * 0; i--)
	{
		m_pObstacle1[i]->Finalize();
		delete m_pObstacle1[i];
	}
}

void SceneGame::CreateSandStorm(D3DXVECTOR3 pos, int n) {
	if (n == 0) 
	{
		if (m_2.sandStormCounter >= CREATED_OBSTACLE_NUM / 2) {
			m_2.sandStormCounter = 0;
		}
		m_2.createdObst[m_2.sandStormCounter]->Reset();
		m_2.createdObst[m_2.sandStormCounter]->SetPlayerPos(m_player[1].GetPlayerPosition());
		m_2.createdObst[m_2.sandStormCounter++]->SetPosition(pos);

	}
	else 
	{
		if (m_1.sandStormCounter >= CREATED_OBSTACLE_NUM / 2) {
			m_1.sandStormCounter = 0;
		}
		m_1.createdObst[m_1.sandStormCounter]->Reset();
		m_1.createdObst[m_1.sandStormCounter]->SetPlayerPos(m_player[1].GetPlayerPosition());
		m_1.createdObst[m_1.sandStormCounter++]->SetPosition(pos);
	}
}

void SceneGame::CreatePitfalls(D3DXVECTOR3 pos, int n) {
	if (n == 0)
	{
		if (m_2.pitFallCounter >= CREATED_OBSTACLE_NUM) {
			m_2.pitFallCounter = 10;
		}
		m_2.createdObst[m_2.pitFallCounter]->Reset();
		m_2.createdObst[m_2.pitFallCounter]->SetPlayerPos(m_player[0].GetPlayerPosition());
		m_2.createdObst[m_2.pitFallCounter++]->SetPosition(pos);
	}
	else
	{
		if (m_1.pitFallCounter >= CREATED_OBSTACLE_NUM) {
			m_1.pitFallCounter = 10;
		}
		m_1.createdObst[m_1.pitFallCounter]->Reset();
		m_1.createdObst[m_1.pitFallCounter]->SetPlayerPos(m_player[0].GetPlayerPosition());
		m_1.createdObst[m_1.pitFallCounter++]->SetPosition(pos);
	}
}