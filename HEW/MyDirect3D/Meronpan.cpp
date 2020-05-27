#include "Meronpan.h"

Meronpan::Meronpan()
{
}

Meronpan::~Meronpan()
{
}

void Meronpan::Initialize() {
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_type = MERONPAN;
	m_bEnable = true;
	m_bHit = false;
}

void Meronpan::Update() {
	if (fabs(m_playerPos.y - m_pos.y) > 30.0f || fabs(m_playerPos.z - m_pos.z) > 30.0f || fabs(m_playerPos.x - m_pos.x) > 30.0f)
	{
		m_bEnable = false;
	}
	else {
		if (!m_bHit)
		{
			m_bEnable = true;
		}
	}
}

void Meronpan::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool Meronpan::IsEnable() {
	return m_bEnable;
}

void Meronpan::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Meronpan::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Meronpan::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

D3DXVECTOR3 Meronpan::GetPosition() {
	return m_pos;
}

D3DXVECTOR3 Meronpan::GetRotation() {
	return m_rot;
}

D3DXVECTOR3 Meronpan::GetScale() {
	return m_scale;
}

ItemInfo Meronpan::GetInfo() {
	ItemInfo info(m_pos, m_rot, m_scale, m_type, false, false);
	return info;
}

void Meronpan::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}