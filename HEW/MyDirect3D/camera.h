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
	float		angle;
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;// �r���[�}�g���b�N�X
	
} CAMERA;

void Camera_Initialize(void);

void Camera_Update(void);

void SetCamera(void);

void SetPlayerPos(D3DXVECTOR3 pos);

void SetPlayerAngle(float angle);

// ���ʐ��`��Ԋ֐�
// out   : ��ԃx�N�g���i�o�́j
// start : �J�n�x�N�g��
// end : �I���x�N�g��
// t : ��Ԓl�i0�`1�j
D3DXVECTOR3* Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t);