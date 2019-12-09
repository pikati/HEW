#pragma once
#include "MyDirect3D.h"
class Cameran
{
private:
	D3DXVECTOR3			m_posV;			// ���_
	D3DXVECTOR3			m_posR;			// �����_
	D3DXVECTOR3			m_vecU;			// ������x�N�g��
	D3DXVECTOR3			m_playerPos;	//�v���C���[���W
	D3DXVECTOR3			m_endPos;		//�ڕW�n�_
	float				m_angle;
	D3DXMATRIX			m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX			m_mtxView;// �r���[�}�g���b�N�X
	LPDIRECT3DDEVICE9	m_d3dDevice;
	// ���ʐ��`��Ԋ֐�
	// out   : ��ԃx�N�g���i�o�́j
	// start : �J�n�x�N�g��
	// end : �I���x�N�g��
	// t : ��Ԓl�i0�`1�j
	D3DXVECTOR3* Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t);
public:
	Cameran();
	~Cameran();

	void Initialize(void);

	void Update(void);

	void SetCamera(void);

	void SetPlayerPos(D3DXVECTOR3 pos);

	void SetPlayerAngle(float angle);
};

