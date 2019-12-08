#include "Wakka.h"
#include "Enum.h"
#include "Input.h"
#include "MyDirect3D.h"
//���a0.15
#define KAZU 4

Wakka::Wakka() {
}

Wakka::~Wakka() {
}

void Wakka::Initialize(ELEM elem) {
	m_elem = elem;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model = new XManager;
	m_model->Initialize();
	DecidePosition(0);
	SetElem();
	m_playerAngle = 90.0f * (D3DX_PI / 180.0f);
}

void Wakka::Update() {
	m_model->SetTranslation(m_pos);
	m_model->Update();
}

void Wakka::Draw() {
	m_model->Draw();
}

void Wakka::Finalize() {
	m_model->Finalize();
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
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle * 0.2f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle * 0.2f) * 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle * 0.4f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle * 0.4f) * 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle * 0.6f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle * 0.6f) * 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x - cosf(m_playerAngle * 0.8f) * 0.5f, m_playerPos.y, m_playerPos.z + sinf(m_playerAngle * 0.8f) * 0.5f);
			break;
		default:
			break;
		}
		break;
	/*case 0:
		m_pos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
		break;
	case 1:
		m_pos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
		break;
	case 2:
		m_pos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
		break;
	case 3:
		m_pos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
		break;
	case 4:
		m_pos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
		break;*/
	default:
	case WATER:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SAND:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SOIL:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		default:
			break;
		}
		break;
	case WOOD:
		switch (center)
		{
		case 0:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 1:
			m_pos = D3DXVECTOR3(m_playerPos.x + 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 2:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.35f, m_playerPos.y, m_playerPos.z - 0.5f);
			break;
		case 3:
			m_pos = D3DXVECTOR3(m_playerPos.x - 0.5f, m_playerPos.y, m_playerPos.z);
			break;
		case 4:
			m_pos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 0.5f);
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
		m_model->LoadXFile("Models/Red.x", true);
		break;
	case WATER:
		m_model->LoadXFile("Models/Blue.x", true);
		break;
	case SAND:
		m_model->LoadXFile("Models/Yellow.x", true);
		break;
	case SOIL:
		m_model->LoadXFile("Models/Tuchi.x", true);
		break;
	case WOOD:
		m_model->LoadXFile("Models/Green.x", true);
		break;
	default:
		break;
	}
}

D3DXVECTOR3 Wakka::GetPosition() {
	return m_pos;
}

/*���Ԃ����Ⴎ���Ⴞ����C������I�I*/
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

//OBB* Wakka::GetOBB() {
//	return m_model->GetOBB();
//}

COBBTree& Wakka::GetOBB() const {
	return m_model->GetOBB();
}

D3DXMATRIX* Wakka::GetMatrix() {
	return m_model->GetMatrix();
}

void Wakka::MoveForward(int frame) {
	m_pos = D3DXVECTOR3(m_playerPos.x, m_playerPos.y, m_playerPos.z + 1.0f + 0.25f * frame);
	m_model->SetTranslation(m_pos);

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