#include "Fire.h"
#include "main.h"
#include <stdlib.h>

Fire::Fire()
{
}


Fire::~Fire()
{
}

void Fire::Initialize()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = FIREWOOD;
}

void Fire::Update() {
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

void Fire::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool Fire::IsEnable() {
	return m_bEnable;
}

void Fire::CreateObstacle(D3DXVECTOR3 pos) {
	m_pos = pos;
	m_pos.y += 0.2f;
}

float* Fire::CreateRondam(float* random) {
	random[0] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	do {
		random[1] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[1]);
	do {
		random[2] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[2] || random[1] == random[2]);
	return random;
}

void Fire::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void Fire::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Fire::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Fire::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

D3DXVECTOR3 Fire::GetPosition() {
	return m_pos;
}

D3DXVECTOR3 Fire::GetRotation() {
	return m_rot;
}

D3DXVECTOR3 Fire::GetScale() {
	return m_scale;
}

ObstacleInfo Fire::GetInfo() {
	ObstacleInfo info(m_pos, m_rot, m_scale, m_elem, false, false, -1);
	return info;
}

void Fire::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE Fire::GetElem() {
	return m_elem;
}