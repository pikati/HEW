﻿/**
 *	@file		HitEffect.cpp
 *	@brief		サンプルのエフェクトのエミッターの実装
 *	@authotr	AT-12C-342 門脇 喬哉
*/

#include "HitEffect.h"
#include "main.h"
#include "input.h"
#include "CameraMediator.h"


#define HITEFFECT_LIFE 10
#define MAX_HIT_EFFECT 1
#define HITTEXTURE_WIDTH 0.1666667f

void HitEffect::Initialize(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 size) {
	m_pDevice = GetDevice();

	for (int nCntParticle = 0; nCntParticle < MAX_HIT_EFFECT; nCntParticle++)
	{
		particles[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		particles[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		particles[nCntParticle].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		particles[nCntParticle].move = D3DXVECTOR3(0.5f, 1.0f, 0.5f);
		particles[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		particles[nCntParticle].fSizeX = size.x * 8.0f;
		particles[nCntParticle].fSizeY = size.y * 8.0f;
		particles[nCntParticle].nIdxShadow = -1;
		particles[nCntParticle].nLife = 0;
		particles[nCntParticle].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexParticle();

	m_pD3DTextureParticle = texture;

	m_roty = 0.0f;
	m_spd = 0.0f;
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_enable = true;
	m_life = HITEFFECT_LIFE;
	m_particleType = PARTICLE_NORMAL;

	for (int i = 0; i < MAX_HIT_EFFECT; i++)
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		float fAngle, fLength;
		int nLife;
		pos = m_posBase;

		fAngle = 0;
		fLength = 0;
		move.x = cosf(fAngle) * fLength;
		move.y = sinf(fAngle) * fLength;
		move.z = 0;

		nLife = 30;

		/*fSize = 2.0f;

		pos.y = fSize / 2;*/

		// ビルボードの設定
		SetParticle(pos, move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), nLife);
	}
}

void HitEffect::Update() {
	if (fabs(m_playerPos.y - m_posBase.y) > 30.0f || fabs(m_playerPos.z - m_posBase.z) > 30.0f || fabs(m_playerPos.x - m_posBase.x) > 30.0f)
	{
		m_enable = false;
	}
	else
	{
		m_enable = true;
	}

	UpdateLife();

	UpdateParticle();
}

void HitEffect::Draw() {

	if (m_enable)
	{
		D3DXMATRIX mtxView, mtxScale, mtxTranslate;
		D3DXMATRIX* mat = CameraMediator::GetCameraMatrix();

		// ライティングを無効に
		m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// 加算合成に設定
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				// Zバッファーの書き込みをしない
		m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし

		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

		for (int nCntParticle = 0; nCntParticle < MAX_HIT_EFFECT; nCntParticle++)
		{
			if (particles[nCntParticle].bUse)
			{
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&m_mtxWorldParticle);

				m_mtxWorldParticle._11 = mat->_11;
				m_mtxWorldParticle._12 = mat->_21;
				m_mtxWorldParticle._13 = mat->_31;
				m_mtxWorldParticle._21 = mat->_12;
				m_mtxWorldParticle._22 = mat->_22;
				m_mtxWorldParticle._23 = mat->_32;
				m_mtxWorldParticle._31 = mat->_13;
				m_mtxWorldParticle._32 = mat->_23;
				m_mtxWorldParticle._33 = mat->_33;

				// スケールを反映
				D3DXMatrixScaling(&mtxScale, particles[nCntParticle].scale.x, particles[nCntParticle].scale.y, particles[nCntParticle].scale.z);
				D3DXMatrixMultiply(&m_mtxWorldParticle, &m_mtxWorldParticle, &mtxScale);

				// 移動を反映
				D3DXMatrixTranslation(&mtxTranslate, particles[nCntParticle].pos.x, particles[nCntParticle].pos.y, particles[nCntParticle].pos.z);
				D3DXMatrixMultiply(&m_mtxWorldParticle, &m_mtxWorldParticle, &mtxTranslate);

				// ワールドマトリックスの設定
				m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldParticle);

				// 頂点バッファをデバイスのデータストリームにバインド
				m_pDevice->SetStreamSource(0, m_pD3DVtxBuffParticle, 0, sizeof(VERTEX_PARTICLE_3D));

				// 頂点フォーマットの設定
				m_pDevice->SetFVF(FVF_VERTEX_3D);

				// テクスチャの設定
				m_pDevice->SetTexture(0, m_pD3DTextureParticle);

				// ポリゴンの描画
				m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntParticle * 4), NUM_POLYGON);
			}
		}

		// ライティングを有効に
		m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// 通常ブレンドに戻す
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Zバッファーの書き込みをする
		m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);				// Z比較あり

		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);	// アルファブレンディング処理
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// ２番目のアルファ引数
	}
}

void HitEffect::Finalize() {
	SAFE_RELEASE(m_pD3DVtxBuffParticle);
	SAFE_RELEASE(m_pD3DTextureParticle);
}

HRESULT HitEffect::MakeVertexParticle()
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_PARTICLE_3D) * NUM_VERTEX * MAX_HIT_EFFECT,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
		FVF_VERTEX_3D,								// 使用する頂点フォーマット
		D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
		&m_pD3DVtxBuffParticle,					// 頂点バッファインターフェースへのポインタ
		NULL)))										// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_PARTICLE_3D* pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntParticle = 0; nCntParticle < MAX_HIT_EFFECT; nCntParticle++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-particles[nCntParticle].fSizeX / 2, -particles[nCntParticle].fSizeY / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(particles[nCntParticle].fSizeX / 2, -particles[nCntParticle].fSizeY / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-particles[nCntParticle].fSizeX / 2, particles[nCntParticle].fSizeY / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(particles[nCntParticle].fSizeX / 2, particles[nCntParticle].fSizeY / 2, 0.0f);

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		m_pD3DVtxBuffParticle->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void HitEffect::SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_PARTICLE_3D* pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		m_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void HitEffect::SetColorParticle(int nIdxParticle, D3DXCOLOR col)
{
	float tex = 0;
	tex = (HITEFFECT_LIFE - m_life) / 2 * HITTEXTURE_WIDTH;
	{//頂点バッファの中身を埋める
		VERTEX_PARTICLE_3D* pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;

		pVtx[0].tex = D3DXVECTOR2(tex, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(tex + HITTEXTURE_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(tex, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(tex + HITTEXTURE_WIDTH, 1.0f);

		// 頂点データをアンロックする
		m_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int HitEffect::SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	int nIdxParticle = -1;

	for (int nCntParticle = 0; nCntParticle < MAX_HIT_EFFECT; nCntParticle++)
	{
		if (!particles[nCntParticle].bUse)
		{
			particles[nCntParticle].pos = pos;
			particles[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			particles[nCntParticle].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			particles[nCntParticle].move = move;
			particles[nCntParticle].col = col;
			particles[nCntParticle].nLife = nLife;
			particles[nCntParticle].bUse = true;

			// 頂点座標の設定
			SetVertexParticle(nCntParticle, particles[nCntParticle].fSizeX, particles[nCntParticle].fSizeY);

			nIdxParticle = nCntParticle;


			break;
		}
	}

	return nIdxParticle;
}

void HitEffect::SetPosition(D3DXVECTOR3 pos) {
	m_posBase = pos;
}

int HitEffect::GetLifeTime() {
	return m_life;
}

void HitEffect::SetPlayerPosition(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void HitEffect::SetplayerAngle(float angle) {
	m_angle = angle;
}

void HitEffect::UpdateLife() {
	m_life--;
	if (m_life <= 0)
	{
		m_enable = false;
	}
}

void HitEffect::UpdateParticle() {
	if (m_enable)
	{
		if (m_bPause == false)
		{
			for (int nCntParticle = 0; nCntParticle < MAX_HIT_EFFECT; nCntParticle++)
			{
				
				particles[nCntParticle].col.r = 1.0f;
				particles[nCntParticle].col.g = 1.0f;
				particles[nCntParticle].col.b = 1.0f;
				particles[nCntParticle].col.a = 1.0f;
				// 色の設定
				SetColorParticle(nCntParticle, particles[nCntParticle].col);		
			}
		}
	}
}

ParticleType HitEffect::GetParticleType() {
	return m_particleType;
}