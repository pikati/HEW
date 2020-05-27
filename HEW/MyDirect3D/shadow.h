//=============================================================================
//
// 影処理 [shadow.h]
//
//=============================================================================
#pragma once
#include "MyDirect3D.h"

typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scl;		// 拡大縮小
	bool bUse;				// 使用しているかどうか
} SHADOW;

class Shadow {
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_pTextureShadow;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffShadow;
	SHADOW m_shadow;
	void MakeVertexShadow();
	void SetVertex();

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void CreateShadow();
	void ReleaseShadow();
	void SetPosition(D3DXVECTOR3 pos);
	void SetScale(D3DXVECTOR3 scale);

};