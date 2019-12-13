#include "ObstacleManager.h"

ObstacleManager::ObstacleManager()
{
}


ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::Initialize() {
	m_obstacle[0] = new Fire;
	m_obstacle[1] = new Tree;
	m_obstacle[2] = new SandStorm;
	m_obstacle[3] = new PitFall;
	m_obstacle[4] = new DriftWood;
	for (int i = 0; i < OBSTACLE_KIND; i++)
	{
		m_obstacle[i]->Initialize();
	}
}

void ObstacleManager::Update() {
}

void ObstacleManager::Draw() {
	for (int i = 0; i < (int)m_obstacleInfo.size(); i++)
	{
		m_obstacle[m_obstacleInfo[i].type]->SetPosition(m_obstacleInfo[i].pos);
		m_obstacle[m_obstacleInfo[i].type]->SetRotation(m_obstacleInfo[i].rot);
		m_obstacle[m_obstacleInfo[i].type]->SetScale(m_obstacleInfo[i].scale);
		m_obstacle[m_obstacleInfo[i].type]->Update();
		m_obstacle[m_obstacleInfo[i].type]->Draw();
	}
}

void ObstacleManager::Finalize() {
	m_obstacleInfo.erase(m_obstacleInfo.begin(), m_obstacleInfo.end());
	for (int i = OBSTACLE_KIND - 1; i >= 0; i--)
	{
		m_obstacle[i]->Finalize();
	}
	for (int i = OBSTACLE_KIND - 1; i >= 0; i--)
	{
		delete m_obstacle[i];
	}
}

void ObstacleManager::CreateObstacle(ObstacleInfo info) {
	m_obstacleInfo.push_back(info);
}

void ObstacleManager::CreateObstacle(D3DXVECTOR3 pos, OBST_TYPE type) {
	m_obstacleInfo.push_back(ObstacleInfo(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f), type));
}

int ObstacleManager::GetObstacleNum() {
	return (int)m_obstacleInfo.size();
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

COBBTree& ObstacleManager::GetOBB(OBST_TYPE type) const {
	return m_obstacle[type]->GetOBB();
}

void ObstacleManager::Hit(int idx) {
	m_obstacleInfo.erase(m_obstacleInfo.begin() + idx);
}

void ObstacleManager::SetPlayerPosition(D3DXVECTOR3 pos) {
	for (int i = 0; i < 5; i++)
	{
		m_obstacle[i]->SetPlayerPos(pos);
	}
}