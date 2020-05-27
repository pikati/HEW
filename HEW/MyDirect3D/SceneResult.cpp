#include "SceneResult.h"
#include "main.h"
#include "Fade.h"
#include "Input.h"
#include "Joycon.h"
#include "SceneManager.h"

void SceneResult::Initialize() {
	m_pDevice = GetDevice();
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Result/Win.png", &m_texWin);
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Result/Lose.png", &m_texLose);
	/*m_fbx = new Fbx[2];
	m_fbx*/
	m_score = new Score[2];
	m_score[0].Initialize();
	m_score[1].Initialize();
	m_score[0].SetPosition(D3DXVECTOR2(280.0f, 400.0f));
	m_score[1].SetPosition(D3DXVECTOR2(920.0f, 400.0f));
	m_score1 = 9999;
	m_score2 = 12345;
	m_changeScene = false;
	Fade::FadeOut();
	m_score[0].AddScore(m_score1);
	m_score[1].AddScore(m_score2);
}

void SceneResult::Update() {
	if (!Fade::IsFadeOut())
	{
		if (!m_changeScene)
		{
			if (g_diJoyState2[1] & BUTTON_M || g_diJoyState2[1] & BUTTON_R || g_diJoyState2[1] & BUTTON_START || g_diJoyState2[3] & BUTTON_M || g_diJoyState2[3] & BUTTON_R || g_diJoyState2[3] & BUTTON_START)
			{
				Fade::FadeIn();
				m_changeScene = true;
			}
			if (Input::TriggerKey(DIK_RETURN))
			{
				Fade::FadeIn();
				m_changeScene = true;
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
}

void SceneResult::Draw() {
	m_score[0].Draw();
	m_score[1].Draw();
	Fade::Fading();
}

void SceneResult::Finalize() {
	m_score[1].Finalize();
	m_score[0].Finalize();
	delete m_score;
	SAFE_RELEASE(m_texLose);
	SAFE_RELEASE(m_texWin);
}

void SceneResult::GetInfomation(bool win, int score1, int score2) {
	m_win = win;
	m_score1 = score1;
	m_score2 = score2;
	m_score[0].AddScore(m_score1);
	m_score[1].AddScore(m_score2);
}