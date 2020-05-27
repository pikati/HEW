/**
 *	@file		Emitter.h
 *	@brief		�G�~�b�^�[�̋��ʂȂ��̂𒊏o�������ۃN���X�̃w�b�_
 *	@authotr	AT-12C-342 ��e ����
*/
#pragma once
#include "Particle.h"
#include "MyDirect3D.h"

/** @def
 * �p�[�e�B�N���̍ő吔
 */
#define	MAX_PARTICLE			(128)
#define NUM_POLYGON 2
#define NUM_VERTEX 4

typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR	diffuse;	// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_PARTICLE_3D;


struct PowerParticleInfo
{
	float		radius;
	float		angle;
	D3DXCOLOR	color;
};

/**
 * @enum Enum
 * �p�[�e�B�N���̎�ނ𔻕ʂ���񋓑�
 */
enum ParticleType {
	//!�T���v���̃G�t�F�N�g���o���G�~�b�^�[
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
 *	@brief		�G�~�b�^�[�̒��ۃN���X
 *  @detail		�e�G�~�b�^�[�̐e�Ƃ��Čp������ƊǗ����Ƃ��Ă��y�ɂȂ�̂���
*/
class Emitter
{
protected:
	//!�p�[�e�B�N���̔z��
	Particle particles[MAX_PARTICLE];

	//!�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pD3DTextureParticle = NULL;

	//!���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffParticle = NULL;	

	//!�f�o�C�X
	LPDIRECT3DDEVICE9		m_pDevice;

	//!���[���h�}�g���b�N�X
	D3DXMATRIX				m_mtxWorldParticle;				

	//!�r���{�[�h�����ʒu
	D3DXVECTOR3				m_posBase;						

	//!��̕�
	float					m_fWidthBase = 5.0f;			

	//!��̍���
	float					m_fHeightBase = 10.0f;			

	//!�|�[�YON/OFF
	bool					m_bPause = false;			

	//!�ړ�����
	float					m_roty = 0.0f;					

	//!�ړ��X�s�[�h
	float					m_spd = 0.0f;					

	//!�v���C���[�ɂ�����
	bool					m_bPlayerTouch = true;

	ParticleType			m_particleType;

	float					m_angle;
	/**
	 *	@brief		���_�o�b�t�@������
	 *	@return		�o�b�t�@���������FS_OK �o�b�t�@�������s�FE_FAIL
	*/
	virtual HRESULT MakeVertexParticle() = 0;

	/**
	 *	@brief		���_�o�b�t�@������
	 *  @param[in]	nIdxParticle	�p�[�e�B�N���̃C���f�b�N�X
	 *  @param[in]	fSizeX			�p�[�e�B�N���̉���
	 *  @param[in]	fSizeY			�p�[�e�B�N���̏c��
	*/
	virtual void SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY) = 0;

	/**
	 *	@brief		���_�J���[��ݒ肷���
	 *  @param[in]	nIdxParticle	�p�[�e�B�N���̃C���f�b�N�X
	 *  @param[in]	col				�p�[�e�B�N���̐F
	*/
	virtual void SetColorParticle(int nIdxParticle, D3DXCOLOR col) = 0;

	/**
	 *	@brief		�V�����p�[�e�B�N����ݒ肵���
	 *  @param[in]	pos		�p�[�e�B�N���̔����ꏊ
	 *  @param[in]	move	�p�[�e�B�N���̈ړ����x
	 *  @param[in]	col		�p�[�e�B�N���̐F
	 *  @param[in]	nLife	�p�[�e�B�N���̐�������
	*/
	virtual int SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife) = 0;

	virtual void UpdateLife() = 0;

	virtual void UpdateParticle() = 0;
public:
	/**
	 *	@brief		�f�X�g���N�^
	*/
	~Emitter() {};

	/**
	 *	@brief		������
	 *  @param[in]	texture		�e�N�X�`���̃|�C���^
	 *  @param[in]	size		�p�[�e�B�N���̃T�C�Y
	*/
	virtual void Initialize(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 size) = 0;

	/**
	 *	@brief		�X�V
	*/
	virtual void Update() = 0;

	/**
	 *	@brief		�`��
	*/
	virtual void Draw() = 0;

	/**
	 *	@brief		�I������
	*/
	virtual void Finalize() = 0;

	/**
	 *	@brief		�G�~�b�^�[�̈ʒu�ݒ�
	*/
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;

	virtual int GetLifeTime() = 0;

	virtual void SetPlayerPosition(D3DXVECTOR3 pos) = 0;

	virtual void SetplayerAngle(float angle) = 0;

	virtual ParticleType GetParticleType() = 0;
};

