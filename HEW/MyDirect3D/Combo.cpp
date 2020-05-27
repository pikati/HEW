#include "Combo.h"
#include "main.h"
void Combo::Initialize() {
	m_pDevice = GetDevice();
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/Num3.png", &m_texture1);
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/Combo.png", &m_texture2);
	m_combo = 0;
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
}

void Combo::CountUp() {
	m_combo++;
}

void Combo::Draw() {
	int combo = m_combo;
	if (combo != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			float u = 0;
			float v = 0;
			u = combo % 5 * COMBO_TEX_WIDTH;
			v = combo / 5 * COMBO_TEX_HEIGHT;
			Polygons::Draw(m_pos.x + i * -50.0f, m_pos.y, COMBO_WIDTH, COMBO_HEIGHT, u, v, COMBO_TEX_WIDTH, COMBO_TEX_HEIGHT, m_texture1);
			Polygons::Draw(m_pos.x + 130.0f, m_pos.y, COMBO_WIDTH, COMBO_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, m_texture2);
			combo /= 10;
		}
		
	}
	
}

void Combo::CountReset() {
	m_combo = 0;
}

int Combo::GetCombo() {
	return m_combo;
}

void Combo::SetPosition(D3DXVECTOR2 pos) {
	m_pos = pos;
}

void Combo::Finalize() {
	SAFE_RELEASE(m_texture2);
	SAFE_RELEASE(m_texture1);
}