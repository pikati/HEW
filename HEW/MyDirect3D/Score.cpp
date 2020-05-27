#include "Score.h"
#include "Polygons.h"
#include "main.h"

#define SCORE_TEX_WIDTH 0.2f
#define SCORE_TEX_HEGIHT 0.5f

#define SCORE_WIDTH 64
#define SCORE_HEIGHT 64

void Score::Initialize() {
	m_pDevice = GetDevice();
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/Num2.png", &m_texture);
	m_score = 0;

}

void Score::Draw() {
	float u = 0;
	float v = 0;
	int num = m_score;
	for (int i = 0; i < 5; i++)
	{
		int digit = num % 10;
		u = digit % 5 * SCORE_TEX_WIDTH;
		v = digit / 5 * SCORE_TEX_HEGIHT;
		Polygons::Draw(m_pos.x - i * 50.0f, m_pos.y, SCORE_WIDTH, SCORE_HEIGHT, u, v, SCORE_TEX_WIDTH, SCORE_TEX_HEGIHT, m_texture);
		num /= 10;
	}
}

void Score::Finalize() {
	SAFE_RELEASE(m_texture);
}

void Score::AddScore(int score) {
	m_score += score;
}

void Score::SetPosition(D3DXVECTOR2 pos) {
	m_pos = pos;
}

int Score::GetScore() {
	return m_score;
}