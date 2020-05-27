#include "SandStorm.h"
#include "main.h"
#include <stdlib.h>

SandStorm::SandStorm()
{
}


SandStorm::~SandStorm()
{
}

void SandStorm::Initialize()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = SANDSTORM;
}

void SandStorm::Update() {
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

void SandStorm::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool SandStorm::IsEnable() {
	return m_bEnable;
}

void SandStorm::CreateObstacle(D3DXVECTOR3 pos) {
	m_pos = pos;
	m_pos.y += 0.2f;
}

float* SandStorm::CreateRondam(float* random) {
	random[0] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	do {
		random[1] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[1]);
	do {
		random[2] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[2] || random[1] == random[2]);
	return random;
}

void SandStorm::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void SandStorm::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void SandStorm::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void SandStorm::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

D3DXVECTOR3 SandStorm::GetPosition() {
	return m_pos;
}

D3DXVECTOR3 SandStorm::GetRotation() {
	return m_rot;
}

D3DXVECTOR3 SandStorm::GetScale() {
	return m_scale;
}

ObstacleInfo SandStorm::GetInfo() {
	ObstacleInfo info(m_pos, m_rot, m_scale, m_elem, false, false, -1);
	return info;
}

void SandStorm::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE SandStorm::GetElem() {
	return m_elem;
}