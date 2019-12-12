#pragma once
#include "MyDirect3D.h"
class CameraMediator
{
private:
	static D3DXMATRIX m_mat;
public:
	CameraMediator();
	~CameraMediator();
	static D3DXMATRIX* GetCameraMatrix();
	static void SetCameraMatrix(D3DXMATRIX* mat);
};

