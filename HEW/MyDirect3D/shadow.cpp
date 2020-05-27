//=============================================================================
//
// �e���� [shadow.cpp]
//
//=============================================================================
#include "shadow.h"
#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SHADOW		"Asset/Texture/shadow.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SHADOW_SIZE_X		(1.0f)							// �e�̕�
#define	SHADOW_SIZE_Z		(1.0f)							// �e�̍���

#define SHADOW_NUM_VERTEX	4
#define SHADOW_NUM_POLYGON	2

#define	MAX_SHADOW			(32)							// �e�ő吔


//=============================================================================
// ����������
//=============================================================================
void Shadow::Initialize(void)
{
	m_pDevice = GetDevice();

	// ���_���̍쐬5
	MakeVertexShadow();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(m_pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SHADOW,			// �t�@�C���̖��O
								&m_pTextureShadow);		// �ǂݍ��ރ������[

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		m_shadow.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		m_shadow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_shadow.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_shadow.bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void Shadow::Finalize(void)
{
	SAFE_RELEASE(m_pVtxBuffShadow);
	SAFE_RELEASE(m_pTextureShadow);
}

//=============================================================================
// �X�V����
//=============================================================================
void Shadow::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void Shadow::Draw(void)
{
	D3DXMATRIX matScale, matRot, matTranslate;

	//���Z����
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//z��r����
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	if (m_shadow.bUse)
	{
		D3DXMatrixIdentity(&m_shadow.mtxWorld);

		D3DXMatrixScaling(&matScale, m_shadow.scl.x, m_shadow.scl.y, m_shadow.scl.z);
		D3DXMatrixMultiply(&m_shadow.mtxWorld, &m_shadow.mtxWorld, &matScale);

		D3DXMatrixRotationYawPitchRoll(&matRot, m_shadow.rot.y, m_shadow.rot.x, m_shadow.rot.z);
		D3DXMatrixMultiply(&m_shadow.mtxWorld, &m_shadow.mtxWorld, &matRot);

		D3DXMatrixTranslation(&matTranslate, m_shadow.pos.x, m_shadow.pos.y, m_shadow.pos.z);
		D3DXMatrixMultiply(&m_shadow.mtxWorld, &m_shadow.mtxWorld, &matTranslate);

		m_pDevice->SetTransform(D3DTS_WORLD, &m_shadow.mtxWorld);

		m_pDevice->SetStreamSource(0, m_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		m_pDevice->SetFVF(FVF_VERTEX_3D);

		m_pDevice->SetTexture(0, m_pTextureShadow);

		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, SHADOW_NUM_POLYGON);
	}

	//���Z����
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//z��r����
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void Shadow::MakeVertexShadow()
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 32 * 4,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&m_pVtxBuffShadow,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
		MessageBox(NULL, "���_�o�b�t�@���܂���ł���", NULL, MB_OK);
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void Shadow::SetVertex()
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		pVtx[1].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		pVtx[2].pos = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
		pVtx[3].pos = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// �e�̍쐬
//=============================================================================
void Shadow::CreateShadow()
{
	
	if(!m_shadow.bUse)
	{
		m_shadow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_shadow.bUse = true;

		SetVertex();
	}
	
}

//=============================================================================
// �e�̔j��
//=============================================================================
void Shadow::ReleaseShadow()
{
	m_shadow.bUse = false;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void Shadow::SetPosition(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 position = pos;
	position.y -= 1.0f;
	m_shadow.pos = position;
}

//=============================================================================
// �X�P�[���̐ݒ�
//=============================================================================
void Shadow::SetScale(D3DXVECTOR3 scl)
{
	m_shadow.scl = scl;
}

