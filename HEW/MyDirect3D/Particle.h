/**
 *	@file		Particle.h
 *	@brief		Particle�\���̂̐錾�̃w�b�_
 *  @detail		�e�G�~�b�^�[�ŃC���N���[�h����̂���
 *	@authotr	AT-12C-342 ��e ����
*/
#pragma once
#include "MyDirect3D.h"

struct Particle
{
	//!�ʒu
	D3DXVECTOR3 pos;

	//!��]
	D3DXVECTOR3 rot;

	//!�X�P�[��
	D3DXVECTOR3 scale;

	//!�ړ���
	D3DXVECTOR3 move;

	//!�F
	D3DXCOLOR col;

	//!��
	float fSizeX;

	//!����
	float fSizeY;

	//!�eID
	int nIdxShadow;

	//!����
	int nLife;

	//!�g�p���Ă��邩�ǂ���
	bool bUse;
} ;