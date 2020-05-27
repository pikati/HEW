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
	float		angle;
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;// ビューマトリックス
	
} CAMERA;

void Camera_Initialize(void);

void Camera_Update(void);

void SetCamera(void);

void SetPlayerPos(D3DXVECTOR3 pos);

void SetPlayerAngle(float angle);

// 球面線形補間関数
// out   : 補間ベクトル（出力）
// start : 開始ベクトル
// end : 終了ベクトル
// t : 補間値（0～1）
D3DXVECTOR3* Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t);