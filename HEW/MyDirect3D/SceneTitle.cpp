#include "SceneTitle.h"
#include "main.h"
#include "Input.h"
#include "Joycon.h"
#include "SceneManager.h"
#include "Polygons.h"
#include "Fade.h"
#include "Sound.h"


void SceneTitle::Initialize() {
	PlaySound(SOUND_BGM_TITLE);
	m_pDevice = GetDevice();
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Title/Title.png", &m_texture);
	Fade::FadeOut();
	m_changeScene = false;
}

void SceneTitle::Update() {
	if (!Fade::IsFadeOut())
	{
		if (!m_changeScene)
		{
			if (g_diJoyState2[1] & BUTTON_M || g_diJoyState2[1] & BUTTON_R || g_diJoyState2[1] & BUTTON_START || g_diJoyState2[3] & BUTTON_M || g_diJoyState2[3] & BUTTON_R || g_diJoyState2[3] & BUTTON_START)
			{
				Fade::FadeIn();
				m_changeScene = true;
				PlaySound(SOUND_SE_SCHANGE);
			}
			if (Input::TriggerKey(DIK_RETURN))
			{
				Fade::FadeIn();
				m_changeScene = true;
				PlaySound(SOUND_SE_SCHANGE);
			}
		}
	}
	if (m_changeScene)
	{
		if (!Fade::IsFadeIn())
		{
			StopSound(SOUND_BGM_TITLE);
			SceneManager::ChangeSceneState();
		}
	}
}

void SceneTitle::Draw() {
	Polygons::Draw(0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_texture);
	Fade::Fading();
}

void SceneTitle::Finalize() {
	SAFE_RELEASE(m_texture);
}