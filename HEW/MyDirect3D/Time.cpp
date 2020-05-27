#include "Time.h"
#include "Polygons.h"
#include "main.h"


void Time::Initialize() {
	m_pDevice = GetDevice();
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/Num1.png", &m_texture);
	m_time = 0;
	m_frame = 0;
	m_pos = D3DXVECTOR2(720.0f, 20.0f);
}

void Time::Update() {
	m_frame++;
	if (m_frame >= 30)
	{
		m_time++;
		m_frame = 0;
	}
}

void Time::Draw() {
	D3DVIEWPORT9 viwePort;
	viwePort.X = 0;
	viwePort.Y = 0;
	viwePort.Width = 1280;
	viwePort.Height = 720;
	viwePort.MaxZ = 1.0f;
	viwePort.MinZ = 0.0f;
	m_pDevice->SetViewport(&viwePort);
	float u = 0;
	float v = 0;
	int num = m_time;
	for (int i = 0; i < 3; i++)
	{
		int digit = num % 10;
		u = digit % 5 * TIME_TEX_WIDTH;
		v = digit / 5 * TIME_TEX_HEIGHT;
		Polygons::Draw(m_pos.x - i * 100.0f, m_pos.y, TIME_WIDTH, TIME_HEIGHT, u, v, TIME_TEX_WIDTH, TIME_TEX_HEIGHT, m_texture);
		num /= 10;
	}
}

void Time::Finalize() {
	SAFE_RELEASE(m_texture);
}

int Time::GetTime() {
	return m_time;
}