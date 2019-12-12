#include "CameraMediator.h"

D3DXMATRIX CameraMediator::m_mat;

CameraMediator::CameraMediator()
{
}

CameraMediator::~CameraMediator()
{
}

D3DXMATRIX* CameraMediator::GetCameraMatrix() {
	return &m_mat;
}

void CameraMediator::SetCameraMatrix(D3DXMATRIX* mat) {
	m_mat = *mat;
}