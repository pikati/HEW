#include "ObstacleManager.h"

ObstacleManager::ObstacleManager()
{
}

ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::Initialize() {
	m_x = new XManager[OBST_MAX];
	for (int i = 0; i < OBST_MAX; i++)
	{
		m_x[i].Initialize(true, true);
		m_x[i].SetMinMax(D3DXVECTOR3(-0.35f, -10.35f, -0.35f), D3DXVECTOR3(0.35f, 10.35f, 0.35f));
	}

	m_obstacleInfo.resize(OBSTACLE_NUM);
	m_x[FIREWOOD].LoadXFile("Asset/Models/Obstacle/obstacleFire.x");
	m_x[TREE].LoadXFile("Asset/Models/Obstacle/obstacleTree.x");
	m_x[SANDSTORM].LoadXFile("Asset/Models/Obstacle/obstacleSandStorm.x");
	m_x[PITFALL].LoadXFile("Asset/Models/Obstacle/obstaclePitFall.x");
	m_x[DRIFTWOOD].LoadXFile("Asset/Models/Obstacle/obstacleDriftWood.x");
	m_x[TREE].SetScaling(0.1f);
	m_index = 0;	
	m_x[TREE].Update();
	
	for (int i = 0; i < m_obstacleInfo.size(); i++)
	{
		m_obstacleInfo[i].pos = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	}
}

void ObstacleManager::Update() {
	for (int i = 0; i < m_obstacleInfo.size(); i++)
	{
		if (fabsf(m_playerPos.x - m_obstacleInfo[i].pos.x) > 50.0f || fabsf(m_playerPos.y - m_obstacleInfo[i].pos.y) > 50.0f || fabsf(m_playerPos.z - m_obstacleInfo[i].pos.z) > 50.0f)
		{
			m_obstacleInfo[i].enable = false;
		}
		else
		{
			if (!m_obstacleInfo[i].hit)
			{
				m_obstacleInfo[i].enable = true;
			}
		}
	}
}

void ObstacleManager::Draw() {
	for (int i = 0; i < m_obstacleInfo.size(); i++)
	{
		if (m_obstacleInfo[i].enable)
		{
			m_x[m_obstacleInfo[i].type].SetTranslation(m_obstacleInfo[i].pos);
			m_x[m_obstacleInfo[i].type].SetRotation(m_obstacleInfo[i].rot);
			m_x[m_obstacleInfo[i].type].SetScaling(m_obstacleInfo[i].scale.x);
			m_x[m_obstacleInfo[i].type].Update();
			m_x[m_obstacleInfo[i].type].Draw();
		}
	}
}

void ObstacleManager::Finalize() {
	for (int i = OBST_MAX - 1; i >= 0; i--)
	{
		m_x[i].Finalize();
	}
	delete[] m_x;
}

void ObstacleManager::CreateObstacle(ObstacleInfo info) {
	m_obstacleInfo[m_index++] = info;
	if (m_index >= m_obstacleInfo.size())
	{
		m_index = 0;
	}
}

void ObstacleManager::CreateObstacle(D3DXVECTOR3 pos, OBST_TYPE type) {
	D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	if (type == DRIFTWOOD)
	{
		scale = D3DXVECTOR3(2.5f, 2.5f, 2.5f);
	}
	m_obstacleInfo[m_index++] = ObstacleInfo(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale, type, false, false, -1);
	if (m_index >= m_obstacleInfo.size())
	{
		m_index = 0;
	}
}

int ObstacleManager::GetObstacleNum() {
	/*int num = 0;
	for (int i = 0; i < m_obstacleInfo.size(); i++)
	{
		if (m_obstacleInfo[i].enable)
		{
			num++;
		}
	}*/
	return int(m_obstacleInfo.size());
}

ObstacleInfo* ObstacleManager::GetObstacleInfo(int idx) {
	return &m_obstacleInfo[idx];
}

D3DXVECTOR3 ObstacleManager::GetObstaclePosition(int idx) {
	return m_obstacleInfo[idx].pos;
}

D3DXVECTOR3 ObstacleManager::GetObstacleRotation(int idx) {
	return m_obstacleInfo[idx].rot;
}

AABB& ObstacleManager::GetAABB(int idx)const {
	ObstacleInfo info = m_obstacleInfo[idx];
	m_x[info.type].SetTranslation(info.pos);
	m_x[info.type].Update();
	return m_x[info.type].GetAABB();
}

void ObstacleManager::Hit(int idx) {
	m_obstacleInfo[idx].enable = false;
	m_obstacleInfo[idx].hit = true;
}

void ObstacleManager::SetPlayerPosition(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void ObstacleManager::SetParticleIndex(int particleIdx) {
	m_obstacleInfo[m_index - 1].particleIndex = particleIdx;
}

int ObstacleManager::GetParticleIndex(int idx) {
	int index = m_obstacleInfo[idx].particleIndex;
	OBST_TYPE type = m_obstacleInfo[idx].type;
	m_obstacleInfo.erase(m_obstacleInfo.begin() + idx);
	if (type == SANDSTORM)
	{
		for (int i = idx; i < m_obstacleInfo.size(); i++)
		{
			if (m_obstacleInfo[i].type == SANDSTORM)
			{
				m_obstacleInfo[i].particleIndex--;
			}
		}
	}
	
	return index;
}