#include "Taiyaki.h"



Taiyaki::Taiyaki()
{
}


Taiyaki::~Taiyaki()
{
}

void Taiyaki::Initialize() {
	m_pXmanager = new XManager;
	m_pXmanager->Initialize();
	m_pXmanager->LoadXFile("Models/Taiyaki.x", true);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void Taiyaki::Update() {
	m_pXmanager->SetTranslation(m_pos);
	m_pXmanager->SetRotation(m_rot);
	m_pXmanager->SetScaling(m_scale);
	m_pXmanager->Update();
}

void Taiyaki::Draw() {
	m_pXmanager->Draw();
}

void Taiyaki::Finalize() {
	m_pXmanager->Finalize();
	delete m_pXmanager;
}

void Taiyaki::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Taiyaki::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Taiyaki::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

COBBTree& Taiyaki::GetOBB() const {
	return m_pXmanager->GetOBB();
}

D3DXMATRIX* Taiyaki::GetMatrix() {
	return m_pXmanager->GetMatrix();
}