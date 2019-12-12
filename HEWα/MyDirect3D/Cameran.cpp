#include "Cameran.h"
#include "main.h"
#include "CameraMediator.h"
#define CAMERA_X 0.0f
#define CAMERA_Y 1.5f
#define CAMERA_Z 3.0f


Cameran::Cameran()
{
}


Cameran::~Cameran()
{
}

void Cameran::Initialize(void)
{
	m_d3dDevice = GetDevice();
	m_posV = D3DXVECTOR3(CAMERA_X, CAMERA_Y, CAMERA_Z);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_endPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

/**
* @brief �J�����̃A�b�v�f�[�g
* @param[in] a(������) �����̐���
* @param[out] b(������) �����̐���
* @return bool �߂�l�̐���
* @details �v���C���[�̈ʒu��񂩂�J�����̈ʒu�����肷��i�Ǐ]�j
*/
void Cameran::Update(void)
{
	m_endPos = D3DXVECTOR3(cosf(m_angle) * 3.0f + m_playerPos.x, m_playerPos.y + CAMERA_Y, sinf(m_angle) * -3.0f + m_playerPos.z);
	Lerp(&m_posV, &m_posV, &m_endPos, 0.1f);
	//m_posV = D3DXVECTOR3(cosf(m_camera.angle) * 3.0f + playerPos.x, playerPos.y + CAMERA_Y, sinf(m_camera.angle) * -3.0f + playerPos.z);
	m_posR = D3DXVECTOR3(m_playerPos.x, 0.2f, m_playerPos.z + sinf(m_angle));
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

/**
* @brief �J�����̐ݒu�i�H�j
* @param[in] a(������) �����̐���
* @param[out] b(������) �����̐���
* @return bool �߂�l�̐���
* @details �J�����̂����ȏ�񂩂猩���������߂�
*/
void Cameran::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �v���W�F�N�V�����}�g���b�N�X�̏�����

	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,		// �J�����̎��_
		&m_posR,		// �J�����̒����_
		&m_vecU);	// �J�����̏�����x�N�g��

// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	D3DXMATRIX mat;
	mat = m_mtxView * m_mtxProjection;
	CameraMediator::SetCameraMatrix(&mat);
}

void Cameran::SetPlayerPos(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}

void Cameran::SetPlayerAngle(float angle) {
	m_angle = angle;
}

// ���ʐ��`��Ԋ֐�
// out   : ��ԃx�N�g���i�o�́j
// start : �J�n�x�N�g��
// end : �I���x�N�g��
// t : ��Ԓl�i0�`1�j
D3DXVECTOR3* Cameran::Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t) {
	out->x = start->x + t * (end->x - start->x);
	out->y = start->y + t * (end->y - start->y);
	out->z = start->z + t * (end->z - start->z);
	return out;
}