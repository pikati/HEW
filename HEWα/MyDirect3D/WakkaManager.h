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
	// 球面線形補間関数
	// out   : 補間ベクトル（出力）
	// start : 開始ベクトル
	// end : 終了ベクトル
	// t : 補間値（0～1）
	D3DXVECTOR3* SphereLinear(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t);
	// 球面線形補間による補間姿勢算出関数
// out : 補間姿勢（出力）
// start : 開始姿勢
// end : 目標姿勢
// t : 補間係数（0～1）
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

