#include "Collision.h"
#include "MyDirect3D.h"

bool Collision::IsCollision(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2) {
	if (powf(pos2.x - pos1.x, 2.0f) + powf(pos2.y - pos1.y, 2.0f) + powf(pos2.z - pos1.z, 2.0f) <= powf(r1 + r2, 2.0f)) {
		return true;
	}
	return false;
}

bool Collision::IsCollision(float x1, float y1, float z1, float r1, float x2, float y2, float z2, float r2) {
	if (powf(x2 - x1, 2.0f) + powf(y2 - y1, 2.0f) + powf(z2 - z1, 2.0f) <= powf(r1 + r2, 2.0f)) {
		return true;
	}
	return false;
}

bool Collision::CheckCollision(const COBBTree &OBBTreeA, const D3DXMATRIX &TransMatA,
	const COBBTree &OBBTreeB, const D3DXMATRIX &TransMatB)
{
	D3DXMATRIX TransMat, InvMat, RotMat;
	D3DXMatrixIdentity(&TransMat);
	D3DXMatrixIdentity(&InvMat);
	D3DXMatrixIdentity(&RotMat);
	//D3DXMatrixMultiply(&TransMat, &TransMatB, D3DXMatrixInverse(&InvMat, NULL, &TransMatA));
	
	D3DXMatrixInverse(&InvMat, NULL, &TransMatA);
	D3DXMatrixMultiply(&TransMat, &TransMatB, &InvMat);
	RotMat = TransMat;
	RotMat._41 = 0; RotMat._42 = 0; RotMat._43 = 0;
	return CheckCollision(OBBTreeA.pOBBTopNode, OBBTreeB.pOBBTopNode, TransMat, RotMat);
}

bool Collision::CheckCollision(OBBNODE *pNodeA, OBBNODE *pNodeB, D3DXMATRIX &TransMat, D3DXMATRIX &RotMat)
{
	// BoxAから見た座標系にBoxBを変換
	OBBDATA OBBDataB = pNodeB->OBBData;

	D3DXVECTOR4 Center;
	D3DXVec3Transform(&Center, &OBBDataB.Center, &TransMat);
	OBBDataB.Center.x = Center.x;
	OBBDataB.Center.y = Center.y;
	OBBDataB.Center.z = Center.z;

	for (int i = 0; i < 3; ++i) {
		D3DXVECTOR4 Vec;
		D3DXVec3Transform(&Vec, &OBBDataB.Axis[i], &RotMat);
		OBBDataB.Axis[i].x = Vec.x;
		OBBDataB.Axis[i].y = Vec.y;
		OBBDataB.Axis[i].z = Vec.z;
	}

	OBBNODE *pAL = pNodeA->pOBBNodeL, *pAR = pNodeA->pOBBNodeR, *pBL = pNodeB->pOBBNodeL, *pBR = pNodeB->pOBBNodeR;
	bool Result = false;
	if (IsCollision(pNodeA->OBBData, OBBDataB)) {
		if (!pAL && !pAR && !pBL && !pBR) Result = true;
		else {
			if (pAL &&  pBL) if (Result = CheckCollision(pAL, pBL, TransMat, RotMat)) goto EXIT;
			if (pAL &&  pBR) if (Result = CheckCollision(pAL, pBR, TransMat, RotMat)) goto EXIT;
			if (pAR &&  pBL) if (Result = CheckCollision(pAR, pBL, TransMat, RotMat)) goto EXIT;
			if (pAR &&  pBR) if (Result = CheckCollision(pAR, pBR, TransMat, RotMat)) goto EXIT;

			if (!pAL &&  pBL) if (Result = CheckCollision(pNodeA, pBL, TransMat, RotMat)) goto EXIT;
			if (!pAL &&  pBR) if (Result = CheckCollision(pNodeA, pBR, TransMat, RotMat)) goto EXIT;
			// 上二つと等価なので省略
		//	if( !pAR &&  pBL ) if( Result = CheckCollision( pNodeA, pBL, TransMat, RotMat ) ) goto EXIT;
		//	if( !pAR &&  pBR ) if( Result = CheckCollision( pNodeA, pBR, TransMat, RotMat ) ) goto EXIT;

			if (pAL && !pBL) if (Result = CheckCollision(pAL, pNodeB, TransMat, RotMat)) goto EXIT;
			if (pAR && !pBL) if (Result = CheckCollision(pAR, pNodeB, TransMat, RotMat)) goto EXIT;
			// 上二つと等価なので省略
		//	if(  pAL && !pBR ) if( Result = CheckCollision( pAL, pNodeB, TransMat, RotMat ) ) goto EXIT;
		//	if(  pAR && !pBR ) if( Result = CheckCollision( pAR, pNodeB, TransMat, RotMat ) ) goto EXIT;
		}
	}
EXIT:
	return Result;
}

bool Collision::IsCollision(OBBDATA &BoxA, OBBDATA &BoxB)
{
	// BoxAの3軸がxyz軸になる空間に変換
	D3DXVECTOR4 Axis[3];
	D3DXMATRIX Matrix = BoxA.Matrix;
	Matrix._41 = 0; Matrix._42 = 0; Matrix._43 = 0;
	for (int i = 0; i < 3; ++i) D3DXVec3Transform(&Axis[i], &BoxB.Axis[i], &Matrix);

	D3DXVECTOR4 VecAtoBTrans;
	D3DXVec3Transform(&VecAtoBTrans, &(BoxB.Center - BoxA.Center), &Matrix); // 平行移動成分はキャンセルされなければならないのでBoxA.MatrixではなくMatrixを使う

	// 無駄な計算を省くために下ごしらえ
	float B[3][3] = {
		{ Axis[0].x, Axis[0].y, Axis[0].z },
		{ Axis[1].x, Axis[1].y, Axis[1].z },
		{ Axis[2].x, Axis[2].y, Axis[2].z }
	};

	float absB[3][3] = {
		{ fabs(B[0][0]), fabs(B[0][1]), fabs(B[0][2]) },
		{ fabs(B[1][0]), fabs(B[1][1]), fabs(B[1][2]) },
		{ fabs(B[2][0]), fabs(B[2][1]), fabs(B[2][2]) }
	};

	float T[3] = { VecAtoBTrans.x, VecAtoBTrans.y, VecAtoBTrans.z };

	float a[3] = { BoxA.Length[0] / 2, BoxA.Length[1] / 2, BoxA.Length[2] / 2 };
	float b[3] = { BoxB.Length[0] / 2, BoxB.Length[1] / 2, BoxB.Length[2] / 2 };

	// 以下、判定ルーチン

	// 分離軸 A.Axis[?]
	for (int i = 0; i < 3; ++i) {
		if (fabs(T[i])
	> a[i] + b[0] * absB[0][i] + b[1] * absB[1][i] + b[2] * absB[2][i]) return false;
	}

	// 分離軸 B.Axis[?]
	for (int i = 0; i < 3; ++i) {
		if (fabs(T[0] * B[i][0] + T[1] * B[i][1] + T[2] * B[i][2])
	> b[i] + a[0] * absB[i][0] + a[1] * absB[i][1] + a[2] * absB[i][2]) return false;
	}

	// 分離軸 A.Axis[?] x B.Axis[?]
	for (int j0 = 0; j0 < 3; ++j0) {
		int j1 = (j0 + 1) % 3;
		int j2 = (j0 + 2) % 3;
		for (int i0 = 0; i0 < 3; ++i0) {
			int i1 = (i0 + 1) % 3;
			int i2 = (i0 + 2) % 3;
			if (fabs(-T[j1] * B[i0][j2] + T[j2] * B[i0][j1])
		> a[j1] * absB[i0][j2] + a[j2] * absB[i0][j1]
				+ b[i1] * absB[i2][j0] + b[i2] * absB[i1][j0]) return false;
		}
	}

	return true;
}