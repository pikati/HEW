#include "OBB.h"

void OBB::Initialize() {
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_posMove = D3DXVECTOR3(0, 0, 0);
	m_normaDirect[0] = D3DXVECTOR3(0, 0, 0);
	m_normaDirect[1] = D3DXVECTOR3(0, 0, 0);
	m_normaDirect[2] = D3DXVECTOR3(0, 0, 0);
	m_fLength[0] = 0;
	m_fLength[1] = 0;
	m_fLength[2] = 0;
	//最大値、最小値の初期値設定
	m_max = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	m_min = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
}

void OBB::CreateOBB(MeshInfo* meshInfo) {
	for (int meshIndex = 0; meshIndex < meshInfo[meshIndex].vertexCount; meshIndex++)
	{
		for (int i = 0; i < meshInfo[meshIndex].vertexCount; i++)
		{
			D3DXVECTOR3 pos = meshInfo[meshIndex].vertex->pos;
			if (pos.x < m_min.x)m_min.x = pos.x;
			if (pos.x > m_max.x)m_max.x = pos.x;
			if (pos.y < m_min.y)m_min.y = pos.y;
			if (pos.y > m_max.y)m_max.y = pos.y;
			if (pos.z < m_min.z)m_min.z = pos.z;
			if (pos.z > m_max.z)m_max.z = pos.z;
		}
	}
	m_pos.x = (m_min.x + m_max.x) * 0.5f;
	m_pos.y = (m_min.y + m_max.y) * 0.5f;
	m_pos.z = (m_min.z + m_max.z) * 0.5f;

	m_fLength[0] = fabsf(m_max.x - m_min.x) * 0.5f;
	m_fLength[1] = fabsf(m_max.y - m_min.y) * 0.5f;
	m_fLength[2] = fabsf(m_max.z - m_min.z) * 0.5f;
}

void OBB::Update(D3DXMATRIX &mat) {
	m_posMove.x = m_pos.x + mat._14;
	m_posMove.y = m_pos.y + mat._24;
	m_posMove.z = m_pos.z + mat._34;

	m_normaDirect[0] = D3DXVECTOR3(mat._11, mat._12, mat._13);
	m_normaDirect[1] = D3DXVECTOR3(mat._21, mat._22, mat._23);
	m_normaDirect[2] = D3DXVECTOR3(mat._31, mat._32, mat._33);

	m_fLength[0] = fabsf(m_max.x - m_min.x) * 0.5f * mat._11; 
	m_fLength[1] = fabsf(m_max.y - m_min.y) * 0.5f * mat._22; 
	m_fLength[2] = fabsf(m_max.z - m_min.z) * 0.5f * mat._33; 
}

D3DXVECTOR3 OBB::GetDirect(int index) {
	return m_normaDirect[index];
}

float OBB::GetLen_W(int index) {
	return m_fLength[index];
}

D3DXVECTOR3 OBB::GetPos_W() {
	return m_posMove;
}