#include "StageManager.h"

void StageManager::Initialize() {
	m_stageInfo = new StageInfo[STAGE_NUM];
	for (int i = 0; i < STAGE_NUM; i++)
	{
		m_stageInfo[i].pos = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	}
	m_x = new XManager[STAGE_MAX];
	m_x[STAGE_ROAD].Initialize(false, false);
	m_x[STAGE_TREE].Initialize(true, true);
	m_x[STAGE_HOUSE1].Initialize(true, true);
	m_x[STAGE_HOUSE3].Initialize(true, true);
	m_x[STAGE_CHURCH].Initialize(true, true);
	m_x[STAGE_TEMPLE].Initialize(true, true);
	m_x[STAGE_TREE].SetMinMax(D3DXVECTOR3(-0.1f, -10.0f, -5.0f), D3DXVECTOR3(0.1f, 10.0f, 5.0f));
	m_x[STAGE_HOUSE1].SetMinMax(D3DXVECTOR3(-5.0f, -10.0f, -5.0f), D3DXVECTOR3(5.0f, 10.0f, 5.0f));
	m_x[STAGE_HOUSE3].SetMinMax(D3DXVECTOR3(-5.0f, -10.0f, -6.0f), D3DXVECTOR3(5.0f, 10.0f, 6.0f));
	m_x[STAGE_CHURCH].SetMinMax(D3DXVECTOR3(-5.0f, -10.0f, -6.0f), D3DXVECTOR3(5.0f, 10.0f, 6.0f));
	m_x[STAGE_TEMPLE].SetMinMax(D3DXVECTOR3(-10.0f, -10.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	m_x[STAGE_ROAD].LoadXFile("Asset/Models/Stage/Load.x");
	m_x[STAGE_TREE].LoadXFile("Asset/Models/Obstacle/obstacleTree.x");
	m_x[STAGE_HOUSE1].LoadXFile("Asset/Models/Stage/House1.x");
	m_x[STAGE_HOUSE3].LoadXFile("Asset/Models/Stage/House3.x");
	m_x[STAGE_CHURCH].LoadXFile("Asset/Models/Stage/Church.x");
	m_x[STAGE_TEMPLE].LoadXFile("Asset/Models/Stage/Temple.x");
}

void StageManager::Update() {
	for (int i = 0; i < STAGE_NUM; i++)
	{
		/*if (fabsf(m_playerPos.x - m_stageInfo[i].pos.x) > 50.0f || fabsf(m_playerPos.y - m_stageInfo[i].pos.y) > 50.0f || fabsf(m_playerPos.z - m_stageInfo[i].pos.z) > 50.0f)
		{
			m_stageInfo[i].enable = false;
		}
		else
		{
			m_stageInfo[i].enable = true;
		}*/
		m_stageInfo[i].enable = true;
	}
}

void StageManager::Draw() {
	for (int i = 1; i < STAGE_NUM; i++)
	{
		StageInfo info = m_stageInfo[i];
		if (info.pos.x == 0.0f &&info.pos.y == 0.0f &&info.pos.z == 0.0f)
		{
			int a = 0;
		}
		if (info.enable)
		{
			if (info.type == STAGE_CHURCH)
			{
				int a = 0;
			}
			if (i == 263) {
				int a = 0;
			}
			m_x[info.type].SetTranslation(info.pos);
			m_x[info.type].SetRotation(info.rot);
			m_x[info.type].SetScaling(info.scale.x);
			m_x[info.type].Update();
			m_x[info.type].Draw();
		}
	}
}

void StageManager::Finalize() {
	for (int i = STAGE_MAX - 1; i >= 0; i--)
	{
		m_x[i].Finalize();
	}
	delete[] m_x;
	delete[] m_stageInfo;
}

void StageManager::CreateStage(StageInfo info) {
	if (m_index == 462)
	{
		int a = 0;
	}
	m_stageInfo[m_index++] = info;
	if (m_index >= STAGE_NUM)
	{
		m_index = 0;
	}
}

void StageManager::CreateStage(D3DXVECTOR3 pos, STAGE_TYPE type, DIRECTION dir) {
	m_stageInfo[m_index++] = StageInfo(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), type, dir, false);
	if (m_index >= STAGE_NUM)
	{
		m_index = 0;
	}
}

void StageManager::CreateStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, STAGE_TYPE type, DIRECTION dir) {
	if (m_index == 462)
	{
		int a = 0;
	}
	m_stageInfo[m_index++] = StageInfo(pos, rot, D3DXVECTOR3(1.0f, 1.0f, 1.0f), type, dir, false);
	if (m_index >= STAGE_NUM)
	{
		m_index = 0;
	}
}

void StageManager::CreateStage(D3DXVECTOR3 pos, float scale, STAGE_TYPE type, DIRECTION dir) {
	if (m_index == 462)
	{
		int a = 0;
	}
	m_stageInfo[m_index++] = StageInfo(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(scale, scale, scale), type, dir, false);
	if (m_index >= STAGE_NUM)
	{
		m_index = 0;
	}
}

void StageManager::CreateStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float scale, STAGE_TYPE type, DIRECTION dir) {
	if (m_index == 462)
	{
		int a = 0;
	}
	m_stageInfo[m_index++] = StageInfo(pos, rot, D3DXVECTOR3(scale, scale, scale), type, dir, false);
	if (m_index >= STAGE_NUM)
	{
		m_index = 0;
	}
}

int StageManager::GetStageNum() {
	return m_index;
}

StageInfo* StageManager::GetStageInfo(int idx) {
	return &m_stageInfo[idx];
}

//OBB& StageManager::GetOBB(int index)const {
//	StageInfo info = m_stageInfo[index];
//	m_x[info.type].SetTranslation(info.pos);
//	m_x[info.type].SetRotation(info.rot);
//	m_x[info.type].SetScaling(info.scale);
//	m_x[info.type].Update();
//	return m_x[info.type].GetOBB();
//}

AABB& StageManager::GetAABB(int index) const{
	StageInfo info = m_stageInfo[index];
	m_x[info.type].SetTranslation(info.pos);
	m_x[info.type].Update();
	return m_x[info.type].GetAABB();
}

void StageManager::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}