#include "StartCount.h"
#include "main.h"
void StartCount::Initialize() {
	m_pDevice = GetDevice();
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/Num1.png", &m_texture1);
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/Start.png", &m_texture2);
	m_frame = 0;
	m_count = 3;
	m_start = false;
	m_startEnd = false;
	m_end = false;
	m_pos.x = 510.0f;
	m_pos.y = 280.0f;
}

void StartCount::Update() {
	if (!m_end)
	{
		if (!m_start)
		{
			m_frame++;
			if (m_frame >= 30)
			{
				m_frame = 0;
				m_count--;
				if (m_count <= 0)
				{
					m_start = true;
				}
			}
		}
		if (!m_startEnd)
		{
			if (m_start)
			{
				m_frame++;
				if (m_frame >= 45)
				{
					m_frame = 0;
					m_startEnd = true;
				}
			}
		}
		if (m_startEnd)
		{
			m_frame++;
			if (m_frame >= 30)
			{
				m_frame = 0;
				m_startEnd = false;
				m_end = true;
			}
		}
	}
}

void StartCount::Draw() {
	if (!m_end)
	{
		if (!m_start)
		{
			float u = 0;
			float v = 0;
			u = m_count % 5 * START_TEX_WIDTH;
			v = m_count / 5 * START_TEX_HEIGHT;
			Polygons::Draw(m_pos.x, m_pos.y, START_WIDTH, START_HEIGHT, u, v, START_TEX_WIDTH, START_TEX_HEIGHT, m_texture1);
		}

		if (m_start && !m_startEnd)
		{
			Polygons::Draw(490.0f, 310.0f, 150.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_texture2);
		}
	}
}

void StartCount::Finalize() {
	SAFE_RELEASE(m_texture2);
	SAFE_RELEASE(m_texture1);
}

bool StartCount::IsStart() {
	return m_start;
}