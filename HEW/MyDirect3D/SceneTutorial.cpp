//#define _CRT_SECURE_NO_WARNINGS
//#include "SceneTutorial.h"
//#include "Input.h"
//#include "Joycon.h"
//#include "Wakka.h"
//#include "camera.h"
//#include "Player.h"
//#include "Stage.h"
//#include "main.h"
//#include "Collision.h"
//#include "Utility.h"
//#include "DriftWood.h"
//#include "SandStorm.h"
//#include <time.h>
//#include "Fire.h"
//#include "Tree.h"
//#include "PitFall.h"
//#include "Cameran.h"
//#include "TextBack.h"
//#include "Text.h"
//
//static int count = 0;
//static bool a = false;
//static int count2 = 0;
//static bool b = false;
//static int tcount = 0;
//
////static const int OBSTACLE_NUM = 50;
////static const int CREATED_OBSTACLE_NUM = 20;
//
//SceneTutorial::~SceneTutorial() {
//
//}
//
//
//void SceneTutorial::Initialize(){
//	TextInitialize();
//	for (int i = 0; i < TEXT; i++)
//	{
//		TextInitialize(i);
//	}
//	PlayerInitialize();
//	WakkaInitialize();
//	PlayerInitialize(0);
//	PlayerInitialize(1);
//	StageInitialize();
//	//ObstacleInitialize();
//	CameraInitialize();
//	m_d3dDevice = GetDevice();
//}
//
//void SceneTutorial::Update() {
//	TextUpdate();
//	PlayerUpdate(0);
//	PlayerUpdate(1);
//	WakkaUpdate();
//	CollisionUpdate();
//}
//
//void SceneTutorial::Draw() {
//	PlayerDraw(0);
//	//ObstacleDraw(0);
//	PlayerDraw(1);
//	//ObstacleDraw(1);
//	TextDraw();  //レンダリング
//}
//
//void SceneTutorial::Finalize() {
//	CameraFinalize();
//	//ObstacleFinalize();
//	for (int i = 0; i < TEXT; i++)
//	{
//		TextFinalize(i);
//	}
//	StageFinalize();
//	PlayerFinalize(1);
//	PlayerFinalize(0);
//	WakkaFinalize();
//	PlayerFinalize();
//}
//
//void SceneTutorial::PlayerInitialize() {
//	m_player = new Player[PLAYER];
//}
//
//void SceneTutorial::PlayerInitialize(int j) {
//	m_player[j].Initialize(j);
//}
//
//void SceneTutorial::PlayerUpdate(int j) {
//	m_player[j].Update();
//	if (a) {
//		count++;
//		if (count > 20) {
//			a = false;
//			count = 0;
//		}
//	}
//	if (b) {
//		count2++;
//		if (count2 > 20) {
//			b = false;
//			count2 = 0;
//		}
//	}
//	if (j == 0) {
//		if (Input::TriggerKey(DIK_Q) || g_diJoyState2[1] & BUTTON_M) {
//			if (!a) {
//				m_wakka[j].Change(1);
//				a = true;
//				if (tcount == 3) {
//					clear1 = true;
//				}
//
//			}
//
//		}
//		if (Input::TriggerKey(DIK_E) || g_diJoyState2[1] & BUTTON_R) {
//			if (!a)
//			{
//				m_wakka[j].Change(0);
//				a = true;
//				if (tcount == 3) {
//					clear1 = true;
//				}
//			}
//		}
//			if (Input::TriggerKey(DIK_W) || g_diJoyState2[1] & BUTTON_START) {
//				m_wakka[j].Shoot();
//				if (tcount == 2){
//					clear1 = true;
//				}
//			}
//	}
//	else {
//		if (Input::TriggerKey(DIK_U) || g_diJoyState2[3] & BUTTON_M) {
//			if (!b)
//			{
//				m_wakka[j].Change(1);
//				b = true;
//				if (tcount == 3) {
//					clear2 = true;
//				}
//			}
//		}
//		if (Input::TriggerKey(DIK_O) || g_diJoyState2[3] & BUTTON_R) {
//			if (!b)
//			{
//				m_wakka[j].Change(1);
//				b = true;
//				if (tcount == 3) {
//					clear2 = true;
//				}
//			}
//		}
//		if (Input::TriggerKey(DIK_I) || g_diJoyState2[3] & BUTTON_START) {
//			m_wakka[j].Shoot();
//			if (tcount == 2)
//			{
//				clear2 = true;
//			}
//		}
//		}
//	}
//
//
//	/*if (Input::TriggerKey(DIK_C)) {
//	m_wakka[j].Hit();
//	}*/
//
//void SceneTutorial::PlayerDraw(int j) {
//	Rendering(j);
//
//	m_player[j].Draw();
//
//	m_wakka[j].Draw();
//	StageDraw(m_player[j].GetPlayerPosition());
//}
//
//void SceneTutorial::PlayerFinalize(int j) {
//	m_player[j].Finalize();
//}
//
//void SceneTutorial::PlayerFinalize() {
//	delete[] m_player;
//}
//
//void SceneTutorial::WakkaInitialize() {
//	m_wakka = new WakkaManager[2];
//	m_wakka[0].Initialize();
//	m_wakka[1].Initialize();
//}
//
//void SceneTutorial::WakkaUpdate() {
//	for (int i = 0; i < WAKKA; i++)
//	{
//		m_wakka[i].SetPlayerPosition(m_player[i].GetPlayerPosition());
//		m_wakka[i].SetPlayerAngle(m_player[i].GetPlayerAngle());
//		m_wakka[i].Update();
//	}
//}
//
//
//void SceneTutorial::WakkaFinalize() {
//	m_wakka[1].Finalize();
//	m_wakka[0].Finalize();
//	delete[] m_wakka;
//}
//
//void SceneTutorial::StageInitialize() {
//	m_stage = new Stage;
//	m_stageWall = new Stage;
//	m_stage->Initialize(0);
//	m_stageWall->Initialize(1);
//	for (int i = 0; i < STAGE; i++)
//	{
//		m_stageInfo[i][0] = (D3DXVECTOR3(0.0f, -0.4f, i * 10.0f));
//		m_stageInfo[i][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_stageInfo[i][2] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//	}
//	for (int i = 0; i < STAGE * 2; i += 2)
//	{
//		m_stageWallInfo[i][0] = D3DXVECTOR3(1.25f, -0.4f, i * 5.0f);
//		m_stageWallInfo[i][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_stageWallInfo[i][2] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//		m_stageWallInfo[i + 1][0] = D3DXVECTOR3(-1.25f, -0.4f, i * 5.0f);
//		m_stageWallInfo[i + 1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_stageWallInfo[i + 1][2] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//	}
//}
//
//void SceneTutorial::StageDraw(D3DXVECTOR3 pos) {
//	for (int i = 0; i < STAGE; i++) {
//		if (fabs(pos.y - m_stageInfo[i][0].y) < 50.0f || fabs(pos.z - m_stageInfo[i][0].z) < 50.0f || fabs(pos.x - m_stageInfo[i][0].x) < 50.0f)
//		{
//			m_stage->SetPosition(m_stageInfo[i][0]);
//			m_stage->Update();
//			m_stage->Draw();
//		}
//	}
//	for (int i = 0; i < STAGE * 2; i++) {
//		if (fabs(pos.y - m_stageWallInfo[i][0].y) < 50.0f || fabs(pos.z - m_stageWallInfo[i][0].z) < 50.0f || fabs(pos.x - m_stageWallInfo[i][0].x) < 50.0f)
//		{
//			m_stageWall->SetPosition(m_stageWallInfo[i][0]);
//			m_stageWall->Update();
//			m_stageWall->Draw();
//		}
//	}
//}
//
//void SceneTutorial::StageFinalize() {
//	m_stageWall->Finalize();
//	m_stage->Finalize();
//	delete m_stageWall;
//	delete m_stage;
//}
//
//void SceneTutorial::ObstacleInitialize() {
//	for (int i = (OBSTACLE_NUM / 5) * 0; i < (OBSTACLE_NUM / 5) * 1; i++)
//	{
//		m_pObstacle1[i] = new Fire;
//		m_pObstacle1[i]->Initialize();
//		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 0; i < (OBSTACLE_NUM / 5) * 1; i++)
//	{
//		m_pObstacle2[i] = new Fire;
//		m_pObstacle2[i]->Initialize();
//		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 1; i < (OBSTACLE_NUM / 5) * 2; i++)
//	{
//		m_pObstacle1[i] = new Tree;
//		m_pObstacle1[i]->Initialize();
//		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 1; i < (OBSTACLE_NUM / 5) * 2; i++)
//	{
//		m_pObstacle2[i] = new Tree;
//		m_pObstacle2[i]->Initialize();
//		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 2; i < (OBSTACLE_NUM / 5) * 3; i++)
//	{
//		m_pObstacle1[i] = new DriftWood;
//		m_pObstacle1[i]->Initialize();
//		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 2; i < (OBSTACLE_NUM / 5) * 3; i++)
//	{
//		m_pObstacle2[i] = new DriftWood;
//		m_pObstacle2[i]->Initialize();
//		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 3; i < (OBSTACLE_NUM / 5) * 4; i++)
//	{
//		m_pObstacle1[i] = new SandStorm;
//		m_pObstacle1[i]->Initialize();
//		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 3; i < (OBSTACLE_NUM / 5) * 4; i++)
//	{
//		m_pObstacle2[i] = new SandStorm;
//		m_pObstacle2[i]->Initialize();
//		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 4; i < (OBSTACLE_NUM / 5) * 5; i++)
//	{
//		m_pObstacle1[i] = new PitFall;
//		m_pObstacle1[i]->Initialize();
//		m_pObstacle1[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 4; i < (OBSTACLE_NUM / 5) * 5; i++)
//	{
//		m_pObstacle2[i] = new PitFall;
//		m_pObstacle2[i]->Initialize();
//		m_pObstacle2[i]->SetPosition(D3DXVECTOR3(float(rand() % 3) * 0.5f - 0.5f, 0.0f, i * 5.0f + 5.0f));
//	}
//
//	for (int i = 0; i < CREATED_OBSTACLE_NUM / 2; i++)
//	{
//		m_1.createdObst[i] = new SandStorm;
//		m_1.createdObst[i]->Initialize();
//		m_1.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
//	}
//
//	for (int i = CREATED_OBSTACLE_NUM / 2; i < CREATED_OBSTACLE_NUM; i++)
//	{
//		m_1.createdObst[i] = new PitFall;
//		m_1.createdObst[i]->Initialize();
//		m_1.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
//	}
//
//	for (int i = 0; i < CREATED_OBSTACLE_NUM / 2; i++)
//	{
//		m_2.createdObst[i] = new SandStorm;
//		m_2.createdObst[i]->Initialize();
//		m_2.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
//	}
//
//	for (int i = CREATED_OBSTACLE_NUM / 2; i < CREATED_OBSTACLE_NUM; i++)
//	{
//		m_2.createdObst[i] = new PitFall;
//		m_2.createdObst[i]->Initialize();
//		m_2.createdObst[i]->SetPosition(D3DXVECTOR3(0.0f, -100.0f, 0.0f));
//	}
//
//	m_1.pitFallCounter = 10;
//	m_1.sandStormCounter = 0;
//	m_2.pitFallCounter = 10;
//	m_2.sandStormCounter = 0;
//}
//
//void SceneTutorial::ObstacleUpdate() {
//	D3DXVECTOR3 p1Pos = m_player[0].GetPlayerPosition();
//	D3DXVECTOR3 p2Pos = m_player[1].GetPlayerPosition();
//	for (int i = 0; i < OBSTACLE_NUM; i++)
//	{
//		if (m_pObstacle1[i]->IsEnable())
//		{
//			m_pObstacle1[i]->SetPlayerPos(p1Pos);
//			m_pObstacle1[i]->Update();
//		}
//		if (m_pObstacle2[i]->IsEnable())
//		{
//			m_pObstacle2[i]->SetPlayerPos(p2Pos);
//			m_pObstacle2[i]->Update();
//		}
//	}
//	for (int i = 0; i < CREATED_OBSTACLE_NUM ; i++)
//	{
//		m_1.createdObst[i]->SetPlayerPos(p1Pos);
//		m_1.createdObst[i]->Update();
//		m_2.createdObst[i]->SetPlayerPos(p2Pos);
//		m_2.createdObst[i]->Update();
//	}
//}
//
//void SceneTutorial::ObstacleDraw(int n) {
//	if (n == 0)
//	{
//		for (int i = 0; i < OBSTACLE_NUM; i++)
//		{
//			if (m_pObstacle1[i]->IsEnable())
//			{
//				m_pObstacle1[i]->Draw();
//			}
//		}
//		for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
//		{
//			if (m_1.createdObst[i]->IsEnable())
//			{
//				m_1.createdObst[i]->Draw();
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < OBSTACLE_NUM; i++)
//		{
//			if (m_pObstacle2[i]->IsEnable())
//			{
//				m_pObstacle2[i]->Draw();
//			}
//		}
//		for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
//		{
//			if (m_2.createdObst[i]->IsEnable())
//			{
//				m_2.createdObst[i]->Draw();
//			}
//		}
//	}
//}
//
//void SceneTutorial::ObstacleFinalize() {
//	for (int i = CREATED_OBSTACLE_NUM - 1; i >= 0; i--) {
//		m_2.createdObst[i]->Finalize();
//		delete m_2.createdObst[i];
//	}
//
//	for (int i = CREATED_OBSTACLE_NUM - 1; i >= 0; i--) {
//		m_1.createdObst[i]->Finalize();
//		delete m_1.createdObst[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 5 - 1; i >= (OBSTACLE_NUM / 5) * 4; i--)
//	{
//		m_pObstacle2[i]->Finalize();
//		delete m_pObstacle2[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 5 - 1; i >= (OBSTACLE_NUM / 5) * 4; i--)
//	{
//		m_pObstacle1[i]->Finalize();
//		delete m_pObstacle1[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 4 - 1; i >= (OBSTACLE_NUM / 5) * 3; i--)
//	{
//		m_pObstacle2[i]->Finalize();
//		delete m_pObstacle2[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 4 - 1; i >= (OBSTACLE_NUM / 5) * 3; i--)
//	{
//		m_pObstacle1[i]->Finalize();
//		delete m_pObstacle1[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 3 - 1; i >= (OBSTACLE_NUM / 5) * 2; i--)
//	{
//		m_pObstacle2[i]->Finalize();
//		delete m_pObstacle2[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 3 - 1; i >= (OBSTACLE_NUM / 5) * 2; i--)
//	{
//		m_pObstacle1[i]->Finalize();
//		delete m_pObstacle1[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 2 - 1; i >= (OBSTACLE_NUM / 5) * 1; i--)
//	{
//		m_pObstacle2[i]->Finalize();
//		delete m_pObstacle2[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 2 - 1; i >= (OBSTACLE_NUM / 5) * 1; i--)
//	{
//		m_pObstacle1[i]->Finalize();
//		delete m_pObstacle1[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 1 - 1; i >= (OBSTACLE_NUM / 5) * 0; i--)
//	{
//		m_pObstacle2[i]->Finalize();
//		delete m_pObstacle2[i];
//	}
//
//	for (int i = (OBSTACLE_NUM / 5) * 1 - 1; i >= (OBSTACLE_NUM / 5) * 0; i--)
//	{
//		m_pObstacle1[i]->Finalize();
//		delete m_pObstacle1[i];
//	}
//}
//
//void SceneTutorial::CreateSandStorm(D3DXVECTOR3 pos, int n) {
//	if (n == 0)
//	{
//		if (m_2.sandStormCounter >= CREATED_OBSTACLE_NUM / 2) {
//			m_2.sandStormCounter = 0;
//		}
//		m_2.createdObst[m_2.sandStormCounter]->Reset();
//		m_2.createdObst[m_2.sandStormCounter]->SetPlayerPos(m_player[1].GetPlayerPosition());
//		m_2.createdObst[m_2.sandStormCounter++]->SetPosition(pos);
//
//	}
//	else
//	{
//		if (m_1.sandStormCounter >= CREATED_OBSTACLE_NUM / 2) {
//			m_1.sandStormCounter = 0;
//		}
//		m_1.createdObst[m_1.sandStormCounter]->Reset();
//		m_1.createdObst[m_1.sandStormCounter]->SetPlayerPos(m_player[1].GetPlayerPosition());
//		m_1.createdObst[m_1.sandStormCounter++]->SetPosition(pos);
//	}
//}
//
//void SceneTutorial::CreatePitfalls(D3DXVECTOR3 pos, int n) {
//	if (n == 0)
//	{
//		if (m_2.pitFallCounter >= CREATED_OBSTACLE_NUM) {
//			m_2.pitFallCounter = 10;
//		}
//		m_2.createdObst[m_2.pitFallCounter]->Reset();
//		m_2.createdObst[m_2.pitFallCounter]->SetPlayerPos(m_player[0].GetPlayerPosition());
//		m_2.createdObst[m_2.pitFallCounter++]->SetPosition(pos);
//	}
//	else
//	{
//		if (m_1.pitFallCounter >= CREATED_OBSTACLE_NUM) {
//			m_1.pitFallCounter = 10;
//		}
//		m_1.createdObst[m_1.pitFallCounter]->Reset();
//		m_1.createdObst[m_1.pitFallCounter]->SetPlayerPos(m_player[0].GetPlayerPosition());
//		m_1.createdObst[m_1.pitFallCounter++]->SetPosition(pos);
//	}
//}
//
//void SceneTutorial::TextInitialize()
//{
//	m_textback = new TextBack;
//	m_textback->Initialize();
//
//	m_text = new Text[TEXT];
//
//	m_next = new Text;
//	m_next->NextInitialize();
//}
//
//void SceneTutorial::TextInitialize(int j) {
//	m_text[j].Initialize(j);
//}
//
//void SceneTutorial::TextUpdate()
//{
//	m_next->CheckInterval();
//
//	//このゲームのルールを説明するよ
//	if (tcount == 0)
//	{
//		if (m_next->GetbInterval() == false) {
//			ClearInit();
//		}
//	}
//	//移動
//	if (tcount == 1)
//	{
//		if (Input::GetKey(DIK_D) || Input::GetKey(DIK_A))	{
//			clear1 = true;
//		}
//		if (Input::GetKey(DIK_L) || Input::GetKey(DIK_J)) {
//			clear2 = true;
//		}
//
//		ClearFlag();
//		if (m_next->GetbInterval() == false && once) {
//			ClearInit();
//		}
//	}
//	//縦にふる
//	if (tcount == 2)
//	{
//		ClearFlag();
//		if (m_next->GetbInterval() == false && once) {
//			ClearInit();
//		}
//	}
//	//横にふる
//	if (tcount == 3)
//	{
//		ClearFlag();
//		if (m_next->GetbInterval() == false && once) {
//			ClearInit();
//		}
//	}
//	//わっかのガイドがでるよ
//	if (tcount == 4)
//	{
//		if (m_next->GetbInterval() == false) {
//			ClearInit();
//		}
//	}
//	//燃えてる障害物に青のわっか
//	if (tcount == 5)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once) 
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//流木に赤のわっか
//	if (tcount == 6)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once) 
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//すなあらしに青のわっか
//	if (tcount == 7)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once) 
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//落とし穴に黒のわっか
//	if (tcount == 8)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once)
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//じゃま緑
//	if (tcount == 9)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once)
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//じゃま黒
//	if (tcount == 10)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once) 
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//じゃま黄
//	if (tcount == 11)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once) 
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//アイテム説明
//	if (tcount == 12)
//	{
//		if (m_next->GetbInterval() == false) {
//			ClearInit();
//		}
//	}
//	//たい焼き
//	if (tcount == 13)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once) 
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//メロンパン
//	if (tcount == 14)
//	{
//		//ClearFlag();
//		//if (m_next->GetbInterval() == false && once) 
//		if (m_next->GetbInterval() == false)
//		{
//			ClearInit();
//		}
//	}
//	//先にゴールした方の勝ち
//	if (tcount == 15)
//	{
//		if (m_next->GetbInterval() == false) {
//			ClearInit();
//		}
//	}
//	//レーススタート
//	if (tcount == 16)
//	{
//		if (m_next->GetbInterval() == false) {
//			ClearInit();
//		}
//	}
//
//		m_textback->Update();
//		m_text[tcount].Update();
//		m_next->NextUpdate();
//		
//
//		/*if (tcount == 15)
//		{
//			smanager->ChangeSceneState();
//		}*/
//}
//
//void SceneTutorial::TextDraw()
//{
//	Rendering(2);
//
//	m_textback->Draw();
//	m_text[tcount].Draw();
//	if (m_next->IsEnable())
//	{
//		m_next->NextDraw();
//	}
//}
//
//void SceneTutorial::TextFinalize(int j)
//{
//	m_text[j].Finalize();
//}
//
//void SceneTutorial::TextFinalize()
//{
//	m_textback->Finalize();
//	delete m_textback;
//
//	delete[] m_text;
//
//	m_next->NextFinalize();
//	delete m_next;
//}
//
//void SceneTutorial::CameraInitialize() {
//	m_camera = new Cameran[3];
//
//	for (int i = 0; i < 2; i++)
//	{
//		m_camera[i].Initialize();
//	}
//
//	m_camera[2].TextCameraInitialize();
//	m_camera[2].SetPosR(m_textback->GetTextBackPos());
//}
//
//void SceneTutorial::CameraUpdate(int player) {
//	if (player != 2)
//	{
//		m_camera[player].SetPlayerPos(m_player[player].GetPlayerPosition());
//		m_camera[player].SetPlayerAngle(m_player[player].GetPlayerAngle());
//		m_camera[player].Update();
//		m_camera[player].SetCamera();
//	}
//	else
//	{
//		m_camera[player].SetPlayerPos(m_textback->GetTextBackPos());
//		m_camera[player].TextCameraUpdate();
//		m_camera[player].SetCamera();
//	}
//}
//
//void SceneTutorial::CameraFinalize() {
//	delete[] m_camera;
//}
//
//
//void SceneTutorial::Rendering(int a) {
//	D3DVIEWPORT9 viwePort;
//	if (a == 0) {
//		viwePort.X = 0;
//		viwePort.Y = 0;
//		viwePort.Width = 640;
//		viwePort.Height = 720;
//		viwePort.MaxZ = 1.0f;
//		viwePort.MinZ = 0.0f;
//		m_d3dDevice->SetViewport(&viwePort);
//	}
//	else if (a == 1){
//		viwePort.X = 640;
//		viwePort.Y = 0;
//		viwePort.Width = 640;
//		viwePort.Height = 720;
//		viwePort.MaxZ = 1.0f;
//		viwePort.MinZ = 0.0f;
//		m_d3dDevice->SetViewport(&viwePort);
//	}
//	else if (a == 2) {
//		viwePort.X = 350;
//		viwePort.Y = 10;
//		viwePort.Width = 570;
//		viwePort.Height = 200;
//		viwePort.MaxZ = 1.0f;
//		viwePort.MinZ = 0.0f;
//		m_d3dDevice->SetViewport(&viwePort);
//	}
//
//	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 225, 35), 1.0f, 0);
//	// プロジェクショントランスフォーム（射影変換）
//	D3DXMATRIXA16 matProj;
//	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
//	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
//
//	CameraUpdate(a);
//	
//
//	// ライトをあてる 白色で鏡面反射ありに設定
//	D3DXVECTOR3 vecDirection(1, -1, -1);
//	D3DLIGHT9 light;
//	ZeroMemory(&light, sizeof(D3DLIGHT9));
//	light.Type = D3DLIGHT_DIRECTIONAL;
//	light.Diffuse.r = 1.0f;
//	light.Diffuse.g = 1.0f;
//	light.Diffuse.b = 1.0f;
//	light.Specular.r = 1.0f;
//	light.Specular.g = 1.0f;
//	light.Specular.b = 1.0f;
//	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
//	light.Range = 200.0f;
//	m_d3dDevice->SetLight(0, &light);
//	m_d3dDevice->LightEnable(0, TRUE);
//
//}
//
//void SceneTutorial::SceneManagerInitialize()
//{
//	smanager = new SceneManager;
//}
//
//void SceneTutorial::SceneManagerFinalize()
//{
//	delete smanager;
//}
//
//void SceneTutorial::ClearFlag()
//{
//	if (once == false)
//	{
//		if (clear1 && clear2)
//		{
//			once = true;
//		}
//	}
//}
//
//void SceneTutorial::ClearInit()
//{
//			m_next->TrueChange();
//			if (Input::TriggerKey(DIK_B))
//			{
//				m_next->FalseChange();
//				m_next->StartInterval();
//				tcount++;
//				clear1 = false;
//				clear2 = false;
//				once = false;
//			}
//		
//}
//
//void SceneTutorial::CollisionUpdate() {
//	ColP2S();
//	ColP2O();
//}
//
//void SceneTutorial::ColP2S() {
//	D3DXVECTOR3 pos = m_player[0].GetPlayerPosition();
//	/*当たり判定必要なステージオブジェクトの数だけ繰り返すのだ*/
//	for (int i = 0; i < STAGE * 2; i++) {
//		/*当たり判定とる範囲はできる限り小さくしてみた！ キラッとプリ☆チャンはいいぞ*/
//		if (fabs(pos.y - m_stageInfo[i][0].y) < 3.0f || fabs(pos.z - m_stageInfo[i][0].z) < 3.0f || fabs(pos.x - m_stageInfo[i][0].x) < 3.0f)
//		{
//			D3DXMATRIX mat;
//			D3DXMATRIXA16 matTranslation, matRotation, matScale;
//			D3DXMatrixIdentity(&mat);
//			D3DXMatrixIdentity(&matTranslation);
//			D3DXMatrixIdentity(&matRotation);
//			D3DXMatrixIdentity(&matScale);
//			D3DXMatrixTranslation(&matTranslation, m_stageWallInfo[i][0].x, m_stageWallInfo[i][0].y, m_stageWallInfo[i][0].z);
//			D3DXMatrixRotationYawPitchRoll(&matRotation, m_stageWallInfo[i][1].y, m_stageWallInfo[i][1].x, m_stageWallInfo[i][1].z);
//			D3DXMatrixScaling(&matScale, m_stageWallInfo[i][2].x, m_stageWallInfo[i][2].y, m_stageWallInfo[i][2].z);
//			mat = matScale * matRotation * matTranslation;
//			if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_stageWall->GetOBB(), mat))
//			{
//				m_player[0].Hit();
//				m_player[0].HitWall();
//			}
//		}
//		
//	}
//}
//
//void SceneTutorial::ColP2O() {
//	/*最初に設定してある障害物との当たり判定*/
//	for (int i = 0; i < OBSTACLE_NUM; i++)
//	{
//		if (m_pObstacle1[i] != nullptr)
//		{
//			if (m_pObstacle1[i]->IsEnable())
//			{
//				if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_pObstacle1[i]->GetOBB(), *m_pObstacle1[i]->GetMatrix()))
//				{
//					m_pObstacle1[i]->Hit();
//					m_player[0].Hit();
//					MyOutputDebugString("P1ブツカッタヨ！！\n");
//				}
//			}
//		}
//	}
//	for (int i = 0; i < OBSTACLE_NUM; i++)
//	{
//		if (m_pObstacle2[i] != nullptr)
//		{
//			if (m_pObstacle2[i]->IsEnable())
//			{
//				if (Collision::CheckCollision(m_player[1].GetOBB(), *m_player[1].GetMatrix(), m_pObstacle2[i]->GetOBB(), *m_pObstacle2[i]->GetMatrix()))
//				{
//					m_pObstacle2[i]->Hit();
//					m_player[1].Hit();
//					MyOutputDebugString("P2ブツカッタヨ！！\n");
//				}
//			}
//		}
//	}
//
//	/*後から生成された障害物の当たり判定*/
//	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
//	{
//		if (m_1.createdObst[i] != nullptr)
//		{
//			if (m_1.createdObst[i]->IsEnable())
//			{
//				if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_1.createdObst[i]->GetOBB(), *m_1.createdObst[i]->GetMatrix()))
//				{
//					m_1.createdObst[i]->Hit();
//					m_player[0].Hit();
//					MyOutputDebugString("P1ブツカッタヨ！！\n");
//				}
//			}
//		}
//	}
//	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
//	{
//		if (m_2.createdObst[i] != nullptr)
//		{
//			if (m_2.createdObst[i]->IsEnable())
//			{
//				if (Collision::CheckCollision(m_player[1].GetOBB(), *m_player[1].GetMatrix(), m_2.createdObst[i]->GetOBB(), *m_2.createdObst[i]->GetMatrix()))
//				{
//					m_2.createdObst[i]->Hit();
//					m_player[1].Hit();
//					MyOutputDebugString("P2ブツカッタヨ！！\n");
//				}
//			}
//		}
//	}
//}
//
////void SceneTutorial::ColW2O() {
////	/*わっかと初期障害物の当たり判定（絶対最適化できるゾ）*/
////	for (int i = 0; i < OBSTACLE_NUM; i++) 
////	{
////		if (m_pObstacle1[i] != nullptr) 
////		{
////			if (m_pObstacle1[i]->IsEnable()) 
////			{
////				for (int j = 0; j < 5; j++) 
////				{
////					if (m_wakka[0][j].IsShoot()) 
////					{
////						if (Collision::CheckCollision(m_wakka[0][j].GetOBB(), *m_wakka[0][j].GetMatrix(), m_pObstacle1[i]->GetOBB(), *m_pObstacle1[i]->GetMatrix()))
////						{
////							m_wakka[0][j].Hit();
////							if (m_pObstacle1[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_pObstacle1[i]->Hit();
////								if (tcount == 6) {
////									clear1 = true;
////								}
////								
////							}
////							else if (m_pObstacle1[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_pObstacle1[i]->Hit();
////								if (tcount == 5) {
////									clear1 = true;
////								}
////							}
////							else if (m_pObstacle1[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_pObstacle1[i]->Hit();
////							}
////							else if (m_pObstacle1[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_pObstacle1[i]->Hit();
////								if (tcount == 7) {
////									clear1 = true;
////								}
////							}
////							else if (m_pObstacle1[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
////							{
////								m_pObstacle1[i]->Hit();
////								if (tcount == 8) {
////									clear1 = true;
////								}
////							}
////							if (!m_player[0].GetCoolTime().bCoolTime)
////							{
////								if (m_wakka[0][j].GetElem() == SAND)
////								{
////									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
////									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									CreateSandStorm(pos, 0);
////								}
////								else if (m_wakka[0][j].GetElem() == SOIL)
////								{
////									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
////									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									CreatePitfalls(pos, 0);
////								}
////								m_player[0].StartCoolTime();
////							}
////						}
////					}
////				}
////			}
////		}
////	}
////	for (int i = 0; i < OBSTACLE_NUM; i++) 
////	{
////		if (m_pObstacle2[i] != nullptr) 
////		{
////			if (m_pObstacle2[i]->IsEnable()) 
////			{
////				for (int j = 0; j < 5; j++) 
////				{
////					if (m_wakka[1][j].IsShoot()) 
////					{
////						if (Collision::CheckCollision(m_wakka[1][j].GetOBB(), *m_wakka[1][j].GetMatrix(), m_pObstacle2[i]->GetOBB(), *m_pObstacle2[i]->GetMatrix()))
////						{
////							m_wakka[1][j].Hit();
////							if (m_pObstacle2[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_pObstacle2[i]->Hit();
////								if (tcount == 6) {
////									clear2 = true;
////								}
////							}
////							else if (m_pObstacle2[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_pObstacle2[i]->Hit();
////								if (tcount == 5) {
////									clear2 = true;
////								}
////							}
////							else if (m_pObstacle2[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_pObstacle2[i]->Hit();
////							}
////							else if (m_pObstacle2[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_pObstacle2[i]->Hit();
////								if (tcount == 7) {
////									clear2 = true;
////								}
////							}
////							else if (m_pObstacle2[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
////							{
////								m_pObstacle2[i]->Hit();
////								if (tcount == 8) {
////									clear2 = true;
////								}
////							}
////							if (!m_player[1].GetCoolTime().bCoolTime)
////							{
////								if (m_wakka[1][j].GetElem() == SAND)
////								{
////									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
////									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									CreateSandStorm(pos, 1);
////								}
////								else if (m_wakka[1][j].GetElem() == SOIL)
////								{
////									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
////									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									CreatePitfalls(pos, 1);
////								}
////								m_player[1].StartCoolTime();
////							}
////						}
////					}
////				}
////			}
////		}
////	}
////
////	/*わっかと生成された障害物の当たり判定（上に同じ）*/
////	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
////	{
////		if (m_1.createdObst[i] != nullptr)
////		{
////			if (m_1.createdObst[i]->IsEnable())
////			{
////				for (int j = 0; j < 5; j++)
////				{
////					if (m_wakka[0][j].IsShoot())
////					{
////						if (Collision::CheckCollision(m_wakka[0][j].GetOBB(), *m_wakka[0][j].GetMatrix(), m_1.createdObst[i]->GetOBB(), *m_1.createdObst[i]->GetMatrix()))
////						{
////							m_wakka[0][j].Hit();
////							if (m_1.createdObst[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_1.createdObst[i]->Hit();
////							}
////							else if (m_1.createdObst[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_1.createdObst[i]->Hit();
////							}
////							else if (m_1.createdObst[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_1.createdObst[i]->Hit();
////							}
////							else if (m_1.createdObst[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_1.createdObst[i]->Hit();
////							}
////							else if (m_1.createdObst[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
////							{
////								m_1.createdObst[i]->Hit();
////							}
////							if (!m_player[0].GetCoolTime().bCoolTime)
////							{
////								if (m_wakka[0][j].GetElem() == SAND)
////								{
////									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
////									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									CreateSandStorm(pos, 0);
////								}
////								else if (m_wakka[0][j].GetElem() == SOIL)
////								{
////									D3DXVECTOR3 pos = m_wakka[0][j].GetPosition(0);
////									D3DXVECTOR3 pos1 = m_player[0].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[1].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									CreatePitfalls(pos, 0);
////								}
////								m_player[0].StartCoolTime();
////							}
////						}
////					}
////				}
////			}
////		}
////	}
////	for (int i = 0; i < CREATED_OBSTACLE_NUM; i++)
////	{
////		if (m_2.createdObst[i] != nullptr)
////		{
////			if (m_2.createdObst[i]->IsEnable())
////			{
////				for (int j = 0; j < 5; j++)
////				{
////					if (m_wakka[1][j].IsShoot())
////					{
////						if (Collision::CheckCollision(m_wakka[1][j].GetOBB(), *m_wakka[1][j].GetMatrix(), m_2.createdObst[i]->GetOBB(), *m_2.createdObst[i]->GetMatrix()))
////						{
////							m_wakka[1][j].Hit();
////							if (m_2.createdObst[i]->GetElem() == DRIFTWOOD && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_2.createdObst[i]->Hit();
////							}
////							else if (m_2.createdObst[i]->GetElem() == FIREDRIFTWOOD && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_2.createdObst[i]->Hit();
////							}
////							else if (m_2.createdObst[i]->GetElem() == TREE && m_wakka[0][j].GetElem() == FIRE)
////							{
////								m_2.createdObst[i]->Hit();
////							}
////							else if (m_2.createdObst[i]->GetElem() == SANDSTORM && m_wakka[0][j].GetElem() == WATER)
////							{
////								m_2.createdObst[i]->Hit();
////							}
////							else if (m_2.createdObst[i]->GetElem() == PITFALL && m_wakka[0][j].GetElem() == SOIL)
////							{
////								m_2.createdObst[i]->Hit();
////							}
////							if (!m_player[1].GetCoolTime().bCoolTime)
////							{
////								if (m_wakka[1][j].GetElem() == SAND)
////								{
////									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
////									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									CreateSandStorm(pos, 1);
////								}
////								else if (m_wakka[1][j].GetElem() == SOIL)
////								{
////									D3DXVECTOR3 pos = m_wakka[1][j].GetPosition(1);
////									D3DXVECTOR3 pos1 = m_player[1].GetPlayerPosition();
////									D3DXVECTOR3 pos2 = m_player[0].GetPlayerPosition();
////									float pos3 = pos1.z - pos2.z;
////									pos.z -= pos3;
////									pos.z += 3.0f;
////									pos.z -= m_player[1].GetPlayerPosition().z - m_player[0].GetPlayerPosition().z;
////									CreatePitfalls(pos, 1);
////								}
////								m_player[1].StartCoolTime();
////							}
////						}
////					}
////				}
////			}
////		}
////	}
////}
//
//void SceneGame::ColP2S() {
//	D3DXVECTOR3 pos = m_player[0].GetPlayerPosition();
//	/*当たり判定必要なステージオブジェクトの数だけ繰り返すのだ*/
//	for (int i = 0; i < STAGE * 2; i++) {
//		/*当たり判定とる範囲はできる限り小さくしてみた！ キラッとプリ☆チャンはいいぞ*/
//		if (fabs(pos.y - m_stageInfo[i][0].y) < 3.0f || fabs(pos.z - m_stageInfo[i][0].z) < 3.0f || fabs(pos.x - m_stageInfo[i][0].x) < 3.0f)
//		{
//			D3DXMATRIX mat;
//			D3DXMATRIXA16 matTranslation, matRotation, matScale;
//			D3DXMatrixIdentity(&mat);
//			D3DXMatrixIdentity(&matTranslation);
//			D3DXMatrixIdentity(&matRotation);
//			D3DXMatrixIdentity(&matScale);
//			D3DXMatrixTranslation(&matTranslation, m_stageWallInfo[i][0].x, m_stageWallInfo[i][0].y, m_stageWallInfo[i][0].z);
//			D3DXMatrixRotationYawPitchRoll(&matRotation, m_stageWallInfo[i][1].y, m_stageWallInfo[i][1].x, m_stageWallInfo[i][1].z);
//			D3DXMatrixScaling(&matScale, m_stageWallInfo[i][2].x, m_stageWallInfo[i][2].y, m_stageWallInfo[i][2].z);
//			mat = matScale * matRotation * matTranslation;
//			if (Collision::CheckCollision(m_player[0].GetOBB(), *m_player[0].GetMatrix(), m_stageWall->GetOBB(), mat))
//			{
//				m_player[0].Hit();
//				m_player[0].HitWall();
//			}
//		}
//		
//	}
//}
