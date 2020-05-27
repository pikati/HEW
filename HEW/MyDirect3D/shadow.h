//=============================================================================
//
// �e���� [shadow.h]
//
//=============================================================================
#pragma once
#include "MyDirect3D.h"

typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scl;		// �g��k��
	bool bUse;				// �g�p���Ă��邩�ǂ���
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