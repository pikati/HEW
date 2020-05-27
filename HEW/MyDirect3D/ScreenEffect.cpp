#include "ScreenEffect.h"
#include "main.h"
#include "Polygons.h"

int ScreenEffect::m_playerNumber = 0;


void ScreenEffect::Initialize() {
	m_pDevice = GetDevice();
	m_tex = new LPDIRECT3DTEXTURE9[SCREEN_EFEFCT_MAX];
	m_info = new TextureInfo[SCREEN_EFEFCT_MAX];
	TextureInitialize();
	m_type = SCREEN_EFFECT_SPEED;
	m_enable = false;
}

void ScreenEffect::Update() {
	if (!m_enable)
	{
		return;
	}

	UpdateFrame();
}

void ScreenEffect::Draw() {
	if(!m_enable)
	{
		return;
	}
	ScreenEffectDraw();
	PlayerNumUpdate();
}


void ScreenEffect::TextureInitialize() {
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Screen/Speed.png", &m_tex[SCREEN_EFFECT_SPEED]);
	m_info[SCREEN_EFFECT_SPEED].holizontalSplit = 2;
	m_info[SCREEN_EFFECT_SPEED].verticalSplit = 2;
	m_info[SCREEN_EFFECT_SPEED].maxFrame = 4;
}

void ScreenEffect::UpdateFrame() {
	m_frame++;
	if (m_frame >= m_info[m_type].maxFrame)
	{
		m_frame = 0;
	}
}

void ScreenEffect::ScreenEffectDraw() {
	float tx = CalcTextureX();
	float ty = CalcTextureY();

	if (m_playerNumber == 0)
	{
		Polygons::Draw(0.0f, 0.0f, 640.0f, 720.0f, tx, ty, 1.0f / (float)m_info[m_type].holizontalSplit, 1.0f / (float)m_info[m_type].verticalSplit, m_tex[m_type]);
	}
	else
	{
		Polygons::Draw(640.0f, 0.0f, 1280.0f, 720.0f, tx, ty, 1.0f / (float)m_info[m_type].holizontalSplit, 1.0f / (float)m_info[m_type].verticalSplit, m_tex[m_type]);
	}
}

void ScreenEffect::PlayerNumUpdate() {
	m_playerNumber++;
	if (m_playerNumber >= 2)
	{
		m_playerNumber = 0;
	}
}

float ScreenEffect::CalcTextureX() {
	return (float)(m_frame % (m_info[m_type].holizontalSplit * (m_info[m_type].maxFrame / (m_info[m_type].holizontalSplit * m_info[m_type].verticalSplit)))) / (float)m_info[m_type].holizontalSplit;
}

float ScreenEffect::CalcTextureY() {
	return (float)(m_frame % (m_info[m_type].verticalSplit * (m_info[m_type].maxFrame / (m_info[m_type].holizontalSplit * m_info[m_type].verticalSplit)))) / (float)m_info[m_type].verticalSplit;
}