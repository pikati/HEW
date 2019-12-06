/**
* @file camera.cpp
* @brief カメラ関係のソースファイル
* @author ドメイン
* @date 2019/10/21
*/
#include "XManager.h"
#include "main.h"
#include "MyDirect3D.h"
#include "camera.h"

#define CAMERA_X 0.0f
#define CAMERA_Y 1.5f
#define CAMERA_Z 3.0f

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
CAMERA g_camera;		// カメラ情報

LPDIRECT3DDEVICE9	m_d3dDevice;
static float playerPosZ;

/**
* @brief カメラの初期化
* @param[in] a(引数名) 引数の説明
* @param[out] b(引数名) 引数の説明
* @return bool 戻り値の説明
* @details カメラの位置・注視点・上方向の初期化
*/
void Camera_Initialize(void)
{
	m_d3dDevice = GetDevice();
	g_camera.posV = D3DXVECTOR3(CAMERA_X, CAMERA_Y, CAMERA_Z);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

/**
* @brief カメラのアップデート
* @param[in] a(引数名) 引数の説明
* @param[out] b(引数名) 引数の説明
* @return bool 戻り値の説明
* @details プレイヤーの位置情報からカメラの位置も決定する（追従）
*/
void Camera_Update(void)
{
	g_camera.posV = D3DXVECTOR3(CAMERA_X, CAMERA_Y, playerPosZ - CAMERA_Z);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.2f, playerPosZ + 1.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

/**
* @brief カメラの設置（？）
* @param[in] a(引数名) 引数の説明
* @param[out] b(引数名) 引数の説明
* @return bool 戻り値の説明
* @details カメラのいろんな情報から見え方を決める
*/
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// プロジェクションマトリックスの初期化

	D3DXMatrixIdentity(&g_camera.mtxProjection);
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
	D3DXMatrixIdentity(&g_camera.mtxView);
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,		// カメラの視点
		&g_camera.posR,		// カメラの注視点
		&g_camera.vecU);	// カメラの上方向ベクトル

// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

void SetPlayerPosZ(float z) {
	playerPosZ = z;
}