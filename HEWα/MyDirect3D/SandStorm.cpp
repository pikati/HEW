#include "SandStorm.h"
#include "main.h"

SandStorm::SandStorm()
{
}


SandStorm::~SandStorm()
{
}

void SandStorm::Initialize()
{
	m_pos.x = ((float)(rand() % 10) - 5.0f) * 0.2f;
	m_pos.y = 0.2f;
	m_pos.z = 5.0f;
	m_pXmanager = new XManager;
	m_pXmanager->Initialize();
	m_pXmanager->SetTranslation(m_pos);
	m_pXmanager->LoadXFile("Models/Obst/obstacleSand.x", true);
	m_pXmanager->SetScaling(1.0f);
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
			m_pXmanager->SetTranslation(m_pos);
			m_pXmanager->Update();
		}
	}
}

void SandStorm::Draw() {
	if (m_bEnable)
	{
		m_pXmanager->SetTranslation(m_pos);
		m_pXmanager->Draw();
	}
}

void SandStorm::Finalize() {
	m_pXmanager->Finalize();
	delete m_pXmanager;
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

//OBB* SandStorm::GetOBB() {
//	return m_pXmanager->GetOBB();
//}

void SandStorm::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void SandStorm::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void SandStorm::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

COBBTree& SandStorm::GetOBB() const{
	return m_pXmanager->GetOBB();
}

D3DXMATRIX* SandStorm::GetMatrix() {
	return m_pXmanager->GetMatrix();
}

void SandStorm::Reset() {
	 m_bEnable = false;
	 m_bHit = false;
}

OBST_TYPE SandStorm::GetElem() {
	return m_elem;
}