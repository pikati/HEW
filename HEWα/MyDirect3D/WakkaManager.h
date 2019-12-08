#pragma once
#include "Wakka.h"
#include "Enum.h"


class WakkaManager
{
private:
	Wakka*		m_wakka;
	D3DXVECTOR3 m_playerPos;
	int			m_center;
	int			m_frame;
	bool		m_shoot;
	bool		m_bLerp;
	bool		m_t;

	void ShotUpdate();
	void LerpUpdate();
	// ���ʐ��`��Ԋ֐�
	// out   : ��ԃx�N�g���i�o�́j
	// start : �J�n�x�N�g��
	// end : �I���x�N�g��
	// t : ��Ԓl�i0�`1�j
	D3DXVECTOR3* SphereLinear(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t);
	// ���ʐ��`��Ԃɂ���Ԏp���Z�o�֐�
// out : ��Ԏp���i�o�́j
// start : �J�n�p��
// end : �ڕW�p��
// t : ��ԌW���i0�`1�j
	D3DXMATRIX* CalcInterPause(D3DXMATRIX* out, D3DXMATRIX* start, D3DXMATRIX* end, float t);
public:
	WakkaManager();
	~WakkaManager();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void SetPosition();
	void CreateWakka(ELEM elem);
	void Change(int dir);
	D3DXMATRIX*	GetEndMatrix(D3DXMATRIX* out, int i);
	void SetPlayerPosition(D3DXVECTOR3 playerPos);
};

