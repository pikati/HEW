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
	m_pos.x = /*((float)(rand() % 10) - 5.0f) * 0.2f*/0.0f;
	m_pos.y = 0.2f;
	m_pos.z = 5.0f;
	m_pXmanager = new XManager;
	m_pXmanager->Initialize();
	m_pXmanager->SetTranslation(m_pos);
	m_pXmanager->LoadXFile("Models/Obst/obstaclePitFall.x", true);
	m_pXmanager->SetScaling(1.0f);
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
			m_pXmanager->SetTranslation(m_pos);
			m_pXmanager->Update();
		}
	}
}

void PitFall::Draw() {
	m_pXmanager->SetTranslation(m_pos);
	m_pXmanager->Draw();
}

void PitFall::Finalize() {
	m_pXmanager->Finalize();
	delete m_pXmanager;
}

D3DXVECTOR3 PitFall::GetPosition() {
	return m_pos;
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
//
//OBB* PitFall::GetOBB() {
//	return m_pXmanager->GetOBB();
//}

void PitFall::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

COBBTree& PitFall::GetOBB() const {
	return m_pXmanager->GetOBB();
}

D3DXMATRIX* PitFall::GetMatrix() {
	return m_pXmanager->GetMatrix();
}

void PitFall::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_ELEM PitFall::GetElem() {
	return m_elem;
}