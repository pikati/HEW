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
	m_obst = new Fbx;
	m_obst->Initialize();
	m_obst->SetTranslation(m_pos);
	m_obst->Load("Models/FBX/obstacleSandStorm.fbx", false);
	m_obst->SetScaling(1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = FIREDRIFTWOOD;
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
			m_obst->SetTranslation(m_pos);
			m_obst->Update();
		}
	}
}

void SandStorm::Draw() {
	m_obst->SetTranslation(m_pos);
	m_obst->Draw();
}

void SandStorm::Finalize() {
	m_obst->Finalize();
	delete m_obst;
}

D3DXVECTOR3 SandStorm::GetPosition() {
	return m_pos;
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

OBB& SandStorm::GetOBB()const {
	return m_obst->GetOBB();
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

//COBBTree& SandStorm::GetOBB() const {
//	return m_obst->GetOBB();
//}
//
//D3DXMATRIX* SandStorm::GetMatrix() {
//	return m_obst->GetMatrix();
//}

void SandStorm::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE SandStorm::GetElem() {
	return m_elem;
}