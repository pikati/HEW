#include "Tree.h"
#include "main.h"
#include <stdlib.h>

Tree::Tree()
{
}


Tree::~Tree()
{
}

void Tree::Initialize()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = TREE;
}

void Tree::Update() {
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

void Tree::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool Tree::IsEnable() {
	return m_bEnable;
}

void Tree::CreateObstacle(D3DXVECTOR3 pos) {
	m_pos = pos;
	m_pos.y += 0.2f;
}

float* Tree::CreateRondam(float* random) {
	random[0] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	do {
		random[1] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[1]);
	do {
		random[2] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[2] || random[1] == random[2]);
	return random;
}

void Tree::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void Tree::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Tree::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Tree::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

D3DXVECTOR3 Tree::GetPosition() {
	return m_pos;
}

D3DXVECTOR3 Tree::GetRotation() {
	return m_rot;
}

D3DXVECTOR3 Tree::GetScale() {
	return m_scale;
}

ObstacleInfo Tree::GetInfo() {
	ObstacleInfo info(m_pos, m_rot, m_scale, m_elem, false, false, -1);
	return info;
}

void Tree::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE Tree::GetElem() {
	return m_elem;
}