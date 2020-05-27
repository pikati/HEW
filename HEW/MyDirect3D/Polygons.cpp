#include "Polygons.h"
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)



VERTEX Polygons::vertex[4];

void Polygons::Draw(float x, float y, float w, float h, float tx, float ty, float tw, float th, LPDIRECT3DTEXTURE9 texture) {
	LPDIRECT3DDEVICE9 d3dDvice = GetDevice();
	//���_�o�b�t�@
	IDirect3DVertexBuffer9* pVB;
	//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 pIB;

	/*2D�p�̐ݒ�*/
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;

	/*���_���W�ݒ�*/
	vertex[0].x = x;
	vertex[0].y = y;
	vertex[1].x = x + w;
	vertex[1].y = y;
	vertex[2].x = x;
	vertex[2].y = y + h;
	vertex[3].x = x + w;
	vertex[3].y = y + h;

	/*�e�N�X�`�����W�ݒ�*/
	vertex[0].tu = tx;
	vertex[0].tv = ty;
	vertex[1].tu = tx + tw;
	vertex[1].tv = ty;
	vertex[2].tu = tx;
	vertex[2].tv = ty + th;
	vertex[3].tu = tx + tw;
	vertex[3].tv = ty + th;

	/*���_�F�ݒ�*/
	vertex[0].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[1].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[2].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[3].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//��̒��_�o�b�t�@�쐬
	d3dDvice->CreateVertexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVB,
		NULL);

	void *pData;
	if (D3D_OK == pVB->Lock(0, sizeof(VERTEX) * 4, (void**)&pData, 0)) {
		memcpy(pData, vertex, sizeof(VERTEX) * 4);
		pVB->Unlock();
	}

	d3dDvice->CreateIndexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIB, NULL);

	WORD* pI;
	if (D3D_OK == pIB->Lock(0, 0, (void**)&pI, 0)) {
		pI[0] = 0;
		pI[1] = 1;
		pI[2] = 2;
		pI[3] = 3;
	}

	d3dDvice->SetStreamSource(0, pVB, 0, sizeof(VERTEX));
	d3dDvice->SetIndices(pIB);
	d3dDvice->SetFVF(FVF_VERTEX_2D);
	d3dDvice->SetTexture(0, texture);
	d3dDvice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
	d3dDvice->SetTexture(0, NULL);
	
	SAFE_RELEASE(pIB);
	SAFE_RELEASE(pVB);
}

void Polygons::FadeDraw(float x, float y, float w, float h, float tx, float ty, float tw, float th, int alfa, LPDIRECT3DTEXTURE9 texture) {
	LPDIRECT3DDEVICE9 d3dDvice = GetDevice();
	//���_�o�b�t�@
	IDirect3DVertexBuffer9* pVB;
	//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 pIB;

	/*2D�p�̐ݒ�*/
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;

	/*���_���W�ݒ�*/
	vertex[0].x = x;
	vertex[0].y = y;
	vertex[1].x = x + w;
	vertex[1].y = y;
	vertex[2].x = x;
	vertex[2].y = y + h;
	vertex[3].x = x + w;
	vertex[3].y = y + h;

	/*�e�N�X�`�����W�ݒ�*/
	vertex[0].tu = tx;
	vertex[0].tv = ty;
	vertex[1].tu = tx + tw;
	vertex[1].tv = ty;
	vertex[2].tu = tx;
	vertex[2].tv = ty + th;
	vertex[3].tu = tx + tw;
	vertex[3].tv = ty + th;

	/*���_�F�ݒ�*/
	vertex[0].deffuse = D3DCOLOR_RGBA(255, 255, 255, alfa);
	vertex[1].deffuse = D3DCOLOR_RGBA(255, 255, 255, alfa);
	vertex[2].deffuse = D3DCOLOR_RGBA(255, 255, 255, alfa);
	vertex[3].deffuse = D3DCOLOR_RGBA(255, 255, 255, alfa);

	//��̒��_�o�b�t�@�쐬
	d3dDvice->CreateVertexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVB,
		NULL);

	void *pData;
	if (D3D_OK == pVB->Lock(0, sizeof(VERTEX) * 4, (void**)&pData, 0)) {
		memcpy(pData, vertex, sizeof(VERTEX) * 4);
		pVB->Unlock();
	}

	d3dDvice->CreateIndexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIB, NULL);

	WORD* pI;
	if (D3D_OK == pIB->Lock(0, 0, (void**)&pI, 0)) {
		pI[0] = 0;
		pI[1] = 1;
		pI[2] = 2;
		pI[3] = 3;
	}

	d3dDvice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	d3dDvice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3dDvice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// �A���t�@�E�u�����f�B���O���s��
	d3dDvice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���ߏ������s��
	d3dDvice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �������������s��
	d3dDvice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	d3dDvice->SetStreamSource(0, pVB, 0, sizeof(VERTEX));
	d3dDvice->SetTexture(0, texture);
	d3dDvice->SetIndices(pIB);
	d3dDvice->SetFVF(FVF_VERTEX_2D);
	d3dDvice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
	d3dDvice->SetTexture(0, NULL);

	SAFE_RELEASE(pIB);
	SAFE_RELEASE(pVB);
}