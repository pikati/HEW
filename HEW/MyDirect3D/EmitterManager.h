/**
 *	@file		EmitteManager.h
 *	@brief		エミッター管理クラスのヘッダ
 *	@authotr	AT-12C-342 門脇 喬哉
*/

#pragma once
#include "Emitter.h"
#include "NormalParticle.h"
#include "MyDirect3D.h"
#include <vector>

/**
 *	@class		EmitteManager
 *	@brief		エミッター管理クラス 複数種類のエミッターを管理できる（はず）
*/
class EmitterManager {
private:
	//!各エミッターのインスタンスを入れる入れ物
	std::vector<Emitter*>			m_emitter;

	//!各パーティクルのテクスチャを入れる入れ物
	std::vector<LPDIRECT3DTEXTURE9>	m_texture;

	float m_playerAngle;
public:
	/**
	 *	@brief		初期化
	*/
	void Initialize();

	/**
	 *	@brief		更新
	 *	@param[in]	pos		エフェクトの座標
	*/
	void Update(D3DXVECTOR3 pos);

	/**
	 *	@brief		描画
	*/
	void Draw();

	/**
	 *	@brief		終了処理
	*/
	void Finalize();

	/**
	 *	@brief		エミッター作成
	 *  @param[in]	type	作成するエミッターの種類
	*/
	int CreateEmitter(ParticleType type, D3DXVECTOR3 pos);

	void DestroyEmitter(int idx);

	void SetPlayerAngle(float angle);
};