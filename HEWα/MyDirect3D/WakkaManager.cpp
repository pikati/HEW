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
	m_bLerp = false;
}

void WakkaManager::Update() {
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		if (m_shoot && m_center == i)
		{
			ShotUpdate();
		}
		else if (m_bLerp)
		{
			LerpUpdate();
			m_t += 0.1f;
			if (m_t > 1.0f)
			{
				m_t = 0;
				m_bLerp = false;
			}
		}
		m_wakka[i].Update(m_playerPos);
	}
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
	//右に振った時
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

void WakkaManager::LerpUpdate() {
	for (int i = 0; i < WAKKA_NUM; i++)
	{
		if (m_center != i)
		{
			D3DXMATRIX matStart;
			D3DXMATRIX matEnd;
			D3DXVECTOR3 pos = m_wakka[i].GetPosition();
			D3DXMatrixIdentity(&matStart);
			D3DXMatrixIdentity(&matEnd);
			D3DXMatrixTranslation(&matStart, pos.x, pos.y, pos.z);
			GetEndMatrix(&matEnd, i);
			CalcInterPause(&matStart, &matStart, &matEnd, m_t);
			m_wakka[i].SetPosition(D3DXVECTOR3(matStart._14, matStart._24, matStart._34));
		}
	}
}

D3DXVECTOR3* WakkaManager::SphereLinear(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t) {

	D3DXVECTOR3 s, e;
	D3DXVec3Normalize(&s, start);
	D3DXVec3Normalize(&e, end);


	// 2ベクトル間の角度（鋭角側）
	float angle = acos(D3DXVec3Dot(&s, &e));

	// sinθ
	float SinTh = sin(angle);

	// 補間係数
	float Ps = sin(angle * (1 - t));
	float Pe = sin(angle * t);

	*out = (Ps * s + Pe * e) / SinTh;

	// 一応正規化して球面線形補間に
	D3DXVec3Normalize(out, out);

	return out;
}

D3DXMATRIX* WakkaManager::CalcInterPause(D3DXMATRIX* out, D3DXMATRIX* start, D3DXMATRIX* end, float t) {

	// 各姿勢ベクトル抽出
	D3DXVECTOR3 Sy, Sz;
	D3DXVECTOR3 Ey, Ez;

	memcpy(&Sy, start->m[1], sizeof(float) * 3);
	memcpy(&Sz, start->m[2], sizeof(float) * 3);
	memcpy(&Ey, end->m[1], sizeof(float) * 3);
	memcpy(&Ez, end->m[2], sizeof(float) * 3);

	// 中間ベクトル算出
	D3DXVECTOR3 IY, IZ;
	SphereLinear(&IY, &Sy, &Ey, t);
	SphereLinear(&IZ, &Sz, &Ez, t);

	// 中間ベクトルから姿勢ベクトルを再算出
	D3DXVECTOR3 IX;
	D3DXVec3Cross(&IX, &IY, &IZ);
	D3DXVec3Cross(&IY, &IZ, &IX);
	D3DXVec3Normalize(&IX, &IX);
	D3DXVec3Normalize(&IY, &IY);
	D3DXVec3Normalize(&IZ, &IZ);

	memset(out, 0, sizeof(D3DXMATRIX));
	memcpy(out->m[0], &IX, sizeof(float) * 3);
	memcpy(out->m[1], &IY, sizeof(float) * 3);
	memcpy(out->m[2], &IZ, sizeof(float) * 3);
	out->_44 = 1.0f;

	return out;
}

D3DXMATRIX*	WakkaManager::GetEndMatrix(D3DXMATRIX* out, int i) {
	D3DXVECTOR3 endPos;
	D3DXVECTOR3 pos = m_wakka[i].GetPosition();
	switch (m_wakka[i].GetElem())
	{
	case FIRE:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(pos.x, pos.y, pos.z + 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(pos.x + 0.5f, pos.y, pos.z);

			break;
		case 2:
			endPos = D3DXVECTOR3(pos.x + 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(pos.x - 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(pos.x - 0.5f, pos.y, pos.z);
			break;
		default:
			break;
		}

		break;
	case WATER:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(pos.x - 0.5f, pos.y, pos.z);
			break;
		case 1:
			endPos = D3DXVECTOR3(pos.x, pos.y, pos.z + 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(pos.x + 0.5f, pos.y, pos.z);
			break;
		case 3:
			endPos = D3DXVECTOR3(pos.x + 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(pos.x - 0.35f, pos.y, pos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SAND:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(pos.x - 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(pos.x - 0.5f, pos.y, pos.z);
			break;
		case 2:
			endPos = D3DXVECTOR3(pos.x, pos.y, pos.z + 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(pos.x + 0.5f, pos.y, pos.z);
			break;
		case 4:
			endPos = D3DXVECTOR3(pos.x + 0.35f, pos.y, pos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SOIL:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(pos.x + 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 1:
			endPos = D3DXVECTOR3(pos.x - 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(pos.x - 0.5f, pos.y, pos.z);
			break;
		case 3:
			endPos = D3DXVECTOR3(pos.x, pos.y, pos.z + 0.5f);
			break;
		case 4:
			endPos = D3DXVECTOR3(pos.x + 0.5f, pos.y, pos.z);
			break;
		default:
			break;
		}
		break;
	case WOOD:
		switch (m_center)
		{
		case 0:
			endPos = D3DXVECTOR3(pos.x + 0.5f, pos.y, pos.z);
			break;
		case 1:
			endPos = D3DXVECTOR3(pos.x + 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 2:
			endPos = D3DXVECTOR3(pos.x - 0.35f, pos.y, pos.z - 0.5f);
			break;
		case 3:
			endPos = D3DXVECTOR3(pos.x - 0.5f, pos.y, pos.z);
			break;
		case 4:
			endPos = D3DXVECTOR3(pos.x, pos.y, pos.z + 0.5f);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	D3DXMatrixIdentity(out);
	D3DXMatrixTranslation(out, pos.x, pos.y, pos.z);
	return out;
}

void WakkaManager::SetPlayerPosition(D3DXVECTOR3 playerPos) {
	m_playerPos = playerPos;
}