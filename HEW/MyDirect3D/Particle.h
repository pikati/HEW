/**
 *	@file		Particle.h
 *	@brief		Particle構造体の宣言のヘッダ
 *  @detail		各エミッターでインクルードするのじゃ
 *	@authotr	AT-12C-342 門脇 喬哉
*/
#pragma once
#include "MyDirect3D.h"

struct Particle
{
	//!位置
	D3DXVECTOR3 pos;

	//!回転
	D3DXVECTOR3 rot;

	//!スケール
	D3DXVECTOR3 scale;

	//!移動量
	D3DXVECTOR3 move;

	//!色
	D3DXCOLOR col;

	//!幅
	float fSizeX;

	//!高さ
	float fSizeY;

	//!影ID
	int nIdxShadow;

	//!寿命
	int nLife;

	//!使用しているかどうか
	bool bUse;
} ;