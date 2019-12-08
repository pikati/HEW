#include "WakkaManager.h"

static const int WAKKA_NUM = 5;

WakkaManager::WakkaManager()
{
}


WakkaManager::~WakkaManager()
{
}

void WakkaManager::Initialize() {
	m_wakka = new Wakka[WAKKA_NUM];
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		CreateWakka((ELEM)i);
	}
	m_center = 0;
	m_frame = 0;
	m_shoot = false;
}

void WakkaManager::Update() {
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		m_wakka[i].SetPlayerPosition(m_playerPos);
		m_wakka[i].DecidePosition(m_center);
		if (m_shoot && m_center == i)
		{
			ShotUpdate();
		}
		else
		{
			LerpUpdate(i);
		}
		m_wakka[i].Update();
	}
}

void WakkaManager::Draw() {
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		m_wakka[i].Draw();
	}
}

void WakkaManager::Finalize() {
	for (int i = WAKKA_NUM - 1; i >= 0; i--)
	{
		m_wakka[i].Finalize();
	}
	delete[] m_wakka;
}

void WakkaManager::CreateWakka(ELEM elem) {
	m_wakka[(int)elem].Initialize(elem);
}

void WakkaManager::ShotUpdate() {
	m_wakka[m_center].MoveForward(++m_frame);
	if (m_frame > 50)
	{
		m_frame = 0;
		m_shoot = false;
	}
}

void WakkaManager::Change(int dir) {
	//‰E‚ÉU‚Á‚½Žž
	if (dir = 0)
	{
		m_center++;
		if (m_center > WAKKA_NUM) {
			m_center = 0;
		}
	}
	else
	{
		m_center--;
		if (m_center < WAKKA_NUM) {
			m_center = WAKKA_NUM - 1;
		}
	}
}

void WakkaManager::Shoot() {
	m_shoot = true;
}

int WakkaManager::GetCenter() {
	return m_center;
}

void WakkaManager::Hit() {
	m_shoot = false;
	m_frame = 0;
}

bool WakkaManager::IsShoot() {
	return m_shoot;
}

ELEM WakkaManager::GetElem(int i) {
	return m_wakka[i].GetElem();
}

void WakkaManager::LerpUpdate(int i) {
	D3DXVECTOR3 startPos = m_wakka[i].GetPosition();
	D3DXVECTOR3 endPos = GetEndPos(i);
	Lerp(&startPos, &startPos, &endPos, 0.1f);
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
			endPos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);

			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		default:
			break;
		}

		break;
	case WATER:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SAND:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SOIL:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		default:
			break;
		}
		break;
	case WOOD:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 1:
			endPos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 4:
			endPos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
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
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		m_wakka[i].SetPlayerAngle(angle);
	}
}