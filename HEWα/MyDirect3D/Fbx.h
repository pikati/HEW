#pragma once
#include <iostream>
#include <fbxsdk.h>
#include <vector>
#include "MyDirect3D.h"
#include "OBB.h"
#include "Enum.h"

#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Fbx
{
private:
	//!fbxのマネージャ
	FbxManager* m_manager;
	//!fbxのシーン
	FbxScene*	m_scene;
	//!fbxの情報
	FbxInfo		m_fbxInfo;
	//!メッシュの情報
	MeshInfo*	m_meshInfo;

	//!アニメーションするか
	bool		m_isAnim;
	//!アニメーションの数
	int				m_animationStackNumber;
	//!いろいろ
	FbxTime			m_frameTime, m_timeCount, m_start, m_stop;

	/*DirectXの機能のための変数たち*/
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scale;
	OBB*		m_obb;

	void LoadFBX(const char* filePath);
	void InitializeFBX();
	void InitializeUnit();
	void InitializeAnimation(bool isAnimation);
	std::vector<FbxMesh*> GetMesh();
	void MeshTrianglate();
	void SetInfomation();
	int  GetPolygonCount(int meshIndex);
	int  GetVertexCount(int meshIndex);
	int	 GetIndexCount(int meshIndex);
	void GetVertex(int meshIndex, VERTEX_3D* vertex);
	void GetNormal(int meshIndex, VERTEX_3D* vertex);
	void GetUVSetName(int meshIndex);
	void GetUV(int meshIndex);
	void GetMaterial();
	void GetTextureInfo(int meshindex);
	bool CreateVertexBuffer(int meshIndex);
	bool CreateIndexBuffer(int meshIndex);
	void SetVertexBuffer(int meshIndex);
	void SetIndexBuffer(int meshIndex);

	void TextureMemoryAllocate(int meshIndex);
	void LoadTexture(int meshIndex);
	void SetTexture(int meshIndex);

	int GetUVSetNum();

	void DrawModel();
	void DrawAnimation();
	/*デバッグ用の描画*/
	void DrawPoint();
	void DrawWire();
	/*デバッグ用のファイル出力*/
	void PrintFile();


public:
	Fbx();
	~Fbx();

	void Initialize();
	void Load(const char* filePath, bool animation = false);
	void Update();
	void Draw();
	void Finalize();

	/*移動 1:移動させたい行列 2:x方向の移動量 3:y方向の移動量 4:z方向の移動量*/
	void SetTranslation(float x, float y, float z);
	void SetTranslation(D3DXVECTOR3 pos);
	/*回転 1:回転させたい行列 2:回転させたい角度（ラジアン角じゃなくて〇°の形で大丈夫やで）同時に複数の軸を回転できない*/
	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotation(float x, float y, float z);
	/*拡縮 1:拡縮させたい行列 2:各縮率（1だと同じ） */
	void SetScaling(float scale);
	void SetScaling(float scaleX, float scaleY, float scaleZ);

	OBB& GetOBB()const;
};

