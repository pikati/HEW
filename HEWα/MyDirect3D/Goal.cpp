#include "Goal.h"

void Goal::Initialize(D3DXVECTOR3 pos) {
	m_pos = pos;
	m_pXManager = new XManager;
	m_pXManager->Initialize();
	m_pXManager->LoadXFile("Models/Goal.x", false);
	m_pXManager->SetRotationY(90.0f);
}

void Goal::Update() {
	m_pXManager->SetTranslation(m_pos);
	m_pXManager->Update();
}

void Goal::Draw() {
	m_pXManager->Draw();
}

void Goal::Finalize() {
	m_pXManager->Finalize();
	delete m_pXManager;
}

bool Goal::IsGoal(D3DXVECTOR3 targetPos) {
	if ((m_pos.x - targetPos.x) * (m_pos.x - targetPos.x) + (m_pos.y - targetPos.y) * (m_pos.y - targetPos.y) + (m_pos.z - targetPos.z) * (m_pos.z - targetPos.z) <= 5.0f)
	{
		return true;
	}
	return false;
}