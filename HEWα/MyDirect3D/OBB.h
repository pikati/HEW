#pragma once
#include "MyDirect3D.h"
#include <vector>
#include "Enum.h"

class OBB
{
private:
	D3DXVECTOR3 m_pos;              // 位置
	D3DXVECTOR3 m_posMove;              // 位置
	D3DXVECTOR3 m_normaDirect[3];   // 方向ベクトル
	float m_fLength[3];      // 各軸方向の長さ
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
public:
	void Initialize();
	void Update(D3DXMATRIX &mat);
	void CreateOBB(MeshInfo* meshInfo);
	D3DXVECTOR3 GetDirect(int elem);   // 指定軸番号の方向ベクトルを取得
	float GetLen_W(int elem);          // 指定軸方向の長さを取得
	D3DXVECTOR3 GetPos_W();             // 位置を取得
};