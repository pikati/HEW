#pragma once
#include "MyDirect3D.h"
#include <vector>
#include "Enum.h"

class OBB
{
private:
	D3DXVECTOR3 m_pos;              // �ʒu
	D3DXVECTOR3 m_posMove;              // �ʒu
	D3DXVECTOR3 m_normaDirect[3];   // �����x�N�g��
	float m_fLength[3];      // �e�������̒���
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
public:
	void Initialize();
	void Update(D3DXMATRIX &mat);
	void CreateOBB(MeshInfo* meshInfo);
	D3DXVECTOR3 GetDirect(int elem);   // �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen_W(int elem);          // �w�莲�����̒������擾
	D3DXVECTOR3 GetPos_W();             // �ʒu���擾
};