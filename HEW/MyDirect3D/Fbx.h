#pragma once
#include <iostream>
#include <fbxsdk.h>
#include <vector>
#include "MyDirect3D.h"
#include "AABB.h"

//メッシュの情報
struct MeshInfo {
	//ポリゴンの数
	int							polygonCount;
	//頂点の数
	int							vertexCount;
	//頂点インデックスの数
	int							indexCount;
	//頂点
	VERTEX_3D*					vertex;
	//頂点インデックスの順番
	int*						indexBuffer;
	//UVSetの数
	int							uvSetCount;
	//UVSetの名前
	std::string*				uvSetName;
	//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9		pVB;
	//インデックスバッファ
	LPDIRECT3DINDEXBUFFER9		pIB;
	//テクスチャ
	LPDIRECT3DTEXTURE9*			texture;
	//テクスチャパス
	std::vector<std::string>	texturePath;
};

//FBXの情報
struct FbxInfo {
	//メッシュ
	std::vector<FbxMesh*>			 meshes;
	//メッシュの数
	int								 meshCount;
	//マテリアル
	std::vector<FbxSurfaceMaterial*> material;
	//マテリアルの数
	int								 materialCount;
	//UVSetの数
	int								 uvSetCount;
	//UVSetの名前
	std::string*					 uvSetName;
	//マテリアルの色
	D3DXCOLOR*						 color;
};

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

	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	FbxMatrix clusterDeformation[2404];//1.9053

	std::vector<std::vector<std::vector<D3DXVECTOR3>>> m_animVertex;


	bool		m_isMove;

	//OBB*		m_obb;
	bool		m_isCollison;
	bool		m_isaabb;
	int testCount;
	AABB*		m_aabb;

	int m_frame;
	int m_count;

	std::vector<FbxSkin*>	m_skinDeformer;
	std::vector<FbxNode*>	m_link;

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

	void UpdateTime();

	/*デバッグ用のファイル出力*/
	void PrintFile();

	void LoadTexture();

	void SetAnimationVertex();
	void SetSkinDeformer();
public:

	void Initialize(bool col, bool aabb);
	void Load(const char* filePath, bool animation = false);
	void Update();
	void Draw();
	void Finalize();

	/*移動 1:移動させたい行列 2:x方向の移動量 3:y方向の移動量 4:z方向の移動量*/
	void SetTranslation(float x, float y, float z);
	void SetTranslation(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotation(float x, float y, float z);
	/*拡縮 1:拡縮させたい行列 2:各縮率（1だと同じ） */
	void SetScaling(float scale);
	void SetScaling(float scaleX, float scaleY, float scaleZ);

	//OBB& GetOBB()const;
	AABB& GetAABB()const;
	void Move(bool b);
};

