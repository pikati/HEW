#pragma once
#include "MyDirect3D.h"
#include "COBBTree.h"
class Collision
{
private:
	static bool CheckCollision(OBBNODE *pNodeA, OBBNODE *pNodeB, D3DXMATRIX &TransMat, D3DXMATRIX &RotMat);
	static bool IsCollision(OBBDATA &BoxA, OBBDATA &BoxB);
public:
	static bool IsCollision(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2);
	static bool IsCollision(float x1, float y1, float z1, float r1, float x2, float y2, float z2, float r2);
	static bool CheckCollision(const COBBTree &OBBTreeA, const D3DXMATRIX &TransMatA, const COBBTree &OBBTreeB, const D3DXMATRIX &TransMatB);

};

