#include "Wakka.h"
#include "Input.h"
#include "MyDirect3D.h"

//”¼Œa0.15

Wakka::Wakka() {
}

Wakka::~Wakka() {
}

void Wakka::Initialize(ELEM elem) {
	m_elem = elem;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_x = new XManager;
	m_x->Initialize(true, true);
	m_x->SetMinMax(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	DecidePosition(0);
	SetElem();
	m_playerAngle = 90.0f * (D3DX_PI / 180.0f);
	m_shotPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_shotAngle = 0.0f;
	m_frame = 0;
}

void Wakka::Update() {
	m_x->SetTranslation(m_pos);
	m_x->SetRotation(m_rot);
	m_x->SetScaling(m_scale.x);
	m_x->Update();
}

void Wakka::Draw() {
	m_x->Draw();
}

void Wakka::Finalize() {
	m_x->Finalize();
}

void Wakka::DecidePosition(int center) {
	switch (m_elem)
	{
	case FIRE:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case WATER:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case SAND:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case SOIL:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	case WOOD:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.4f) * 0.5f);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 0.8f) * 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.2f) * 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle + D3DX_PI * 1.6f) * 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle) * 0.5f);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Wakka::SetElem() {
	switch (m_elem)
	{
	case FIRE:
		m_x->LoadXFile("Asset/Models/Wakka/Red.x");
		break;
	case WATER:
		m_x->LoadXFile("Asset/Models/Wakka/Blue.x");
		break;
	case SAND:
		m_x->LoadXFile("Asset/Models/Wakka/Yellow.x");
		break;
	case SOIL:
		m_x->LoadXFile("Asset/Models/Wakka/Tuchi.x");
		break;
	case WOOD:
		m_x->LoadXFile("Asset/Models/Wakka/Green.x");
		break;
	default:
		break;
	}
}

D3DXVECTOR3 Wakka::GetPosition() {
	return m_pos;
}

bool Wakka::CollisionObstacle(ELEM elem) {
	switch (elem) {
	case FIRE:
		if (m_elem == WATER) {
			return true;
		}
		return false;
	case WATER:
		if (m_elem == WATER) {
			return true;
		}
		return false;
	case SAND:
		if (m_elem == SOIL) {
			return true;
		}
		return false;
	case SOIL:
	case WOOD:
		if (m_elem == FIRE) {
			return true;
		}
		else {
			return false;
		}
	default:
		return false;
		break;
	}
}

ELEM Wakka::GetElem() {
	return m_elem;
}

//OBB& Wakka::GetOBB()const {
//	m_x->SetTranslation(m_pos);
//	m_x->SetRotation(m_rot);
//	m_x->SetScaling(m_scale.x);
//	m_x->Update();
//	return m_x->GetOBB();
//}

AABB& Wakka::GetAABB()const {
	m_x->SetTranslation(m_pos);
	m_x->Update();
	return m_x->GetAABB();
}

bool Wakka::MoveForward() {
	m_pos = D3DXVECTOR3(m_shotPos.x - cosf(m_shotAngle) * (0.7f * ++m_frame), m_shotPos.y, m_shotPos.z + sinf(m_shotAngle) * (0.7f * ++m_frame));
	m_x->SetTranslation(m_pos);
	if (m_frame > 40) 
	{
		m_frame = 0;
		return true;
	}
	return false;
}

void Wakka::SetPlayerPosition(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void Wakka::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Wakka::SetPlayerAngle(float angle) {
	m_playerAngle = angle;
}

void Wakka::SetShotPosition(D3DXVECTOR3 pos) {
	m_shotPos = pos;
}

void Wakka::SetShotAngle(float angle) {
	m_shotAngle = angle;
}

void Wakka::ResetFrame() {
	m_frame = 0;
}