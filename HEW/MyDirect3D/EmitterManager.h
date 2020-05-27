/**
 *	@file		EmitteManager.h
 *	@brief		�G�~�b�^�[�Ǘ��N���X�̃w�b�_
 *	@authotr	AT-12C-342 ��e ����
*/

#pragma once
#include "Emitter.h"
#include "NormalParticle.h"
#include "MyDirect3D.h"
#include <vector>

/**
 *	@class		EmitteManager
 *	@brief		�G�~�b�^�[�Ǘ��N���X ������ނ̃G�~�b�^�[���Ǘ��ł���i�͂��j
*/
class EmitterManager {
private:
	//!�e�G�~�b�^�[�̃C���X�^���X��������ꕨ
	std::vector<Emitter*>			m_emitter;

	//!�e�p�[�e�B�N���̃e�N�X�`����������ꕨ
	std::vector<LPDIRECT3DTEXTURE9>	m_texture;

	float m_playerAngle;
public:
	/**
	 *	@brief		������
	*/
	void Initialize();

	/**
	 *	@brief		�X�V
	 *	@param[in]	pos		�G�t�F�N�g�̍��W
	*/
	void Update(D3DXVECTOR3 pos);

	/**
	 *	@brief		�`��
	*/
	void Draw();

	/**
	 *	@brief		�I������
	*/
	void Finalize();

	/**
	 *	@brief		�G�~�b�^�[�쐬
	 *  @param[in]	type	�쐬����G�~�b�^�[�̎��
	*/
	int CreateEmitter(ParticleType type, D3DXVECTOR3 pos);

	void DestroyEmitter(int idx);

	void SetPlayerAngle(float angle);
};