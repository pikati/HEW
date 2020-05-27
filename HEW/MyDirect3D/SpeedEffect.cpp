/**
 *	@file		SpeedEffect.cpp
 *	@brief		�T���v���̃G�t�F�N�g�̃G�~�b�^�[�̎���
 *	@authotr	AT-12C-342 ��e ����
*/

#include "SpeedEffect.h"
#include "main.h"
#include "input.h"
#include "CameraMediator.h"

#define SPEED_EFFECT_LIFE 150
#define MAX_SPEED_EFFECT 5
#define SPEED_TEXTURE_WIDTH	0.25f
#define SPEED_TEXTURE_HEIGHT	0.25f

static float angle[MAX_SPEED_EFFECT];

void SpeedEffect::Initialize(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 size) {
	m_pDevice = GetDevice();

	for (int nCntParticle = 0; nCntParticle < MAX_SPEED_EFFECT; nCntParticle++)
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
		angle[nCntParticle] = (float)nCntParticle * 72.0f * RADIAN;
	}

	// ���_���̍쐬
	MakeVertexParticle();

	m_pD3DTextureParticle = texture;

	m_roty = 0.0f;
	m_spd = 0.0f;
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_enable = true;
	m_life = SPEED_EFFECT_LIFE;
	m_particleType = PARTICLE_SPEED;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fLength;
	int nLife;
	pos = m_posBase;
	fLength = 0.1f;
	move.z = 0.2f;

	nLife = 8;
	m_frame = 0;
	/*fSize = 2.0f;

	pos.y = fSize / 2;*/

	// �r���{�[�h�̐ݒ�
	SetParticle(pos, move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), nLife);
	
}

void SpeedEffect::Update() {
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

void SpeedEffect::Draw() {

	if (m_enable)
	{
		D3DXMATRIX mtxView, mtxScale, mtxTranslate;
		D3DXMATRIX* mat = CameraMediator::GetCameraMatrix();

		// ���C�e�B���O�𖳌���
		m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ���Z�����ɐݒ�
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���� = �]����(SRC) + �]����(DEST)
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
		//m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				// Z�o�b�t�@�[�̏������݂����Ȃ�
		//m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�

		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

		for (int nCntParticle = 0; nCntParticle < MAX_SPEED_EFFECT; nCntParticle++)
		{
			if (particles[nCntParticle].bUse)
			{
				// ���[���h�}�g���b�N�X�̏�����
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

				// �X�P�[���𔽉f
				D3DXMatrixScaling(&mtxScale, particles[nCntParticle].scale.x, particles[nCntParticle].scale.y, particles[nCntParticle].scale.z);
				D3DXMatrixMultiply(&m_mtxWorldParticle, &m_mtxWorldParticle, &mtxScale);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTranslate, particles[nCntParticle].pos.x, particles[nCntParticle].pos.y, particles[nCntParticle].pos.z);
				D3DXMatrixMultiply(&m_mtxWorldParticle, &m_mtxWorldParticle, &mtxTranslate);

				// ���[���h�}�g���b�N�X�̐ݒ�
				m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldParticle);

				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				m_pDevice->SetStreamSource(0, m_pD3DVtxBuffParticle, 0, sizeof(VERTEX_PARTICLE_3D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				m_pDevice->SetFVF(FVF_VERTEX_3D);

				// �e�N�X�`���̐ݒ�
				m_pDevice->SetTexture(0, m_pD3DTextureParticle);

				// �|���S���̕`��
				m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntParticle * 4), NUM_POLYGON);
			}
		}

		// ���C�e�B���O��L����
		m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// �ʏ�u�����h�ɖ߂�
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���� = �]����(SRC) + �]����(DEST)
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
		//m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Z�o�b�t�@�[�̏������݂�����
		//m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);				// Z��r����

		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);	// �A���t�@�u�����f�B���O����
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// �ŏ��̃A���t�@����
		//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// �Q�Ԗڂ̃A���t�@����
	}
}

void SpeedEffect::Finalize() {
	SAFE_RELEASE(m_pD3DVtxBuffParticle);
	SAFE_RELEASE(m_pD3DTextureParticle);
}

HRESULT SpeedEffect::MakeVertexParticle()
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_PARTICLE_3D) * NUM_VERTEX * MAX_SPEED_EFFECT,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pD3DVtxBuffParticle,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))										// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_PARTICLE_3D* pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntParticle = 0; nCntParticle < MAX_SPEED_EFFECT; nCntParticle++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-particles[nCntParticle].fSizeX / 2, -particles[nCntParticle].fSizeY / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(particles[nCntParticle].fSizeX / 2, -particles[nCntParticle].fSizeY / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-particles[nCntParticle].fSizeX / 2, particles[nCntParticle].fSizeY / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(particles[nCntParticle].fSizeX / 2, particles[nCntParticle].fSizeY / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuffParticle->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SpeedEffect::SetVertexParticle(int nIdxParticle, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		
		VERTEX_PARTICLE_3D* pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);


		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SpeedEffect::SetColorParticle(int nIdxParticle, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		m_frame += 2;

		if (m_frame == 16)
		{
			m_frame = 0;
		}

		float tx = float(m_frame % 4) * SPEED_TEXTURE_WIDTH;
		float ty = float(m_frame / 4) * SPEED_TEXTURE_HEIGHT;
		VERTEX_PARTICLE_3D* pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;

		pVtx[0].tex = D3DXVECTOR2(tx, ty);
		pVtx[1].tex = D3DXVECTOR2(tx + SPEED_TEXTURE_WIDTH, ty);
		pVtx[2].tex = D3DXVECTOR2(tx, ty + SPEED_TEXTURE_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2(tx + SPEED_TEXTURE_WIDTH, ty + SPEED_TEXTURE_HEIGHT);

		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SpeedEffect::SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	int nIdxParticle = -1;

	for (int nCntParticle = 0; nCntParticle < MAX_SPEED_EFFECT; nCntParticle++)
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

			// ���_���W�̐ݒ�
			SetVertexParticle(nCntParticle, particles[nCntParticle].fSizeX, particles[nCntParticle].fSizeY);

			nIdxParticle = nCntParticle;
			break;
		}
	}

	return nIdxParticle;
}

void SpeedEffect::SetPosition(D3DXVECTOR3 pos) {
	m_posBase = pos;
}

int SpeedEffect::GetLifeTime() {
	return m_life;
}

void SpeedEffect::SetPlayerPosition(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void SpeedEffect::SetplayerAngle(float angle) {
	m_angle = angle;
}

void SpeedEffect::UpdateLife() {
	m_life--;
	if (m_life <= 0)
	{
		m_enable = false;
	}
}

void SpeedEffect::UpdateParticle() {
	if (m_enable)
	{
		if (m_bPause == false)
		{
			for (int nCntParticle = 0; nCntParticle < MAX_SPEED_EFFECT; nCntParticle++)
			{
				if (particles[nCntParticle].bUse)
				{
					float cos = cosf(m_angle);
					float sin = sinf(m_angle);
					particles[nCntParticle].move.z = -sinf(m_angle) * 0.5;
					particles[nCntParticle].move.x = cosf(m_angle) * 0.5;
					particles[nCntParticle].pos.z += particles[nCntParticle].move.z;
					particles[nCntParticle].pos.x += particles[nCntParticle].move.x;

					particles[nCntParticle].col.r = 1.0f;
					particles[nCntParticle].col.g = 1.0f;
					particles[nCntParticle].col.b = 1.0f;

					particles[nCntParticle].col.a = 1.0f;
					// �F�̐ݒ�
					SetColorParticle(nCntParticle, particles[nCntParticle].col);
					angle[nCntParticle] += 3.0f * RADIAN;
					particles[nCntParticle].nLife--;
					if (particles[nCntParticle].nLife == 0)
					{
						particles[nCntParticle].bUse = false;
						D3DXVECTOR3 position = m_posBase;
						position.x = position.x + -cosf(m_angle) * 4.0f;
						position.z = position.z + sinf(m_angle) * 4.0f;
						SetParticle(position, D3DXVECTOR3(0.0f, 0.2f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8);
					}
				}
			}
		}
	}
}

ParticleType SpeedEffect::GetParticleType() {
	return m_particleType;
}