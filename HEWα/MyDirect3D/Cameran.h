#pragma once
#include "MyDirect3D.h"
class Cameran
{
private:
	D3DXVECTOR3			m_posV;			// 視点
	D3DXVECTOR3			m_posR;			// 注視点
	D3DXVECTOR3			m_vecU;			// 上方向ベクトル
	D3DXVECTOR3			m_playerPos;	//プレイヤー座標
	D3DXVECTOR3			m_endPos;		//目標地点
	float				m_angle;
	D3DXMATRIX			m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX			m_mtxView;// ビューマトリックス
	LPDIRECT3DDEVICE9	m_d3dDevice;
	// 球面線形補間関数
	// out   : 補間ベクトル（出力）
	// start : 開始ベクトル
	// end : 終了ベクトル
	// t : 補間値（0～1）
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

