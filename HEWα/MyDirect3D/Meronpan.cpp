#include "Meronpan.h"

Meronpan::Meronpan()
{
}

Meronpan::~Meronpan()
{
}

void Meronpan::Initialize() {
	m_pXmanager = new XManager;
	m_pXmanager->Initialize();
	m_pXmanager->LoadXFile("Models/Meronpan.x", true);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void Meronpan::Update() {
	m_pXmanager->SetTranslation(m_pos);
	m_pXmanager->SetRotation(m_rot);
	m_pXmanager->SetScaling(m_scale);
	m_pXmanager->Update();
}

void Meronpan::Draw() {
	m_pXmanager->Draw();
}

void Meronpan::Finalize() {
	m_pXmanager->Finalize();
	delete m_pXmanager;
}

void Meronpan::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Meronpan::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Meronpan::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

COBBTree& Meronpan::GetOBB() const {
	return m_pXmanager->GetOBB();
}

D3DXMATRIX* Meronpan::GetMatrix() {
	return m_pXmanager->GetMatrix();
}