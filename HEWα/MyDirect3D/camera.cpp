/**
* @file camera.cpp
* @brief �J�����֌W�̃\�[�X�t�@�C��
* @author �h���C��
* @date 2019/10/21
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Utility.h"
#include "XManager.h"
#include "main.h"
#include "MyDirect3D.h"
#include "camera.h"

#define CAMERA_X 0.0f
#define CAMERA_Y 1.5f
#define CAMERA_Z 3.0f

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static CAMERA g_camera;		// �J�������
static CAMERA g_camera2;		// �J�������

LPDIRECT3DDEVICE9	m_d3dDevice;
static D3DXVECTOR3 playerPos;
static D3DXVECTOR3 playerPos2;
static D3DXVECTOR3 g_endPos;
static D3DXVECTOR3 g_endPos2;
static int i = 0;

/**
* @brief �J�����̏�����
* @param[in] a(������) �����̐���
* @param[out] b(������) �����̐���
* @return bool �߂�l�̐���
* @details �J�����̈ʒu�E�����_�E������̏�����
*/
void Camera_Initialize(void)
{
	m_d3dDevice = GetDevice();
	g_camera.posV = D3DXVECTOR3(CAMERA_X, CAMERA_Y, CAMERA_Z);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_endPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera2.posV = D3DXVECTOR3(CAMERA_X, CAMERA_Y, CAMERA_Z);
	g_camera2.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera2.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_endPos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

/**
* @brief �J�����̃A�b�v�f�[�g
* @param[in] a(������) �����̐���
* @param[out] b(������) �����̐���
* @return bool �߂�l�̐���
* @details �v���C���[�̈ʒu��񂩂�J�����̈ʒu�����肷��i�Ǐ]�j
*/
void Camera_Update(void)
{
	if (i == 0)
	{
		g_endPos = D3DXVECTOR3(cosf(g_camera.angle) * 3.0f + playerPos.x, playerPos.y + CAMERA_Y, sinf(g_camera.angle) * -3.0f + playerPos.z);
		Lerp(&g_camera.posV, &g_camera.posV, &g_endPos, 0.1f);
		//g_camera.posV = D3DXVECTOR3(cosf(g_camera.angle) * 3.0f + playerPos.x, playerPos.y + CAMERA_Y, sinf(g_camera.angle) * -3.0f + playerPos.z);
		g_camera.posR = D3DXVECTOR3(playerPos.x, 0.2f, playerPos.z + sinf(g_camera.angle));
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		g_endPos2 = D3DXVECTOR3(cosf(g_camera2.angle) * 3.0f + playerPos2.x, playerPos2.y + CAMERA_Y, sinf(g_camera2.angle) * -3.0f + playerPos2.z);
		Lerp(&g_camera2.posV, &g_camera2.posV, &g_endPos2, 0.1f);
		//g_camera2.posV = D3DXVECTOR3(cosf(g_camera2.angle) * 3.0f + playerPos2.x, playerPos2.y + CAMERA_Y, sinf(g_camera2.angle) * -3.0f + playerPos2.z);
		g_camera2.posR = D3DXVECTOR3(playerPos2.x, 0.2f, playerPos2.z + sinf(g_camera2.angle));
		g_camera2.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
}

/**
* @brief �J�����̐ݒu�i�H�j
* @param[in] a(������) �����̐���
* @param[out] b(������) �����̐���
* @return bool �߂�l�̐���
* @details �J�����̂����ȏ�񂩂猩���������߂�
*/
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �v���W�F�N�V�����}�g���b�N�X�̏�����

	D3DXMatrixIdentity(&g_camera.mtxProjection);
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
	D3DXMatrixIdentity(&g_camera.mtxView);
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,		// �J�����̎��_
		&g_camera.posR,		// �J�����̒����_
		&g_camera.vecU);	// �J�����̏�����x�N�g��

// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
	i++;
	if (i == 2)
	{
		i = 0;
	}
}

void SetPlayerPos(D3DXVECTOR3 pos) {
	playerPos = pos;
}

void SetPlayerAngle(float angle) {
	g_camera.angle = angle;
}

// ���ʐ��`��Ԋ֐�
// out   : ��ԃx�N�g���i�o�́j
// start : �J�n�x�N�g��
// end : �I���x�N�g��
// t : ��Ԓl�i0�`1�j
D3DXVECTOR3* Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t) {
	out->x = start->x + t * (end->x - start->x);
	out->y = start->y + t * (end->y - start->y);
	out->z = start->z + t * (end->z - start->z);
	return out;
}