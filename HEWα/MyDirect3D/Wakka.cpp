#include "Wakka.h"
#include "Enum.h"
#include "Input.h"
#include "MyDirect3D.h"
//”¼Œa0.15
#define KAZU 4

Wakka::Wakka() {
}

Wakka::~Wakka() {
}

void Wakka::Initialize(ELEM elem) {
	m_elem = elem;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model = new XManager;
	m_model->Initialize();
	SetElemModel();
}

void Wakka::Update(D3DXVECTOR3 playerPos) {
	
}

void Wakka::Draw() {
	m_model->Draw();
}

void Wakka::Finalize() {
	m_model->Finalize();
}

void Wakka::SetPosition(int i) {
	if (m_shoot) {
		
		if (m_frame > 50) {
			m_frame = 0;
			m_shoot = false;
		}
		return;
	}
	if (i == 0) {
		switch (m_elem)
		{

		case FIRE:
			switch (m_center1)
			{
			case 0:
				m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
				break;
			case 1:
				m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
				break;
			case 2:
				m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 3:
				m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 4:
				m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
				break;
			default:
				break;
			}

			break;
		case WATER:
			switch (m_center1)
			{
			case 0:
				m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
				break;
			case 1:
				m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
				break;
			case 2:
				m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
				break;
			case 3:
				m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 4:
				m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			default:
				break;
			}
			break;
		case SAND:
			switch (m_center1)
			{
			case 0:
				m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 1:
				m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
				break;
			case 2:
				m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
				break;
			case 3:
				m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
				break;
			case 4:
				m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			default:
				break;
			}
			break;
		case SOIL:
			switch (m_center1)
			{
			case 0:
				m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 1:
				m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 2:
				m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
				break;
			case 3:
				m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
				break;
			case 4:
				m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
				break;
			default:
				break;
			}
			break;
		case WOOD:
			switch (m_center1)
			{
			case 0:
				m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
				break;
			case 1:
				m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 2:
				m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
				break;
			case 3:
				m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
				break;
			case 4:
				m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else {
	switch (m_elem)
	{

	case FIRE:
		switch (m_center2)
		{
		case 0:
			m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
			break;
		case 1:
			m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
			break;
		case 2:
			m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 3:
			m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 4:
			m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
			break;
		default:
			break;
		}

		break;
	case WATER:
		switch (m_center2)
		{
		case 0:
			m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
			break;
		case 1:
			m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
			break;
		case 2:
			m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
			break;
		case 3:
			m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 4:
			m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SAND:
		switch (m_center2)
		{
		case 0:
			m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 1:
			m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
			break;
		case 2:
			m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
			break;
		case 3:
			m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
			break;
		case 4:
			m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		default:
			break;
		}
		break;
	case SOIL:
		switch (m_center2)
		{
		case 0:
			m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 1:
			m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 2:
			m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
			break;
		case 3:
			m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
			break;
		case 4:
			m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
			break;
		default:
			break;
		}
		break;
	case WOOD:
		switch (m_center2)
		{
		case 0:
			m_model->SetTranslation(m_pos.x + 0.5f, m_pos.y, m_pos.z);
			break;
		case 1:
			m_model->SetTranslation(m_pos.x + 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 2:
			m_model->SetTranslation(m_pos.x - 0.35f, m_pos.y, m_pos.z - 0.5f);
			break;
		case 3:
			m_model->SetTranslation(m_pos.x - 0.5f, m_pos.y, m_pos.z);
			break;
		case 4:
			m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 0.5f);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	}
	
}

void Wakka::SetElemModel() {
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

void Wakka::Shoot() {
	m_shoot = true;
}

int Wakka::GetCenter(int i) {
	if (i == 0) {
		return m_center1;
	}
	return m_center2;
}

void Wakka::Hit() {
	m_shoot = false;
	m_frame = 0;
}

D3DXVECTOR3 Wakka::GetPosition() {
	return m_pos;
}

/*‡”Ô‚®‚¿‚á‚®‚¿‚á‚¾‚©‚ç‹C‚ð‚Â‚¯‚ëII*/
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

bool Wakka::IsShoot() {
	return m_shoot;
}

ELEM Wakka::GetElem() {
	return m_elem;
}

//OBB* Wakka::GetOBB() {
//	return m_model->GetOBB();
//}

COBBTree& Wakka::GetOBB() const{
	return m_model->GetOBB();
}

D3DXMATRIX* Wakka::GetMatrix() {
	return m_model->GetMatrix();
}

void Wakka::MoveForward(int frame) {
	m_model->SetTranslation(m_pos.x, m_pos.y, m_pos.z + 1.0f + 0.25f * frame);
}

void Wakka::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}