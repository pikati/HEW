#pragma once
/**
* @file camera.h
* @brief カメラ関係のヘッダー
* @author ドメイン
* @date 2019/10/21
*/

//
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;// ビューマトリックス
	
} CAMERA;

void Camera_Initialize(void);

void Camera_Update(void);

void SetCamera(void);

void SetPlayerPosZ(float z);

