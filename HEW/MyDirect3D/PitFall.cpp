#include "PitFall.h"
#include "main.h"
#include <stdlib.h>

PitFall::PitFall()
{
}


PitFall::~PitFall()
{
}

void PitFall::Initialize()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = PITFALL;
}

void PitFall::Update() {
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

void PitFall::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool PitFall::IsEnable() {
	return m_bEnable;
}

void PitFall::CreateObstacle(D3DXVECTOR3 pos) {
	m_pos = pos;
	m_pos.y += 0.2f;
}

float* PitFall::CreateRondam(float* random) {
	random[0] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	do {
		random[1] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[1]);
	do {
		random[2] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[2] || random[1] == random[2]);
	return random;
}

void PitFall::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void PitFall::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void PitFall::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void PitFall::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

D3DXVECTOR3 PitFall::GetPosition() {
	return m_pos;
}

D3DXVECTOR3 PitFall::GetRotation() {
	return m_rot;
}

D3DXVECTOR3 PitFall::GetScale() {
	return m_scale;
}

ObstacleInfo PitFall::GetInfo() {
	ObstacleInfo info(m_pos, m_rot, m_scale, m_elem, false, false, -1);
	return info;
}

void PitFall::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE PitFall::GetElem() {
	return m_elem;
}