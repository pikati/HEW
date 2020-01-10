#include "Tree.h"
#include "main.h"
#include <stdlib.h>

Tree::Tree()
{
}


Tree::~Tree()
{
}

void Tree::Initialize()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_obst = new Fbx;
	m_obst->Initialize();
	m_obst->SetTranslation(m_pos);
	m_obst->Load("Models/FBX/obstacleTree.fbx", false);
	m_obst->SetScaling(1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = FIREDRIFTWOOD;
}

void Tree::Update() {
	if (fabs(m_playerPos.y - m_pos.y) > 30.0f || fabs(m_playerPos.z - m_pos.z) > 30.0f || fabs(m_playerPos.x - m_pos.x) > 30.0f)
	{
		m_bEnable = false;
	}
	else {
		if (!m_bHit)
		{
			m_bEnable = true;
			m_obst->SetTranslation(m_pos);
			m_obst->Update();
		}
	}
}

void Tree::Draw() {
	m_obst->SetTranslation(m_pos);
	m_obst->Draw();
}

void Tree::Finalize() {
	m_obst->Finalize();
	delete m_obst;
}

D3DXVECTOR3 Tree::GetPosition() {
	return m_pos;
}

void Tree::Hit() {
	m_bEnable = false;
	m_bHit = true;
}

bool Tree::IsEnable() {
	return m_bEnable;
}

void Tree::CreateObstacle(D3DXVECTOR3 pos) {
	m_pos = pos;
	m_pos.y += 0.2f;
}

float* Tree::CreateRondam(float* random) {
	random[0] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	do {
		random[1] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[1]);
	do {
		random[2] = ((float)(rand() % 5) - 2.0f) * 0.5f;
	} while (random[0] == random[2] || random[1] == random[2]);
	return random;
}

void Tree::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

OBB& Tree::GetOBB()const {
	return m_obst->GetOBB();
}

void Tree::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Tree::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Tree::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

//COBBTree& Tree::GetOBB() const {
//	return m_obst->GetOBB();
//}
//
//D3DXMATRIX* Tree::GetMatrix() {
//	return m_obst->GetMatrix();
//}

void Tree::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE Tree::GetElem() {
	return m_elem;
}