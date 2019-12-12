#include "Cameran.h"
#include "main.h"
#include "CameraMediator.h"
#define CAMERA_X 0.0f
#define CAMERA_Y 1.5f
#define CAMERA_Z 3.0f


Cameran::Cameran()
{
}


Cameran::~Cameran()
{
}

void Cameran::Initialize(void)
{
	m_d3dDevice = GetDevice();
	m_posV = D3DXVECTOR3(CAMERA_X, CAMERA_Y, CAMERA_Z);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_endPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

/**
* @brief カメラのアップデート
* @param[in] a(引数名) 引数の説明
* @param[out] b(引数名) 引数の説明
* @return bool 戻り値の説明
* @details プレイヤーの位置情報からカメラの位置も決定する（追従）
*/
void Cameran::Update(void)
{
	m_endPos = D3DXVECTOR3(cosf(m_angle) * 3.0f + m_playerPos.x, m_playerPos.y + CAMERA_Y, sinf(m_angle) * -3.0f + m_playerPos.z);
	Lerp(&m_posV, &m_posV, &m_endPos, 0.1f);
	//m_posV = D3DXVECTOR3(cosf(m_camera.angle) * 3.0f + playerPos.x, playerPos.y + CAMERA_Y, sinf(m_camera.angle) * -3.0f + playerPos.z);
	m_posR = D3DXVECTOR3(m_playerPos.x, 0.2f, m_playerPos.z + sinf(m_angle));
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

/**
* @brief カメラの設置（？）
* @param[in] a(引数名) 引数の説明
* @param[out] b(引数名) 引数の説明
* @return bool 戻り値の説明
* @details カメラのいろんな情報から見え方を決める
*/
void Cameran::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// プロジェクションマトリックスの初期化

	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,		// カメラの視点
		&m_posR,		// カメラの注視点
		&m_vecU);	// カメラの上方向ベクトル

// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	D3DXMATRIX mat;
	mat = m_mtxView * m_mtxProjection;
	CameraMediator::SetCameraMatrix(&mat);
}

void Cameran::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void Cameran::SetPlayerAngle(float angle) {
	m_angle = angle;
}

// 球面線形補間関数
// out   : 補間ベクトル（出力）
// start : 開始ベクトル
// end : 終了ベクトル
// t : 補間値（0～1）
D3DXVECTOR3* Cameran::Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t) {
	out->x = start->x + t * (end->x - start->x);
	out->y = start->y + t * (end->y - start->y);
	out->z = start->z + t * (end->z - start->z);
	return out;
}