#pragma once
/**
* @file camera.h
* @brief �J�����֌W�̃w�b�_�[
* @author �h���C��
* @date 2019/10/21
*/

//
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;// �r���[�}�g���b�N�X
	
} CAMERA;

void Camera_Initialize(void);

void Camera_Update(void);

void SetCamera(void);

void SetPlayerPosZ(float z);

