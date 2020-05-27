#include "Taiyaki.h"

Taiyaki::Taiyaki()
{
}

Taiyaki::~Taiyaki()
{
}

void Taiyaki::Initialize() {
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_type = TAIYAKI;
	m_bEnable = true;
	m_bHit = false;
}

void Taiyaki::Update() {
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

void Taiyaki::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool Taiyaki::IsEnable() {
	return m_bEnable;
}

void Taiyaki::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Taiyaki::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Taiyaki::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

D3DXVECTOR3 Taiyaki::GetPosition() {
	return m_pos;
}

D3DXVECTOR3 Taiyaki::GetRotation() {
	return m_rot;
}

D3DXVECTOR3 Taiyaki::GetScale() {
	return m_scale;
}

ItemInfo Taiyaki::GetInfo() {
	ItemInfo info(m_pos, m_rot, m_scale, m_type, false, false);
	return info;
}

void Taiyaki::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}