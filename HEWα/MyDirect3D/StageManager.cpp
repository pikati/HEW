#include "StageManager.h"

StageManager::StageManager()
{
}


StageManager::~StageManager()
{
}

void StageManager::Initialize() {
	m_stage = new Stage[STAGE_KIND];
	m_stage[0].Initialize(STAGE_NORMAL);
	m_stage[1].Initialize(STAGE_WALL);
	m_stage[2].Initialize(STAGE_CURVE);
}

void StageManager::Update() {
}

void StageManager::Draw() {
	for (int i = 0; i < (int)m_stageInfo.size(); i++)
	{
		m_stage[m_stageInfo[i].type].SetPosition(m_stageInfo[i].pos);
		m_stage[m_stageInfo[i].type].SetRotation(m_stageInfo[i].rot);
		m_stage[m_stageInfo[i].type].SetScale(m_stageInfo[i].scale);
		m_stage[m_stageInfo[i].type].Update();
		m_stage[m_stageInfo[i].type].Draw();
	}
}

void StageManager::Finalize() {
	m_stageInfo.erase(m_stageInfo.begin(), m_stageInfo.end());
	for (int i = STAGE_KIND - 1; i >= 0; i--)
	{
		m_stage[i].Finalize();
	}
	delete[] m_stage;
}

void StageManager::CreateStage(StageInfo info) {
	m_stageInfo.push_back(info);
}

void StageManager::CreateStage(D3DXVECTOR3 pos, STAGE_TYPE type) {
	m_stageInfo.push_back(StageInfo(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), type));
}

int StageManager::GetStageNum() {
	return (int)m_stageInfo.size();
}

StageInfo* StageManager::GetStageInfo(int idx) {
	return &m_stageInfo[idx];
}
//
//COBBTree& StageManager::GetOBB(STAGE_TYPE type) const {
//	return m_stage[type].GetOBB();
//}

OBB& StageManager::GetOBB(STAGE_TYPE type)const {
	return m_stage[type].GetOBB();
}