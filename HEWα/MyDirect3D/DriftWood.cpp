#include "DriftWood.h"
#include "main.h"
#include <stdlib.h>

DriftWood::DriftWood()
{
}


DriftWood::~DriftWood()
{
}

void DriftWood::Initialize()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_obst = new Fbx;
	m_obst->Initialize();
	m_obst->SetTranslation(m_pos);
	m_obst->Load("Models/FBX/obstacleDriftWood.fbx", false);
	m_obst->SetScaling(1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = FIREDRIFTWOOD;
}

void DriftWood::Update() {
	if (fabs(m_playerPos.y - m_pos.y) > 30.0f || fabs(m_playerPos.z - m_pos.z) > 30.0f || fabs(m_playerPos.x - m_pos.x) > 30.0f)
	{
		m_bEnable = false;
	}
	else {
		if (!m_bHit)
		{
			m_bEnable = true;
			m_obst->SetTranslation(m_pos);
			m_obst->Update();
		}
	}
}

void DriftWood::Draw() {
	m_obst->SetTranslation(m_pos);
	m_obst->Draw();
}

void DriftWood::Finalize() {
	m_obst->Finalize();
	delete m_obst;
}

D3DXVECTOR3 DriftWood::GetPosition() {
	return m_pos;
}

void DriftWood::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool DriftWood::IsEnable() {
	return m_bEnable;
}

void DriftWood::CreateObstacle(D3DXVECTOR3 pos) {
	m_pos = pos;
	m_pos.y += 0.2f;
}

float* DriftWood::CreateRondam(float* random) {
	random[0] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	do {
		random[1] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[1]);
	do {
		random[2] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[2] || random[1] == random[2]);
	return random;
}

void DriftWood::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

OBB& DriftWood::GetOBB()const {
	return m_obst->GetOBB();
}

void DriftWood::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void DriftWood::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void DriftWood::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

//COBBTree& DriftWood::GetOBB() const {
//	return m_obst->GetOBB();
//}
//
//D3DXMATRIX* DriftWood::GetMatrix() {
//	return m_obst->GetMatrix();
//}

void DriftWood::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE DriftWood::GetElem() {
	return m_elem;
}