#include "PlayerManager.h"

#define OBSTACLE_EFFECT_TIME	150 

void PlayerManager::Initialize() {
	m_fbx = new Fbx;
	m_fbx->Initialize(true, true);
	m_fbx->SetScaling(0.01f);
	m_fbx->Load("Asset/Models/Player/susumi.fbx", true);
	m_player = new Player[2];
	m_player[0].Initialize();
	m_player[1].Initialize();
	m_goalTime[0] = 0;
	m_goalTime[1] = 0;
	m_shadow = new Shadow[2];
	m_shadow[0].Initialize();
	m_shadow[1].Initialize();
	m_shadow[0].CreateShadow();
	m_shadow[1].CreateShadow();
	m_shadow[0].SetPosition(m_player[0].GetPlayerPosition() + m_player[0].GetPlayerFlow());
	m_shadow[1].SetPosition(m_player[1].GetPlayerPosition() + m_player[1].GetPlayerFlow());
	m_obstacleEffectTime[0] = 0;
	m_obstacleEffectTime[1] = 0;
	m_sand = new DisplaySandStorm;
	m_sand->Initialize();
}

void PlayerManager::Update(bool b1, bool b2) {
	if (!b1)
	{
		m_player[0].Update(0);
		m_shadow[0].SetPosition(m_player[0].GetPlayerPosition() + m_player[0].GetPlayerFlow());
		if (m_obstacleEffectTime[0] > 0)
		{
			m_obstacleEffectTime[0]--;
		}
	}
	if (!b2)
	{
		m_player[1].Update(1);
		m_shadow[1].SetPosition(m_player[1].GetPlayerPosition() + m_player[1].GetPlayerFlow());
		if (m_obstacleEffectTime[1] > 0)
		{
			m_obstacleEffectTime[1]--;
		}
	}
}

void PlayerManager::Draw(int i) {
	PlayerInfo info = m_player[i].GetPlayerInfo();
	m_shadow[i].Draw();
	m_fbx->SetTranslation(info.position.x + info.flowPosition.x, info.position.y + info.flowPosition.y, info.position.z + info.flowPosition.z);
	m_fbx->SetRotationY(info.angle - 90.0f * RADIAN);
	m_fbx->SetRotationZ(info.curveAngle);
	m_fbx->SetScaling(0.01f);
	m_fbx->Draw();
	if (m_obstacleEffectTime[i] > 0)
	{
		if (i == 0)
		{
			m_sand->SetPlayer(true);
		}
		else
		{
			m_sand->SetPlayer(false);
		}
		m_sand->Draw();
	}
}

void PlayerManager::Finalize() {
	m_sand->Finalize();
	delete m_sand;
	m_shadow[1].Finalize();
	m_shadow[0].Finalize();
	delete[] m_shadow;
	delete[] m_player;
	m_fbx->Finalize();
	delete m_fbx;
}

//OBB& PlayerManager::GetOBB(int i)const {
//	PlayerInfo info = m_player[i].GetPlayerInfo();
//	m_fbx->SetTranslation(info.position.x + info.flowPosition.x, info.position.y + info.flowPosition.y, info.position.z + info.flowPosition.z);
//	m_fbx->SetRotationY(info.angle + 90.0f * RADIAN);
//	m_fbx->SetRotationZ(info.curveAngle);
//	m_fbx->Update();
//	return m_fbx->GetOBB();
//}

AABB& PlayerManager::GetAABB(int i)const {
	PlayerInfo info = m_player[i].GetPlayerInfo();
	m_fbx->SetTranslation(info.position.x + info.flowPosition.x, info.position.y + info.flowPosition.y, info.position.z + info.flowPosition.z);
	m_fbx->Update();
	return m_fbx->GetAABB();
}

D3DXVECTOR3 PlayerManager::GetPlayerPosition(int i) {
	return m_player[i].GetPlayerPosition();
}

float PlayerManager::GetPlayerAngle(int i) {
	return m_player[i].GetPlayerAngle();
}

D3DXVECTOR3 PlayerManager::GetPlayerFlow(int i) {
	return m_player[i].GetPlayerFlow();
}

void PlayerManager::Hit(int idx, DIRECTION dir) {
	m_player[idx].Hit(dir); 
}

CoolTime& PlayerManager::GetCoolTime(int idx) {
	return m_player[idx].GetCoolTime();
}

void PlayerManager::SetItemEffect(int idx, ITEM_TYPE type) {
	m_player[idx].SetItemEffect(type);
}

void PlayerManager::StartCoolTime(int idx) {
	m_player[idx].StartCoolTime();
}

void PlayerManager::GetGoalTime(int time, int idx)
{
	m_goalTime[idx] = time;
}

void PlayerManager::SetObstacleEffect(int idx, OBST_TYPE type) {
	switch (type)
	{
	case FIREWOOD:
		break;
	case TREE:
		break;
	case SANDSTORM:
		m_obstacleEffectTime[idx] = OBSTACLE_EFFECT_TIME;
		break;
	case PITFALL:
		break;
	case DRIFTWOOD:
		break;
	case OBST_MAX:
		break;
	default:
		break;
	}
}