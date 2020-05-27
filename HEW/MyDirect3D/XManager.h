#pragma once
#include "MyDirect3D.h"
#include "AABB.h"

class XManager {
private:
	LPDIRECT3DDEVICE9	m_d3dDevice;
	D3DMATERIAL9		*m_pMaterials;
	DWORD				m_numMaterials;
	LPD3DXMESH			m_pMesh;
	LPDIRECT3DTEXTURE9* m_pTextures;
	D3DXVECTOR3			m_position;
	D3DXVECTOR3			m_rotation;
	D3DXVECTOR3			m_scale;
	D3DXVECTOR3			m_max;
	D3DXVECTOR3			m_min;
	D3DXMATRIX			m_mat;

	AABB*				m_aabb;
	//OBB*				m_obb;

	bool				m_isCol;
	bool				m_isaabb;
public:
	/*インスタンス作ったらすぐに呼んでね*/
	void Initialize(bool col, bool isAABB);
	/*引数にしたファイルを読み込むよ isColがtrueなら当たり判定するよ falseなら当たり判定しないよ*/
	bool LoadXFile(const char* filePath);
	/*更新*/
	void Update();
	/*描画するよ*/
	void Draw();
	/*読み込んだ色々を開放するよ*/
	void Finalize();
	/*移動 1:移動させたい行列 2:x方向の移動量 3:y方向の移動量 4:z方向の移動量*/
	void SetTranslation(float x, float y, float z);
	void SetTranslation(D3DXVECTOR3 pos);
	/*回転 1:回転させたい行列 2:回転させたい角度（ラジアン角じゃなくて〇°の形で大丈夫やで）同時に複数の軸を回転できない*/
	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotation(float x, float y, float z);
	void SetRotation(D3DXVECTOR3 rot);
	/*拡縮 1:拡縮させたい行列 2:各縮率（1だと同じ） */
	void SetScaling(D3DXVECTOR3 scale);
	void SetScaling(float scale);
	void SetScaling(float scaleX, float scaleY, float scaleZ);

	/*OBB& GetOBB()const;*/
	AABB& GetAABB()const;

	void SetMinMax(D3DXVECTOR3 min, D3DXVECTOR3 max);
};
