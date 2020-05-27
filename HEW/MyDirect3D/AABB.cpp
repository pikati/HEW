#include "AABB.h"
#include "MyDirect3D.h"
#include "main.h"

void AABB::Initialize(D3DXVECTOR3 min, D3DXVECTOR3 max, D3DXVECTOR3 pos) {
	m_max = max;
	m_min = min;
	m_pos = pos;
	for (int i = 0; i < 14; i++)
	{
		m_v[i].color = D3DXCOLOR(0,0,255,255);
	}
	m_v[0].pos = m_max + m_pos;
	m_v[1].pos = D3DXVECTOR3(m_min.x + m_pos.x, m_max.y + m_pos.y, m_max.z + m_pos.z);
	m_v[2].pos = D3DXVECTOR3(m_min.x + m_pos.x, m_min.y + m_pos.y, m_max.z + m_pos.z);
	m_v[3].pos = D3DXVECTOR3(m_max.x + m_pos.x, m_min.y + m_pos.y, m_max.z + m_pos.z);
	m_v[4].pos = D3DXVECTOR3(m_max.x + m_pos.x, m_max.y + m_pos.y, m_min.z + m_pos.z);
	m_v[5].pos = D3DXVECTOR3(m_min.x + m_pos.x, m_max.y + m_pos.y, m_min.z + m_pos.z);
	m_v[6].pos = D3DXVECTOR3(m_min.x + m_pos.x, m_min.y + m_pos.y, m_min.z + m_pos.z);
	m_v[7].pos = D3DXVECTOR3(m_max.x + m_pos.x, m_min.y + m_pos.y, m_min.z + m_pos.z);
	m_v[8].pos = m_max + m_pos;
	m_v[9].pos = D3DXVECTOR3(m_max.x + m_pos.x, m_max.y + m_pos.y, m_min.z + m_pos.z);
	m_v[10].pos = D3DXVECTOR3(m_max.x + m_pos.x, m_min.y + m_pos.y, m_max.z + m_pos.z);
	m_v[11].pos = D3DXVECTOR3(m_max.x + m_pos.x, m_min.y + m_pos.y, m_min.z + m_pos.z);
	m_v[12].pos = D3DXVECTOR3(m_min.x + m_pos.x, m_max.y + m_pos.y, m_max.z + m_pos.z);
	m_v[13].pos = D3DXVECTOR3(m_min.x + m_pos.x, m_max.y + m_pos.y, m_min.z + m_pos.z);
}

void AABB::Update(const D3DXVECTOR3& pos) {
	m_pos = pos;
	m_v[0].pos = m_max;
	m_v[1].pos = D3DXVECTOR3(m_min.x, m_max.y, m_max.z);
	m_v[2].pos = D3DXVECTOR3(m_min.x, m_min.y, m_max.z);
	m_v[3].pos = D3DXVECTOR3(m_max.x, m_min.y, m_max.z);
	m_v[4].pos = D3DXVECTOR3(m_max.x, m_max.y, m_min.z);
	m_v[5].pos = D3DXVECTOR3(m_min.x, m_max.y, m_min.z);
	m_v[6].pos = D3DXVECTOR3(m_min.x, m_min.y, m_min.z);
	m_v[7].pos = D3DXVECTOR3(m_max.x, m_min.y, m_min.z);
	m_v[8].pos = m_max;
	m_v[9].pos = D3DXVECTOR3(m_max.x, m_max.y, m_min.z);
	m_v[10].pos = D3DXVECTOR3(m_max.x, m_min.y, m_max.z);
	m_v[11].pos = D3DXVECTOR3(m_max.x, m_min.y, m_min.z);
	m_v[12].pos = D3DXVECTOR3(m_min.x, m_max.y, m_max.z);
	m_v[13].pos = D3DXVECTOR3(m_min.x, m_max.y, m_min.z);
}

D3DXVECTOR3 AABB::GetMax() {
	return m_max;
}

D3DXVECTOR3 AABB::GetMin() {
	return m_min;
}

D3DXVECTOR3 AABB::GetPosition() {
	return m_pos;
}

void AABB::Draw() {
	LPDIRECT3DDEVICE9 d = GetDevice();
	d->SetFVF(MY_FVF);
	d->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, m_v, sizeof(LINE_VERTEX));
	d->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &m_v[4], sizeof(LINE_VERTEX));
	d->DrawPrimitiveUP(D3DPT_LINELIST, 2, &m_v[8], sizeof(LINE_VERTEX));
	d->DrawPrimitiveUP(D3DPT_LINELIST, 2, &m_v[10], sizeof(LINE_VERTEX));
	d->DrawPrimitiveUP(D3DPT_LINELIST, 2, &m_v[12], sizeof(LINE_VERTEX));
}