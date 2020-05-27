/**
 *	@file		FlameParticle.cpp
 *	@brief		サンプルのエフェクトのエミッターの実装
 *	@authotr	AT-12C-342 門脇 喬哉
*/

#include "FlameParticle.h"
#include "main.h"
#include "input.h"
#include "CameraMediator.h"

void FlameParticle::Initialize(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 size) {
	m_pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexParticle();

	m_pD3DTextureParticle = texture;

	for (int nCntParticle = 0; nCntParticle < MAX_FLAME_PARTICLE; nCntParticle++)
	{
		particles[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		particles[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		particles[nCntParticle].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		particles[nCntParticle].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		particles[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		particles[nCntParticle].fSizeX = size.x * 20.0f;
		particles[nCntParticle].fSizeY = size.y * 20.0f;
		particles[nCntParticle].nIdxShadow = -1;
		particles[nCntParticle].nLife = 0;
		particles[nCntParticle].bUse = false;
	}

	m_posBase = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_roty = 0.0f;
	m_spd = 0.0f;
	m_life = 10000;
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_enable = false;
	m_particleType = PARTICLE_FLAME;
}

void FlameParticle::Update() {
	/*if (fabs(m_playerPos.y - m_posBase.y) > 30.0f || fabs(m_playerPos.z - m_posBase.z) > 30.0f || fabs(m_playerPos.x - m_posBase.x) > 30.0f)
	{
		m_enable = false;
	}
	else 
	{
		m_enable = true;
	}*/

	UpdateLife();
	UpdateParticle();
}

void FlameParticle::Draw() {

	if (m_enable)
	{
		D3DXMATRIX mtxView, mtxScale, mtxTranslate;
		D3DXMATRIX *mat = CameraMediator::GetCameraMatrix();

		// ライティングを無効に
		m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// 加算合成に設定
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				// Zバッファーの書き込みをしない
	//	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし

		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

		for (int nCntParticle = 0; nCntParticle < MAX_FLAME_PARTICLE; nCntParticle++)
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
	//	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);				// Z比較あり

		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);	// アルファブレンディング処理
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// ２番目のアルファ引数
	}
}

void FlameParticle::Finalize() {
	SAFE_RELEASE(m_pD3DVtxBuffParticle);
	SAFE_RELEASE(m_pD3DTextureParticle);
}

HRESULT FlameParticle::MakeVertexParticle()
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_PARTICLE_3D) * NUM_VERTEX * MAX_FLAME_PARTICLE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
		FVF_VERTEX_3D,								// 使用する頂点フォーマット
		D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
		&m_pD3DVtxBuffParticle,					// 頂点バッファインターフェースへのポインタ
		NULL)))										// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_PARTICLE_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntParticle = 0; nCntParticle < MAX_FLAME_PARTICLE; nCntParticle++, pVtx += 4)
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
void FlameParticle::SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_PARTICLE_3D *pVtx;

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
void FlameParticle::SetColorParticle(int nIdxParticle, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_PARTICLE_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		m_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int FlameParticle::SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	int nIdxParticle = -1;

	for (int nCntParticle = 0; nCntParticle < MAX_FLAME_PARTICLE; nCntParticle++)
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

void FlameParticle::SetPosition(D3DXVECTOR3 pos) {
	m_posBase = pos;
}

int FlameParticle::GetLifeTime() {
	return m_life;
}

void FlameParticle::SetPlayerPosition(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void FlameParticle::SetplayerAngle(float angle) {
	m_angle = angle;
}

void FlameParticle::UpdateLife() {
	m_life--;
	if (m_life <= 0)
	{
		m_enable = false;
	}
}

void FlameParticle::UpdateParticle() {
	if (m_enable)
	{
		m_life--;
		if (m_bPause == false)
		{
			for (int nCntParticle = 0; nCntParticle < MAX_FLAME_PARTICLE; nCntParticle++)
			{
				if (particles[nCntParticle].bUse)
				{// 使用中
					//
					particles[nCntParticle].pos.x += particles[nCntParticle].move.x;
					particles[nCntParticle].pos.z += particles[nCntParticle].move.z;
					particles[nCntParticle].pos.y += particles[nCntParticle].move.y;

					particles[nCntParticle].move.x += (0.0f - particles[nCntParticle].move.x) * 0.015f;
					particles[nCntParticle].move.y += 0.25f;
					particles[nCntParticle].move.z += (0.0f - particles[nCntParticle].move.z) * 0.015f;
					//

					particles[nCntParticle].nLife--;
					if (particles[nCntParticle].nLife <= 0)
					{
						particles[nCntParticle].bUse = false;
						particles[nCntParticle].nIdxShadow = -1;
					}
					else
					{
						if (particles[nCntParticle].nLife <= 80)
						{
							particles[nCntParticle].col.r = 0.60f - (float)(80 - particles[nCntParticle].nLife) / 8.0f * 0.06f + 0.2f;
							particles[nCntParticle].col.g = 0.70f - (float)(80 - particles[nCntParticle].nLife) / 8.0f * 0.07f;
							particles[nCntParticle].col.b = 0.05f;
						}

						if (particles[nCntParticle].nLife <= 20)
						{
							// α値設定
							particles[nCntParticle].col.a -= 0.05f;
							if (particles[nCntParticle].col.a < 0.0f)
							{
								particles[nCntParticle].col.a = 0.0f;
							}
						}

						// 色の設定
						SetColorParticle(nCntParticle, particles[nCntParticle].col);
					}
				}
			}

			// パーティクル発生
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;
				float fAngle, fLength;
				int nLife;
				float fSize;

				pos = m_posBase;

				fAngle = (float)(rand() % 628 - 314) / 100.0f;
				fLength = rand() % (int)(m_fWidthBase * 200) / 100.0f - m_fWidthBase;
				move.x = sinf(fAngle) * fLength;
				move.y = rand() % 300 / 100.0f;
				move.z = cosf(fAngle) * fLength;

				nLife = rand() % 100 + 50;

				fSize = (float)(rand() % 30 + 20);

				pos.y = fSize / 2;

				// ビルボードの設定
				SetParticle(pos, move, D3DXCOLOR(0.8f, 0.7f, 0.2f, 0.85f), nLife);
			}
		}
	}
}

ParticleType FlameParticle::GetParticleType() {
	return m_particleType;
}