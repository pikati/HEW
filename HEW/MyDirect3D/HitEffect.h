/**
 *	@file		HitEffect.h
 *	@brief		�q�b�g�G�t�F�N�g�̃w�b�_
 *	@authotr	AT-12C-342 ��e ����
*/
#pragma once
#include "MyDirect3D.h"
#include "Emitter.h"


/**
 *	@class		HitEffect
 *	@brief		�q�b�g�G�t�F�N�g�̃G�~�b�^�[
*/
class HitEffect : public Emitter {
private:

	/**
	 *	@brief		���_�o�b�t�@������
	 *	@return		�o�b�t�@���������FS_OK �o�b�t�@�������s�FE_FAIL
	*/
	HRESULT MakeVertexParticle();

	/**
	 *	@brief		���_�o�b�t�@������
	 *  @param[in]	nIdxParticle	�p�[�e�B�N���̃C���f�b�N�X
	 *  @param[in]	fSizeX			�p�[�e�B�N���̉���
	 *  @param[in]	fSizeY			�p�[�e�B�N���̏c��
	*/
	void SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY);

	/**
	 *	@brief		���_�J���[��ݒ肷��� UV�����߂Ă邩�璍�ӂ��Ă�
	 *  @param[in]	nIdxParticle	�p�[�e�B�N���̃C���f�b�N�X
	 *  @param[in]	col				�p�[�e�B�N���̐F
	*/
	void SetColorParticle(int nIdxParticle, D3DXCOLOR col);

	/**
	 *	@brief		�V�����p�[�e�B�N����ݒ肵���
	 *  @param[in]	pos		�p�[�e�B�N���̔����ꏊ
	 *  @param[in]	move	�p�[�e�B�N���̈ړ����x
	 *  @param[in]	col		�p�[�e�B�N���̐F
	 *  @param[in]	nLife	�p�[�e�B�N���̐�������
	*/
	int SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);

	void UpdateLife();

	void UpdateParticle();

	int m_life;
	D3DXVECTOR3 m_playerPos;
	bool	m_enable;

public:
	/**
	 *	@brief		�f�X�g���N�^
	*/
	~HitEffect() {};

	/**
	 *	@brief		������
	 *  @param[in]	texture		�e�N�X�`���̃|�C���^
	 *  @param[in]	size		�p�[�e�B�N���̃T�C�Y
	*/
	void Initialize(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 size);

	/**
	 *	@brief		�X�V
	*/
	void Update();

	/**
	 *	@brief		�`��
	*/
	void Draw();

	/**
	 *	@brief		�I������
	*/
	void Finalize();

	/**
	 *	@brief		�G�~�b�^�[�̈ʒu�ݒ�
	 *  @param[in]	pos		�G�~�b�^�[�̏ꏊ
	*/
	void SetPosition(D3DXVECTOR3 pos);

	int GetLifeTime();

	void SetPlayerPosition(D3DXVECTOR3 pos);
	void SetplayerAngle(float angle);

	ParticleType GetParticleType();

};