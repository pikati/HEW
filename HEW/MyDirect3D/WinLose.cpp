#include "WinLose.h"

void WinLose::Initialize() {
	m_fbx = new Fbx[2];
	m_fbx[0].Initialize(false, false);
	m_fbx[1].Initialize(false, false);
	m_fbx[0].Load("Asset/Models/Player/win.fbx", true);
	m_fbx[1].Load("Asset/Models/Player/lose.fbx", true);
	m_fbx[0].SetRotationY(180.0f * RADIAN);
	m_fbx[1].SetRotationY(180.0f * RADIAN);

	m_pos = new D3DXVECTOR3[2];
	m_pos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_win = 0;
}

void WinLose::Update() {
	for (int i = 0; i < 2; i++) 
	{
		m_fbx[i].SetTranslation(m_pos[i]);
		m_fbx[i].SetScaling(0.01f);
		m_fbx[i].Update();
	}
}

void WinLose::Draw(int idx) {
	if (m_win == 0)
	{
		if (idx == 0)
		{
			m_fbx[0].Draw();
		}
		if (idx == 1)
		{
			m_fbx[1].Draw();
		}
	}
	if (m_win == 1)
	{
		if (idx == 0)
		{
			m_fbx[1].Draw();
		}
		if (idx == 1)
		{
			m_fbx[0].Draw();
		}
	}
}

void WinLose::Finalize() {
	delete[] m_pos;
	m_fbx[1].Finalize();
	m_fbx[0].Finalize();
	delete[] m_fbx;
}

void WinLose::SetPosition(D3DXVECTOR3 pos, int idx){
	m_pos[idx] = pos;
}

void WinLose::Win(int idx) {
	m_win = idx;
}