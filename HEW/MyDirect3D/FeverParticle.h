#pragma once
#include "Emitter.h"

#define MAX_FEVER_PARTICLE 120

struct HSV {
	float hue;
	float saturation;
	float value;
};

class FeverParticle : public Emitter
{
private:
	/**
	 *	@brief		頂点バッファを作るよ
	 *	@return		バッファ生成成功：S_OK バッファ生成失敗：E_FAIL
	*/
	HRESULT MakeVertexParticle();

	/**
	 *	@brief		頂点バッファを作るよ
	 *  @param[in]	nIdxParticle	パーティクルのインデックス
	 *  @param[in]	fSizeX			パーティクルの横幅
	 *  @param[in]	fSizeY			パーティクルの縦幅
	*/
	void SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY);

	/**
	 *	@brief		頂点カラーを設定するよ
	 *  @param[in]	nIdxParticle	パーティクルのインデックス
	 *  @param[in]	col				パーティクルの色
	*/
	void SetColorParticle(int nIdxParticle, D3DXCOLOR col);

	/**
	 *	@brief		新しいパーティクルを設定しるよ
	 *  @param[in]	pos		パーティクルの発生場所
	 *  @param[in]	move	パーティクルの移動速度
	 *  @param[in]	col		パーティクルの色
	 *  @param[in]	nLife	パーティクルの生存時間
	*/
	int SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);

	void UpdateLife();

	void UpdateParticle();

	void HSV2RGB(float hue);

	int m_life;
	
	D3DXVECTOR3 m_playerPos;
	bool	m_enable;
	PowerParticleInfo m_info;
	float	m_radius[MAX_FEVER_PARTICLE];
	float	m_feverAngle[MAX_FEVER_PARTICLE];
	HSV		m_hsv;
	float	m_decrease[MAX_FEVER_PARTICLE];
public:
	/**
	 *	@brief		デストラクタ
	*/
	~FeverParticle() {};

	/**
	 *	@brief		初期化
	 *  @param[in]	texture		テクスチャのポインタ
	 *  @param[in]	size		パーティクルのサイズ
	*/
	void Initialize(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 size);

	/**
	 *	@brief		更新
	*/
	void Update();

	/**
	 *	@brief		描画
	*/
	void Draw();

	/**
	 *	@brief		終了処理
	*/
	void Finalize();

	/**
	 *	@brief		エミッターの位置設定
	 *  @param[in]	pos		エミッターの場所
	*/
	void SetPosition(D3DXVECTOR3 pos);

	int GetLifeTime();

	void SetPlayerPosition(D3DXVECTOR3 pos);
	void SetplayerAngle(float angle);

	ParticleType GetParticleType();
};

