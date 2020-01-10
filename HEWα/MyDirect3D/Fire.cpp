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
	m_obst = new Fbx;
	m_obst->Initialize();
	m_obst->SetTranslation(m_pos);
	m_obst->Load("Models/FBX/obstacleFire.fbx", false);
	m_obst->SetScaling(1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = FIREDRIFTWOOD;
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
			m_obst->SetTranslation(m_pos);
			m_obst->Update();
		}
	}
}

void Fire::Draw() {
	m_obst->SetTranslation(m_pos);
	m_obst->Draw();
}

void Fire::Finalize() {
	m_obst->Finalize();
	delete m_obst;
}

D3DXVECTOR3 Fire::GetPosition() {
	return m_pos;
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

OBB& Fire::GetOBB()const {
	return m_obst->GetOBB();
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

//COBBTree& Fire::GetOBB() const {
//	return m_obst->GetOBB();
//}
//
//D3DXMATRIX* Fire::GetMatrix() {
//	return m_obst->GetMatrix();
//}

void Fire::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE Fire::GetElem() {
	return m_elem;
}