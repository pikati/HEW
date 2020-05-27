/**
 *	@file		Emitter.h
 *	@brief		エミッターの共通なものを抽出した抽象クラスのヘッダ
 *	@authotr	AT-12C-342 門脇 喬哉
*/
#pragma once
#include "Particle.h"
#include "MyDirect3D.h"

/** @def
 * パーティクルの最大数
 */
#define	MAX_PARTICLE			(128)
#define NUM_POLYGON 2
#define NUM_VERTEX 4

typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR	diffuse;	// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_PARTICLE_3D;


struct PowerParticleInfo
{
	float		radius;
	float		angle;
	D3DXCOLOR	color;
};

/**
 * @enum Enum
 * パーティクルの種類を判別する列挙体
 */
enum ParticleType {
	//!サンプルのエフェクトを出すエミッター
	PARTICLE_NORMAL,
	PARTICLE_FLAME,
	PARTICLE_WATER,
	PARTICLE_FEVER,
	PARTICLE_POWERUP,
	PARTICLE_POWERDOWN,
	PARTICLE_SAND_STORM,
	PARTICLE_HIT_PLAYER,
	PARTICLE_SPEED
};


/**
 *	@class		Emitter
 *	@brief		エミッターの抽象クラス
 *  @detail		各エミッターの親として継承すると管理がとっても楽になるのじゃ
*/
class Emitter
{
protected:
	//!パーティクルの配列
	Particle particles[MAX_PARTICLE];

	//!テクスチャへのポインタ
	LPDIRECT3DTEXTURE9		m_pD3DTextureParticle = NULL;

	//!頂点バッファインターフェースへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffParticle = NULL;	

	//!デバイス
	LPDIRECT3DDEVICE9		m_pDevice;

	//!ワールドマトリックス
	D3DXMATRIX				m_mtxWorldParticle;				

	//!ビルボード発生位置
	D3DXVECTOR3				m_posBase;						

	//!基準の幅
	float					m_fWidthBase = 5.0f;			

	//!基準の高さ
	float					m_fHeightBase = 10.0f;			

	//!ポーズON/OFF
	bool					m_bPause = false;			

	//!移動方向
	float					m_roty = 0.0f;					

	//!移動スピード
	float					m_spd = 0.0f;					

	//!プレイヤーにくっつく
	bool					m_bPlayerTouch = true;

	ParticleType			m_particleType;

	float					m_angle;
	/**
	 *	@brief		頂点バッファを作るよ
	 *	@return		バッファ生成成功：S_OK バッファ生成失敗：E_FAIL
	*/
	virtual HRESULT MakeVertexParticle() = 0;

	/**
	 *	@brief		頂点バッファを作るよ
	 *  @param[in]	nIdxParticle	パーティクルのインデックス
	 *  @param[in]	fSizeX			パーティクルの横幅
	 *  @param[in]	fSizeY			パーティクルの縦幅
	*/
	virtual void SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY) = 0;

	/**
	 *	@brief		頂点カラーを設定するよ
	 *  @param[in]	nIdxParticle	パーティクルのインデックス
	 *  @param[in]	col				パーティクルの色
	*/
	virtual void SetColorParticle(int nIdxParticle, D3DXCOLOR col) = 0;

	/**
	 *	@brief		新しいパーティクルを設定しるよ
	 *  @param[in]	pos		パーティクルの発生場所
	 *  @param[in]	move	パーティクルの移動速度
	 *  @param[in]	col		パーティクルの色
	 *  @param[in]	nLife	パーティクルの生存時間
	*/
	virtual int SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife) = 0;

	virtual void UpdateLife() = 0;

	virtual void UpdateParticle() = 0;
public:
	/**
	 *	@brief		デストラクタ
	*/
	~Emitter() {};

	/**
	 *	@brief		初期化
	 *  @param[in]	texture		テクスチャのポインタ
	 *  @param[in]	size		パーティクルのサイズ
	*/
	virtual void Initialize(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 size) = 0;

	/**
	 *	@brief		更新
	*/
	virtual void Update() = 0;

	/**
	 *	@brief		描画
	*/
	virtual void Draw() = 0;

	/**
	 *	@brief		終了処理
	*/
	virtual void Finalize() = 0;

	/**
	 *	@brief		エミッターの位置設定
	*/
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;

	virtual int GetLifeTime() = 0;

	virtual void SetPlayerPosition(D3DXVECTOR3 pos) = 0;

	virtual void SetplayerAngle(float angle) = 0;

	virtual ParticleType GetParticleType() = 0;
};

