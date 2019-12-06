#include "Stage.h"
#include "XManager.h"

void Stage::Initialize(int n) {
	m_stage = new XManager;
	m_stage->Initialize();
	switch (n) 
	{
	case 0:
		m_stage->LoadXFile("Models/Stage.x", false);
		break;
	case 1:
		m_stage->LoadXFile("Models/StageWall.x", true);
		break;
	case 2:
		m_stage->LoadXFile("Models/StageCurve.x", true);
		break;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_sca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void Stage::Update() {
	m_stage->SetTranslation(m_pos.x, m_pos.y, m_pos.z);
	m_stage->SetRotation(m_rot.x, m_rot.y, m_rot.z);
	m_stage->SetScaling(m_sca.x, m_sca.y, m_sca.z);
	m_stage->Update();
}

void Stage::Draw() {
	m_stage->Draw();
}

void Stage::Finalize() {
	m_stage->Finalize();
	delete m_stage;
}
void Stage::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Stage::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Stage::SetScale(D3DXVECTOR3 sca) {
	m_sca = sca;
}

COBBTree& Stage::GetOBB() const{
	return m_stage->GetOBB();
}

D3DXMATRIX* Stage::GetMatrix() {
	return m_stage->GetMatrix();
}