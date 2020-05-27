#include "DispResult.h"

void DispResult::Initialize(int idx) {
	m_score = new Score;
	m_score->Initialize();
	m_pDevice = GetDevice();
	if (idx == 0)
	{
		D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/win.png", &m_tex);
	}
	else
	{
		D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/lose.png", &m_tex);
	}
}

void DispResult::Draw(int idx) {
	float pos = 0.0f;
	if (idx == 0)
	{
		pos = 180.0f;
	}
	else
	{
		pos = 820.0f;
	}

	Polygons::Draw(pos, 60.0f, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_tex);
	m_score->SetPosition(D3DXVECTOR2(pos + 200.0f, 220.0f));
	m_score->Draw();
}

void DispResult::Finalize() {
	SAFE_RELEASE(m_tex);
}

void DispResult::SetScore(int s) {
	m_score->AddScore(s);
}