#include "SceneManager.h"
#include "SceneResult.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "Input.h"
#include "main.h"
//#include "Sound.h"
#include "light.h"
#include "Joycon.h"
#include "Fade.h"
#include "Sound.h"

#define FPS 30.0f

BaseScene			*SceneManager::m_scene[3];
SCENE_STATE			SceneManager::m_sceneState;
PDIRECT3DDEVICE9	SceneManager::m_d3dDevice;
const float			SceneManager::MIN_FREAM_TIME = 1.0f / FPS;
float				SceneManager::frameTime = 0;
float				SceneManager::fps = 0;
bool				SceneManager::frame = false;
LARGE_INTEGER		SceneManager::timeStart;
LARGE_INTEGER		SceneManager::timeEnd;
LARGE_INTEGER		SceneManager::timeFreq;

void SceneManager::Initialize() {
	srand((unsigned int)time(NULL));
	m_d3dDevice = GetDevice();
	InitSound(GetHWND());
	// Joypad Object の初期化^-------------------
	Input::Initialize();
	InitDInput(GetHInstance());
	InitJoypad2();
	//各シーンのインスタンス作成
	m_scene[0] = new SceneTitle;
	m_scene[1] = new SceneGame;
	m_scene[2] = new SceneResult;
	//初期シーン設定
	m_sceneState = SCENE_GAME;
	//初期シーン初期化
	m_scene[m_sceneState]->Initialize();
	Light_Initialize();
	QueryPerformanceFrequency(&timeFreq);
	// 1度取得しておく(初回計算用)
	QueryPerformanceCounter(&timeStart);
	
	Fade::Initialize();

}

void SceneManager::Update() {
	frame = PastOneFrame();
	if (frame)
	{
		GetJoypadState2();
		if (Input::TriggerKey(DIK_A)) {
			if (m_sceneState == SCENE_TITLE) {
				//Sound::SE(0)->Play(0, 0, 0);
				SceneManager::ChangeSceneState();
			}
		}
		if (Input::TriggerKey(DIK_SPACE)) {
			ResetGame();
		}
		m_scene[m_sceneState]->Update();
	}
}

void SceneManager::Draw() {
	if (frame) {
		m_d3dDevice->BeginScene();
		m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(160, 216, 239), 1.0f, 0);
		m_scene[m_sceneState]->Draw();
		m_d3dDevice->EndScene();
		m_d3dDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void SceneManager::Finalize() {
	Fade::Finalize();
	m_scene[m_sceneState]->Finalize();

	ReleaseDInput();
	Input::Finalize();
	
	//m_scene[1]->Finalize();
	//delete m_scene[1];
	delete m_scene[0];
	UninitSound();
}

void SceneManager::ChangeSceneState() {
	switch (m_sceneState)
	{
	case SCENE_TITLE:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_GAME;
		m_scene[m_sceneState]->Initialize();
		break;
	case SCENE_GAME:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_TITLE;
		m_scene[m_sceneState]->Initialize();
		break;
	case SCENE_RESULT:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_TITLE;
		m_scene[m_sceneState]->Initialize();
		break;
	default:
		break;
	}
}

bool SceneManager::PastOneFrame() {
	QueryPerformanceCounter(&timeEnd);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FREAM_TIME) { // 時間に余裕がある
		// ミリ秒に変換
		DWORD sleepTime = static_cast<DWORD>((MIN_FREAM_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度はガタガタ)
		Sleep(sleepTime);   // 寝る
		timeEndPeriod(1);   // 戻す
		// 次週に持ち越し(こうしないとfpsが変になる?)
		return false;
	}
	timeStart = timeEnd; // 入れ替え
	return true;
}

BaseScene* SceneManager::SetSceneGame() {
	return m_scene[1];
}

void SceneManager::ResetGame() {
	m_scene[m_sceneState]->Finalize();
	m_scene[m_sceneState]->Initialize();
}