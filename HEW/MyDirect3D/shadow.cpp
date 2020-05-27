//=============================================================================
//
// 影処理 [shadow.cpp]
//
//=============================================================================
#include "shadow.h"
#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SHADOW		"Asset/Texture/shadow.jpg"	// 読み込むテクスチャファイル名
#define	SHADOW_SIZE_X		(1.0f)							// 影の幅
#define	SHADOW_SIZE_Z		(1.0f)							// 影の高さ

#define SHADOW_NUM_VERTEX	4
#define SHADOW_NUM_POLYGON	2

#define	MAX_SHADOW			(32)							// 影最大数


//=============================================================================
// 初期化処理
//=============================================================================
void Shadow::Initialize(void)
{
	m_pDevice = GetDevice();

	// 頂点情報の作成5
	MakeVertexShadow();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(m_pDevice,					// デバイスへのポインタ
								TEXTURE_SHADOW,			// ファイルの名前
								&m_pTextureShadow);		// 読み込むメモリー

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		m_shadow.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		m_shadow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_shadow.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_shadow.bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void Shadow::Finalize(void)
{
	SAFE_RELEASE(m_pVtxBuffShadow);
	SAFE_RELEASE(m_pTextureShadow);
}

//=============================================================================
// 更新処理
//=============================================================================
void Shadow::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void Shadow::Draw(void)
{
	D3DXMATRIX matScale, matRot, matTranslate;

	//減算合成
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//z比較無し
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	if (m_shadow.bUse)
	{
		D3DXMatrixIdentity(&m_shadow.mtxWorld);

		D3DXMatrixScaling(&matScale, m_shadow.scl.x, m_shadow.scl.y, m_shadow.scl.z);
		D3DXMatrixMultiply(&m_shadow.mtxWorld, &m_shadow.mtxWorld, &matScale);

		D3DXMatrixRotationYawPitchRoll(&matRot, m_shadow.rot.y, m_shadow.rot.x, m_shadow.rot.z);
		D3DXMatrixMultiply(&m_shadow.mtxWorld, &m_shadow.mtxWorld, &matRot);

		D3DXMatrixTranslation(&matTranslate, m_shadow.pos.x, m_shadow.pos.y, m_shadow.pos.z);
		D3DXMatrixMultiply(&m_shadow.mtxWorld, &m_shadow.mtxWorld, &matTranslate);

		m_pDevice->SetTransform(D3DTS_WORLD, &m_shadow.mtxWorld);

		m_pDevice->SetStreamSource(0, m_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		m_pDevice->SetFVF(FVF_VERTEX_3D);

		m_pDevice->SetTexture(0, m_pTextureShadow);

		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, SHADOW_NUM_POLYGON);
	}

	//加算合成
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//z比較あり
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void Shadow::MakeVertexShadow()
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 32 * 4,		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_3D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&m_pVtxBuffShadow,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
		MessageBox(NULL, "頂点バッファ作れませんでした", NULL, MB_OK);
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		m_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void Shadow::SetVertex()
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
		pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		m_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 影の作成
//=============================================================================
void Shadow::CreateShadow()
{
	
	if(!m_shadow.bUse)
	{
		m_shadow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_shadow.bUse = true;

		SetVertex();
	}
	
}

//=============================================================================
// 影の破棄
//=============================================================================
void Shadow::ReleaseShadow()
{
	m_shadow.bUse = false;
}

//=============================================================================
// 位置の設定
//=============================================================================
void Shadow::SetPosition(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 position = pos;
	position.y -= 1.0f;
	m_shadow.pos = position;
}

//=============================================================================
// スケールの設定
//=============================================================================
void Shadow::SetScale(D3DXVECTOR3 scl)
{
	m_shadow.scl = scl;
}

