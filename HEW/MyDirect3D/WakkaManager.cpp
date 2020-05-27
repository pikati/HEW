#define _CRT_SECURE_NO_WARNINGS
#include "WakkaManager.h"
#include "Utility.h"

#define WAKKA_NUM  5
#define FEVER_TIME 100

WakkaManager::WakkaManager()
{
}


WakkaManager::~WakkaManager()
{
}

void WakkaManager::Initialize(int idx) {
	m_wakka = new Wakka[WAKKA_NUM];
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		CreateWakka((ELEM)i);
		m_shoot[i] = false;
	}

	m_combo = new Combo;
	m_combo->Initialize();
	D3DXVECTOR2 pos;
	if (idx == 0)
	{
		pos = D3DXVECTOR2(100.0f, 650.0f);
	}
	else {
		pos = D3DXVECTOR2(740.0f, 650.0f);
	}
	m_combo->SetPosition(pos);


	m_fever = true;
	m_feverTime = FEVER_TIME;

	m_center = 0;
	
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_playerAngle = 0.0f;
	m_destroyObstacleNum = 0;
	m_playerFlowPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void WakkaManager::Update() {
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		m_wakka[i].SetPlayerPosition(m_playerPos);
		if (m_shoot[i])
		{
			ShotUpdate(i);
		}
		else
		{
			//m_wakka[i].DecidePosition(m_center);
			LerpUpdate(i);
		}
		m_wakka[i].Update();
	}
	CheckFever();
	FeverUpdate();
}

void WakkaManager::Draw() {
	m_combo->Draw();
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		m_wakka[i].Draw();
	}
}

void WakkaManager::Finalize() {
	m_combo->Finalize();
	delete m_combo;
	for (int i = WAKKA_NUM - 1; i >= 0; i--)
	{
		m_wakka[i].Finalize();
	}
	delete[] m_wakka;
}

void WakkaManager::CreateWakka(ELEM elem) {
	m_wakka[(int)elem].Initialize(elem);
}

void WakkaManager::ShotUpdate(int i) {
	if (m_wakka[i].MoveForward())
	{
		m_shoot[i] = false;
		m_combo->CountReset();
	}
}

void WakkaManager::Change(int dir) {
	//‰E‚ÉU‚Á‚½Žž
	if (dir == 0)
	{
		m_center++;
		if (m_center >= WAKKA_NUM) {
			m_center = 0;
		}
	}
	else
	{
		m_center--;
		if (m_center < 0) {
			m_center = WAKKA_NUM - 1;
		}
	}
}

void WakkaManager::Shoot() {
	if (!m_shoot[m_center])
	{
		m_wakka[m_center].SetShotPosition(m_playerPos);
		m_wakka[m_center].SetShotAngle(m_playerAngle);
		m_shoot[m_center] = true;
	}
}

int WakkaManager::GetCenter() {
	return m_center;
}

void WakkaManager::Hit(int idx) {
	m_shoot[idx] = false;
	m_wakka[idx].ResetFrame();
}

bool WakkaManager::IsShoot(int i) {
	return m_shoot[i];
}

ELEM WakkaManager::GetElem(int i) {
	return m_wakka[i].GetElem();
}

void WakkaManager::LerpUpdate(int i) {
	D3DXVECTOR3 startPos = m_wakka[i].GetPosition();
	startPos.x += m_playerFlowPos.x;
	startPos.y += m_playerFlowPos.y;
	startPos.z += m_playerFlowPos.z;
	D3DXVECTOR3 endPos = GetEndPos(i);
	Lerp(&startPos, &startPos, &endPos, 0.4f);
	
	m_wakka[i].SetPosition(startPos);
}

D3DXVECTOR3	WakkaManager::GetEndPos(int i) {
	D3DXVECTOR3 endPos;
	switch (m_wakka[i].GetElem())
	{
	case FIRE:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case WATER:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case SAND:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case SOIL:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case WOOD:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return endPos;
}

void WakkaManager::SetPlayerPosition(D3DXVECTOR3 playerPos) {
	m_playerPos = playerPos;
}

D3DXVECTOR3* WakkaManager::Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t) {
	out->x = start->x + t * (end->x - start->x);
	out->y = start->y + t * (end->y - start->y);
	out->z = start->z + t * (end->z - start->z);
	return out;
}

void WakkaManager::SetPlayerAngle(float angle) {
	m_playerAngle = angle;
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		m_wakka[i].SetPlayerAngle(angle);
	}
}

//COBBTree& WakkaManager::GetOBB(int idx) const{
//	return m_wakka[idx].GetOBB();
//}
//
//D3DXMATRIX* WakkaManager::GetMatrix(int idx) {
//	return m_wakka[idx].GetMatrix();
//}

//OBB& WakkaManager::GetOBB(int idx)const {
//	return m_wakka[idx].GetOBB();
//}

AABB& WakkaManager::GetAABB(int idx)const {
	return m_wakka[idx].GetAABB();
}

D3DXVECTOR3 WakkaManager::GetPosition(int idx) {
	return m_wakka[idx].GetPosition();
}

int WakkaManager::GetDestroyObstacleNum() {
	return m_combo->GetCombo();
}

void WakkaManager::DestroyObstacleCountUp() {
	m_combo->CountUp();
}

void WakkaManager::SetPlayerFlow(D3DXVECTOR3 pos) {
	m_playerFlowPos = pos;
}

void WakkaManager::CheckFever() {
	int conboCount = m_combo->GetCombo();
	if (conboCount % 10 == 0 && conboCount != 0)
	{
		m_fever = true;
	}
}

void WakkaManager::FeverUpdate() {
	if (m_fever)
	{
		m_feverTime--;
		if (m_feverTime <= 0)
		{
			m_feverTime = FEVER_TIME;
			m_fever = false;
		}
	}
}

bool WakkaManager::GetIsFever() {
	return m_fever;
}

int WakkaManager::GetComboCount() {
	return m_combo->GetCombo();
}