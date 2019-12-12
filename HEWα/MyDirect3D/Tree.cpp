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
	m_pos.x = /*((float)(rand() % 10) - 5.0f) * 0.2f*/0.0f;
	m_pos.y = 0.2f;
	m_pos.z = 5.0f;
	m_pXmanager = new XManager;
	m_pXmanager->Initialize();
	m_pXmanager->SetTranslation(m_pos);
	m_pXmanager->LoadXFile("Models/Obst/obstacleTree.x", true);
	m_pXmanager->SetScaling(1.0f);
	m_bEnable = false;
	m_bHit = false;
	m_elem = TREE;
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
			m_pXmanager->SetTranslation(m_pos);
			m_pXmanager->Update();
		}
	}
}

void Tree::Draw() {
	m_pXmanager->SetTranslation(m_pos);
	m_pXmanager->Draw();
}

void Tree::Finalize() {
	m_pXmanager->Finalize();
	delete m_pXmanager;
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
//
//OBB* Tree::GetOBB() {
//	return m_pXmanager->GetOBB();
//}

void Tree::SetPosition(D3DXVECTOR3 pos) {
	m_pos = pos;
}

void Tree::SetRotation(D3DXVECTOR3 rot) {
	m_rot = rot;
}

void Tree::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
}

COBBTree& Tree::GetOBB() const {
	return m_pXmanager->GetOBB();
}

D3DXMATRIX* Tree::GetMatrix() {
	return m_pXmanager->GetMatrix();
}

void Tree::Reset() {
	m_bEnable = false;
	m_bHit = false;
}

OBST_TYPE Tree::GetElem() {
	return m_elem;
}