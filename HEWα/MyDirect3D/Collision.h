#pragma once
#include "MyDirect3D.h"
#include "COBBTree.h"
#include "OBB.h"
class Collision
{
private:
	static bool CheckCollision(OBBNODE *pNodeA, OBBNODE *pNodeB, D3DXMATRIX &TransMat, D3DXMATRIX &RotMat);
	static bool IsCollision(OBBDATA &BoxA, OBBDATA &BoxB);
	static float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);
public:
	static bool IsCollision(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2);
	static bool IsCollision(float x1, float y1, float z1, float r1, float x2, float y2, float z2, float r2);
	static bool CheckCollision(const COBBTree &OBBTreeA, const D3DXMATRIX &TransMatA, const COBBTree &OBBTreeB, const D3DXMATRIX &TransMatB);
	static bool CheckCollision(OBB &obb1, OBB &obb2);
};

