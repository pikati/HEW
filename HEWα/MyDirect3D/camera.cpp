/**
* @file camera.cpp
* @brief �J�����֌W�̃\�[�X�t�@�C��
* @author �h���C��
* @date 2019/10/21
*/
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
CAMERA g_camera;		// �J�������

LPDIRECT3DDEVICE9	m_d3dDevice;
static float playerPosZ;

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
	g_camera.posV = D3DXVECTOR3(CAMERA_X, CAMERA_Y, playerPosZ - CAMERA_Z);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.2f, playerPosZ + 1.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
}

void SetPlayerPosZ(float z) {
	playerPosZ = z;
}